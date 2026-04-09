#ifndef STATE_HPP
#define STATE_HPP

#include "dominios.hpp"
#include <stdexcept>

class State: public Dominio {
    private:
        void validate(std::string) override;
};

#endif