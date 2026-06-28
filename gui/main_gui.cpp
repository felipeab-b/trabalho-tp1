#include <QApplication>
#include "gui/MainWindow.hpp"
#include "gui/AuthWidget.hpp"
#include "controllers/CtrlPersonService.hpp"
#include "entidades/person.hpp"
#include "dominios/derivados/email.hpp"
#include <QMessageBox>
#include "controllers/CtrlProjectService.hpp"
#include "controllers/CtrlSprintPlanService.hpp"
#include "controllers/CtrlUserStoryService.hpp"
#include "controllers/CtrlAuthService.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    CntrServicoPessoa servicoPessoa("scrum.db");
    CntrServicoProjeto servicoProjeto("scrum.db");
    CntrServicoPlanoSprint servicoPlanoSprint("scrum.db");
    CntrServicoHistoriaUsuario servicoHistoriaUsuario("scrum.db");
    
    CntrAuthService authService(&servicoPessoa); 

    servicoProjeto.setSprintPlanService(&servicoPlanoSprint);
    servicoProjeto.setUserStoryService(&servicoHistoriaUsuario);
    servicoPlanoSprint.setProjectService(&servicoProjeto);
    servicoHistoriaUsuario.setSprintPlanService(&servicoPlanoSprint);

    // We'll show an auth widget first (login/register). After successful login we construct the main window
    AuthWidget authWidget(authService, servicoPessoa);

    QObject::connect(&authWidget, &AuthWidget::loginSucesso, [&](const QString& email){
        // Obtain the person object and then construct/show main window with services
        try {
            Email e;
            e.set(email.toStdString());
            Person pessoa = servicoPessoa.lerPessoa(e);

            MainWindow *window = new MainWindow(&servicoPessoa, &servicoProjeto, &servicoPlanoSprint, &servicoHistoriaUsuario, email);
            // MainWindow stores the current user email; further propagation to widgets can be implemented as needed
            window->show();
            authWidget.close();
        } catch (const std::exception& ex) {
            QMessageBox::warning(nullptr, "Erro", ex.what());
        }
    });

    authWidget.show();
    
    return app.exec();
}