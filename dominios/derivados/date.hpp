#ifndef DATE_HPP
#define DATE_HPP

#include "dominios.hpp"
#include <stdexcept>

using namespace std;

/// @brief Domínio que representa uma data no formato brasileiro.
///
/// A data deve estar no formato DD/MM/YYYY ou D/MM/YYYY,
/// com validação completa de dias, meses e anos bissextos.
/// O dia deve estar entre 1 e 31 (dependendo do mês),
/// o mês entre 1 e 12, e o ano entre 2000 e 2999.
class Date:public Dominio {
    private:
        /// @brief Valida o formato e validade da data.
        /// @param date String a ser validada no formato DD/MM/YYYY.
        /// @throws invalid_argument se o formato for inválido, se o dia/mês/ano
        /// forem inválidos, ou se a data for impossível (ex: 31/02/2020).
        void validate(string) override;
};

#endif