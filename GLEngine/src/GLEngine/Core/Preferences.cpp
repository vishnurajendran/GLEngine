#include "GLEngine/Core/Preferences.h"
#include "GLEngine/FileHandling.h"
#include "GLEngine/Debugging.h"
#include <sstream>

namespace GLengine {

    const std::string DEF_PREFS = "Width = 1920,\nHeight = 1080,\nFramerate = 0,\nFullscreen = 1";

    bool Preferences::isInitialised = false;
    std::map<std::string, std::string> Preferences::prefMap;

    std::string trim(const std::string& str,
        const std::string& whitespace = " \t")
    {
        const auto strBegin = str.find_first_not_of(whitespace);
        if (strBegin == std::string::npos)
            return ""; // no content

        const auto strEnd = str.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }

    std::string reduce(const std::string& str,
        const std::string& fill = " ",
        const std::string& whitespace = " \t")
    {
        // trim first
        auto result = trim(str, whitespace);

        // replace sub ranges
        auto beginSpace = result.find_first_of(whitespace);
        while (beginSpace != std::string::npos)
        {
            const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
            const auto range = endSpace - beginSpace;

            result.replace(beginSpace, range, fill);

            const auto newStart = beginSpace + fill.length();
            beginSpace = result.find_first_of(whitespace, newStart);
        }

        return result;
    }

    void Preferences::Initialise() {
        isInitialised = true;
        std::string data = "";
        char* datChar = ReadTextFile("Prefs.prf");
        
        if (datChar == NULL) {
            WriteTextFile("Prefs.prf", DEF_PREFS.c_str());
            data = DEF_PREFS.c_str();
        }
        else
            data = datChar;

        std::string prop = "";
        for (auto x : data) {

            if (x == '\n')
                x = ' ';

            if (x == ',') {
                AddLineAsKVPair(&prefMap, prop);
                prop = "";
            }
            else {
                prop += x;
            }
        }
        AddLineAsKVPair(&prefMap, prop);
    }

    void Preferences::AddLineAsKVPair(std::map<std::string, std::string>* mp, std::string entry) {
        std::string copy = std::string(entry);
        copy = trim(copy);
        std::string kvPair[2];
        int indx = 0;
        std::string propSplit;
        for (auto c : copy) {
            if (c == '=') {
                kvPair[indx] = trim(propSplit);
                propSplit = "";
                if (indx >= 2)
                    break;
            }
            else {
                propSplit += c;
            }
        }

        kvPair[1] = trim(propSplit);
        mp->insert({ kvPair[0], kvPair[1] });
        std::string prnt = kvPair[0] + "=" + kvPair[1];
    }

    bool Preferences::HasKey(std::string key) {
        if (!isInitialised)
            Initialise();
        return prefMap.count(key);
    }

    void Preferences::Remove(std::string key) {
        if (!isInitialised)
            Initialise();

        if (HasKey(key)) {
            auto it1 = prefMap.find(key);
            prefMap.erase(it1);
        }
    }

    std::string Preferences::GetString(std::string key) {
        if (!isInitialised)
            Initialise();

        if (HasKey(key)) {
            return prefMap[key];
        }
        return "";
    }

    int Preferences::GetInt(std::string key) {
        if (!isInitialised)
            Initialise();

        if (HasKey(key)) {
            int n = 0;
            std::stringstream ss(prefMap[key]);
            ss >> n;
            return n;
        }
        return 0;
    }

    float Preferences::GetFloat(std::string key) {
        if (!isInitialised)
            Initialise();

        if (HasKey(key)) {
            float n = 0.0f;
            std::stringstream ss(prefMap[key]);
            ss >> n;
            return n;
        }
        return 0.0f;
    }

    void Preferences::SetString(std::string key, std::string value) {
        if (!isInitialised)
            Initialise();

        if (HasKey(key)) {
            prefMap[key] = value;
        }
        else {
            prefMap.insert({ key, value });
        }
    }

    void Preferences::SetInt(std::string key, int value) {
        if (!isInitialised)
            Initialise();

        if (HasKey(key)) {
            prefMap[key] = std::to_string(value);
        }
        else {
            prefMap.insert({ key, std::to_string(value) });
        }
    }

    void Preferences::SetFloat(std::string key, float value) {
        if (!isInitialised)
            Initialise();

        if (HasKey(key)) {
            prefMap[key] = std::to_string(value);
        }
        else {
            prefMap.insert({ key, std::to_string(value) });
        }
    }
}