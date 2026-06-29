#include "HistoriaWidget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>

HistoriaWidget::HistoriaWidget(IUserStoryService& service, const QString& currentUserRole, QWidget *parent)
    : QWidget(parent), service_(service), currentProjectCode_(""), currentUserRole_(currentUserRole), codigoSelecionado_("") {
    setupUI();
}

void HistoriaWidget::setProjectCode(const QString& code) {
    currentProjectCode_ = code;
    if (!code.isEmpty()) {
        projetoInput_->setText(code);
    }
}

void HistoriaWidget::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    QHBoxLayout *inputLayout1 = new QHBoxLayout();
    inputLayout1->addWidget(new QLabel("Código:"));
    codigoInput_ = new QLineEdit();
    inputLayout1->addWidget(codigoInput_);
    
    inputLayout1->addWidget(new QLabel("Título:"));
    tituloInput_ = new QLineEdit();
    inputLayout1->addWidget(tituloInput_);
    mainLayout->addLayout(inputLayout1);
    
    QHBoxLayout *inputLayout2 = new QHBoxLayout();
    inputLayout2->addWidget(new QLabel("Papel:"));
    papelInput_ = new QLineEdit();
    inputLayout2->addWidget(papelInput_);
    
    inputLayout2->addWidget(new QLabel("Ação:"));
    acaoInput_ = new QLineEdit();
    inputLayout2->addWidget(acaoInput_);
    mainLayout->addLayout(inputLayout2);
    
    QHBoxLayout *inputLayout3 = new QHBoxLayout();
    inputLayout3->addWidget(new QLabel("Valor:"));
    valorInput_ = new QLineEdit();
    inputLayout3->addWidget(valorInput_);
    
    inputLayout3->addWidget(new QLabel("Estimativa (dias):"));
    estimativaInput_ = new QLineEdit();
    inputLayout3->addWidget(estimativaInput_);
    mainLayout->addLayout(inputLayout3);
    
    QHBoxLayout *inputLayout4 = new QHBoxLayout();
    inputLayout4->addWidget(new QLabel("Prioridade:"));
    prioridadeCombo_ = new QComboBox();
    prioridadeCombo_->addItems({"ALTA", "MEDIA", "BAIXA"});
    inputLayout4->addWidget(prioridadeCombo_);
    
    inputLayout4->addWidget(new QLabel("Projeto:"));
    projetoInput_ = new QLineEdit();
    inputLayout4->addWidget(projetoInput_);
    mainLayout->addLayout(inputLayout4);
    
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

    QHBoxLayout *workflowLayout = new QHBoxLayout();
    workflowLayout->addWidget(new QLabel("Desenvolvedor:"));
    desenvolvedorInput_ = new QLineEdit();
    workflowLayout->addWidget(desenvolvedorInput_);

    workflowLayout->addWidget(new QLabel("Plano Sprint:"));
    planoSprintInput_ = new QLineEdit();
    workflowLayout->addWidget(planoSprintInput_);

    workflowLayout->addWidget(new QLabel("Estado:"));
    estadoCombo_ = new QComboBox();
    estadoCombo_->addItems({"A FAZER", "FAZENDO", "FEITO"});
    workflowLayout->addWidget(estadoCombo_);
    mainLayout->addLayout(workflowLayout);

    QHBoxLayout *btnWorkflowLayout = new QHBoxLayout();
    btnAssociar_ = new QPushButton("Associar pessoa");
    btnRemoverAssociacao_ = new QPushButton("Remover associação");
    btnMoverSprint_ = new QPushButton("Mover para sprint");
    btnAlterarEstado_ = new QPushButton("Alterar estado");

    btnWorkflowLayout->addWidget(btnAssociar_);
    btnWorkflowLayout->addWidget(btnRemoverAssociacao_);
    btnWorkflowLayout->addWidget(btnMoverSprint_);
    btnWorkflowLayout->addWidget(btnAlterarEstado_);
    mainLayout->addLayout(btnWorkflowLayout);
    
    tabelaHistorias_ = new QTableWidget();
    tabelaHistorias_->setColumnCount(4);
    tabelaHistorias_->setHorizontalHeaderLabels({"Código", "Título", "Prioridade", "Estimativa"});
    tabelaHistorias_->horizontalHeader()->setStretchLastSection(true);
    tabelaHistorias_->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabelaHistorias_->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(tabelaHistorias_);
    
    connect(btnAdicionar_, &QPushButton::clicked, this, &HistoriaWidget::onAdicionarClicked);
    connect(btnAtualizar_, &QPushButton::clicked, this, &HistoriaWidget::onAtualizarClicked);
    connect(btnRemover_, &QPushButton::clicked, this, &HistoriaWidget::onRemoverClicked);
    connect(btnBuscar_, &QPushButton::clicked, this, &HistoriaWidget::onBuscarClicked);
    connect(btnAssociar_, &QPushButton::clicked, this, &HistoriaWidget::onAssociarClicked);
    connect(btnRemoverAssociacao_, &QPushButton::clicked, this, &HistoriaWidget::onRemoverAssociacaoClicked);
    connect(btnMoverSprint_, &QPushButton::clicked, this, &HistoriaWidget::onMoverSprintClicked);
    connect(btnAlterarEstado_, &QPushButton::clicked, this, &HistoriaWidget::onAlterarEstadoClicked);
    connect(btnLimpar_, &QPushButton::clicked, this, &HistoriaWidget::onLimparClicked);
    connect(tabelaHistorias_, &QTableWidget::itemSelectionChanged, this, &HistoriaWidget::onTabelaSelecao);
    
    aplicarPermissoes();
    setLayout(mainLayout);
}

void HistoriaWidget::aplicarPermissoes() {
    const bool isProductOwner = currentUserRole_.toStdString() == "PROPRIETARIO DE PRODUTO";
    btnAdicionar_->setEnabled(isProductOwner);
    btnAtualizar_->setEnabled(isProductOwner);
    btnRemover_->setEnabled(isProductOwner);

    const bool isScrumMaster = currentUserRole_.toStdString() == "MESTRE SCRUM";
    btnAssociar_->setEnabled(isScrumMaster);
    btnRemoverAssociacao_->setEnabled(isScrumMaster);
    btnMoverSprint_->setEnabled(isScrumMaster);
    btnAlterarEstado_->setEnabled(isScrumMaster);
}

void HistoriaWidget::onAdicionarClicked() {
    try {
        if (codigoInput_->text().isEmpty() || tituloInput_->text().isEmpty() || 
            papelInput_->text().isEmpty() || acaoInput_->text().isEmpty() ||
            valorInput_->text().isEmpty() || estimativaInput_->text().isEmpty() ||
            projetoInput_->text().isEmpty()) {
            exibirMensagem("Erro", "Preencha todos os campos.", false);
            return;
        }
        
        Code codigo;
        codigo.set(codigoInput_->text().toStdString());
        
        Text titulo;
        titulo.set(tituloInput_->text().toStdString());
        
        Text papel;
        papel.set(papelInput_->text().toStdString());
        
        Text acao;
        acao.set(acaoInput_->text().toStdString());
        
        Text valor;
        valor.set(valorInput_->text().toStdString());
        
        Time estimativa;
        estimativa.set(estimativaInput_->text().toStdString());
        
        Priority prioridade;
        prioridade.set(prioridadeCombo_->currentText().toStdString());
        
        QString projetoCode = projetoInput_->text();
        if (projetoCode.isEmpty() && !currentProjectCode_.isEmpty()) {
            projetoCode = currentProjectCode_;
        }

        if (projetoCode.isEmpty()) {
            exibirMensagem("Erro", "Selecione um projeto antes de criar a história.", false);
            return;
        }

        Code projeto;
        projeto.set(projetoCode.toStdString());
        
        service_.criarHistoriaDeUsuario(codigo, titulo, papel, acao, valor, estimativa, prioridade, projeto);
        exibirMensagem("Sucesso", "História adicionada com sucesso.");
        onLimparClicked();
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void HistoriaWidget::onAtualizarClicked() {
    try {
        if (codigoSelecionado_.isEmpty()) {
            exibirMensagem("Erro", "Selecione uma história para atualizar.", false);
            return;
        }
        
        Code codigo;
        codigo.set(codigoSelecionado_.toStdString());
        
        Text titulo;
        titulo.set(tituloInput_->text().toStdString());
        
        Text papel;
        papel.set(papelInput_->text().toStdString());
        
        Text acao;
        acao.set(acaoInput_->text().toStdString());
        
        Text valor;
        valor.set(valorInput_->text().toStdString());
        
        Time estimativa;
        estimativa.set(estimativaInput_->text().toStdString());
        
        Priority prioridade;
        prioridade.set(prioridadeCombo_->currentText().toStdString());
        
        service_.atualizarHistoriaDeUsuario(codigo, titulo, papel, acao, valor, estimativa, prioridade);
        exibirMensagem("Sucesso", "História atualizada com sucesso.");
        onLimparClicked();
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void HistoriaWidget::onRemoverClicked() {
    try {
        if (codigoSelecionado_.isEmpty()) {
            exibirMensagem("Erro", "Selecione uma história para remover.", false);
            return;
        }
        
        Code codigo;
        codigo.set(codigoSelecionado_.toStdString());
        
        service_.excluirHistoriaDeUsuario(codigo);
        exibirMensagem("Sucesso", "História removida com sucesso.");
        onLimparClicked();
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void HistoriaWidget::onBuscarClicked() {
    try {
        if (codigoInput_->text().isEmpty()) {
            exibirMensagem("Erro", "Digite um código para buscar.", false);
            return;
        }
        
        Code codigo;
        codigo.set(codigoInput_->text().toStdString());
        
        UserStory historia = service_.lerHistoriaDeUsuario(codigo);
        tabelaHistorias_->setRowCount(0);
        
        int row = tabelaHistorias_->rowCount();
        tabelaHistorias_->insertRow(row);
        
        tabelaHistorias_->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(historia.getCode().get())));
        tabelaHistorias_->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(historia.getTitle().get())));
        tabelaHistorias_->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(historia.getPriority().get())));
        tabelaHistorias_->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(historia.getEstimation().get())));
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void HistoriaWidget::onAssociarClicked() {
    try {
        if (codigoSelecionado_.isEmpty() || desenvolvedorInput_->text().isEmpty()) {
            exibirMensagem("Erro", "Selecione uma história e informe um desenvolvedor.", false);
            return;
        }

        Code codigo;
        codigo.set(codigoSelecionado_.toStdString());

        Email desenvolvedor;
        desenvolvedor.set(desenvolvedorInput_->text().toStdString());

        service_.associarPessoaAHistoriaDeUsuario(codigo, desenvolvedor);
        exibirMensagem("Sucesso", "Pessoa associada com sucesso.");
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void HistoriaWidget::onRemoverAssociacaoClicked() {
    try {
        if (codigoSelecionado_.isEmpty() || desenvolvedorInput_->text().isEmpty()) {
            exibirMensagem("Erro", "Selecione uma história e informe o desenvolvedor a remover.", false);
            return;
        }

        Code codigo;
        codigo.set(codigoSelecionado_.toStdString());

        Email desenvolvedor;
        desenvolvedor.set(desenvolvedorInput_->text().toStdString());

        service_.removerAssociacaoPessoaHistoriaDeUsuario(codigo, desenvolvedor);
        exibirMensagem("Sucesso", "Associação removida com sucesso.");
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void HistoriaWidget::onMoverSprintClicked() {
    try {
        if (codigoSelecionado_.isEmpty() || projetoInput_->text().isEmpty() || planoSprintInput_->text().isEmpty()) {
            exibirMensagem("Erro", "Selecione uma história, informe o projeto e o plano de sprint.", false);
            return;
        }

        Code codigo;
        codigo.set(codigoSelecionado_.toStdString());

        Code projeto;
        projeto.set(projetoInput_->text().toStdString());

        Code plano;
        plano.set(planoSprintInput_->text().toStdString());

        service_.moverHistoriaDeUsuarioParaPlanoDeSprint(codigo, projeto, plano);
        exibirMensagem("Sucesso", "História movida para o plano de sprint com sucesso.");
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void HistoriaWidget::onAlterarEstadoClicked() {
    try {
        if (codigoSelecionado_.isEmpty()) {
            exibirMensagem("Erro", "Selecione uma história para alterar o estado.", false);
            return;
        }

        Code codigo;
        codigo.set(codigoSelecionado_.toStdString());

        State estado;
        estado.set(estadoCombo_->currentText().toStdString());

        service_.alterarEstadoHistoriaDeUsuario(codigo, estado);
        exibirMensagem("Sucesso", "Estado da história atualizado com sucesso.");
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void HistoriaWidget::onTabelaSelecao() {
    int row = tabelaHistorias_->currentRow();
    if (row >= 0) {
        codigoSelecionado_ = tabelaHistorias_->item(row, 0)->text();
        codigoInput_->setText(codigoSelecionado_);
        tituloInput_->setText(tabelaHistorias_->item(row, 1)->text());
        prioridadeCombo_->setCurrentText(tabelaHistorias_->item(row, 2)->text());
        estimativaInput_->setText(tabelaHistorias_->item(row, 3)->text());
    }
}

void HistoriaWidget::onLimparClicked() {
    codigoInput_->clear();
    tituloInput_->clear();
    papelInput_->clear();
    acaoInput_->clear();
    valorInput_->clear();
    estimativaInput_->clear();
    projetoInput_->clear();
    desenvolvedorInput_->clear();
    planoSprintInput_->clear();
    if (!currentProjectCode_.isEmpty()) {
        projetoInput_->setText(currentProjectCode_);
    }
    prioridadeCombo_->setCurrentIndex(0);
    estadoCombo_->setCurrentIndex(0);
    tabelaHistorias_->setRowCount(0);
    codigoSelecionado_ = "";
}

void HistoriaWidget::exibirMensagem(const QString& titulo, const QString& mensagem, bool sucesso) {
    if (sucesso) {
        QMessageBox::information(this, titulo, mensagem);
    } else {
        QMessageBox::warning(this, titulo, mensagem);
    }
}
