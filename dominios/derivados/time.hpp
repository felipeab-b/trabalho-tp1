#ifndef TIME_HPP
#define TIME_HPP

#include "dominios.hpp"
#include <stdexcept>

class Time: public Dominio {
    private:
        void validate(std::string) override;
};

#endif