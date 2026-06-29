#include "ProjetoWidget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>

ProjetoWidget::ProjetoWidget(IProjectService& service, const QString& currentUserEmail, const QString& currentUserRole, QWidget *parent)
    : QWidget(parent), service_(service), currentUserEmail_(currentUserEmail), currentUserRole_(currentUserRole), codigoSelecionado_("") {
    setupUI();
}

void ProjetoWidget::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    QHBoxLayout *inputLayout1 = new QHBoxLayout();
    inputLayout1->addWidget(new QLabel("Código:"));
    codigoInput_ = new QLineEdit();
    inputLayout1->addWidget(codigoInput_);
    
    inputLayout1->addWidget(new QLabel("Nome:"));
    nomeInput_ = new QLineEdit();
    inputLayout1->addWidget(nomeInput_);
    mainLayout->addLayout(inputLayout1);
    
    QHBoxLayout *inputLayout2 = new QHBoxLayout();
    inputLayout2->addWidget(new QLabel("Data Início (DD/MM/YYYY):"));
    dataInicioInput_ = new QLineEdit();
    inputLayout2->addWidget(dataInicioInput_);
    
    inputLayout2->addWidget(new QLabel("Data Fim (DD/MM/YYYY):"));
    dataFimInput_ = new QLineEdit();
    inputLayout2->addWidget(dataFimInput_);
    mainLayout->addLayout(inputLayout2);
    
    QHBoxLayout *inputLayout3 = new QHBoxLayout();
    inputLayout3->addWidget(new QLabel("Scrum Master (Email):"));
    scrumInput_ = new QLineEdit();
    inputLayout3->addWidget(scrumInput_);
    mainLayout->addLayout(inputLayout3);
    
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
    
    tabelaProjetos_ = new QTableWidget();
    tabelaProjetos_->setColumnCount(4);
    tabelaProjetos_->setHorizontalHeaderLabels({"Código", "Nome", "Início", "Fim"});
    tabelaProjetos_->horizontalHeader()->setStretchLastSection(true);
    tabelaProjetos_->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabelaProjetos_->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(tabelaProjetos_);
    
    connect(btnAdicionar_, &QPushButton::clicked, this, &ProjetoWidget::onAdicionarClicked);
    connect(btnAtualizar_, &QPushButton::clicked, this, &ProjetoWidget::onAtualizarClicked);
    connect(btnRemover_, &QPushButton::clicked, this, &ProjetoWidget::onRemoverClicked);
    connect(btnBuscar_, &QPushButton::clicked, this, &ProjetoWidget::onBuscarClicked);
    connect(btnLimpar_, &QPushButton::clicked, this, &ProjetoWidget::onLimparClicked);
    connect(tabelaProjetos_, &QTableWidget::itemSelectionChanged, this, &ProjetoWidget::onTabelaSelecao);
    
    if (!currentUserEmail_.isEmpty()) {
        scrumInput_->setText(currentUserEmail_);
    }

    aplicarPermissoes();
    carregarProjetosDoUsuario();
    setLayout(mainLayout);
}

void ProjetoWidget::onAdicionarClicked() {
    try {
        if (codigoInput_->text().isEmpty() || nomeInput_->text().isEmpty() || 
            dataInicioInput_->text().isEmpty() || dataFimInput_->text().isEmpty()) {
            exibirMensagem("Erro", "Preencha todos os campos obrigatórios.", false);
            return;
        }

        if (currentUserEmail_.isEmpty()) {
            exibirMensagem("Erro", "Usuário não autenticado. Faça login para criar um projeto.", false);
            return;
        }
        
        Code codigo;
        codigo.set(codigoInput_->text().toStdString());
        
        Name nome;
        nome.set(nomeInput_->text().toStdString());
        
        Date dataInicio;
        dataInicio.set(dataInicioInput_->text().toStdString());
        
        Date dataFim;
        dataFim.set(dataFimInput_->text().toStdString());
        
        QString scrumEmail = scrumInput_->text();
        if (scrumEmail.isEmpty() && !currentUserEmail_.isEmpty()) {
            scrumEmail = currentUserEmail_;
        }

        if (scrumEmail.isEmpty()) {
            exibirMensagem("Erro", "Informe o email do Scrum Master.", false);
            return;
        }

        Email scrum;
        scrum.set(scrumEmail.toStdString());

        // O usuário logado, que precisa ter papel de Proprietário de Produto
        // (ver aplicarPermissoes), torna-se o Proprietário de Produto do projeto.
        Email proprietario;
        proprietario.set(currentUserEmail_.toStdString());
        
        service_.criarProjeto(codigo, nome, dataInicio, dataFim, proprietario, scrum);
        exibirMensagem("Sucesso", "Projeto associado ao usuário logado com sucesso.");
        emit projetoSelecionado(QString::fromStdString(codigo.get()));
        onLimparClicked();
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void ProjetoWidget::onAtualizarClicked() {
    try {
        if (codigoSelecionado_.isEmpty()) {
            exibirMensagem("Erro", "Selecione um projeto para atualizar.", false);
            return;
        }
        
        Code codigo;
        codigo.set(codigoSelecionado_.toStdString());
        
        Name nome;
        nome.set(nomeInput_->text().toStdString());
        
        Date dataInicio;
        dataInicio.set(dataInicioInput_->text().toStdString());
        
        Date dataFim;
        dataFim.set(dataFimInput_->text().toStdString());
        
        service_.atualizarProjeto(codigo, nome, dataInicio, dataFim);
        exibirMensagem("Sucesso", "Projeto atualizado com sucesso.");
        onLimparClicked();
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void ProjetoWidget::onRemoverClicked() {
    try {
        if (codigoSelecionado_.isEmpty()) {
            exibirMensagem("Erro", "Selecione um projeto para remover.", false);
            return;
        }
        
        Code codigo;
        codigo.set(codigoSelecionado_.toStdString());
        
        service_.excluirProjeto(codigo);
        exibirMensagem("Sucesso", "Projeto removido com sucesso.");
        onLimparClicked();
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void ProjetoWidget::onBuscarClicked() {
    try {
        if (codigoInput_->text().isEmpty()) {
            carregarProjetosDoUsuario();
            return;
        }
        
        Code codigo;
        codigo.set(codigoInput_->text().toStdString());
        
        Project projeto = service_.lerProjeto(codigo);
        tabelaProjetos_->setRowCount(0);
        
        int row = tabelaProjetos_->rowCount();
        tabelaProjetos_->insertRow(row);
        
        tabelaProjetos_->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(projeto.getCode().get())));
        tabelaProjetos_->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(projeto.getName().get())));
        tabelaProjetos_->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(projeto.getBeginning().get())));
        tabelaProjetos_->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(projeto.getEnding().get())));
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void ProjetoWidget::onTabelaSelecao() {
    int row = tabelaProjetos_->currentRow();
    if (row >= 0) {
        codigoSelecionado_ = tabelaProjetos_->item(row, 0)->text();
        codigoInput_->setText(codigoSelecionado_);
        nomeInput_->setText(tabelaProjetos_->item(row, 1)->text());
        dataInicioInput_->setText(tabelaProjetos_->item(row, 2)->text());
        dataFimInput_->setText(tabelaProjetos_->item(row, 3)->text());
        emit projetoSelecionado(codigoSelecionado_);
    }
}

void ProjetoWidget::onLimparClicked() {
    codigoInput_->clear();
    nomeInput_->clear();
    dataInicioInput_->clear();
    dataFimInput_->clear();
    scrumInput_->clear();
    if (!currentUserEmail_.isEmpty()) {
        scrumInput_->setText(currentUserEmail_);
    }
    tabelaProjetos_->setRowCount(0);
    codigoSelecionado_ = "";
    carregarProjetosDoUsuario();
}

void ProjetoWidget::aplicarPermissoes() {
    const bool isProductOwner = currentUserRole_.toStdString() == "PROPRIETARIO DE PRODUTO";
    btnAdicionar_->setEnabled(isProductOwner);
    btnAtualizar_->setEnabled(isProductOwner);
    btnRemover_->setEnabled(isProductOwner);
}

void ProjetoWidget::carregarProjetosDoUsuario() {
    tabelaProjetos_->setRowCount(0);

    if (currentUserEmail_.isEmpty()) {
        return;
    }

    try {
        Email pessoa;
        pessoa.set(currentUserEmail_.toStdString());

        auto projetos = service_.listarProjetosDePessoa(pessoa);
        for (const auto& codigo : projetos) {
            Project projeto = service_.lerProjeto(codigo);
            int row = tabelaProjetos_->rowCount();
            tabelaProjetos_->insertRow(row);
            tabelaProjetos_->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(projeto.getCode().get())));
            tabelaProjetos_->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(projeto.getName().get())));
            tabelaProjetos_->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(projeto.getBeginning().get())));
            tabelaProjetos_->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(projeto.getEnding().get())));
        }
    } catch (const std::exception&) {
        // Ignora se não houver projetos para o usuário atual.
    }
}

void ProjetoWidget::exibirMensagem(const QString& titulo, const QString& mensagem, bool sucesso) {
    if (sucesso) {
        QMessageBox::information(this, titulo, mensagem);
    } else {
        QMessageBox::warning(this, titulo, mensagem);
    }
}