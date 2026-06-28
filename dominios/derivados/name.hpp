#ifndef NAME_HPP
#define NAME_HPP

#include "../dominios.hpp"
#include <stdexcept>
#include <cctype>

/// @brief Domínio que representa o nome de uma pessoa.
///
/// O nome deve conter entre 1 e 10 caracteres, compostos apenas por
/// letras (a-zA-Z) e espaços. Não pode começar ou terminar com espaço,
/// e após um espaço deve haver obrigatoriamente uma letra.
class Name: public Dominio {
    private:
        /// @brief Valida o formato do nome.
        /// @param name String a ser validada.
        /// @throws invalid_argument se o tamanho estiver fora do intervalo [1, 10],
        /// se contiver caracteres não alfabéticos (exceto espaços),
        /// ou se começar/terminar com espaço ou tiver espaço seguido de não-letra.
        void validate(std::string) override;
};

#endif