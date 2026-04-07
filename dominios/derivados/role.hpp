#ifndef ROLE_HPP
#define ROLE_HPP

#include "dominios.hpp"
#include <stdexcept>

class Role: public Dominio {
    protected:
        void validate(std::string) override;
};

#endif