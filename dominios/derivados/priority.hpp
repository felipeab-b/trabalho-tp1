#ifndef PRIORITY_HPP
#define PRIORITY_HPP

#include "dominios.hpp"
#include <stdexcept>

class Priority: public Dominio {
        private:
                void validade(std::string);
};

#endif
