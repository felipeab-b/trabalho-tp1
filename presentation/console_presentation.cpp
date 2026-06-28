#include "console_presentation.hpp"

#include <iostream>
#include <limits>
#include <stdexcept>

ConsolePresentation::ConsolePresentation(IPersonService& servicePessoa,
    IProjectService& serviceProjeto,
    ISprintPlanService& servicePlano,
    IUserStoryService& serviceHistoria
)
    : servicePessoa_(servicePessoa),
      serviceProjeto_(serviceProjeto),
      servicePlano_(servicePlano),
      serviceHistoria_(serviceHistoria) {}

void ConsolePresentation::run() {
    int opcao = -1;

    while (opcao != 0) {
        exibirMenu();
        std::cout << "Opcao: ";
        std::cin >> opcao;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            switch (opcao) {
                case 1:
                    cadastrarPessoa();
                    break;
                case 2:
                    buscarPessoa();
                    break;
                case 3:
                    atualizarPessoa();
                    break;
                case 4:
                    removerPessoa();
                    break;
                case 5:
                    cadastrarProjeto();
                    break;
                case 6:
                    buscarProjeto();
                    break;
                case 7:
                    atualizarProjeto();
                    break;
                case 8:
                    removerProjeto();
                    break;
                case 9:
                    cadastrarPlanoSprint();
                    break;
                case 10:
                    buscarPlanoSprint();
                    break;
                case 11:
                    atualizarPlanoSprint();
                    break;
                case 12:
                    removerPlanoSprint();
                    break;
                case 13:
                    cadastrarHistoria();
                    break;
                case 14:
                    buscarHistoria();
                    break;
                case 15:
                    atualizarHistoria();
                    break;
                case 16:
                    removerHistoria();
                    break;
                case 0:
                    std::cout << "Encerrando o sistema..." << std::endl;
                    break;
                default:
                    std::cout << "Opcao invalida." << std::endl;
                    break;
            }
        } catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
}

void ConsolePresentation::exibirMenu() const {
    std::cout << "\n=== Sistema Scrum ===" << std::endl;
    std::cout << "1. Cadastrar pessoa" << std::endl;
    std::cout << "2. Buscar pessoa" << std::endl;
    std::cout << "3. Atualizar pessoa" << std::endl;
    std::cout << "4. Remover pessoa" << std::endl;
    std::cout << "5. Cadastrar projeto" << std::endl;
    std::cout << "6. Buscar projeto" << std::endl;
    std::cout << "7. Atualizar projeto" << std::endl;
    std::cout << "8. Remover projeto" << std::endl;
    std::cout << "9. Cadastrar plano de sprint" << std::endl;
    std::cout << "10. Buscar plano de sprint" << std::endl;
    std::cout << "11. Atualizar plano de sprint" << std::endl;
    std::cout << "12. Remover plano de sprint" << std::endl;
    std::cout << "13. Cadastrar historia de usuario" << std::endl;
    std::cout << "14. Buscar historia de usuario" << std::endl;
    std::cout << "15. Atualizar historia de usuario" << std::endl;
    std::cout << "16. Remover historia de usuario" << std::endl;
    std::cout << "0. Sair" << std::endl;
}

void ConsolePresentation::cadastrarPessoa() {
    Email email = lerEmail("Email: ");
    Name nome = lerNome("Nome: ");
    Password senha = lerSenha("Senha: ");
    Role papel = lerPapel("Papel (DESENVOLVEDOR, MESTRE SCRUM, PROPRIETARIO DE PRODUTO): ");

    servicePessoa_.criarPessoa(email, nome, senha, papel);
    std::cout << "Pessoa cadastrada com sucesso." << std::endl;
}

void ConsolePresentation::buscarPessoa() {
    Email email = lerEmail("Email para buscar: ");
    exibirPessoa(servicePessoa_.lerPessoa(email));
}

void ConsolePresentation::atualizarPessoa() {
    Email email = lerEmail("Email da pessoa para atualizar: ");
    Name nome = lerNome("Novo nome: ");
    Password senha = lerSenha("Nova senha: ");
    Role papel = lerPapel("Novo papel: ");

    servicePessoa_.atualizarPessoa(email, nome, senha, papel);
    std::cout << "Pessoa atualizada com sucesso." << std::endl;
}

void ConsolePresentation::removerPessoa() {
    Email email = lerEmail("Email da pessoa para remover: ");
    servicePessoa_.excluirPessoa(email);
    std::cout << "Pessoa removida com sucesso." << std::endl;
}

void ConsolePresentation::cadastrarProjeto() {
    Code codigo = lerCodigo("Codigo do projeto: ");
    Name nome = lerNome("Nome do projeto: ");
    Date inicio = lerData("Data de inicio (DD/MM/YYYY): ");
    Date fim = lerData("Data de termino (DD/MM/YYYY): ");
    Email scrum = lerEmail("Email do Scrum Master: ");

    serviceProjeto_.criarProjeto(codigo, nome, inicio, fim, scrum);
    std::cout << "Projeto cadastrado com sucesso." << std::endl;
}

void ConsolePresentation::buscarProjeto() {
    Code codigo = lerCodigo("Codigo do projeto para buscar: ");
    exibirProjeto(serviceProjeto_.lerProjeto(codigo));
}

void ConsolePresentation::atualizarProjeto() {
    Code codigo = lerCodigo("Codigo do projeto para atualizar: ");
    Name nome = lerNome("Novo nome: ");
    Date inicio = lerData("Nova data de inicio: ");
    Date fim = lerData("Nova data de termino: ");
    serviceProjeto_.atualizarProjeto(codigo, nome, inicio, fim);
    std::cout << "Projeto atualizado com sucesso." << std::endl;
}

void ConsolePresentation::removerProjeto() {
    Code codigo = lerCodigo("Codigo do projeto para remover: ");
    serviceProjeto_.excluirProjeto(codigo);
    std::cout << "Projeto removido com sucesso." << std::endl;
}

void ConsolePresentation::cadastrarPlanoSprint() {
    Code codigo = lerCodigo("Codigo do plano de sprint: ");
    Text objetivo = lerTexto("Objetivo: ");
    Time capacidade = lerTempo("Capacidade (dias): ");
    Code projeto = lerCodigo("Codigo do projeto associado: ");

    servicePlano_.criarPlanoDeSprint(codigo, objetivo, capacidade, projeto);
    std::cout << "Plano de sprint cadastrado com sucesso." << std::endl;
}

void ConsolePresentation::buscarPlanoSprint() {
    Code codigo = lerCodigo("Codigo do plano de sprint para buscar: ");
    exibirPlano(servicePlano_.lerPlanoDeSprint(codigo));
}

void ConsolePresentation::atualizarPlanoSprint() {
    Code codigo = lerCodigo("Codigo do plano de sprint para atualizar: ");
    Text objetivo = lerTexto("Novo objetivo: ");
    Time capacidade = lerTempo("Nova capacidade: ");
    servicePlano_.atualizarPlanoDeSprint(codigo, objetivo, capacidade);
    std::cout << "Plano de sprint atualizado com sucesso." << std::endl;
}

void ConsolePresentation::removerPlanoSprint() {
    Code codigo = lerCodigo("Codigo do plano de sprint para remover: ");
    servicePlano_.excluirPlanoDeSprint(codigo);
    std::cout << "Plano de sprint removido com sucesso." << std::endl;
}

void ConsolePresentation::cadastrarHistoria() {
    Code codigo = lerCodigo("Codigo da historia: ");
    Text title = lerTexto("Titulo: ");
    Text role = lerTexto("Papel: ");
    Text action = lerTexto("Acao: ");
    Text value = lerTexto("Valor: ");
    Time estimation = lerTempo("Estimativa (dias): ");
    Priority priority = lerPrioridade("Prioridade (ALTA, MEDIA, BAIXA): ");
    Code projeto = lerCodigo("Codigo do projeto associado: ");

    serviceHistoria_.criarHistoriaDeUsuario(codigo, title, role, action, value, estimation, priority, projeto);
    std::cout << "Historia de usuario cadastrada com sucesso." << std::endl;
}

void ConsolePresentation::buscarHistoria() {
    Code codigo = lerCodigo("Codigo da historia para buscar: ");
    exibirHistoria(serviceHistoria_.lerHistoriaDeUsuario(codigo));
}

void ConsolePresentation::atualizarHistoria() {
    Code codigo = lerCodigo("Codigo da historia para atualizar: ");
    Text title = lerTexto("Novo titulo: ");
    Text role = lerTexto("Novo papel: ");
    Text action = lerTexto("Nova acao: ");
    Text value = lerTexto("Novo valor: ");
    Time estimation = lerTempo("Nova estimativa: ");
    Priority priority = lerPrioridade("Nova prioridade: ");

    serviceHistoria_.atualizarHistoriaDeUsuario(codigo, title, role, action, value, estimation, priority);
    std::cout << "Historia de usuario atualizada com sucesso." << std::endl;
}

void ConsolePresentation::removerHistoria() {
    Code codigo = lerCodigo("Codigo da historia para remover: ");
    serviceHistoria_.excluirHistoriaDeUsuario(codigo);
    std::cout << "Historia de usuario removida com sucesso." << std::endl;
}

Email ConsolePresentation::lerEmail(const std::string& prompt) const {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);

    Email email;
    email.set(valor);
    return email;
}

Name ConsolePresentation::lerNome(const std::string& prompt) const {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);

    Name nome;
    nome.set(valor);
    return nome;
}

Password ConsolePresentation::lerSenha(const std::string& prompt) const {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);

    Password senha;
    senha.set(valor);
    return senha;
}

Role ConsolePresentation::lerPapel(const std::string& prompt) const {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);

    Role papel;
    papel.set(valor);
    return papel;
}

Code ConsolePresentation::lerCodigo(const std::string& prompt) const {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);

    Code codigo;
    codigo.set(valor);
    return codigo;
}

Date ConsolePresentation::lerData(const std::string& prompt) const {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);

    Date data;
    data.set(valor);
    return data;
}

Text ConsolePresentation::lerTexto(const std::string& prompt) const {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);

    Text texto;
    texto.set(valor);
    return texto;
}

Time ConsolePresentation::lerTempo(const std::string& prompt) const {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);

    Time tempo;
    tempo.set(valor);
    return tempo;
}

Priority ConsolePresentation::lerPrioridade(const std::string& prompt) const {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);

    Priority prioridade;
    prioridade.set(valor);
    return prioridade;
}

State ConsolePresentation::lerEstado(const std::string& prompt) const {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);

    State estado;
    estado.set(valor);
    return estado;
}

void ConsolePresentation::exibirPessoa(const Person& pessoa) const {
    std::cout << "Email: " << pessoa.getEmail().get() << std::endl;
    std::cout << "Nome: " << pessoa.getName().get() << std::endl;
    std::cout << "Role: " << pessoa.getRole().get() << std::endl;
}

void ConsolePresentation::exibirProjeto(const Project& projeto) const {
    std::cout << "Codigo: " << projeto.getCode().get() << std::endl;
    std::cout << "Nome: " << projeto.getName().get() << std::endl;
    std::cout << "Inicio: " << projeto.getBeginning().get() << std::endl;
    std::cout << "Termino: " << projeto.getEnding().get() << std::endl;
}

void ConsolePresentation::exibirPlano(const SprintPlan& plano) const {
    std::cout << "Codigo: " << plano.getCode().get() << std::endl;
    std::cout << "Objetivo: " << plano.getObjective().get() << std::endl;
    std::cout << "Capacidade: " << plano.getCapacity().get() << std::endl;
}

void ConsolePresentation::exibirHistoria(const UserStory& historia) const {
    std::cout << "Codigo: " << historia.getCode().get() << std::endl;
    std::cout << "Titulo: " << historia.getTitle().get() << std::endl;
    std::cout << "Prioridade: " << historia.getPriority().get() << std::endl;
    std::cout << "Estado: " << historia.getState().get() << std::endl;
}
