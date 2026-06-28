#include "../controllers/CtrlProjectService.hpp"
#include "../controllers/CtrlSprintPlanService.hpp"
#include "../controllers/CtrlUserStoryService.hpp"
#include <cassert>
#include <cstdio>

int main() {
    std::remove("test_scrum.db");

    CntrServicoProjeto projetoService;
    CntrServicoPlanoSprint sprintService;
    CntrServicoHistoriaUsuario userStoryService;

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

    projetoService.criarProjeto(codeProjeto, nameProjeto, inicio, fim, scrumMaster);
    Project projeto = projetoService.lerProjeto(codeProjeto);
    assert(projeto.getCode().get() == "AB123");

    Code codeSprint;
    codeSprint.set("SP123");
    Text objective;
    objective.set("Objetivo do sprint");
    Time capacity;
    capacity.set("10");
    projetoService.criarProjeto(codeProjeto, nameProjeto, inicio, fim, scrumMaster);

    sprintService.criarPlanoDeSprint(codeSprint, objective, capacity, codeProjeto);
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

    userStoryService.criarHistoriaDeUsuario(codeHistoria, title, role, action, value, estimation, priority, codeProjeto);
    UserStory historia = userStoryService.lerHistoriaDeUsuario(codeHistoria);
    assert(historia.getCode().get() == "US123");

    return 0;
}
