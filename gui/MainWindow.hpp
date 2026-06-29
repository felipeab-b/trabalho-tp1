#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTabWidget>
#include "../controllers/CtrlPersonService.hpp"
#include "../controllers/CtrlProjectService.hpp"
#include "../controllers/CtrlSprintPlanService.hpp"
#include "../controllers/CtrlUserStoryService.hpp"

class PessoaWidget;
class ProjetoWidget;
class SprintWidget;
class HistoriaWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(CntrServicoPessoa* p, CntrServicoProjeto* proj,
               CntrServicoPlanoSprint* sprint, CntrServicoHistoriaUsuario* hist,
               const QString& currentUserEmail = QString(),
               QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onProjetoSelecionado(const QString& code);

private:
    QTabWidget *tabWidget_;

    CntrServicoPessoa *servicePessoa_;
    CntrServicoProjeto *serviceProjeto_;
    CntrServicoPlanoSprint *servicePlano_;
    CntrServicoHistoriaUsuario *serviceHistoria_;

    PessoaWidget *pessoaWidget_;
    ProjetoWidget *projetoWidget_;
    SprintWidget *sprintWidget_;
    HistoriaWidget *historiaWidget_;

    QString currentUserEmail_;
    QString currentUserRole_;
    QString currentProjectCode_;

    void createTabs();
    void setupUI();
};

#endif
