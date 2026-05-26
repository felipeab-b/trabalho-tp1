#ifndef DOMINIO_HPP
#define DOMINIO_HPP

#include <string>

using namespace std;

/// @brief Classe base abstrata para todos os domínios do sistema.
///
/// Define a interface comum de acesso (set/get) compartilhada por todos os domínios.
/// Cada subclasse deve implementar validate() com suas próprias regras de validação.
class Dominio {
protected:
    string valor; ///< Valor armazenado pelo domínio.

    /// @brief Valida o valor fornecido.
    /// @param valor String a ser validada.
    /// @throws invalid_argument se o valor não atender ao formato esperado.
    virtual void validate(string valor) = 0;

public:
    /// @brief Define o valor do domínio após validação.
    /// @param valor String a ser validada e armazenada.
    /// @throws invalid_argument se o formato for inválido.
    void set(string valor);

    /// @brief Retorna o valor armazenado.
    /// @return String com o valor do domínio.
    string get() const;

    /// @brief Destrutor virtual.
    virtual ~Dominio() {}
};

inline string Dominio::get() const {
    return this->valor;
}

#endif