#ifndef IPERSON_SERVICE_HPP
#define IPERSON_SERVICE_HPP

#include <vector>
#include <string>
#include "../entidades/person.hpp"
#include "../dominios/derivados/email.hpp"
#include "../dominios/derivados/name.hpp"
#include "../dominios/derivados/password.hpp"
#include "../dominios/derivados/role.hpp"

/// @brief Interface do módulo Pessoa.
///
/// Declara os serviços relacionados à entidade Pessoa que a camada de
/// serviço deve prover e dos quais a camada de apresentação depende.
/// A camada de apresentação nunca depende da implementação concreta,
/// apenas desta interface, declarada como classe abstrata com métodos
/// virtuais puros (Requisito 14 e 19 do Trabalho).
class IPersonService {
    public:
        virtual void setCurrentUser(const std::string& email, const std::string& role) = 0;

        /// @brief Cria uma nova pessoa no sistema.
        /// @param email Email da pessoa, identificador único (chave primária).
        /// @param name Nome da pessoa.
        /// @param password Senha de acesso da pessoa.
        /// @param role Papel da pessoa no projeto.
        /// @throws std::invalid_argument se já existir pessoa com o mesmo email,
        ///         ou se algum parâmetro tiver formato inválido.
        virtual void criarPessoa(Email email, Name name, Password password, Role role) = 0;

        /// @brief Obtém os dados de uma pessoa cadastrada.
        /// @param email Email identificador da pessoa.
        /// @return Objeto Person com os dados da pessoa.
        /// @throws std::invalid_argument se não existir pessoa com o email informado.
        virtual Person lerPessoa(Email email) const = 0;

        /// @brief Atualiza os dados de uma pessoa existente.
        ///
        /// O email (chave primária) não pode ser alterado.
        /// @param email Email identificador da pessoa a ser atualizada.
        /// @param name Novo nome da pessoa.
        /// @param password Nova senha da pessoa.
        /// @param role Novo papel da pessoa no projeto.
        /// @throws std::invalid_argument se não existir pessoa com o email informado,
        ///         ou se algum parâmetro tiver formato inválido.
        virtual void atualizarPessoa(Email email, Name name, Password password, Role role) = 0;

        /// @brief Exclui uma pessoa do sistema.
        /// @param email Email identificador da pessoa a ser excluída.
        /// @throws std::invalid_argument se não existir pessoa com o email informado,
        ///         ou se a exclusão resultar em inconsistência (ex.: pessoa é
        ///         Mestre Scrum de algum projeto ou está associada a história de usuário).
        virtual void excluirPessoa(Email email) = 0;

        virtual std::vector<Person> listarTodasAsPessoas() const = 0;

        /// @brief Destrutor virtual da interface.
        virtual ~IPersonService() {}
};

#endif