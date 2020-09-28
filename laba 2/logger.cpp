#include "logger.h"

Logger::Logger(const string &sDir, const string &cDir)
{
    searchDir = sDir;
    copyToDir = cDir;
}

LOGGER_LIB Logger* createLoggerObject(const string &sDir, const string &cDir)
{
    return new Logger(sDir, cDir);
}

void Logger::printError(const string &text)
{
    string result = generateMessage(text, "Error");

    cout << result << endl;
}

void Logger::printDebug(const string &text)
{
    string result = generateMessage(text, "Debug");

    cout << result << endl;
}

void Logger::printTrace(const string &text)
{
    string result = generateMessage(text, "Trace");

    cout << result << endl;
}

void Logger::setFormat()
{
    cout << "Input format:";
    getline(cin, format);

    cout << "Your current format is: " << format << endl;
}

string Logger::generateMessage(const string &message, const string &prior)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string str = format;

    array<string, 4> tags = {"-prior-", "%data%", "%%time%%", "--message--"};
    string data = to_string(ltm->tm_mday) + "." + to_string(1 + ltm->tm_mon) + "." + to_string(1900 + ltm->tm_year);
    string time = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
    array<string, 4> replacements = {prior, data, time, message};

    for (int i = 0; i < tags.size(); i++)
    {
        regex rx(tags[i]);

        str = regex_replace(str, rx, replacements[i]);
    }

    !dirCreated || writingMessageToFile(str);

    return str;
}

bool Logger::existingDirectoryCheck(const string &path)
{
    if (!fs::exists(path))
    {
        string answer;
        cout << "Directory /" << fs::path(path).filename().string() << " doesn't exist, you want to create it? [y/n]";
        getline(cin, answer);

        if (answer == "y")
        {
            fs::create_directories(path);
            cout << "Directory created" << endl;
            return true;
        }
        else
        {
            cout << "Directory doesn't created" << endl;
            return false;
        }
    }
    return true;
}

bool Logger::writingMessageToFile(const std::string &message)
{
    string extension = ".txt";
    dirCreated = existingDirectoryCheck(searchDir);

    if (dirCreated)
    {
        dirCreated = existingDirectoryCheck(copyToDir);
    }

    if (dirCreated)
    {
        for (auto &p : fs::recursive_directory_iterator(searchDir))
        {
            if (!fs::is_regular_file(p.status()))
                continue;

            string currFile(p.path().filename().string());
            string copyFile = copyToDir + "/" + currFile;

            if (!currFile.ends_with(extension))
                continue;

            if (!fs::exists(copyFile))
            {
                fs::copy_file(p.path().string(), copyFile);
            }

            ofstream f(copyFile, ios::app);
            f << message << endl;
            f.close();
        }
    }

    return dirCreated;
}