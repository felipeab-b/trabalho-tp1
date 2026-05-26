#ifndef PERSON_HPP
#define PERSON_HPP

#include "dominios/derivados/email.hpp"
#include "dominios/derivados/name.hpp"
#include "dominios/derivados/role.hpp"
#include "dominios/derivados/password.hpp"

using namespace std;

/// @brief Entidade que representa um usuário do sistema.
///
/// Cada pessoa é identificada unicamente por seu email,
/// definido na criação e não editável posteriormente.
/// Uma pessoa possui nome, senha e papel no projeto,
/// que determinam quais serviços ela pode acessar.
class Person {
private:
    Email email;       ///< Identificador único da pessoa (chave primária).
    Name name;         ///< Nome da pessoa.
    Password password; ///< Senha de acesso da pessoa.
    Role role;         ///< Papel da pessoa no projeto.

public:
    /// @brief Constrói uma pessoa com o email fornecido.
    /// @param email Email identificador da pessoa.
    Person(Email email);

    /// @brief Retorna o email da pessoa.
    /// @return Objeto Email com o identificador da pessoa.
    Email getEmail() const;

    /// @brief Define o nome da pessoa.
    /// @param name Objeto Name com o nome desejado.
    void setName(Name name);

    /// @brief Retorna o nome da pessoa.
    /// @return Objeto Name com o nome da pessoa.
    Name getName() const;

    /// @brief Define a senha da pessoa.
    /// @param password Objeto Password com a senha desejada.
    void setPassword(Password password);

    /// @brief Retorna a senha da pessoa.
    /// @return Objeto Password com a senha da pessoa.
    Password getPassword() const;

    /// @brief Define o papel da pessoa no projeto.
    /// @param role Objeto Role com o papel desejado.
    void setRole(Role role);

    /// @brief Retorna o papel da pessoa no projeto.
    /// @return Objeto Role com o papel da pessoa.
    Role getRole() const;
};

#endif