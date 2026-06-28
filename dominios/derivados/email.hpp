#ifndef EMAIL_HPP
#define EMAIL_HPP

#include "../dominios.hpp"
#include <stdexcept>
#include <cctype>

using namespace std;

/// @brief Domínio que representa um endereço de email válido.
///
/// O email deve conter exatamente um '@' separando a parte local (até 64 caracteres)
/// e o domínio (até 255 caracteres). A parte local deve conter apenas
/// caracteres alfanuméricos, pontos e hífens (não pode começar ou terminar com
/// ponto ou hífen). O domínio deve conter pelo menos um ponto.
class Email:public Dominio {
    private:
        /// @brief Valida o formato do email.
        /// @param email String a ser validada.
        /// @throws invalid_argument se não contiver '@', contiver múltiplos '@',
        /// tiver parte local vazia ou inválida, ou tiver domínio inválido.
        void validate(std::string) override;
};

#endif