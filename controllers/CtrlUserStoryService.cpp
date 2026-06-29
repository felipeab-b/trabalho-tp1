#include "CtrlUserStoryService.hpp"
#include <iostream>

CntrServicoHistoriaUsuario::CntrServicoHistoriaUsuario(const std::string& dbPath)
    : database_(dbPath) {
    inicializarBanco();
    carregarHistorias();
}

void CntrServicoHistoriaUsuario::inicializarBanco() {
    database_.execute(
        "CREATE TABLE IF NOT EXISTS historias_usuario ("
        "code TEXT PRIMARY KEY,"
        "title TEXT NOT NULL,"
        "role TEXT NOT NULL,"
        "action TEXT NOT NULL,"
        "value TEXT NOT NULL,"
        "estimation TEXT NOT NULL,"
        "priority TEXT NOT NULL,"
        "state TEXT NOT NULL,"
        "project TEXT,"
        "sprint_plan TEXT"
        ");"
    );
    database_.execute(
        "CREATE TABLE IF NOT EXISTS historias_associacoes ("
        "historia TEXT NOT NULL,"
        "pessoa TEXT NOT NULL"
        ");"
    );
}

void CntrServicoHistoriaUsuario::carregarHistorias() {
    auto rows = database_.query("SELECT code, title, role, action, value, estimation, priority, state, project, sprint_plan FROM historias_usuario ORDER BY code");
    for (const auto& row : rows) {
        if (row.size() < 10) {
            continue;
        }

        Code code;
        code.set(row[0]);

        UserStory historia(code);
        Text title; title.set(row[1]); historia.setTitle(title);
        Text role; role.set(row[2]); historia.setRole(role);
        Text action; action.set(row[3]); historia.setAction(action);
        Text value; value.set(row[4]); historia.setValue(value);
        Time estimation; estimation.set(row[5]); historia.setEstimation(estimation);
        Priority priority; priority.set(row[6]); historia.setPriority(priority);
        State state; state.set(row[7]); historia.setState(state);

        Code project; project.set(row[8]); historia.setProject(project);
        Code sprintPlan; sprintPlan.set(row[9]); historia.setSprintPlan(sprintPlan);

        containerHistorias.push_back(historia);
    }
}

void CntrServicoHistoriaUsuario::inserirHistoriaNoBanco(const UserStory& historia) {
    std::string sql = "INSERT INTO historias_usuario (code, title, role, action, value, estimation, priority, state, project, sprint_plan) VALUES ('" +
        escaparTexto(historia.getCode().get()) + "', '" +
        escaparTexto(historia.getTitle().get()) + "', '" +
        escaparTexto(historia.getRole().get()) + "', '" +
        escaparTexto(historia.getAction().get()) + "', '" +
        escaparTexto(historia.getValue().get()) + "', '" +
        escaparTexto(historia.getEstimation().get()) + "', '" +
        escaparTexto(historia.getPriority().get()) + "', '" +
        escaparTexto(historia.getState().get()) + "', '" +
        escaparTexto(historia.getProject().get()) + "', '" +
        escaparTexto(historia.getSprintPlan().get()) + "');";
    database_.execute(sql);
}

void CntrServicoHistoriaUsuario::atualizarHistoriaNoBanco(const UserStory& historia) {
    std::string sql = "UPDATE historias_usuario SET title='" +
        escaparTexto(historia.getTitle().get()) + "', role='" +
        escaparTexto(historia.getRole().get()) + "', action='" +
        escaparTexto(historia.getAction().get()) + "', value='" +
        escaparTexto(historia.getValue().get()) + "', estimation='" +
        escaparTexto(historia.getEstimation().get()) + "', priority='" +
        escaparTexto(historia.getPriority().get()) + "', state='" +
        escaparTexto(historia.getState().get()) + "', project='" +
        escaparTexto(historia.getProject().get()) + "', sprint_plan='" +
        escaparTexto(historia.getSprintPlan().get()) + "' WHERE code='" +
        escaparTexto(historia.getCode().get()) + "';";
    database_.execute(sql);
}

void CntrServicoHistoriaUsuario::removerHistoriaNoBanco(const std::string& code) {
    std::string sql = "DELETE FROM historias_usuario WHERE code='" + escaparTexto(code) + "';";
    database_.execute(sql);
}

void CntrServicoHistoriaUsuario::inserirAssociacao(const std::string& historia, const std::string& pessoa) {
    std::string sql = "INSERT INTO historias_associacoes (historia, pessoa) VALUES ('" +
        escaparTexto(historia) + "', '" + escaparTexto(pessoa) + "');";
    database_.execute(sql);
}

void CntrServicoHistoriaUsuario::removerAssociacao(const std::string& historia, const std::string& pessoa) {
    std::string sql = "DELETE FROM historias_associacoes WHERE historia='" +
        escaparTexto(historia) + "' AND pessoa='" + escaparTexto(pessoa) + "';";
    database_.execute(sql);
}

std::string CntrServicoHistoriaUsuario::escaparTexto(const std::string& valor) const {
    std::string resultado = valor;
    size_t pos = 0;
    while ((pos = resultado.find("'", pos)) != std::string::npos) {
        resultado.insert(pos, "'");
        pos += 2;
    }
    return resultado;
}

void CntrServicoHistoriaUsuario::validarPermissao(const std::string& operacao) const {
    if (currentUserRole_.empty()) {
        return;
    }

    if (operacao == "CRIAR HISTORIA DE USUARIO" || operacao == "ATUALIZAR HISTORIA DE USUARIO" || operacao == "EXCLUIR HISTORIA DE USUARIO") {
        if (currentUserRole_ != "PROPRIETARIO DE PRODUTO") {
            throw std::invalid_argument("Acesso Negado: Apenas Proprietario de Produto pode executar esta operacao.");
        }
        return;
    }

    if (operacao == "ESTABELECER ASSOCIACAO HISTORIA PESSOA" || operacao == "REMOVER ASSOCIACAO HISTORIA PESSOA" || operacao == "MOVER HISTORIA PARA PLANO") {
        if (currentUserRole_ != "MESTRE SCRUM") {
            throw std::invalid_argument("Acesso Negado: Apenas Mestre Scrum pode executar esta operacao.");
        }
        return;
    }

    if (operacao == "ALTERAR ESTADO HISTORIA" || operacao == "LER HISTORIA DE USUARIO" || operacao == "LISTAR HISTORIAS DE USUARIO DE PROJETO" || operacao == "LISTAR HISTORIAS DE USUARIO DE PLANO" || operacao == "LISTAR HISTORIAS DE USUARIO DE PESSOA") {
        if (currentUserRole_ != "PROPRIETARIO DE PRODUTO" && currentUserRole_ != "MESTRE SCRUM" && currentUserRole_ != "DESENVOLVEDOR") {
            throw std::invalid_argument("Acesso Negado: Seu papel nao tem permissao para executar esta operacao.");
        }
    }
}

void CntrServicoHistoriaUsuario::criarHistoriaDeUsuario(Code code, Text title, Text role, Text action,
                                                        Text value, Time estimation, Priority priority,
                                                        Code project) {
    validarPermissao("CRIAR HISTORIA DE USUARIO");

    for (const auto& historia : containerHistorias) {
        if (historia.getCode().get() == code.get()) {
            throw std::invalid_argument("Erro: Ja existe uma historia de usuario com este codigo.");
        }
    }

    UserStory novaHistoria(code);
    novaHistoria.setTitle(title);
    novaHistoria.setRole(role);
    novaHistoria.setAction(action);
    novaHistoria.setValue(value);
    novaHistoria.setEstimation(estimation);
    novaHistoria.setPriority(priority);
    novaHistoria.setProject(project); 

    State estadoInicial;
    estadoInicial.set("A FAZER");
    novaHistoria.setState(estadoInicial);

    containerHistorias.push_back(novaHistoria);
    inserirHistoriaNoBanco(novaHistoria);
}

UserStory CntrServicoHistoriaUsuario::lerHistoriaDeUsuario(Code code) const {
    validarPermissao("LER HISTORIA DE USUARIO");

    for (const auto& historia : containerHistorias) {
        if (historia.getCode().get() == code.get()) {
            return historia;
        }
    }
    throw std::invalid_argument("Erro: Historia de usuario nao encontrada.");
}

void CntrServicoHistoriaUsuario::atualizarHistoriaDeUsuario(Code code, Text title, Text role, Text action,
                                                            Text value, Time estimation, Priority priority) {
    validarPermissao("ATUALIZAR HISTORIA DE USUARIO");

    for (auto& historia : containerHistorias) {
        if (historia.getCode().get() == code.get()) {
            historia.setTitle(title);
            historia.setRole(role);
            historia.setAction(action);
            historia.setValue(value);
            historia.setEstimation(estimation);
            historia.setPriority(priority);
            atualizarHistoriaNoBanco(historia);
            return;
        }
    }
    throw std::invalid_argument("Erro: Nao foi possivel atualizar. Historia de usuario nao encontrada.");
}

void CntrServicoHistoriaUsuario::excluirHistoriaDeUsuario(Code code) {
    validarPermissao("EXCLUIR HISTORIA DE USUARIO");

    for (auto it = containerHistorias.begin(); it != containerHistorias.end(); ++it) {
        if (it->getCode().get() == code.get()) {
            removerHistoriaNoBanco(it->getCode().get());
            containerHistorias.erase(it);
            return;
        }
    }
    throw std::invalid_argument("Erro: Nao foi possivel excluir. Historia de usuario nao encontrada.");
}

void CntrServicoHistoriaUsuario::associarPessoaAHistoriaDeUsuario(Code userStory, Email person) {
    validarPermissao("ESTABELECER ASSOCIACAO HISTORIA PESSOA");

    auto rows = database_.query("SELECT historia FROM historias_associacoes WHERE historia='" + escaparTexto(userStory.get()) + "' AND pessoa='" + escaparTexto(person.get()) + "'");
    if (rows.empty()) {
        inserirAssociacao(userStory.get(), person.get());
        for (auto& historia : containerHistorias) {
            if (historia.getCode().get() == userStory.get()) {
                historia.setDeveloper(person);
                break;
            }
        }
    }
}

void CntrServicoHistoriaUsuario::removerAssociacaoPessoaHistoriaDeUsuario(Code userStory, Email person) {
    validarPermissao("REMOVER ASSOCIACAO HISTORIA PESSOA");

    removerAssociacao(userStory.get(), person.get());
    for (auto& historia : containerHistorias) {
        if (historia.getCode().get() == userStory.get()) {
            Email emailVazio;
            historia.setDeveloper(emailVazio);
            break;
        }
    }
}

std::vector<Code> CntrServicoHistoriaUsuario::listarHistoriasDeUsuarioDeProjeto(Code project) const {
    validarPermissao("LISTAR HISTORIAS DE USUARIO DE PROJETO");

    std::vector<Code> historiasDoProjeto;
    for (const auto& historia : containerHistorias) {
        if (historia.getProject().get() == project.get()) {
            historiasDoProjeto.push_back(historia.getCode());
        }
    }
    return historiasDoProjeto;
}

std::vector<Code> CntrServicoHistoriaUsuario::listarHistoriasDeUsuarioDePlanoDeSprint(Code sprintPlan) const {
    validarPermissao("LISTAR HISTORIAS DE USUARIO DE PLANO");

    std::vector<Code> historiasDoPlano;
    for (const auto& historia : containerHistorias) {
        if (historia.getSprintPlan().get() == sprintPlan.get()) {
            historiasDoPlano.push_back(historia.getCode());
        }
    }
    return historiasDoPlano;
}

std::vector<Code> CntrServicoHistoriaUsuario::listarHistoriasDeUsuarioDePessoa(Email person) const {
    validarPermissao("LISTAR HISTORIAS DE USUARIO DE PESSOA");

    std::vector<Code> historiasDaPessoa;
    std::vector<std::vector<std::string>> rows = database_.query("SELECT historia FROM historias_associacoes WHERE pessoa='" + escaparTexto(person.get()) + "'");
    for (const auto& row : rows) {
        if (!row.empty()) {
            Code code;
            code.set(row[0]);
            historiasDaPessoa.push_back(code);
        }
    }
    return historiasDaPessoa;
}

void CntrServicoHistoriaUsuario::moverHistoriaDeUsuarioParaPlanoDeSprint(Code userStory, Code project, Code sprintPlan) {
    validarPermissao("MOVER HISTORIA PARA PLANO");

    if (servicoPlanoSprint == nullptr) {
        throw std::logic_error("Erro Interno: Servico de Plano de Sprint nao conectado.");
    }

    SprintPlan planoDestino = servicoPlanoSprint->lerPlanoDeSprint(sprintPlan);
    int capacidadeMaxima = std::stoi(planoDestino.getCapacity().get());

    int somaEstimativasAtuais = 0;
    UserStory* historiaAlvo = nullptr;

    for (auto& historia : containerHistorias) {
        if (historia.getSprintPlan().get() == sprintPlan.get()) {
            somaEstimativasAtuais += std::stoi(historia.getEstimation().get());
        }
        if (historia.getCode().get() == userStory.get()) {
            historiaAlvo = &historia;
        }
    }

    if (historiaAlvo == nullptr) {
        throw std::invalid_argument("Erro: Historia de usuario nao encontrada.");
    }

    int estimativaNova = std::stoi(historiaAlvo->getEstimation().get());
    if ((somaEstimativasAtuais + estimativaNova) > capacidadeMaxima) {
        throw std::invalid_argument("Erro de Validacao: A estimativa dessa historia excede a capacidade restante do Plano de Sprint.");
    }

    historiaAlvo->setProject(project);
    historiaAlvo->setSprintPlan(sprintPlan);
    atualizarHistoriaNoBanco(*historiaAlvo);
}

void CntrServicoHistoriaUsuario::alterarEstadoHistoriaDeUsuario(Code userStory, State state) {
    validarPermissao("ALTERAR ESTADO HISTORIA");

    for (auto& historia : containerHistorias) {
        if (historia.getCode().get() == userStory.get()) {
            historia.setState(state);
            atualizarHistoriaNoBanco(historia);
            return;
        }
    }
    throw std::invalid_argument("Erro: Historia de usuario nao encontrada para alterar estado.");
}
