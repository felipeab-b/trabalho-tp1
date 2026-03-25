#ifndef DATE_HPP
#define DATE_HPP

#include <string>
#include <stdexcept>

using namespace std;

class Date {
    private:
        int day, month, year;
        void validate(int, int, int);
    public:
        void set(int, int, int);
        string get() const;
};

#endif