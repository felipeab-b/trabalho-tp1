#ifndef DATE_HPP
#define DATE_HPP

#include <string>
#include <stdexcept>

using namespace std;

class Date {
    private:
        string date;
        void validate(string);
    public:
        void set(string);
        string get() const;
};

#endif