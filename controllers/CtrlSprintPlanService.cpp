#include "CtrlSprintPlanService.hpp"

// 1. CRIAR PLANO DE SPRINT
void CntrServicoPlanoSprint::criarPlanoDeSprint(Code code, Text objective, Time capacity, Code project) {
    // Verifica se já existe um plano com este código (chave primária)
    for (const auto& plano : containerPlanos) {
        if (plano.getCode().get() == code.get()) {
            throw std::invalid_argument("Erro: Ja existe um plano de sprint com este codigo.");
        }
    }

    // Instancia a classe usando o construtor da Entidade
    SprintPlan novoPlano(code);
    
    // Seta os atributos restantes
    novoPlano.setObjective(objective);
    novoPlano.setCapacity(capacity);
    
    // IMPORTANTE: O plano precisa armazenar o projeto associado a ele.
    // Descomente e ajuste a linha abaixo conforme o que você codou no sprintplan.hpp
    // novoPlano.setProject(project);

    // Guarda no nosso contêiner em memória
    containerPlanos.push_back(novoPlano);
}

// 2. LER PLANO DE SPRINT
SprintPlan CntrServicoPlanoSprint::lerPlanoDeSprint(Code code) const {
    for (const auto& plano : containerPlanos) {
        if (plano.getCode().get() == code.get()) {
            return plano;
        }
    }
    throw std::invalid_argument("Erro: Plano de sprint nao encontrado no sistema.");
}

// 3. ATUALIZAR PLANO DE SPRINT
void CntrServicoPlanoSprint::atualizarPlanoDeSprint(Code code, Text objective, Time capacity) {
    for (auto& plano : containerPlanos) {
        if (plano.getCode().get() == code.get()) {
            // A chave primária (código) está blindada
            plano.setObjective(objective);
            plano.setCapacity(capacity);
            return; 
        }
    }
    throw std::invalid_argument("Erro: Nao foi possivel atualizar. Plano de sprint nao encontrado.");
}

// 4. EXCLUIR PLANO DE SPRINT
void CntrServicoPlanoSprint::excluirPlanoDeSprint(Code code) {
    for (auto it = containerPlanos.begin(); it != containerPlanos.end(); ++it) {
        if (it->getCode().get() == code.get()) {
            containerPlanos.erase(it); 
            return; 
        }
    }
    throw std::invalid_argument("Erro: Nao foi possivel excluir. Plano de sprint nao encontrado.");
}

// 5. LISTAR PLANOS DE SPRINT DE PROJETO
std::vector<Code> CntrServicoPlanoSprint::listarPlanosDeSprintDeProjeto(Code project) const {
    std::vector<Code> planosDoProjeto;
    
    for (const auto& plano : containerPlanos) {
        // Ajuste o getter de acordo com a sua entidade SprintPlan
        // if (plano.getProject().get() == project.get()) {
        //     planosDoProjeto.push_back(plano.getCode());
        // }
    }
    
    return planosDoProjeto;
}