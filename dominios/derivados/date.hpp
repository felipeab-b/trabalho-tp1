#ifndef DATE_HPP
#define DATE_HPP

#include "dominios.hpp"
#include <stdexcept>

using namespace std;

class Date:public Dominio {
    private:
        void validate(string) override;
};

#endif