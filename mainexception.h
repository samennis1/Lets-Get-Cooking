
#ifndef MAINEXCEPTION_H
#define MAINEXCEPTION_H
#include <exception>



class MainException : public std::exception
{
public:
    MainException();

    virtual void log() = 0;
};

#endif // MAINEXCEPTION_H
