#include "AuthWidget.hpp"

AuthWidget::AuthWidget(IAuthService& authService, IPersonService& personService, QWidget *parent)
    : QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    tabs_ = new QTabWidget(this);

    loginWidget_ = new LoginWidget(authService, this);
    registerWidget_ = new RegisterWidget(personService, this);

    tabs_->addTab(loginWidget_, "Login");
    tabs_->addTab(registerWidget_, "Register");

    layout->addWidget(tabs_);

    connect(loginWidget_, &LoginWidget::loginSucesso, this, &AuthWidget::loginSucesso);
    connect(registerWidget_, &RegisterWidget::registerSuccess, this, &AuthWidget::onRegisterSuccess);
}

void AuthWidget::onRegisterSuccess(const QString& email) {
    // Preencher email no login e trocar para a aba de login
    loginWidget_->setEmailPrefill(email);
    tabs_->setCurrentWidget(loginWidget_);
}
