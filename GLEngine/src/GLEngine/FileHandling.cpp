// CPP_ConsoleTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1

#include <iostream>
#include <fstream>
#include <string>
#include <experimental/filesystem>
#include "GLEngine/FileHandling.h"
#include "GLEngine/Debugging.h"
namespace GLengine {
    namespace fs = std::experimental::filesystem;

    char* ReadTextFile(const char* fileName)
    {
        std::ifstream fileReader = std::ifstream(fileName, std::ios_base::in);
        if (!fileReader) {
            LogError((std::string("FileLoader (Text):: Unable to open ") + std::string(fileName)).c_str());
            return NULL;
        }
        else
        {
            std::string file;
            while (!fileReader.eof()) {
                std::string line;
                std::getline(fileReader, line);
                file += (line + "\n");
            }
            fileReader.close();
            char* outputString = new char[file.length()];
            strcpy(outputString, file.c_str());
            return outputString;
        }
        return NULL;
    }

    bool WriteTextFile(const char* fileName, const char* textToWrite) {
        std::ofstream fileWriter = std::ofstream(fileName, std::ios_base::out);
        if (!fileWriter) {
            LogError("Error Writing to file");
            return false;
        }
        fileWriter << textToWrite;
        fileWriter.close();
        return true;
    }

    bool AppendToTextFile(const char* fileName, const char* textToWrite) {
        std::ofstream fileWriter = std::ofstream(fileName, std::ios_base::out | std::ios_base::app);
        if (!fileWriter) {
            LogError("Error Writing to file");
            return false;
        }
        fileWriter << textToWrite;
        fileWriter.close();
        return true;
    }

    bool DirExists(const char* path) {
        return fs::exists(path);
    }

    //quick hack to check if file exists
    bool FileExists(const char* path) {
        return fs::exists(path);
    }

    void MakeDirectory(const char* path) {
        fs::create_directory(path);
    }
}

