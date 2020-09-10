#include <regex>
#include <iostream>
#include <ctime>

using namespace std;

class Logger
{
public:
    string format = "-prior- | %data% %%time%% --message--";
    void setFormat();
    void printError(const string &text);
    void printDebug(const string &text);
    void printTrace(const string &text);
    string generateMessage(const string &message, const string &prior);
};

void Logger::printError(const string &text)
{
    string result = this->generateMessage(text, "Error");

    cout << "Formated: " << result << endl;
}

void Logger::printDebug(const string &text)
{
    cout << text;
}

void Logger::printTrace(const string &text)
{
    cout << text;
}

void Logger::setFormat()
{
    cout << "Input format:";
    getline(cin, this->format);

    cout << "Your current format is: " << this->format << endl;
}

string Logger::generateMessage(const string &message, const string &prior)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string str = this->format;

    string tags[] = {"-prior-", "%data%", "%%time%%", "--message--"};
    string data = to_string(ltm->tm_mday) + "." + to_string(1 + ltm->tm_mon) + "." + to_string(1900 + ltm->tm_year);
    string time = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
    string replacements[] = {prior, data, time, message};

    for (int i = 0; i < sizeof(tags) / sizeof(*tags); i++)
    {
        regex rx(tags[i]);

        str = regex_replace(str, rx, replacements[i]);
    }

    return str;
}

int main()
{
    Logger logger;
    logger.printError("lol it,s Error");
    logger.setFormat();
    logger.printError("lol it,s Error");

    return 0;
}