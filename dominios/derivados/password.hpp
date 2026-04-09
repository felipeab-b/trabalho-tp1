#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include "dominios.hpp"
#include <stdexcept>

class Password: public Dominio {
    private: 
        void validate(std::string) override;
};

#endif