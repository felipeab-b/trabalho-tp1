#include <QApplication>
#include "gui/MainWindow.hpp"
#include "controllers/CtrlPersonService.hpp"
#include "controllers/CtrlProjectService.hpp"
#include "controllers/CtrlSprintPlanService.hpp"
#include "controllers/CtrlUserStoryService.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    CntrServicoPessoa servicoPessoa("scrum.db");
    CntrServicoProjeto servicoProjeto("scrum.db");
    CntrServicoPlanoSprint servicoPlanoSprint("scrum.db");
    CntrServicoHistoriaUsuario servicoHistoriaUsuario("scrum.db");

    servicoProjeto.setSprintPlanService(&servicoPlanoSprint);
    servicoProjeto.setUserStoryService(&servicoHistoriaUsuario);
    servicoPlanoSprint.setProjectService(&servicoProjeto);
    servicoHistoriaUsuario.setSprintPlanService(&servicoPlanoSprint);

    MainWindow window(&servicoPessoa, &servicoProjeto, &servicoPlanoSprint, &servicoHistoriaUsuario);
    window.show();
    
    return app.exec();
}