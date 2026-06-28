#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include "../dominios.hpp"
#include <stdexcept>

using namespace std;

/// @brief Domínio que representa a senha de acesso de um usuário.
///
/// A senha deve ter exatamente 6 caracteres alfanuméricos,
/// alternando obrigatoriamente entre letras e dígitos.
/// Deve conter ao menos uma letra minúscula (a-z),
/// uma letra maiúscula (A-Z) e um dígito (0-9).
/// Exemplo válido: "a1B2c3".
class Password : public Dominio {
private:
    /// @brief Valida o formato da senha.
    /// @param valor String a ser validada.
    /// @throws invalid_argument se o tamanho não for 6, se contiver caracteres
    /// não alfanuméricos, se houver dois caracteres do mesmo tipo consecutivos,
    /// ou se faltar letra minúscula, maiúscula ou dígito.
    void validate(string valor) override;
};

#endif