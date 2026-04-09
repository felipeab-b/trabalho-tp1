#ifndef CODE_HPP
#define CODE_HPP

#include "dominios.hpp"
#include <stdexcept>

using namespace std;

class Code:public Dominio {
    private:
        void validate(string) override;
};

#endif