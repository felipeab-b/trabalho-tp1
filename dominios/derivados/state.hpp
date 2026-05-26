#ifndef STATE_HPP
#define STATE_HPP

#include "dominios.hpp"
#include <stdexcept>

using namespace std;

/// @brief Domínio que representa o estado de uma história de usuário.
///
/// Os valores válidos são: "A FAZER", "FAZENDO" e "FEITO",
/// representando as etapas do fluxo de trabalho no sistema Scrum.
class State : public Dominio {
private:
    /// @brief Valida o estado fornecido.
    /// @param valor String a ser validada.
    /// @throws invalid_argument se o valor não for "A FAZER", "FAZENDO" ou "FEITO".
    void validate(string valor) override;
};

#endif