#ifndef ROLE_HPP
#define ROLE_HPP

#include "dominios.hpp"
#include <stdexcept>

using namespace std;

/// @brief Domínio que representa o papel de um usuário no projeto.
///
/// Os valores válidos são: "DESENVOLVEDOR", "MESTRE SCRUM" e
/// "PROPRIETARIO DE PRODUTO", definindo as permissões de cada usuário
/// sobre os serviços disponíveis no sistema.
class Role : public Dominio {
private:
    /// @brief Valida o papel fornecido.
    /// @param valor String a ser validada.
    /// @throws invalid_argument se o valor não for um dos papéis válidos.
    void validate(string valor) override;
};

#endif