#include <string>
#include <regex>
#include <iostream>
#include <ctime>
#include <fstream>
#include <array>
#include <filesystem>
#include <Windows.h>

using namespace std;
namespace fs = std::filesystem;

#ifndef LOGGER_LIB_H
#define LOGGER_LIB_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef BUILD_DLL
#define LOGGER_LIB __declspec(dllexport)
#else
#define LOGGER_LIB __declspec(dllimport)
#endif

#ifdef __cplusplus
}
#endif

class LOGGER_LIB Logger
{
public:
    void setFormat();
    void printError(const std::string &text);
    void printDebug(const std::string &text);
    void printTrace(const std::string &text);

    Logger(const string &sDir, const string &cDir);

private:
    std::string format = "-prior- | %data% %%time%% --message--";
    std::string searchDir;
    std::string copyToDir;
    bool dirCreated = true;
    std::string generateMessage(const std::string &message, const std::string &prior);
    bool writingMessageToFile(const std::string &message);
    bool existingDirectoryCheck(const string &path);
};


extern "C" 
{
    LOGGER_LIB Logger* createLoggerObject(const string &sDir, const string &cDir);
};

typedef Logger* (*CREATE_LOGGER) (const string &sDir, const string &cDir);
#endif