/**
 * @file console_presentation.hpp
 * @brief Declaração da classe de controle da camada de apresentação em modo console.
 */

#ifndef CONSOLE_PRESENTATION_HPP
#define CONSOLE_PRESENTATION_HPP

#include "../interfaces/IPersonService.hpp"
#include "../interfaces/IProjectService.hpp"
#include "../interfaces/ISprintPlanService.hpp"
#include "../interfaces/IUserStoryService.hpp"

/**
 * @class ConsolePresentation
 * @brief Classe controladora responsável pela interface de usuário via terminal.
 * * Esta classe gerencia o ciclo de vida do menu interativo, captura as entradas
 * do usuário, realiza a invocação dos domínios para validação sintática e
 * delega as regras de negócio para as interfaces da camada de serviço.
 */
class ConsolePresentation {
public:
    /**
     * @brief Construtor que inicializa a controladora com as suas dependências de serviço.
     * @param servicePessoa Referência para a interface do serviço de pessoas.
     * @param serviceProjeto Referência para a interface do serviço de projetos.
     * @param servicePlano Referência para a interface do serviço de planos de sprint.
     * @param serviceHistoria Referência para a interface do serviço de histórias de usuário.
     */
    ConsolePresentation(IPersonService& servicePessoa,
        IProjectService& serviceProjeto,
        ISprintPlanService& servicePlano,
        IUserStoryService& serviceHistoria,
        const std::string& currentUserRole = ""
    );

    /**
     * @brief Inicia o loop principal de execução da interface em console.
     * * Apresenta o menu de opções e processa as escolhas capturadas, tratando
     * exceções de validação lançadas pelas classes de domínio.
     */
    void run();

private:
    /** @brief Exibe as opções textuais do menu principal no terminal. */
    void exibirMenu() const;

    /** @brief Fluxo de captura e chamada para cadastrar uma nova pessoa. */
    void cadastrarPessoa();
    /** @brief Fluxo de captura e chamada para buscar uma pessoa cadastrada. */
    void buscarPessoa();
    /** @brief Fluxo de captura e chamada para atualizar dados de uma pessoa. */
    void atualizarPessoa();
    /** @brief Fluxo de captura e chamada para remover uma pessoa do sistema. */
    void removerPessoa();

    /** @brief Fluxo de captura e chamada para cadastrar um novo projeto. */
    void cadastrarProjeto();
    /** @brief Fluxo de captura e chamada para buscar um projeto existente. */
    void buscarProjeto();
    /** @brief Fluxo de captura e chamada para atualizar dados de um projeto. */
    void atualizarProjeto();
    /** @brief Fluxo de captura e chamada para remover um projeto do sistema. */
    void removerProjeto();

    /** @brief Fluxo de captura e chamada para cadastrar um plano de sprint. */
    void cadastrarPlanoSprint();
    /** @brief Fluxo de captura e chamada para buscar um plano de sprint. */
    void buscarPlanoSprint();
    /** @brief Fluxo de captura e chamada para atualizar dados de um plano de sprint. */
    void atualizarPlanoSprint();
    /** @brief Fluxo de captura e chamada para remover um plano de sprint. */
    void removerPlanoSprint();

    /** @brief Fluxo de captura e chamada para cadastrar uma história de usuário. */
    void cadastrarHistoria();
    /** @brief Fluxo de captura e chamada para buscar uma história de usuário. */
    void buscarHistoria();
    /** @brief Fluxo de captura e chamada para atualizar dados de uma história de usuário. */
    void atualizarHistoria();
    /** @brief Fluxo de captura e chamada para remover uma história de usuário. */
    void removerHistoria();
    /** @brief Fluxo de captura e chamada para associar uma pessoa a uma história de usuário. */
    void associarPessoaHistoria();
    /** @brief Fluxo de captura e chamada para remover a associação de uma pessoa a uma história de usuário. */
    void removerAssociacaoPessoaHistoria();
    /** @brief Fluxo de captura e chamada para mover uma história de usuário para um plano de sprint. */
    void moverHistoriaParaPlanoSprint();
    /** @brief Fluxo de captura e chamada para alterar o estado de uma história de usuário. */
    void alterarEstadoHistoria();

    /**
     * @brief Lê e valida um e-mail a partir da entrada padrão.
     * @param prompt Texto informativo exibido antes da captura.
     * @return Objeto do tipo domínio Email configurado.
     */
    Email lerEmail(const std::string& prompt) const;

    /**
     * @brief Lê e valida um nome a partir da entrada padrão.
     * @param prompt Texto informativo exibido antes da captura.
     * @return Objeto do tipo domínio Name configurado.
     */
    Name lerNome(const std::string& prompt) const;

    /**
     * @brief Lê e valida uma senha a partir da entrada padrão.
     * @param prompt Texto informativo exibido antes da captura.
     * @return Objeto do tipo domínio Password configurado.
     */
    Password lerSenha(const std::string& prompt) const;

    /**
     * @brief Lê e valida um papel profissional a partir da entrada padrão.
     * @param prompt Texto informativo exibido antes da captura.
     * @return Objeto do tipo domínio Role configurado.
     */
    Role lerPapel(const std::string& prompt) const;

    /**
     * @brief Lê e valida um código identificador a partir da entrada padrão.
     * @param prompt Texto informativo exibido antes da captura.
     * @return Objeto do tipo domínio Code configurado.
     */
    Code lerCodigo(const std::string& prompt) const;

    /**
     * @brief Lê e valida uma data a partir da entrada padrão.
     * @param prompt Texto informativo exibido antes da captura.
     * @return Objeto do tipo domínio Date configurado.
     */
    Date lerData(const std::string& prompt) const;

    /**
     * @brief Lê e valida um texto genérico a partir da entrada padrão.
     * @param prompt Texto informativo exibido antes da captura.
     * @return Objeto do tipo domínio Text configurado.
     */
    Text lerTexto(const std::string& prompt) const;

    /**
     * @brief Lê e valida uma unidade de tempo/capacidade a partir da entrada padrão.
     * @param prompt Texto informativo exibido antes da captura.
     * @return Objeto do tipo domínio Time configurado.
     */
    Time lerTempo(const std::string& prompt) const;

    /**
     * @brief Lê e valida um nível de prioridade a partir da entrada padrão.
     * @param prompt Texto informativo exibido antes da captura.
     * @return Objeto do tipo domínio Priority configurado.
     */
    Priority lerPrioridade(const std::string& prompt) const;

    /**
     * @brief Lê e valida o estado atual a partir da entrada padrão.
     * @param prompt Texto informativo exibido antes da captura.
     * @return Objeto do tipo domínio State configurado.
     */
    State lerEstado(const std::string& prompt) const;

    /**
     * @brief Imprime na tela as informações formatadas de uma Entidade Pessoa.
     * @param pessoa Referência constante para a entidade a ser exibida.
     */
    void exibirPessoa(const Person& pessoa) const;

    /**
     * @brief Imprime na tela as informações formatadas de uma Entidade Projeto.
     * @param projeto Referência constante para a entidade a ser exibida.
     */
    void exibirProjeto(const Project& projeto) const;

    /**
     * @brief Imprime na tela as informações formatadas de uma Entidade Plano de Sprint.
     * @param plano Referência constante para a entidade a ser exibida.
     */
    void exibirPlano(const SprintPlan& plano) const;

    /**
     * @brief Imprime na tela as informações formatadas de uma Entidade História de Usuário.
     * @param historia Referência constante para a entidade a ser exibida.
     */
    void exibirHistoria(const UserStory& historia) const;

    void configurarContextoUsuario();
    bool isProductOwner() const;
    bool isScrumMaster() const;

    IPersonService& servicePessoa_;       /**< Referência interna ao serviço de gerenciamento de pessoas. */
    IProjectService& serviceProjeto_;     /**< Referência interna ao serviço de gerenciamento de projetos. */
    ISprintPlanService& servicePlano_;    /**< Referência interna ao serviço de planos de sprint. */
    IUserStoryService& serviceHistoria_;  /**< Referência interna ao serviço de histórias de usuário. */
    std::string currentUserRole_;
};

#endif