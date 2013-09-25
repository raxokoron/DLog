#include "../DLog.h"
#include "DLogInitializer.h"

// Not tested!
#ifdef ANDROID

static std::string GeneratePrefix(const char* functionName, unsigned int line)
{
	std::string prefix = functionName;
	size_t left_pos = prefix.find('(');
	size_t right_pos = prefix.rfind(')');
	prefix = prefix.substr(0, left_pos) + "(...)" + prefix.substr(right_pos+1);

	left_pos = prefix.find('[');
	right_pos = prefix.find(']');
	if( (left_pos != std::string::npos) && (right_pos != std::string::npos) )
		prefix = prefix.substr(0, left_pos) + "[tmpl]" + prefix.substr(right_pos + 1);

	if(line > 0)
	{
		prefix +=" (";
		char linebuff[32];
		snprintf(linebuff, 32, "%d", line);
		prefix += linebuff;
		prefix += "): ";
	}
	return prefix;
}

static void AndroidOutputFunction(Severity severity, const char* functionName, unsigned int line, const char* msg)
{
	std::string prefix = GeneratePrefix(message.prettyFunctionName, message.line);
	int sev = static_cast<int>(severity) + ANDROID_LOG_INFO;
	__android_log_write(sev, prefix.c_str(), msg);
}

static DLogInitializer init(AndroidOutputFunction);


#endif
