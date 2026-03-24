#ifndef ROLE_HPP
#define ROLE_HPP

#include <string>
#include <stdexcept>

using namespace std;

class Role {
    private:
        string role;
        void validate(string);
    public:
        void set(string);
        string get() const;
};

#endif