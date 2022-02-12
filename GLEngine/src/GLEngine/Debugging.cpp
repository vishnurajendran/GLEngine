#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1

#include <Windows.h>
#include <iostream>
#include "GLEngine/Debugging.h"
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
#include <experimental/filesystem>
namespace GLengine {
#define CONSOLE_BLACK			0
#define CONSOLE_BLUE			1
#define CONSOLE_GREEN			2
#define CONSOLE_CYAN			3
#define CONSOLE_RED				4
#define CONSOLE_MAGENTA			5
#define CONSOLE_BROWN			6
#define CONSOLE_LIGHTGRAY		7
#define CONSOLE_DARKGRAY		8
#define CONSOLE_LIGHTBLUE		9
#define CONSOLE_LIGHTGREEN		10
#define CONSOLE_LIGHTCYAN		11
#define CONSOLE_LIGHTRED		12
#define CONSOLE_LIGHTMAGENTA	13
#define CONSOLE_YELLOW			14
#define CONSOLE_WHITE			15

	namespace fs = std::experimental::filesystem;

	bool Debug::loggerInitialised = false;
	std::string Debug::fileName = "";
	HANDLE hConsole;

	std::string activeSectionName;


	bool Debug::AppendToTextFile(const char* fileName, const char* textToWrite) {
		std::ofstream fileWriter = std::ofstream(fileName, std::ios_base::out | std::ios_base::app);
		if (!fileWriter) {
			LogMessage("\t[Internal Error Writing to file]\n", LogType::INTERNAL_LOG, "", false, false);
			return false;
		}
		fileWriter << textToWrite;
		fileWriter.close();
		return true;
	}

	bool Debug::DirExists(const char* path) {
		return fs::exists(path);
	}

	void Debug::MakeDirectory(const char* path) {
		fs::create_directory(path);
	}

	std::string GetTimeNow(std::string dateSeperator = "-", std::string timeSeperator = "-") {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		std::stringstream transTime;
		std::string format = "%d" + dateSeperator + "%m" + dateSeperator + "%Y %H" + timeSeperator + "%M" + timeSeperator + "%S";
		transTime << std::put_time(&tm, format.c_str());
		return transTime.str();
	}


	void Debug::StartLogger() {
		loggerInitialised = true;

		if (!DirExists("Logs"))
			MakeDirectory("Logs");

		fileName = "Logs/" + GetTimeNow() + ".log";
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		activeSectionName.clear();
	}

	void Debug::StartSection(const char* name) {
		activeSectionName = std::string(name);
		std::string text = "\n<SECTION " + std::string(name) + ">\n";
		LogMessage(text, LogType::SECTION_LOG, "\n", false, true);
	}

	void Debug::StopSection() {
		//no open sections
		if (activeSectionName.empty())
			return;

		std::string text = "\n</SECTION " + std::string(activeSectionName) + ">\n";
		LogMessage(text, LogType::SECTION_LOG, "\n", false, true);
		activeSectionName.clear();
	}

	void Debug::LogInfoData(const char* message, const char* file = "", int line = 0) {
		std::string text = GetFormatedLogMessage(message, file, line);
		LogMessage(text, LogType::INFO_LOG, "", true, true);
	}

	void Debug::LogData(const char* message, const char* file = "", int line = 0) {
		std::string text = GetFormatedLogMessage(message, file, line);
		LogMessage(text, LogType::NORMAL_LOG, "", true, true);
	}

	void Debug::LogWarningData(const char* message, const char* file = "", int line = 0) {
		std::string text = GetFormatedLogMessage(message, file, line);
		LogMessage(text, LogType::WARNING_LOG, "", true, true);
	}

	void Debug::LogErrorData(const char* message, const char* file = "", int line = 0) {
		std::string text = GetFormatedLogMessage(message, file, line);;
		LogMessage(text, LogType::ERROR_LOG, "", true, true);

	}

	void Debug::LogMessage(std::string msg, LogType type, std::string postMessage, bool prefixTime, bool writeToFile) {

		std::string timeString = "|" + GetTimeNow("-", ":") + "| ";
		if (prefixTime)
		{
			SetConsoleTextAttribute(hConsole, CONSOLE_LIGHTMAGENTA);
			std::cout << timeString;
			SetConsoleTextAttribute(hConsole, CONSOLE_WHITE);
		}

		switch (type) {

		case LogType::INFO_LOG:
			msg = "INFO:::" + msg;
			SetConsoleTextAttribute(hConsole, CONSOLE_CYAN);
			break;

		case LogType::NORMAL_LOG:
			SetConsoleTextAttribute(hConsole, CONSOLE_WHITE);
			msg = "LOG:::" + msg;
			break;

		case LogType::WARNING_LOG:
			SetConsoleTextAttribute(hConsole, CONSOLE_YELLOW);
			msg = "WARNING::" + msg;
			break;

		case LogType::ERROR_LOG:
			SetConsoleTextAttribute(hConsole, CONSOLE_RED);
			msg = "ERROR:::" + msg;
			break;

		case LogType::SECTION_LOG:
			SetConsoleTextAttribute(hConsole, CONSOLE_GREEN);
			break;

		case LogType::INTERNAL_LOG:
			SetConsoleTextAttribute(hConsole, CONSOLE_DARKGRAY);
			break;
		}

		std::cout << msg;

		if (!loggerInitialised)
		{
			std::cout << "Logger Not initialised" << std::endl;
			std::cout << postMessage;
			return;
		}

		if (prefixTime)
			msg = timeString + msg;

		msg += postMessage;
		if (writeToFile)
			WriteToFile(msg.c_str());

		std::cout << postMessage;

		SetConsoleTextAttribute(hConsole, CONSOLE_WHITE);
	}

	void Debug::WriteToFile(const char* text) {
		if (AppendToTextFile(fileName.c_str(), text)) {
			SetConsoleTextAttribute(hConsole, CONSOLE_DARKGRAY);
			std::cout << "\t(Written to file " << fileName << ")" << std::endl;
			SetConsoleTextAttribute(hConsole, CONSOLE_WHITE);
		}
	}

	std::string Debug::GetFormatedLogMessage(const char* message, const char* file, int line) {

		std::string msg = std::string(message);
		std::string fl = std::string(file);
		std::string ln = std::to_string(line);

		std::string formattedString = msg + "\n[" + fl + " ( Line " + ln + " ) " + "]\n";

		return std::string(formattedString);
	}
}

