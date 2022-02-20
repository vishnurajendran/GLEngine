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
#include <regex>
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
	std::string Debug::applicationName = "GLEngine";
	std::string Debug::fileName = "";
	std::string Debug::htmlFileName = "";
	HANDLE hConsole;

	std::string activeSectionName;

	const std::string HTML_LOG_INIT = "<!DOCTYPE html>\n<html><head><title>{log-title}</title><h1 style=\" font-family:consolas\">{log-name}</h1></head><body style=\"font-family:consolas\">";
	const std::string HTML_LOG_STRING = "<details style=\"font-family:consolas;font-size:16px\"><summary style=\"cursor:pointer; outline: none;font-family:consolas;font-size:16px\"><code style=\"color:{hex-col};font-family:consolas;font-size:16px\">{log-type}</code>|<code style=\"color:green;font-family:consolas;font-size:16px\"> {log-time} </code> | <code style=\"font-family:consolas;font-size:16px\"> {log-msg} </code> </summary> <a href={script-path} style = \"color : font-family:consolas;font-size:16px\"><code style=\"color:#9900FF;font-family:consolas;font-size:16px\">{script-path} [Line {line-no}]</code></a> </details>";
	const std::string HTML_LOG_CLOSE = "</body> </html>";
	const std::string INFO_HEX_COL = "#0091FF";
	const std::string LOG_HEX_COL = "black";
	const std::string WARN_HEX_COL = "#FFA500";
	const std::string ERROR_HEX_COL = "#a6002c";


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


	void Debug::StartLogger(std::string appname) {
		loggerInitialised = true;
		applicationName = appname;
		if (!DirExists("Logs"))
			MakeDirectory("Logs");

		if (!DirExists("Logs/Raw"))
			MakeDirectory("Logs/Raw");

		if (!DirExists("Logs/Web"))
			MakeDirectory("Logs/Web");

		fileName = "Logs/Raw/" + GetTimeNow() + ".log";
		htmlFileName =  "Logs/Web/" + GetTimeNow() + ".html";
		HTMLLogInit();

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		activeSectionName.clear();
	}

	void Debug::StartSection(const char* name) {
		activeSectionName = std::string(name);
		std::string text = "\n<SECTION " + std::string(name) + ">\n";
		LogMessage(text, LogType::SECTION_LOG, "\n", false, true);
		AddToHTMLLog(LogType::SECTION_LOG, name, "na", "na");
	}

	void Debug::StopSection() {
		//no open sections
		if (activeSectionName.empty())
			return;

		std::string text = "\n</SECTION " + std::string(activeSectionName) + ">\n";
		LogMessage(text, LogType::SECTION_LOG, "\n", false, true);
		activeSectionName.clear();
		AddToHTMLLog(LogType::SECTION_LOG, " End " + activeSectionName, "na", "na");
	}

	void Debug::LogInfoData(const char* message, const char* file = "", int line = 0) {
		std::string text = GetFormatedLogMessage(message, file, line);
		LogMessage(text, LogType::INFO_LOG, "", true, true);
		AddToHTMLLog(LogType::INFO_LOG, message, file, std::to_string(line));
	}

	void Debug::LogData(const char* message, const char* file = "", int line = 0) {
		std::string text = GetFormatedLogMessage(message, file, line);
		LogMessage(text, LogType::NORMAL_LOG, "", true, true);
		AddToHTMLLog(LogType::NORMAL_LOG, message, file, std::to_string(line));
	}

	void Debug::LogWarningData(const char* message, const char* file = "", int line = 0) {
		std::string text = GetFormatedLogMessage(message, file, line);
		LogMessage(text, LogType::WARNING_LOG, "", true, true);
		AddToHTMLLog(LogType::WARNING_LOG, message, file, std::to_string(line));
	}

	void Debug::LogErrorData(const char* message, const char* file = "", int line = 0) {
		std::string text = GetFormatedLogMessage(message, file, line);;
		LogMessage(text, LogType::ERROR_LOG, "", true, true);
		AddToHTMLLog(LogType::ERROR_LOG, message, file, std::to_string(line));
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

	void Debug::HTMLLogInit() {
		std::string data = HTML_LOG_INIT;
		std::string titleTag = "{log-title}";
		std::string headingTag = "{log-name}";
		std::string title = applicationName + " Log " + GetTimeNow("/",":");
		data.replace(data.find(titleTag), titleTag.length(), title);
		data.replace(data.find(headingTag), headingTag.length(), title);
		AppendToTextFile(htmlFileName.c_str(), data.c_str());
	}

	void Debug::AddToHTMLLog(LogType logType, std::string msg, std::string file, std::string line) {
		std::string data = HTML_LOG_STRING;
		std::string typeTag = "{log-type}";
		std::string colorTag = "{hex-col}";
		std::string logTimeTag = "{log-time}";
		std::string pathTag = "{script-path}";
		std::string lineTag = "{line-no}";
		std::string msgTag = "{log-msg}";

		std::string header = "";
		data.replace(data.find(logTimeTag), logTimeTag.length(), GetTimeNow("/", ":"));
		
		data.replace(data.find(pathTag), pathTag.length(), file);
		data.replace(data.find(pathTag), pathTag.length(), file);

		data.replace(data.find(lineTag), lineTag.length(), line);
		data.replace(data.find(msgTag), msgTag.length(), msg);

		switch (logType)
		{
		case GLengine::Debug::INFO_LOG:
			data.replace(data.find(typeTag), typeTag.length(), "INFO ");
			data.replace(data.find(colorTag), colorTag.length(), INFO_HEX_COL);
			break;
		case GLengine::Debug::NORMAL_LOG:
			data.replace(data.find(typeTag), typeTag.length(), "LOG &nbsp");
			data.replace(data.find(colorTag), colorTag.length(), LOG_HEX_COL);
			break;
		case GLengine::Debug::WARNING_LOG:
			data.replace(data.find(typeTag), typeTag.length(), "WARN ");
			data.replace(data.find(colorTag), colorTag.length(), WARN_HEX_COL);
			break;
		case GLengine::Debug::ERROR_LOG:
			data.replace(data.find(typeTag), typeTag.length(), "ERROR");
			data.replace(data.find(colorTag), colorTag.length(), ERROR_HEX_COL);
			break;
		case GLengine::Debug::SECTION_LOG:
			header = "<h3 style=\"color:#FB8FFF\"> SECTION " + msg + "<\h3>";
			AppendToTextFile(htmlFileName.c_str(), header.c_str());
			break;
		case GLengine::Debug::INTERNAL_LOG:
			AppendToTextFile(htmlFileName.c_str(), "\n");
			break;
		default:
			break;
		}

		if (logType != INTERNAL_LOG && logType != SECTION_LOG) {
			AppendToTextFile(htmlFileName.c_str(), data.c_str());
			AppendToTextFile(htmlFileName.c_str(), "\n");
		}
	}

	void Debug::EndHTMLLog() {
		AppendToTextFile(htmlFileName.c_str(), HTML_LOG_CLOSE.c_str());
	}

	void Debug::WriteToFile(const char* text) {
		if (AppendToTextFile(fileName.c_str(), text)) {
			SetConsoleTextAttribute(hConsole, CONSOLE_DARKGRAY);
			std::cout << "\t(Written to file " << fileName << ")" << std::endl;
			SetConsoleTextAttribute(hConsole, CONSOLE_WHITE);
		}
	}

	Debug::~Debug() {
		EndHTMLLog();
	}

	std::string Debug::GetFormatedLogMessage(const char* message, const char* file, int line) {

		std::string msg = std::string(message);
		std::string fl = std::string(file);
		std::string ln = std::to_string(line);

		std::string formattedString = msg + "\n[" + fl + " ( Line " + ln + " ) " + "]\n";

		return std::string(formattedString);
	}
}

