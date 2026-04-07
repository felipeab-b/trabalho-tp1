#include "dominios.hpp"

void Dominio::set(std::string valor) {
    validate(valor);
    this->valor = valor;
}