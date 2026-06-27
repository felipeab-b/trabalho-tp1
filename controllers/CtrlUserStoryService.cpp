#include "CtrlUserStoryService.hpp"

// 1. CRIAR HISTÓRIA DE USUÁRIO
void CntrServicoHistoriaUsuario::criarHistoriaDeUsuario(Code code, Text title, Text role, Text action,
                                                        Text value, Time estimation, Priority priority,
                                                        Code project) {
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
    
    // O estado inicial obrigatoriamente é "A FAZER".
    State estadoInicial;
    estadoInicial.set("A FAZER");
    // novaHistoria.setState(estadoInicial);
    
    // Associa ao projeto.
    // novaHistoria.setProject(project);

    containerHistorias.push_back(novaHistoria);
}

// 2. LER HISTÓRIA DE USUÁRIO
UserStory CntrServicoHistoriaUsuario::lerHistoriaDeUsuario(Code code) const {
    for (const auto& historia : containerHistorias) {
        if (historia.getCode().get() == code.get()) {
            return historia;
        }
    }
    throw std::invalid_argument("Erro: Historia de usuario nao encontrada.");
}

// 3. ATUALIZAR HISTÓRIA DE USUÁRIO
void CntrServicoHistoriaUsuario::atualizarHistoriaDeUsuario(Code code, Text title, Text role, Text action,
                                                            Text value, Time estimation, Priority priority) {
    for (auto& historia : containerHistorias) {
        if (historia.getCode().get() == code.get()) {
            historia.setTitle(title);
            historia.setRole(role);
            historia.setAction(action);
            historia.setValue(value);
            historia.setEstimation(estimation);
            historia.setPriority(priority);
            return;
        }
    }
    throw std::invalid_argument("Erro: Nao foi possivel atualizar. Historia de usuario nao encontrada.");
}

// 4. EXCLUIR HISTÓRIA DE USUÁRIO
void CntrServicoHistoriaUsuario::excluirHistoriaDeUsuario(Code code) {
    for (auto it = containerHistorias.begin(); it != containerHistorias.end(); ++it) {
        if (it->getCode().get() == code.get()) {
            containerHistorias.erase(it);
            return;
        }
    }
    throw std::invalid_argument("Erro: Nao foi possivel excluir. Historia de usuario nao encontrada.");
}

// 5. ASSOCIAR PESSOA À HISTÓRIA
void CntrServicoHistoriaUsuario::associarPessoaAHistoriaDeUsuario(Code userStory, Email person) {
    for (auto& historia : containerHistorias) {
        if (historia.getCode().get() == userStory.get()) {
            // historia.setDeveloper(person);
            return;
        }
    }
    throw std::invalid_argument("Erro: Historia de usuario nao encontrada para associacao.");
}

// 6. REMOVER ASSOCIAÇÃO
void CntrServicoHistoriaUsuario::removerAssociacaoPessoaHistoriaDeUsuario(Code userStory, Email person) {
    for (auto& historia : containerHistorias) {
        if (historia.getCode().get() == userStory.get()) {
            // Lógica para remover o desenvolvedor da história
            return;
        }
    }
    throw std::invalid_argument("Erro: Historia de usuario nao encontrada.");
}

// 7. LISTAR HISTÓRIAS DE PROJETO
std::vector<Code> CntrServicoHistoriaUsuario::listarHistoriasDeUsuarioDeProjeto(Code project) const {
    std::vector<Code> historiasDoProjeto;
    for (const auto& historia : containerHistorias) {
        // if (historia.getProject().get() == project.get()) {
        //     historiasDoProjeto.push_back(historia.getCode());
        // }
    }
    return historiasDoProjeto;
}

// 8. LISTAR HISTÓRIAS DE PLANO DE SPRINT
std::vector<Code> CntrServicoHistoriaUsuario::listarHistoriasDeUsuarioDePlanoDeSprint(Code sprintPlan) const {
    std::vector<Code> historiasDoPlano;
    for (const auto& historia : containerHistorias) {
        // if (historia.getSprintPlan().get() == sprintPlan.get()) {
        //     historiasDoPlano.push_back(historia.getCode());
        // }
    }
    return historiasDoPlano;
}

// 9. LISTAR HISTÓRIAS DE PESSOA
std::vector<Code> CntrServicoHistoriaUsuario::listarHistoriasDeUsuarioDePessoa(Email person) const {
    std::vector<Code> historiasDaPessoa;
    for (const auto& historia : containerHistorias) {
        // if (historia.getDeveloper().get() == person.get()) {
        //     historiasDaPessoa.push_back(historia.getCode());
        // }
    }
    return historiasDaPessoa;
}

// 10. MOVER HISTÓRIA PARA PLANO DE SPRINT
void CntrServicoHistoriaUsuario::moverHistoriaDeUsuarioParaPlanoDeSprint(Code userStory, Code project, Code sprintPlan) {
    for (auto& historia : containerHistorias) {
        if (historia.getCode().get() == userStory.get()) {
            // historia.setSprintPlan(sprintPlan);
            return;
        }
    }
    throw std::invalid_argument("Erro: Historia de usuario nao encontrada para mover.");
}

// 11. ALTERAR ESTADO DA HISTÓRIA
void CntrServicoHistoriaUsuario::alterarEstadoHistoriaDeUsuario(Code userStory, State state) {
    for (auto& historia : containerHistorias) {
        if (historia.getCode().get() == userStory.get()) {
            // historia.setState(state);
            return;
        }
    }
    throw std::invalid_argument("Erro: Historia de usuario nao encontrada para alterar estado.");
}