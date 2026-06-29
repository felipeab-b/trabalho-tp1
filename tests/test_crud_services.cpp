#include "../controllers/CtrlProjectService.hpp"
#include "../controllers/CtrlSprintPlanService.hpp"
#include "../controllers/CtrlUserStoryService.hpp"
#include <cassert>
#include <cstdio>

int main() {
    std::remove("test_scrum.db");

    CntrServicoProjeto projetoService("test_scrum.db");
    CntrServicoPlanoSprint sprintService("test_scrum.db");
    CntrServicoHistoriaUsuario userStoryService("test_scrum.db");
    sprintService.setProjectService(&projetoService);
    projetoService.setSprintPlanService(&sprintService);
    projetoService.setUserStoryService(&userStoryService);
    userStoryService.setSprintPlanService(&sprintService);

    Code codeProjeto;
    codeProjeto.set("AB123");
    Name nameProjeto;
    nameProjeto.set("Projeto X");
    Date inicio;
    inicio.set("01/01/2026");
    Date fim;
    fim.set("31/12/2026");
    Email scrumMaster;
    scrumMaster.set("scrum@email.com");

    projetoService.setCurrentUser("po@email.com", "PROPRIETARIO DE PRODUTO");
    projetoService.criarProjeto(codeProjeto, nameProjeto, inicio, fim, scrumMaster);
    projetoService.setCurrentUser("po@email.com", "PROPRIETARIO DE PRODUTO");
    Project projeto = projetoService.lerProjeto(codeProjeto);
    assert(projeto.getCode().get() == "AB123");

    Code codeSprint;
    codeSprint.set("SP123");
    Text objective;
    objective.set("Objetivo do sprint");
    Time capacity;
    capacity.set("10");
    sprintService.setCurrentUser("scrum@email.com", "MESTRE SCRUM");
    sprintService.criarPlanoDeSprint(codeSprint, objective, capacity, codeProjeto);
    sprintService.setCurrentUser("scrum@email.com", "MESTRE SCRUM");
    SprintPlan sprint = sprintService.lerPlanoDeSprint(codeSprint);
    assert(sprint.getCode().get() == "SP123");

    Code codeHistoria;
    codeHistoria.set("US123");
    Text title;
    title.set("Titulo");
    Text role;
    role.set("Como usuario");
    Text action;
    action.set("Eu quero");
    Text value;
    value.set("Para obter valor");
    Time estimation;
    estimation.set("5");
    Priority priority;
    priority.set("ALTA");

    userStoryService.setCurrentUser("po@email.com", "PROPRIETARIO DE PRODUTO");
    userStoryService.criarHistoriaDeUsuario(codeHistoria, title, role, action, value, estimation, priority, codeProjeto);
    userStoryService.setCurrentUser("scrum@email.com", "MESTRE SCRUM");
    UserStory historia = userStoryService.lerHistoriaDeUsuario(codeHistoria);
    assert(historia.getCode().get() == "US123");

    Email developer;
    developer.set("dev@email.com");
    userStoryService.associarPessoaAHistoriaDeUsuario(codeHistoria, developer);
    UserStory historiaComDev = userStoryService.lerHistoriaDeUsuario(codeHistoria);
    assert(historiaComDev.getDeveloper().get() == "dev@email.com");

    userStoryService.removerAssociacaoPessoaHistoriaDeUsuario(codeHistoria, developer);
    UserStory historiaSemDev = userStoryService.lerHistoriaDeUsuario(codeHistoria);
    assert(historiaSemDev.getDeveloper().get().empty());

    userStoryService.moverHistoriaDeUsuarioParaPlanoDeSprint(codeHistoria, codeProjeto, codeSprint);
    UserStory historiaNoPlano = userStoryService.lerHistoriaDeUsuario(codeHistoria);
    assert(historiaNoPlano.getSprintPlan().get() == "SP123");

    State novoEstado;
    novoEstado.set("FEITO");
    userStoryService.alterarEstadoHistoriaDeUsuario(codeHistoria, novoEstado);
    UserStory historiaComEstado = userStoryService.lerHistoriaDeUsuario(codeHistoria);
    assert(historiaComEstado.getState().get() == "FEITO");

    return 0;
}
