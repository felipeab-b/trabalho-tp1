#ifndef ISPRINTPLAN_SERVICE_HPP
#define ISPRINTPLAN_SERVICE_HPP

#include <vector>
#include "../entidades/sprintplan.hpp"
#include "../dominios/derivados/code.hpp"
#include "../dominios/derivados/text.hpp"
#include "../dominios/derivados/time.hpp"

/// @brief Interface do módulo Plano de Sprint.
///
/// Declara os serviços relacionados à entidade Plano de Sprint que a
/// camada de serviço deve prover e dos quais a camada de apresentação
/// depende.
class ISprintPlanService {
    public:
        /// @brief Cria um novo plano de sprint.
        ///
        /// Apenas Mestre Scrum pode criar plano de sprint, e deve
        /// associá-lo a um projeto.
        /// @param code Código do plano de sprint, identificador único (chave primária).
        /// @param objective Objetivo do plano de sprint.
        /// @param capacity Capacidade do plano de sprint, em dias.
        /// @param project Código do projeto ao qual o plano de sprint será associado.
        /// @throws std::invalid_argument se já existir plano de sprint com o mesmo código,
        ///         se não existir projeto com o código informado,
        ///         se a soma das capacidades dos planos de sprint do projeto exceder
        ///         o número de dias entre o início e o término do projeto,
        ///         ou se algum parâmetro tiver formato inválido.
        virtual void criarPlanoDeSprint(Code code, Text objective, Time capacity, Code project) = 0;

        /// @brief Obtém os dados de um plano de sprint cadastrado.
        /// @param code Código identificador do plano de sprint.
        /// @return Objeto SprintPlan com os dados do plano de sprint.
        /// @throws std::invalid_argument se não existir plano de sprint com o código informado.
        virtual SprintPlan lerPlanoDeSprint(Code code) const = 0;

        /// @brief Atualiza os dados de um plano de sprint existente.
        ///
        /// O código (chave primária) não pode ser alterado.
        /// @param code Código identificador do plano de sprint a ser atualizado.
        /// @param objective Novo objetivo do plano de sprint.
        /// @param capacity Nova capacidade do plano de sprint, em dias.
        /// @throws std::invalid_argument se não existir plano de sprint com o código informado,
        ///         se a nova capacidade tornar inválida a soma de capacidades do projeto,
        ///         se a soma das estimativas das histórias de usuário associadas passar a
        ///         exceder a nova capacidade, ou se algum parâmetro tiver formato inválido.
        virtual void atualizarPlanoDeSprint(Code code, Text objective, Time capacity) = 0;

        /// @brief Exclui um plano de sprint do sistema.
        /// @param code Código identificador do plano de sprint a ser excluído.
        /// @throws std::invalid_argument se não existir plano de sprint com o código informado,
        ///         ou se a exclusão resultar em inconsistência (ex.: plano de sprint
        ///         possui histórias de usuário associadas).
        virtual void excluirPlanoDeSprint(Code code) = 0;

        /// @brief Lista os planos de sprint associados a um projeto.
        /// @param project Código identificador do projeto.
        /// @return Vetor com os códigos dos planos de sprint associados ao projeto.
        /// @throws std::invalid_argument se não existir projeto com o código informado.
        virtual std::vector<Code> listarPlanosDeSprintDeProjeto(Code project) const = 0;

        /// @brief Destrutor virtual da interface.
        virtual ~ISprintPlanService() {}
};

#endif