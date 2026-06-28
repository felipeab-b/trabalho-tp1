#include "MainWindow.hpp"
#include "PessoaWidget.hpp"
#include "ProjetoWidget.hpp"
#include "SprintWidget.hpp"
#include "HistoriaWidget.hpp"
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      servicePessoa_(nullptr),
      serviceProjeto_(nullptr),
      servicePlano_(nullptr),
      serviceHistoria_(nullptr),
      pessoaWidget_(nullptr),
      projetoWidget_(nullptr),
      sprintWidget_(nullptr),
      historiaWidget_(nullptr) {
    
    try {
        initializeServices();
        createTabs();
        setupUI();
    } catch (const std::exception& ex) {
        QMessageBox::critical(this, "Erro de Inicialização", 
                            QString::fromStdString("Erro ao inicializar a aplicação: " + std::string(ex.what())));
    }
}

MainWindow::~MainWindow() {
    delete pessoaWidget_;
    delete projetoWidget_;
    delete sprintWidget_;
    delete historiaWidget_;
    delete servicePessoa_;
    delete serviceProjeto_;
    delete servicePlano_;
    delete serviceHistoria_;
}

void MainWindow::initializeServices() {
    servicePessoa_ = new CntrServicoPessoa("scrum.db");
    serviceProjeto_ = new CntrServicoProjeto("scrum.db");
    servicePlano_ = new CntrServicoPlanoSprint("scrum.db");
    serviceHistoria_ = new CntrServicoHistoriaUsuario("scrum.db");
}

void MainWindow::createTabs() {
    tabWidget_ = new QTabWidget(this);
    
    pessoaWidget_ = new PessoaWidget(*servicePessoa_, this);
    projetoWidget_ = new ProjetoWidget(*serviceProjeto_, this);
    sprintWidget_ = new SprintWidget(*servicePlano_, this);
    historiaWidget_ = new HistoriaWidget(*serviceHistoria_, this);
    
    tabWidget_->addTab(pessoaWidget_, "Pessoas");
    tabWidget_->addTab(projetoWidget_, "Projetos");
    tabWidget_->addTab(sprintWidget_, "Planos de Sprint");
    tabWidget_->addTab(historiaWidget_, "Histórias de Usuário");
}

void MainWindow::setupUI() {
    setWindowTitle("Sistema de Gerenciamento Scrum");
    setGeometry(100, 100, 1000, 700);
    setCentralWidget(tabWidget_);
}
