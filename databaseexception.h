#include "mainexception.h"
#include <string>
#include <iostream>

using namespace std;

class DatabaseException : public MainException
{
public:
    DatabaseException(const string& message) : message_(message) {};
    void log() {
        cout << this->message_;
    }
private:
    string message_;
};
