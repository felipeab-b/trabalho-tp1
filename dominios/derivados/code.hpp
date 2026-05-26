#ifndef CODE_HPP
#define CODE_HPP

#include "dominios.hpp"
#include <stdexcept>

using namespace std;

/// @brief Domínio que representa o código identificador de uma entidade.
///
/// O código é composto por exatamente 5 caracteres:
/// os dois primeiros devem ser letras maiúsculas (A-Z)
/// e os três últimos devem ser dígitos (0-9). Exemplo: "AB123".
class Code : public Dominio {
private:
    /// @brief Valida o formato do código.
    /// @param valor String a ser validada.
    /// @throws invalid_argument se o formato for inválido.
    void validate(string valor) override;
};

#endif