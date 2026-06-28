#include "CtrlSprintPlanService.hpp"

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

        containerPlanos.push_back(plano);
    }
}

void CntrServicoPlanoSprint::inserirPlanoNoBanco(const SprintPlan& plano) {
    std::string sql = "INSERT INTO planos_sprint (code, objective, capacity, project) VALUES ('" +
        escaparTexto(plano.getCode().get()) + "', '" +
        escaparTexto(plano.getObjective().get()) + "', '" +
        escaparTexto(plano.getCapacity().get()) + "', '');";
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

void CntrServicoPlanoSprint::criarPlanoDeSprint(Code code, Text objective, Time capacity, Code project) {
    for (const auto& plano : containerPlanos) {
        if (plano.getCode().get() == code.get()) {
            throw std::invalid_argument("Erro: Ja existe um plano de sprint com este codigo.");
        }
    }

    SprintPlan novoPlano(code);
    novoPlano.setObjective(objective);
    novoPlano.setCapacity(capacity);

    containerPlanos.push_back(novoPlano);
    inserirPlanoNoBanco(novoPlano);
}

SprintPlan CntrServicoPlanoSprint::lerPlanoDeSprint(Code code) const {
    for (const auto& plano : containerPlanos) {
        if (plano.getCode().get() == code.get()) {
            return plano;
        }
    }
    throw std::invalid_argument("Erro: Plano de sprint nao encontrado no sistema.");
}

void CntrServicoPlanoSprint::atualizarPlanoDeSprint(Code code, Text objective, Time capacity) {
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
    std::vector<Code> planosDoProjeto;
    for (const auto& plano : containerPlanos) {
        planosDoProjeto.push_back(plano.getCode());
    }
    return planosDoProjeto;
}