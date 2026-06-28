#ifndef CONSOLE_PRESENTATION_HPP
#define CONSOLE_PRESENTATION_HPP

#include "../interfaces/IPersonService.hpp"
#include "../interfaces/IProjectService.hpp"
#include "../interfaces/ISprintPlanService.hpp"
#include "../interfaces/IUserStoryService.hpp"

class ConsolePresentation {
public:
    ConsolePresentation(IPersonService& servicePessoa,
        IProjectService& serviceProjeto, // CORRIGIDO: Adicionado o 'I' de interface
        ISprintPlanService& servicePlano,
        IUserStoryService& serviceHistoria
    );
    void run();

private:
    void exibirMenu() const;
    void cadastrarPessoa();
    void buscarPessoa();
    void atualizarPessoa();
    void removerPessoa();

    void cadastrarProjeto();
    void buscarProjeto();
    void atualizarProjeto();
    void removerProjeto();

    void cadastrarPlanoSprint();
    void buscarPlanoSprint();
    void atualizarPlanoSprint();
    void removerPlanoSprint();

    void cadastrarHistoria();
    void buscarHistoria();
    void atualizarHistoria();
    void removerHistoria();

    Email lerEmail(const std::string& prompt) const;
    Name lerNome(const std::string& prompt) const;
    Password lerSenha(const std::string& prompt) const;
    Role lerPapel(const std::string& prompt) const;
    Code lerCodigo(const std::string& prompt) const;
    Date lerData(const std::string& prompt) const;
    Text lerTexto(const std::string& prompt) const;
    Time lerTempo(const std::string& prompt) const;
    Priority lerPrioridade(const std::string& prompt) const;
    State lerEstado(const std::string& prompt) const;

    void exibirPessoa(const Person& pessoa) const;
    void exibirProjeto(const Project& projeto) const;
    void exibirPlano(const SprintPlan& plano) const;
    void exibirHistoria(const UserStory& historia) const;

    IPersonService& servicePessoa_;
    IProjectService& serviceProjeto_;
    ISprintPlanService& servicePlano_;
    IUserStoryService& serviceHistoria_;
};

#endif