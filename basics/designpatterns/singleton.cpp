#include <iostream>

using namespace std;

class Logger
{

    private:

    static Logger* m_pLogger;

    Logger(){}

    public:

    static Logger* getLogger();
};

Logger* Logger::m_pLogger = nullptr;

Logger* Logger::getLogger()
{

    if(nullptr == m_pLogger)
    {
        m_pLogger = new Logger();
        cout<<"Logger 1st call" << endl;
    }
    else
    {
        cout<< "Logger already initialed" << endl;
    }

    return m_pLogger;
}

int main()
{
    Logger* l1 = Logger::getLogger();
    Logger* l2 = Logger::getLogger();
    return 0;
}