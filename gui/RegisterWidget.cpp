#include "RegisterWidget.hpp"
#include "../dominios/derivados/email.hpp"
#include "../dominios/derivados/name.hpp"
#include "../dominios/derivados/password.hpp"
#include "../dominios/derivados/role.hpp"

RegisterWidget::RegisterWidget(IPersonService& personService, QWidget *parent)
    : QWidget(parent), personService_(personService) {

    QVBoxLayout *layout = new QVBoxLayout(this);

    emailInput_ = new QLineEdit();
    emailInput_->setPlaceholderText("Email");
    layout->addWidget(emailInput_);

    nomeInput_ = new QLineEdit();
    nomeInput_->setPlaceholderText("Nome");
    layout->addWidget(nomeInput_);

    senhaInput_ = new QLineEdit();
    senhaInput_->setPlaceholderText("Senha");
    senhaInput_->setEchoMode(QLineEdit::Password);
    layout->addWidget(senhaInput_);

    papelCombo_ = new QComboBox();
    papelCombo_->addItem("DESENVOLVEDOR");
    papelCombo_->addItem("MESTRE SCRUM");
    papelCombo_->addItem("PROPRIETARIO DE PRODUTO");
    layout->addWidget(papelCombo_);

    btnRegistrar_ = new QPushButton("Registrar");
    layout->addWidget(btnRegistrar_);

    connect(btnRegistrar_, &QPushButton::clicked, this, &RegisterWidget::onRegistrarClicked);
}

void RegisterWidget::onRegistrarClicked() {
    try {
        Email email;
        email.set(emailInput_->text().toStdString());

        Name nome;
        nome.set(nomeInput_->text().toStdString());

        Password senha;
        senha.set(senhaInput_->text().toStdString());

        Role papel;
        papel.set(papelCombo_->currentText().toStdString());

        personService_.criarPessoa(email, nome, senha, papel);

        QMessageBox::information(this, "Sucesso", "Registro efetuado com sucesso.");
        emit registerSuccess(QString::fromStdString(email.get()));
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Erro", e.what());
    }
}
