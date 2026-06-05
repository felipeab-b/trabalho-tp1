#ifndef PRIORITY_HPP
#define PRIORITY_HPP

#include "dominios.hpp"
#include <stdexcept>

/// @brief Domínio que representa uma prioridade válida.
///
/// A prioridade deve ser uma string que pode ser "ALTA", "MEDIA" ou "BAIXA".

class Priority: public Dominio {
        private:
                /// @brief Valida o formato da prioridade.
                /// @param priority String a ser validada.
                /// @throws invalid_argument se não for "ALTA", "MEDIA" ou "BAIXA".
                void validate(std::string) override;
};

#endif
