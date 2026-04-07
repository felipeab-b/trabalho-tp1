#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <stdexcept>
#include <string>

using namespace std;

class Password {
    private:
        std::string password; 
        void validate(std::string);
    public:
        void set(std::string);
        string get() const;
};

#endif