#pragma once
#include <string>
#include "GLEngine/Core/Core.h"

namespace GLengine {

#define Log(data) Debug::LogData(data, __FILE__, __LINE__);
#define LogInfo(data) Debug::LogInfoData(data, __FILE__, __LINE__);
#define LogWarning(data) Debug::LogWarningData(data, __FILE__, __LINE__);
#define LogError(data) Debug::LogErrorData(data, __FILE__, __LINE__);
#define AddSection(data) Debug::StartSection(data);
#define CloseSection() Debug::StopSection();

class GLENGINE_API Debug 
{
	private:
		enum LogType {
			INFO_LOG,
			NORMAL_LOG,
			WARNING_LOG,
			ERROR_LOG,
			SECTION_LOG,
			INTERNAL_LOG
		};

		static std::string applicationName;
		static std::string fileName;
		static std::string htmlFileName;
		static bool loggerInitialised;
		static void WriteToFile(const char* log);
		static std::string GetFormatedLogMessage(const char* message, const char* file, int line);
		static void LogMessage(std::string msg, LogType type, std::string postMessage, bool prefixTime, bool writeToFile);
		static bool DirExists(const char* path);
		static void MakeDirectory(const char* path);
		static bool AppendToTextFile(const char* fileName, const char* textToWrite);
		static void HTMLLogInit();
		static void AddToHTMLLog(LogType logType, std::string msg, std::string file, std::string line);
		static void EndHTMLLog();
	public:
		~Debug();
		static void StartSection(const char* name);
		static void StopSection();
		static void StartLogger(std::string appname);
		static void LogInfoData(const char* message, const char* file, int line);
		static void LogData(const char* message, const char* file, int line);
		static void LogWarningData(const char* message, const char* file, int line);
		static void LogErrorData(const char* message, const char* file, int line);
	};
}