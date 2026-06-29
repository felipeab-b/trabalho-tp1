#include "CtrlSprintPlanService.hpp"
#include <ctime>
#include <cmath>
#include <iostream>

int calcularDiferencaDias(std::string dataInicio, std::string dataFim) {
    std::tm tmInicio = {};
    std::tm tmFim = {};

    tmInicio.tm_mday = std::stoi(dataInicio.substr(0, 2));
    tmInicio.tm_mon  = std::stoi(dataInicio.substr(3, 2)) - 1; 
    tmInicio.tm_year = std::stoi(dataInicio.substr(6, 4)) - 1900; 

    tmFim.tm_mday = std::stoi(dataFim.substr(0, 2));
    tmFim.tm_mon  = std::stoi(dataFim.substr(3, 2)) - 1;
    tmFim.tm_year = std::stoi(dataFim.substr(6, 4)) - 1900;

    std::time_t tempoInicio = std::mktime(&tmInicio);
    std::time_t tempoFim = std::mktime(&tmFim);

    double diferencaSegundos = std::difftime(tempoFim, tempoInicio);
    return std::round(diferencaSegundos / (60 * 60 * 24));
}

CntrServicoPlanoSprint::CntrServicoPlanoSprint(const std::string& dbPath)
    : database_(dbPath) {
    inicializarBanco();
    carregarPlanos();
}

void CntrServicoPlanoSprint::inicializarBanco() {
    database_.execute(
        "CREATE TABLE IF NOT EXISTS planos_sprint ("
        "code TEXT PRIMARY KEY,"
        "objective TEXT NOT NULL,"
        "capacity TEXT NOT NULL,"
        "project TEXT NOT NULL"
        ");"
    );
}

void CntrServicoPlanoSprint::carregarPlanos() {
    auto rows = database_.query("SELECT code, objective, capacity, project FROM planos_sprint ORDER BY code");
    for (const auto& row : rows) {
        if (row.size() < 4) {
            continue;
        }

        Code code;
        code.set(row[0]);

        SprintPlan plano(code);
        Text objective;
        objective.set(row[1]);
        plano.setObjective(objective);

        Time capacity;
        capacity.set(row[2]);
        plano.setCapacity(capacity);

        Code project;
        project.set(row[3]);
        plano.setProject(project);

        containerPlanos.push_back(plano);
    }
}

void CntrServicoPlanoSprint::inserirPlanoNoBanco(const SprintPlan& plano) {
    std::string sql = "INSERT INTO planos_sprint (code, objective, capacity, project) VALUES ('" +
        escaparTexto(plano.getCode().get()) + "', '" +
        escaparTexto(plano.getObjective().get()) + "', '" +
        escaparTexto(plano.getCapacity().get()) + "', '" +
        escaparTexto(plano.getProject().get()) + "');";
    database_.execute(sql);
}

void CntrServicoPlanoSprint::atualizarPlanoNoBanco(const SprintPlan& plano) {
    std::string sql = "UPDATE planos_sprint SET objective='" +
        escaparTexto(plano.getObjective().get()) + "', capacity='" +
        escaparTexto(plano.getCapacity().get()) + "' WHERE code='" +
        escaparTexto(plano.getCode().get()) + "';";
    database_.execute(sql);
}

void CntrServicoPlanoSprint::removerPlanoNoBanco(const std::string& code) {
    std::string sql = "DELETE FROM planos_sprint WHERE code='" + escaparTexto(code) + "';";
    database_.execute(sql);
}

std::string CntrServicoPlanoSprint::escaparTexto(const std::string& valor) const {
    std::string resultado = valor;
    size_t pos = 0;
    while ((pos = resultado.find("'", pos)) != std::string::npos) {
        resultado.insert(pos, "'");
        pos += 2;
    }
    return resultado;
}

void CntrServicoPlanoSprint::validarPermissao(const std::string& operacao) const {
    if (currentUserRole_.empty()) {
        return;
    }

    if (operacao == "CRIAR PLANO DE SPRINT" || operacao == "ATUALIZAR PLANO DE SPRINT" || operacao == "EXCLUIR PLANO DE SPRINT") {
        if (currentUserRole_ != "MESTRE SCRUM") {
            throw std::invalid_argument("Acesso Negado: Apenas Mestre Scrum pode executar esta operacao.");
        }
        return;
    }

    if (operacao == "LER PLANO DE SPRINT" || operacao == "LISTAR PLANOS DE SPRINT ASSOCIADOS A PROJETO") {
        if (currentUserRole_ != "PROPRIETARIO DE PRODUTO" && currentUserRole_ != "MESTRE SCRUM" && currentUserRole_ != "DESENVOLVEDOR") {
            throw std::invalid_argument("Acesso Negado: Seu papel nao tem permissao para executar esta operacao.");
        }
    }
}

void CntrServicoPlanoSprint::criarPlanoDeSprint(Code code, Text objective, Time capacity, Code project) {
    validarPermissao("CRIAR PLANO DE SPRINT");

    for (const auto& plano : containerPlanos) {
        if (plano.getCode().get() == code.get()) {
            throw std::invalid_argument("Erro: Ja existe um plano de sprint com este codigo.");
        }
    }

    if (servicoProjeto == nullptr) {
        throw std::logic_error("Erro do Sistema: Servico de Projeto nao foi conectado.");
    }

    Project projetoAssociado = servicoProjeto->lerProjeto(project);
    int diasDoProjeto = calcularDiferencaDias(projetoAssociado.getBeginning().get(), projetoAssociado.getEnding().get());

    int somaCapacidades = 0;
    for (const auto& plano : containerPlanos) {
        if (plano.getProject().get() == project.get()) {
            somaCapacidades += std::stoi(plano.getCapacity().get());
        }
    }

    int capacidadeNova = std::stoi(capacity.get());
    if ((somaCapacidades + capacidadeNova) > diasDoProjeto) {
        throw std::invalid_argument("Erro de Validacao: A capacidade total dos planos excede a duracao do projeto.");
    }

    SprintPlan novoPlano(code);
    novoPlano.setObjective(objective);
    novoPlano.setCapacity(capacity);
    novoPlano.setProject(project);

    containerPlanos.push_back(novoPlano);
    inserirPlanoNoBanco(novoPlano);
}

SprintPlan CntrServicoPlanoSprint::lerPlanoDeSprint(Code code) const {
    validarPermissao("LER PLANO DE SPRINT");

    for (const auto& plano : containerPlanos) {
        if (plano.getCode().get() == code.get()) {
            return plano;
        }
    }
    throw std::invalid_argument("Erro: Plano de sprint nao encontrado no sistema.");
}

void CntrServicoPlanoSprint::atualizarPlanoDeSprint(Code code, Text objective, Time capacity) {
    validarPermissao("ATUALIZAR PLANO DE SPRINT");

    for (auto& plano : containerPlanos) {
        if (plano.getCode().get() == code.get()) {
            plano.setObjective(objective);
            plano.setCapacity(capacity);
            atualizarPlanoNoBanco(plano);
            return;
        }
    }
    throw std::invalid_argument("Erro: Nao foi possivel atualizar. Plano de sprint nao encontrado.");
}

void CntrServicoPlanoSprint::excluirPlanoDeSprint(Code code) {
    validarPermissao("EXCLUIR PLANO DE SPRINT");

    for (auto it = containerPlanos.begin(); it != containerPlanos.end(); ++it) {
        if (it->getCode().get() == code.get()) {
            removerPlanoNoBanco(it->getCode().get());
            containerPlanos.erase(it);
            return;
        }
    }
    throw std::invalid_argument("Erro: Nao foi possivel excluir. Plano de sprint nao encontrado.");
}

std::vector<Code> CntrServicoPlanoSprint::listarPlanosDeSprintDeProjeto(Code project) const {
    validarPermissao("LISTAR PLANOS DE SPRINT ASSOCIADOS A PROJETO");

    std::vector<Code> planosDoProjeto;
    for (const auto& plano : containerPlanos) {
        if (plano.getProject().get() == project.get()) {
            planosDoProjeto.push_back(plano.getCode());
        }
    }
    return planosDoProjeto;
}