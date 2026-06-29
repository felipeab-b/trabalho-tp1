#ifndef IPROJECT_SERVICE_HPP
#define IPROJECT_SERVICE_HPP

#include <vector>
#include <string>
#include "../entidades/project.hpp"
#include "../dominios/derivados/code.hpp"
#include "../dominios/derivados/name.hpp"
#include "../dominios/derivados/date.hpp"
#include "../dominios/derivados/email.hpp"

/// @brief Interface do módulo Projeto.
///
/// Declara os serviços relacionados à entidade Projeto que a camada de
/// serviço deve prover e dos quais a camada de apresentação depende.
class IProjectService {
    public:
        virtual void setCurrentUser(const std::string& email, const std::string& role) = 0;

        /// @brief Cria um novo projeto.
        ///
        /// Apenas Proprietário de Produto pode criar projeto, e deve
        /// associá-lo a um Mestre Scrum.
        /// @param code Código do projeto, identificador único (chave primária).
        /// @param name Nome do projeto.
        /// @param beginning Data de início do projeto.
        /// @param ending Data de término do projeto.
        /// @param scrumMaster Email da pessoa que assumirá o papel de Mestre Scrum do projeto.
        /// @throws std::invalid_argument se já existir projeto com o mesmo código,
        ///         se a pessoa informada não tiver papel de Mestre Scrum,
        ///         se a data de término for anterior à data de início,
        ///         ou se algum parâmetro tiver formato inválido.
        virtual void criarProjeto(Code code, Name name, Date beginning, Date ending, Email scrumMaster) = 0;

        /// @brief Obtém os dados de um projeto cadastrado.
        /// @param code Código identificador do projeto.
        /// @return Objeto Project com os dados do projeto.
        /// @throws std::invalid_argument se não existir projeto com o código informado.
        virtual Project lerProjeto(Code code) const = 0;

        /// @brief Atualiza os dados de um projeto existente.
        ///
        /// O código (chave primária) não pode ser alterado.
        /// @param code Código identificador do projeto a ser atualizado.
        /// @param name Novo nome do projeto.
        /// @param beginning Nova data de início do projeto.
        /// @param ending Nova data de término do projeto.
        /// @throws std::invalid_argument se não existir projeto com o código informado,
        ///         se a soma das capacidades dos planos de sprint associados passar a exceder
        ///         o novo período do projeto, ou se algum parâmetro tiver formato inválido.
        virtual void atualizarProjeto(Code code, Name name, Date beginning, Date ending) = 0;

        /// @brief Exclui um projeto do sistema.
        /// @param code Código identificador do projeto a ser excluído.
        /// @throws std::invalid_argument se não existir projeto com o código informado,
        ///         ou se a exclusão resultar em inconsistência (ex.: projeto possui
        ///         planos de sprint ou histórias de usuário associados).
        virtual void excluirProjeto(Code code) = 0;

        /// @brief Lista os projetos associados a uma pessoa.
        ///
        /// Retorna os projetos nos quais a pessoa atua como Proprietário de
        /// Produto ou Mestre Scrum.
        /// @param person Email identificador da pessoa.
        /// @return Vetor com os códigos dos projetos associados à pessoa.
        /// @throws std::invalid_argument se não existir pessoa com o email informado.
        virtual std::vector<Code> listarProjetosDePessoa(Email person) const = 0;

        /// @brief Destrutor virtual da interface.
        virtual ~IProjectService() {}
};

#endif