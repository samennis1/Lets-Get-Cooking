#include <exception>
#include <string>
using namespace std;

class DatabaseException : public std::exception
{
public:
    DatabaseException(const string& message) : message_(message) {}

private:
    std::string message_;
};
