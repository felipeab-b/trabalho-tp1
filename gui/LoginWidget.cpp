#include "LoginWidget.hpp"
#include "../dominios/derivados/email.hpp"
#include "../dominios/derivados/password.hpp"

LoginWidget::LoginWidget(IAuthService& authService, QWidget *parent)
    : QWidget(parent), authService_(authService) {
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    emailInput_ = new QLineEdit();
    emailInput_->setPlaceholderText("Email");
    layout->addWidget(emailInput_);
    
    senhaInput_ = new QLineEdit();
    senhaInput_->setPlaceholderText("Senha");
    senhaInput_->setEchoMode(QLineEdit::Password);
    layout->addWidget(senhaInput_);
    
    btnEntrar_ = new QPushButton("Entrar");
    layout->addWidget(btnEntrar_);
    
    connect(btnEntrar_, &QPushButton::clicked, this, &LoginWidget::onEntrarClicked);
}

void LoginWidget::setEmailPrefill(const QString& email) {
    emailInput_->setText(email);
}

void LoginWidget::onEntrarClicked() {
    try {
        Email email;
        email.set(emailInput_->text().toStdString());
        
        Password senha;
        senha.set(senhaInput_->text().toStdString());

        if (authService_.autenticar(email, senha)) {
            emit loginSucesso(QString::fromStdString(email.get()));
        } else {
            QMessageBox::warning(this, "Erro", "Email ou senha incorretos.");
        }
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Erro", e.what());
    }
}