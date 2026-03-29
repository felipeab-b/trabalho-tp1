#ifndef NAME_HPP
#define NAME_HPP

#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;

class Name {
    private:
        string name;
        void validate(string);
    public:
        void set(string);
        string get() const;
};

#endif