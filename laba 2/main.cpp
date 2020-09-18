#include <iostream>
#include <string>
#include "logger.h"

using namespace std;

//запуск через main.exe, если что то меняешь в либе или в коде нужно запускать сначала build.bat a потом build_exe.bat соответсвенно
int main()
{
    string text = "some message";

    Logger logger("Log.txt");

    logger.printError(text);
    logger.printDebug(text);
    logger.printTrace(text);

    logger.setFormat();

    logger.printError(text);
    logger.printDebug(text);
    logger.printTrace(text);

    return 0;
}