#ifndef PROJECT_HPP
#define PROJECT_HPP

#include "dominios/derivados/code.hpp"
#include "dominios/derivados/date.hpp"
#include "dominios/derivados/name.hpp"
#include "dominios/derivados/email.hpp"

/// @brief Entidade que representa um projeto no sistema.
///
/// Um projeto é identificado unicamente por seu código,
/// definido na criação e não editável posteriormente.
/// Um projeto possui nome, data de início e data de fim,
/// que determinam o período de execução do projeto, além de estar
/// associado a um Proprietário de Produto e a um Mestre Scrum.
class Project {
    private:
        Code code;          ///< Identificador único do projeto (chave primária).
        Name name;          ///< Nome do projeto.
        Date beginning;     ///< Data de início do projeto.
        Date ending;        ///< Data de término do projeto.
        Email productOwner; ///< Email do Proprietário de Produto responsável pelo projeto.
        Email scrumMaster;  ///< Email do Mestre Scrum responsável pelo projeto.

    public:
        /// @brief Constrói um projeto com o código fornecido.
        /// @param code Objeto Code com o identificador único do projeto.
        Project(Code code);

        /// @brief Retorna o código do projeto.
        /// @return Objeto Code com o identificador do projeto.
        Code getCode() const;

        /// @brief Define o nome do projeto.
        /// @param name Objeto Name com o nome desejado.
        void setName(Name);

        /// @brief Retorna o nome do projeto.
        /// @return Objeto Name com o nome do projeto.
        Name getName() const;

        /// @brief Define a data de início do projeto.
        /// @param beginning Objeto Date com a data desejada.
        void setBeginning(Date);

        /// @brief Retorna a data de início do projeto.
        /// @return Objeto Date com a data de início.
        Date getBeginning() const;

        /// @brief Define a data de término do projeto.
        /// @param ending Objeto Date com a data desejada.
        void setEnding(Date);

        /// @brief Retorna a data de término do projeto.
        /// @return Objeto Date com a data de término.
        Date getEnding() const;

        /// @brief Define o Proprietário de Produto associado ao projeto.
        /// @param productOwner Objeto Email identificando o Proprietário de Produto.
        void setProductOwner(Email);

        /// @brief Retorna o Proprietário de Produto do projeto.
        /// @return Objeto Email com o identificador do Proprietário de Produto.
        Email getProductOwner() const;

        /// @brief Define o Mestre Scrum associado ao projeto.
        /// @param scrumMaster Objeto Email identificando o Mestre Scrum.
        void setScrumMaster(Email);

        /// @brief Retorna o Mestre Scrum do projeto.
        /// @return Objeto Email com o identificador do Mestre Scrum.
        Email getScrumMaster() const;
};

#endif