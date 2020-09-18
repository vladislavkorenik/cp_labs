#include <string>
#include <regex>
#include <iostream>
#include <ctime>
#include <fstream>
#include <array>

using namespace std;

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

    Logger(const std::string &file);

private:
    std::string format = "-prior- | %data% %%time%% --message--";
    std::string fileName;
    std::string generateMessage(const std::string &message, const std::string &prior);
};

#endif