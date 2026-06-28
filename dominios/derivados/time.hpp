#ifndef TIME_HPP
#define TIME_HPP

#include "../dominios.hpp"
#include <stdexcept>

/// @brief Domínio que representa um tempo válido.
///
/// O tempo deve ser uma string de um valor inteiro entre 1 e 365.

class Time: public Dominio {
    private:
        /// @brief Valida o formato do tempo.
        /// @param time String a ser validada.
        /// @throws invalid_argument se não for um inteiro entre 1 e 365.
        void validate(std::string) override;
};

#endif