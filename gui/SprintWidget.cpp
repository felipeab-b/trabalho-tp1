#include "SprintWidget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>

SprintWidget::SprintWidget(ISprintPlanService& service, const QString& currentUserRole, QWidget *parent)
    : QWidget(parent), service_(service), currentProjectCode_(""), currentUserRole_(currentUserRole), codigoSelecionado_("") {
    setupUI();
}

void SprintWidget::setProjectCode(const QString& code) {
    currentProjectCode_ = code;
    if (!code.isEmpty()) {
        projetoInput_->setText(code);
    }
}

void SprintWidget::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    QHBoxLayout *inputLayout1 = new QHBoxLayout();
    inputLayout1->addWidget(new QLabel("Código:"));
    codigoInput_ = new QLineEdit();
    inputLayout1->addWidget(codigoInput_);
    
    inputLayout1->addWidget(new QLabel("Objetivo:"));
    objetivoInput_ = new QLineEdit();
    inputLayout1->addWidget(objetivoInput_);
    mainLayout->addLayout(inputLayout1);
    
    QHBoxLayout *inputLayout2 = new QHBoxLayout();
    inputLayout2->addWidget(new QLabel("Capacidade (dias):"));
    capacidadeInput_ = new QLineEdit();
    inputLayout2->addWidget(capacidadeInput_);
    
    inputLayout2->addWidget(new QLabel("Projeto:"));
    projetoInput_ = new QLineEdit();
    inputLayout2->addWidget(projetoInput_);
    mainLayout->addLayout(inputLayout2);
    
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnAdicionar_ = new QPushButton("Adicionar");
    btnAtualizar_ = new QPushButton("Atualizar");
    btnRemover_ = new QPushButton("Remover");
    btnBuscar_ = new QPushButton("Buscar");
    btnLimpar_ = new QPushButton("Limpar");
    
    btnLayout->addWidget(btnAdicionar_);
    btnLayout->addWidget(btnAtualizar_);
    btnLayout->addWidget(btnRemover_);
    btnLayout->addWidget(btnBuscar_);
    btnLayout->addWidget(btnLimpar_);
    mainLayout->addLayout(btnLayout);
    
    tabelaSprints_ = new QTableWidget();
    tabelaSprints_->setColumnCount(3);
    tabelaSprints_->setHorizontalHeaderLabels({"Código", "Objetivo", "Capacidade"});
    tabelaSprints_->horizontalHeader()->setStretchLastSection(true);
    tabelaSprints_->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabelaSprints_->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(tabelaSprints_);
    
    connect(btnAdicionar_, &QPushButton::clicked, this, &SprintWidget::onAdicionarClicked);
    connect(btnAtualizar_, &QPushButton::clicked, this, &SprintWidget::onAtualizarClicked);
    connect(btnRemover_, &QPushButton::clicked, this, &SprintWidget::onRemoverClicked);
    connect(btnBuscar_, &QPushButton::clicked, this, &SprintWidget::onBuscarClicked);
    connect(btnLimpar_, &QPushButton::clicked, this, &SprintWidget::onLimparClicked);
    connect(tabelaSprints_, &QTableWidget::itemSelectionChanged, this, &SprintWidget::onTabelaSelecao);
    
    aplicarPermissoes();
    setLayout(mainLayout);
}

void SprintWidget::aplicarPermissoes() {
    const bool isScrumMaster = currentUserRole_.toStdString() == "MESTRE SCRUM";
    btnAdicionar_->setEnabled(isScrumMaster);
    btnAtualizar_->setEnabled(isScrumMaster);
    btnRemover_->setEnabled(isScrumMaster);
}

void SprintWidget::onAdicionarClicked() {
    try {
        if (codigoInput_->text().isEmpty() || objetivoInput_->text().isEmpty() || 
            capacidadeInput_->text().isEmpty() || projetoInput_->text().isEmpty()) {
            exibirMensagem("Erro", "Preencha todos os campos.", false);
            return;
        }
        
        Code codigo;
        codigo.set(codigoInput_->text().toStdString());
        
        Text objetivo;
        objetivo.set(objetivoInput_->text().toStdString());
        
        Time capacidade;
        capacidade.set(capacidadeInput_->text().toStdString());
        
        QString projetoCode = projetoInput_->text();
        if (projetoCode.isEmpty() && !currentProjectCode_.isEmpty()) {
            projetoCode = currentProjectCode_;
        }

        if (projetoCode.isEmpty()) {
            exibirMensagem("Erro", "Selecione um projeto antes de criar o plano de sprint.", false);
            return;
        }

        Code projeto;
        projeto.set(projetoCode.toStdString());
        
        service_.criarPlanoDeSprint(codigo, objetivo, capacidade, projeto);
        exibirMensagem("Sucesso", "Plano de sprint adicionado com sucesso.");
        onLimparClicked();
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void SprintWidget::onAtualizarClicked() {
    try {
        if (codigoSelecionado_.isEmpty()) {
            exibirMensagem("Erro", "Selecione um plano para atualizar.", false);
            return;
        }
        
        Code codigo;
        codigo.set(codigoSelecionado_.toStdString());
        
        Text objetivo;
        objetivo.set(objetivoInput_->text().toStdString());
        
        Time capacidade;
        capacidade.set(capacidadeInput_->text().toStdString());
        
        service_.atualizarPlanoDeSprint(codigo, objetivo, capacidade);
        exibirMensagem("Sucesso", "Plano de sprint atualizado com sucesso.");
        onLimparClicked();
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void SprintWidget::onRemoverClicked() {
    try {
        if (codigoSelecionado_.isEmpty()) {
            exibirMensagem("Erro", "Selecione um plano para remover.", false);
            return;
        }
        
        Code codigo;
        codigo.set(codigoSelecionado_.toStdString());
        
        service_.excluirPlanoDeSprint(codigo);
        exibirMensagem("Sucesso", "Plano de sprint removido com sucesso.");
        onLimparClicked();
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void SprintWidget::onBuscarClicked() {
    try {
        if (codigoInput_->text().isEmpty()) {
            exibirMensagem("Erro", "Digite um código para buscar.", false);
            return;
        }
        
        Code codigo;
        codigo.set(codigoInput_->text().toStdString());
        
        SprintPlan plano = service_.lerPlanoDeSprint(codigo);
        tabelaSprints_->setRowCount(0);
        
        int row = tabelaSprints_->rowCount();
        tabelaSprints_->insertRow(row);
        
        tabelaSprints_->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(plano.getCode().get())));
        tabelaSprints_->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(plano.getObjective().get())));
        tabelaSprints_->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(plano.getCapacity().get())));
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void SprintWidget::onTabelaSelecao() {
    int row = tabelaSprints_->currentRow();
    if (row >= 0) {
        codigoSelecionado_ = tabelaSprints_->item(row, 0)->text();
        codigoInput_->setText(codigoSelecionado_);
        objetivoInput_->setText(tabelaSprints_->item(row, 1)->text());
        capacidadeInput_->setText(tabelaSprints_->item(row, 2)->text());
    }
}

void SprintWidget::onLimparClicked() {
    codigoInput_->clear();
    objetivoInput_->clear();
    capacidadeInput_->clear();
    projetoInput_->clear();
    if (!currentProjectCode_.isEmpty()) {
        projetoInput_->setText(currentProjectCode_);
    }
    tabelaSprints_->setRowCount(0);
    codigoSelecionado_ = "";
}

void SprintWidget::exibirMensagem(const QString& titulo, const QString& mensagem, bool sucesso) {
    if (sucesso) {
        QMessageBox::information(this, titulo, mensagem);
    } else {
        QMessageBox::warning(this, titulo, mensagem);
    }
}
