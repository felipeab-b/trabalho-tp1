#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <stdexcept>

using namespace std;

class State {
    private:
        string state;
        void validate(string);
    public:
        void set(string);
        string get() const;
};

#endif