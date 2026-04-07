#ifndef CODE_HPP
#define CODE_HPP

#include <string>
#include <stdexcept>

using namespace std;

class Code {
    private:
        string code;
        void validate(string);
    public:
        void set(string);
        string get() const;
};

#endif