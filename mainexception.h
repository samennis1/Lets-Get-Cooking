
#ifndef MAINEXCEPTION_H
#define MAINEXCEPTION_H
#include <exception>
#include <string>


class MainException : public std::exception
{
public:
    virtual void log() = 0;

    ~MainException() {};
};

#endif // MAINEXCEPTION_H
