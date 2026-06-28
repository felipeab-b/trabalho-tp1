#include "controllers/CtrlPersonService.hpp"
#include "controllers/CtrlProjectService.hpp"
#include "controllers/CtrlSprintPlanService.hpp"
#include "controllers/CtrlUserStoryService.hpp"
#include "presentation/console_presentation.hpp"

#include <iostream>

int main() {
    try {
        CntrServicoPessoa servicePessoa("scrum.db");
        CntrServicoProjeto serviceProjeto("scrum.db");
        CntrServicoPlanoSprint servicePlano("scrum.db");
        CntrServicoHistoriaUsuario serviceHistoria("scrum.db");
        ConsolePresentation apresentacao(servicePessoa, serviceProjeto, servicePlano, serviceHistoria);
        apresentacao.run();
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}