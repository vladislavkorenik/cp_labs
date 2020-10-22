#include <regex>
#include <array>
#include <ctime>
#include <vector>
#include <math.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <time.h>

using namespace std;

int MAX_CPU_COUNT = 4;

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

    array<string, 4> tags = {"-prior-", "%data%", "%%time%%", "--message--"};
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
int calculatePercentage(int &currentIteration, int &allIterations, int &prevInPercents)
{
    int percentage = 100 * currentIteration / allIterations;
    int inPercents = ((100 * currentIteration / allIterations) / 5) * 5;

    if (inPercents > prevInPercents)
    {
        cout << inPercents << "% ";
    }

    return inPercents;
}

double calculateFunc(int &x, int &i, int j)
{
    return (j + pow(x + j, 1 / 7)) / (2 * i * j - 1);
}

void calculateConsistently(int &x, int &n, Logger &logger)
{
    double result;
    int prevInPercents = -1;

    for (int i = 1; i <= n; i++)
    {
        double intermediateResult;

        for (int j = i; j <= n; j++)
        {
            double resPart = calculateFunc(x, i, j);

            intermediateResult += resPart;
        }

        result += double(1 / intermediateResult);

        prevInPercents = calculatePercentage(i, n, prevInPercents);
    }

    cout << endl;
    string message = "Result: " + to_string(result);

    logger.printTrace(message);
}

void calculateParallel(int &x, int &n, Logger &logger)
{
    double result;
    int loopCount, prevInPercents = -1;
    ;

    for (int i = 1; i <= n; i++)
    {
        double intermediateResult;
        int j = i;

        while (j <= n)
        {
            if (n - j >= MAX_CPU_COUNT)
            {
                loopCount = MAX_CPU_COUNT;
            }
            else
            {
                loopCount = n - j;
            }

            vector<thread> ths;

            for (int k = 0; k <= loopCount; k++)
            {
                ths.push_back(thread([&intermediateResult, j, &x, &i]() {
                    double resPart = calculateFunc(x, i, j);

                    intermediateResult += resPart;
                }));

                j++;
            }

            for (auto &th : ths)
                th.join();
        }

        result += double(1 / intermediateResult);

        prevInPercents = calculatePercentage(i, n, prevInPercents);
    }

    cout << endl;
    string message = "Result: " + to_string(result);

    logger.printTrace(message);
}

double timingFunc(void(func)(int &x, int &n, Logger &logger), int &x, int &n, Logger &logger)
{
    time_t start, end;

    start = clock();

    func(x, n, logger);

    end = clock();

    double milliseconds = difftime(end, start);

    return milliseconds;
}
int main()
{
    int x, n;
    time_t start, end;
    double parallelTime, consistentlyTime;

    Logger logger("Log.txt");

    cout << "Input n: ";
    cin >> n;

    cout << "Input x: ";
    cin >> x;

    consistentlyTime = timingFunc(calculateConsistently, x, n, logger);
    cout << "Consistently milliseconds: " << consistentlyTime << "ms" << endl;

    parallelTime = timingFunc(calculateParallel, x, n, logger);
    cout << "Four parallel threads milliseconds: " << parallelTime << "ms" << endl;

    MAX_CPU_COUNT = 3;
    parallelTime = timingFunc(calculateParallel, x, n, logger);
    cout << "Three parallel threads milliseconds: " << parallelTime << "ms" << endl;

    MAX_CPU_COUNT = 2;
    parallelTime = timingFunc(calculateParallel, x, n, logger);
    cout << "Two parallel threads milliseconds: " << parallelTime << "ms" << endl;

    return 0;
}