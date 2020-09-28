#include <iostream>
#include <string>
#include <Windows.h>
#include "logger.h"

using namespace std;

//запуск через main.exe, если что то меняешь в либе или в коде нужно запускать сначала build.bat a потом build_exe.bat соответсвенно
int main()
{
    HMODULE hm = LoadLibrary("logger.dll");
    if (hm == NULL)
    {
        cout << "DLLvscode.dll not found!" << endl;
    }

    else
    {
        string text = "some message";

        CREATE_LOGGER loggerCreator = (CREATE_LOGGER)GetProcAddress(hm, "createLoggerObject");
        Logger *logger = loggerCreator("d:/cp_labs/laba 2/Test1", "d:/cp_labs/laba 2/Test2");
        
        if (logger)
        {
            logger->printError(text);
            logger->printDebug(text);
            logger->printTrace(text);

            logger->setFormat();

            logger->printError(text);
            logger->printDebug(text);
            logger->printTrace(text);
        }

        FreeLibrary(hm);
    }

    system("pause");
    return 0;
}