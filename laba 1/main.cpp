#include <regex>
#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

class Logger
{
public:
    void setFormat();
    void printError(const string &text);
    void printDebug(const string &text);
    void printTrace(const string &text);

    Logger(const string &file)
    {
        fileName = file;
    }

private:
    string format = "-prior- | %data% %%time%% --message--";
    string fileName;
    string generateMessage(const string &message, const string &prior) const;
};

void Logger::printError(const string &text)
{
    string result = this->generateMessage(text, "Error");

    cout << result << endl;
}

void Logger::printDebug(const string &text)
{
    string result = this->generateMessage(text, "Debug");

    cout << result << endl;
}

void Logger::printTrace(const string &text)
{
    string result = this->generateMessage(text, "Trace");

    cout << result << endl;
}

void Logger::setFormat()
{
    cout << "Input format:";
    getline(cin, this->format);

    cout << "Your current format is: " << this->format << endl;
}

string Logger::generateMessage(const string &message, const string &prior) const
{
    ofstream f(this->fileName, ios::app);

    time_t now = time(0);
    tm *ltm = localtime(&now);

    string str = this->format;

    array<string, 4> tags = {"-prior-","%data%", "%%time%%", "--message--"};
    string data = to_string(ltm->tm_mday) + "." + to_string(1 + ltm->tm_mon) + "." + to_string(1900 + ltm->tm_year);
    string time = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
    array<string, 4> replacements = {prior, data, time, message};

    for (int i = 0; i < tags.size(); i++)
    {
        regex rx(tags[i]);

        str = regex_replace(str, rx, replacements[i]);
    }

    f << str << endl;
    f.close();

    return str;
}

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