#ifndef NAME_HPP
#define NAME_HPP

#include "dominios.hpp"
#include <stdexcept>
#include <cctype>

class Name: public Dominio {
    private:
        void validate(std::string) override;
};

#endif