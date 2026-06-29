#ifndef USERSTORY_HPP
#define USERSTORY_HPP

#include "../dominios/derivados/code.hpp"
#include "../dominios/derivados/text.hpp"
#include "../dominios/derivados/time.hpp"
#include "../dominios/derivados/priority.hpp"
#include "../dominios/derivados/state.hpp"
#include "../dominios/derivados/email.hpp"

/// @brief Entidade que representa uma história de usuário.
///
/// Uma história de usuário é identificada unicamente por seu código,
/// definida na criação e não editável posteriormente.
/// Uma história de usuário possui título, papel, ação, valor, estimativa de tempo, prioridade e estado,
/// que determinam o comportamento esperado do sistema.
class UserStory {
    private:
        Code code;          ///< Identificador único da história de usuário (chave primária).
        Text title;         ///< Título da história de usuário.
        Text role;          ///< Papel do usuário relacionado à história de usuário.
        Text action;        ///< Ação que o usuário deseja realizar, descrita na história de usuário.
        Text value;         ///< Valor ou benefício que o usuário espera obter, descrito na história de usuário.
        Time estimation;    ///< Estimativa de tempo para implementação da história de usuário, em dias.
        Priority priority;  ///< Prioridade da história de usuário, que pode ser "ALTA", "MEDIA" ou "BAIXA".
        State state;        ///< Estado atual da história de usuário, que pode ser "A FAZER", "FAZENDO" ou "FEITO".

        Code project;       ///< Código do projeto ao qual a história pertence.
        Code sprintPlan;    ///< Código do plano de sprint atual ao qual a história está alocada.
        Email developer;    ///< Email da pessoa associada como Desenvolvedor da história.

    public:
        /// @brief Constrói uma história de usuário com o código fornecido.
        /// @param code Objeto Code com o identificador único da história de usuário.
        UserStory(Code code);

        /// @brief Obtém o código da história de usuário.
        /// @return Objeto Code com o identificador único da história de usuário.
        Code getCode() const;

        /// @brief Define o título da história de usuário.
        /// @param title Objeto Text com o título da história de usuário.
        void setTitle(Text);

        /// @brief Obtém o título da história de usuário.
        /// @return Objeto Text com o título da história de usuário.
        Text getTitle() const;

        /// @brief Define o papel do usuário relacionado à história de usuário.
        /// @param role Objeto Text com o papel do usuário.
        void setRole(Text);

        /// @brief Obtém o papel do usuário relacionado à história de usuário.
        /// @return Objeto Text com o papel do usuário.
        Text getRole() const;

        /// @brief Define a ação da história de usuário.
        /// @param action Objeto Text com a ação da história de usuário.
        void setAction(Text);

        /// @brief Obtém a ação da história de usuário.
        /// @return Objeto Text com a ação da história de usuário.
        Text getAction() const;

        /// @brief Define o valor ou benefício que o usuário espera obter.
        /// @param value Objeto Text com o valor da história de usuário.
        void setValue(Text);

        /// @brief Obtém o valor ou benefício que o usuário espera obter.
        /// @return Objeto Text com o valor da história de usuário.
        Text getValue() const;

        /// @brief Define a estimativa de tempo para implementação da história de usuário.
        /// @param estimation Objeto Time com a estimativa de tempo da história de usuário.
        void setEstimation(Time);

        /// @brief Obtém a estimativa de tempo para implementação da história de usuário.
        /// @return Objeto Time com a estimativa de tempo da história de usuário.
        Time getEstimation() const;

        /// @brief Define a prioridade da história de usuário.
        /// @param priority Objeto Priority com a prioridade da história de usuário.
        void setPriority(Priority);

        /// @brief Obtém a prioridade da história de usuário.
        /// @return Objeto Priority com a prioridade da história de usuário.
        Priority getPriority() const;

        /// @brief Define o estado da história de usuário.
        /// @param state Objeto State com o estado da história de usuário.
        void setState(State);

        /// @brief Obtém o estado da história de usuário.
        /// @return Objeto State com o estado da história de usuário.
        State getState() const;

        /// @brief Define o projeto ao qual a história de usuário pertence.
        /// @param project Objeto Code com o identificador do projeto.
        void setProject(Code);

        /// @brief Obtém o projeto ao qual a história de usuário pertence.
        /// @return Objeto Code com o identificador do projeto.
        Code getProject() const;

        /// @brief Define o plano de sprint ao qual a história de usuário está alocada.
        /// @param sprintPlan Objeto Code com o identificador do plano de sprint.
        void setSprintPlan(Code);

        /// @brief Obtém o plano de sprint ao qual a história de usuário está alocada.
        /// @return Objeto Code com o identificador do plano de sprint.
        Code getSprintPlan() const;

        /// @brief Define o desenvolvedor responsável pela história de usuário.
        /// @param developer Objeto Email com o identificador do desenvolvedor.
        void setDeveloper(Email);

        /// @brief Obtém o desenvolvedor responsável pela história de usuário.
        /// @return Objeto Email com o identificador do desenvolvedor.
        Email getDeveloper() const;
};

#endif
