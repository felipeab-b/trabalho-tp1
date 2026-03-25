#ifndef EMAIL_HPP
#define EMAIL_HPP

#include <string>
#include <stdexcept>

using namespace std;

class Email {
    private:
        string email;
        void validate(string);
    public:
        void set(string);
        string get() const;

};

#endif