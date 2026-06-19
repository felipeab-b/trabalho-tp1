#ifndef IUSERSTORY_SERVICE_HPP
#define IUSERSTORY_SERVICE_HPP

#include <vector>
#include "../entidades/userstory.hpp"
#include "../dominios/derivados/code.hpp"
#include "../dominios/derivados/text.hpp"
#include "../dominios/derivados/time.hpp"
#include "../dominios/derivados/priority.hpp"
#include "../dominios/derivados/state.hpp"
#include "../dominios/derivados/email.hpp"

/// @brief Interface do módulo História de Usuário.
///
/// Declara os serviços relacionados à entidade História de Usuário que
/// a camada de serviço deve prover e dos quais a camada de apresentação
/// depende.
class IUserStoryService {
    public:
        /// @brief Cria uma nova história de usuário.
        ///
        /// Apenas Proprietário de Produto pode criar história de usuário, e
        /// deve associá-la a um projeto. O estado inicial é definido
        /// automaticamente como "A FAZER".
        /// @param code Código da história de usuário, identificador único (chave primária).
        /// @param title Título da história de usuário.
        /// @param role Papel descrito na história de usuário ("como...").
        /// @param action Ação descrita na história de usuário ("eu quero...").
        /// @param value Valor descrito na história de usuário ("para...").
        /// @param estimation Estimativa de tempo para implementação, em dias.
        /// @param priority Prioridade da história de usuário.
        /// @param project Código do projeto ao qual a história de usuário será associada.
        /// @throws std::invalid_argument se já existir história de usuário com o mesmo código,
        ///         se não existir projeto com o código informado,
        ///         ou se algum parâmetro tiver formato inválido.
        virtual void criarHistoriaDeUsuario(Code code, Text title, Text role, Text action,
                                             Text value, Time estimation, Priority priority,
                                             Code project) = 0;

        /// @brief Obtém os dados de uma história de usuário cadastrada.
        /// @param code Código identificador da história de usuário.
        /// @return Objeto UserStory com os dados da história de usuário.
        /// @throws std::invalid_argument se não existir história de usuário com o código informado.
        virtual UserStory lerHistoriaDeUsuario(Code code) const = 0;

        /// @brief Atualiza os dados de uma história de usuário existente.
        ///
        /// O código (chave primária) não pode ser alterado.
        /// @param code Código identificador da história de usuário a ser atualizada.
        /// @param title Novo título da história de usuário.
        /// @param role Novo papel descrito na história de usuário.
        /// @param action Nova ação descrita na história de usuário.
        /// @param value Novo valor descrito na história de usuário.
        /// @param estimation Nova estimativa de tempo, em dias.
        /// @param priority Nova prioridade da história de usuário.
        /// @throws std::invalid_argument se não existir história de usuário com o código informado,
        ///         se a nova estimativa tornar inválida a soma de estimativas do plano de
        ///         sprint ao qual a história estiver associada, ou se algum parâmetro
        ///         tiver formato inválido.
        virtual void atualizarHistoriaDeUsuario(Code code, Text title, Text role, Text action,
                                                 Text value, Time estimation, Priority priority) = 0;

        /// @brief Exclui uma história de usuário do sistema.
        /// @param code Código identificador da história de usuário a ser excluída.
        /// @throws std::invalid_argument se não existir história de usuário com o código informado.
        virtual void excluirHistoriaDeUsuario(Code code) = 0;

        /// @brief Associa uma pessoa a uma história de usuário.
        /// @param userStory Código identificador da história de usuário.
        /// @param person Email identificador da pessoa a ser associada.
        /// @throws std::invalid_argument se não existir história de usuário ou pessoa com
        ///         os identificadores informados, ou se a pessoa não tiver papel de Desenvolvedor.
        virtual void associarPessoaAHistoriaDeUsuario(Code userStory, Email person) = 0;

        /// @brief Remove a associação entre uma pessoa e uma história de usuário.
        /// @param userStory Código identificador da história de usuário.
        /// @param person Email identificador da pessoa a ser desassociada.
        /// @throws std::invalid_argument se não existir história de usuário ou pessoa com
        ///         os identificadores informados, ou se não houver associação entre eles.
        virtual void removerAssociacaoPessoaHistoriaDeUsuario(Code userStory, Email person) = 0;

        /// @brief Lista as histórias de usuário associadas a um projeto.
        /// @param project Código identificador do projeto.
        /// @return Vetor com os códigos das histórias de usuário associadas ao projeto.
        /// @throws std::invalid_argument se não existir projeto com o código informado.
        virtual std::vector<Code> listarHistoriasDeUsuarioDeProjeto(Code project) const = 0;

        /// @brief Lista as histórias de usuário associadas a um plano de sprint.
        /// @param sprintPlan Código identificador do plano de sprint.
        /// @return Vetor com os códigos das histórias de usuário associadas ao plano de sprint.
        /// @throws std::invalid_argument se não existir plano de sprint com o código informado.
        virtual std::vector<Code> listarHistoriasDeUsuarioDePlanoDeSprint(Code sprintPlan) const = 0;

        /// @brief Lista as histórias de usuário associadas a uma pessoa.
        /// @param person Email identificador da pessoa.
        /// @return Vetor com os códigos das histórias de usuário associadas à pessoa.
        /// @throws std::invalid_argument se não existir pessoa com o email informado.
        virtual std::vector<Code> listarHistoriasDeUsuarioDePessoa(Email person) const = 0;

        /// @brief Move uma história de usuário de um projeto para um plano de sprint.
        /// @param userStory Código identificador da história de usuário a ser movida.
        /// @param project Código identificador do projeto de origem.
        /// @param sprintPlan Código identificador do plano de sprint de destino.
        /// @throws std::invalid_argument se algum dos identificadores informados não existir,
        ///         se a história de usuário não estiver associada ao projeto informado,
        ///         se o plano de sprint não estiver associado ao mesmo projeto,
        ///         ou se a soma das estimativas das histórias de usuário do plano de sprint
        ///         passar a exceder a capacidade do plano de sprint.
        virtual void moverHistoriaDeUsuarioParaPlanoDeSprint(Code userStory, Code project, Code sprintPlan) = 0;

        /// @brief Altera o estado de uma história de usuário.
        /// @param userStory Código identificador da história de usuário.
        /// @param state Novo estado da história de usuário.
        /// @throws std::invalid_argument se não existir história de usuário com o código informado,
        ///         ou se o estado informado tiver formato inválido.
        virtual void alterarEstadoHistoriaDeUsuario(Code userStory, State state) = 0;

        /// @brief Destrutor virtual da interface.
        virtual ~IUserStoryService() {}
};

#endif