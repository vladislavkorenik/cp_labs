#include <regex>
#include <iostream>
#include <ctime>

using namespace std;

string generateMessage(const string& format,const string& message, const string& prior){
    string str = format;
    string tags[] = {"*prior*", "%data%", "%%time%%", "**message**"};

    for (int i = 0; i < tags->length(); ++i) {
        regex rx(tags[i]);
        string replacement;

        time_t now = time(0);
        tm *ltm = localtime(&now);

        switch (i) {
            case 0: replacement = prior; break;
            case 1: replacement = to_string(ltm->tm_mday) + "." +  to_string(1 + ltm->tm_mon) + "." + to_string(1900 + ltm->tm_year); break;
            case 2: replacement = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec); break;
            case 3: replacement = message;
        }

        str = regex_replace(str, rx, replacement);
    }

    return str;
}

class Logger {
public:
    string format = "*prior* | %data% %%time%% **message**";
    void setFormat();
    void printError(const string& text);
    void printDebug(const string& text);
    void printTrace(const string& text);
};

void Logger::printError(const string& text) {

    regex rx("lol");
    string replacement = "whoa";
    cout << regex_replace(text, rx, replacement) << endl;
}

void Logger::printDebug(const string& text){
    cout << text;
}

void Logger::printTrace(const string& text){
    cout << text;
}

void Logger::setFormat() {
    cout << "Input format:";
    cin >> this->format;

    cout << "Your current format is: " << this->format << endl;
}

int main() {
    Logger logger;
    logger.printError("lol it,s Error");
    logger.setFormat();

    system("pause");
    return 0;
}