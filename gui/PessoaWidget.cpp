#include "PessoaWidget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>
#include <QDebug>

PessoaWidget::PessoaWidget(IPersonService& service, QWidget *parent)
    : QWidget(parent), service_(service), emailSelecionado_("") {
    setupUI();
    carregarDados();
}

void PessoaWidget::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Grupo de entrada
    QHBoxLayout *inputLayout1 = new QHBoxLayout();
    inputLayout1->addWidget(new QLabel("Email:"));
    emailInput_ = new QLineEdit();
    inputLayout1->addWidget(emailInput_);
    
    inputLayout1->addWidget(new QLabel("Nome:"));
    nomeInput_ = new QLineEdit();
    inputLayout1->addWidget(nomeInput_);
    mainLayout->addLayout(inputLayout1);
    
    QHBoxLayout *inputLayout2 = new QHBoxLayout();
    inputLayout2->addWidget(new QLabel("Senha:"));
    senhaInput_ = new QLineEdit();
    senhaInput_->setEchoMode(QLineEdit::Password);
    inputLayout2->addWidget(senhaInput_);
    
    inputLayout2->addWidget(new QLabel("Papel:"));
    papelCombo_ = new QComboBox();
    papelCombo_->addItems({"DESENVOLVEDOR", "MESTRE SCRUM", "PROPRIETARIO DE PRODUTO"});
    inputLayout2->addWidget(papelCombo_);
    mainLayout->addLayout(inputLayout2);
    
    // Botões de ação
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
    
    // Tabela
    tabelaPessoas_ = new QTableWidget();
    tabelaPessoas_->setColumnCount(3);
    tabelaPessoas_->setHorizontalHeaderLabels({"Email", "Nome", "Papel"});
    tabelaPessoas_->horizontalHeader()->setStretchLastSection(true);
    tabelaPessoas_->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabelaPessoas_->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(tabelaPessoas_);
    
    // Conexões
    connect(btnAdicionar_, &QPushButton::clicked, this, &PessoaWidget::onAdicionarClicked);
    connect(btnAtualizar_, &QPushButton::clicked, this, &PessoaWidget::onAtualizarClicked);
    connect(btnRemover_, &QPushButton::clicked, this, &PessoaWidget::onRemoverClicked);
    connect(btnBuscar_, &QPushButton::clicked, this, &PessoaWidget::onBuscarClicked);
    connect(btnLimpar_, &QPushButton::clicked, this, &PessoaWidget::onLimparClicked);
    connect(tabelaPessoas_, &QTableWidget::itemSelectionChanged, this, &PessoaWidget::onTabelaSelecao);
    
    setLayout(mainLayout);
}

void PessoaWidget::carregarDados() {
    try {
        tabelaPessoas_->setRowCount(0);
        
        auto pessoas = service_.listarTodasAsPessoas(); 
        
        for (const auto& p : pessoas) {
            int row = tabelaPessoas_->rowCount();
            tabelaPessoas_->insertRow(row);
            
            tabelaPessoas_->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p.getEmail().get())));
            tabelaPessoas_->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p.getName().get())));
            tabelaPessoas_->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p.getRole().get())));
        }
    } catch (const std::exception& ex) {
        qDebug() << "Erro ao carregar dados:" << ex.what();
    }
}

void PessoaWidget::onAdicionarClicked() {
    try {
        if (emailInput_->text().isEmpty() || nomeInput_->text().isEmpty() || senhaInput_->text().isEmpty()) {
            exibirMensagem("Erro", "Preencha todos os campos.", false);
            return;
        }
        
        Email email;
        email.set(emailInput_->text().toStdString());
        
        Name nome;
        nome.set(nomeInput_->text().toStdString());
        
        Password senha;
        senha.set(senhaInput_->text().toStdString());
        
        Role papel;
        papel.set(papelCombo_->currentText().toStdString());
        
        service_.criarPessoa(email, nome, senha, papel);
        exibirMensagem("Sucesso", "Pessoa adicionada com sucesso.");

        onLimparClicked();
        carregarDados();
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void PessoaWidget::onAtualizarClicked() {
    try {
        if (emailSelecionado_.isEmpty()) {
            exibirMensagem("Erro", "Selecione uma pessoa para atualizar.", false);
            return;
        }
        
        Email email;
        email.set(emailSelecionado_.toStdString());
        
        Name nome;
        nome.set(nomeInput_->text().toStdString());
        
        Password senha;
        senha.set(senhaInput_->text().toStdString());
        
        Role papel;
        papel.set(papelCombo_->currentText().toStdString());
        
        service_.atualizarPessoa(email, nome, senha, papel);
        exibirMensagem("Sucesso", "Pessoa atualizada com sucesso.");
        onLimparClicked();
        carregarDados();
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void PessoaWidget::onRemoverClicked() {
    try {
        if (emailSelecionado_.isEmpty()) {
            exibirMensagem("Erro", "Selecione uma pessoa para remover.", false);
            return;
        }
        
        Email email;
        email.set(emailSelecionado_.toStdString());
        
        service_.excluirPessoa(email);
        exibirMensagem("Sucesso", "Pessoa removida com sucesso.");
        onLimparClicked();
        carregarDados();
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void PessoaWidget::onBuscarClicked() {
    try {
        QString filtro = emailInput_->text().trimmed();
        if (filtro.isEmpty()) {
            carregarDados();
            return;
        }
        
        Email email;
        email.set(filtro.toStdString());
        
        Person pessoa = service_.lerPessoa(email);
        tabelaPessoas_->setRowCount(0);
        
        int row = tabelaPessoas_->rowCount();
        tabelaPessoas_->insertRow(row);
        
        tabelaPessoas_->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(pessoa.getEmail().get())));
        tabelaPessoas_->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(pessoa.getName().get())));
        tabelaPessoas_->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(pessoa.getRole().get())));
    } catch (const std::exception& ex) {
        exibirMensagem("Erro", QString::fromStdString(ex.what()), false);
    }
}

void PessoaWidget::onTabelaSelecao() {
    int row = tabelaPessoas_->currentRow();
    if (row >= 0) {
        emailSelecionado_ = tabelaPessoas_->item(row, 0)->text();
        emailInput_->setText(emailSelecionado_);
        nomeInput_->setText(tabelaPessoas_->item(row, 1)->text());
        papelCombo_->setCurrentText(tabelaPessoas_->item(row, 2)->text());
    }
}

void PessoaWidget::onLimparClicked() {
    emailInput_->clear();
    nomeInput_->clear();
    senhaInput_->clear();
    papelCombo_->setCurrentIndex(0);
    emailSelecionado_ = "";
    carregarDados();
}

void PessoaWidget::exibirMensagem(const QString& titulo, const QString& mensagem, bool sucesso) {
    if (sucesso) {
        QMessageBox::information(this, titulo, mensagem);
    } else {
        QMessageBox::warning(this, titulo, mensagem);
    }
}
