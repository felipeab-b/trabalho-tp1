#ifndef EMAIL_HPP
#define EMAIL_HPP

#include "dominios.hpp"
#include <stdexcept>
#include <cctype>

using namespace std;

class Email:public Dominio {
    private:
        void validate(std::string) override;
};

#endif