#include "MainWindow.hpp"
#include "PessoaWidget.hpp"
#include "ProjetoWidget.hpp"
#include "SprintWidget.hpp"
#include "HistoriaWidget.hpp"
#include <QVBoxLayout>
#include <QStatusBar>

MainWindow::MainWindow(CntrServicoPessoa* p, CntrServicoProjeto* proj, 
                       CntrServicoPlanoSprint* sprint, CntrServicoHistoriaUsuario* hist, 
                       const QString& currentUserEmail, QWidget *parent)
    : QMainWindow(parent),
      servicePessoa_(p),
      serviceProjeto_(proj),
      servicePlano_(sprint),
      serviceHistoria_(hist),
      currentUserEmail_(currentUserEmail) {
    
    createTabs();
    setupUI();
}

MainWindow::~MainWindow() {
    delete pessoaWidget_;
    delete projetoWidget_;
    delete sprintWidget_;
    delete historiaWidget_;
}

void MainWindow::createTabs() {
    tabWidget_ = new QTabWidget(this);
    
    // Passando os serviços injetados para cada widget
    pessoaWidget_ = new PessoaWidget(*servicePessoa_, this);
    projetoWidget_ = new ProjetoWidget(*serviceProjeto_, currentUserEmail_, this);
    sprintWidget_ = new SprintWidget(*servicePlano_, this);
    historiaWidget_ = new HistoriaWidget(*serviceHistoria_, this);

    connect(projetoWidget_, &ProjetoWidget::projetoSelecionado, this, &MainWindow::onProjetoSelecionado);
    
    tabWidget_->addTab(pessoaWidget_, "Pessoas");
    tabWidget_->addTab(projetoWidget_, "Projetos");
    tabWidget_->addTab(sprintWidget_, "Planos de Sprint");
    tabWidget_->addTab(historiaWidget_, "Histórias de Usuário");
}

void MainWindow::setupUI() {
    setWindowTitle("Sistema de Gerenciamento Scrum");
    setGeometry(100, 100, 1000, 700);
    setCentralWidget(tabWidget_);

    if (!currentUserEmail_.isEmpty()) {
        statusBar()->showMessage(QString("Usuário logado: %1").arg(currentUserEmail_));
    }
}

void MainWindow::onProjetoSelecionado(const QString& code) {
    currentProjectCode_ = code;
    sprintWidget_->setProjectCode(code);
    historiaWidget_->setProjectCode(code);
}