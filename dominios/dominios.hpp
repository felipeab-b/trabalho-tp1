#ifndef DOMINIOS_HPP
#define DOMINIOS_HPP

#include <string>

class Dominio {
    protected:
        std::string valor;
        void virtual validate(std::string) = 0;
    public:
        void set(std::string valor);
        std::string get() const;

        virtual ~Dominio() {}
};

inline std::string Dominio::get() const {
    return this->valor;
}

#endif