#ifndef AUTHWIDGET_HPP
#define AUTHWIDGET_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>
#include "LoginWidget.hpp"
#include "RegisterWidget.hpp"
#include "interfaces/IAuthService.hpp"
#include "controllers/CtrlPersonService.hpp"

class AuthWidget : public QWidget {
    Q_OBJECT
public:
    explicit AuthWidget(IAuthService& authService, IPersonService& personService, QWidget *parent = nullptr);

signals:
    void loginSucesso(const QString& email);

private slots:
    void onRegisterSuccess(const QString& email);

private:
    QTabWidget *tabs_;
    LoginWidget *loginWidget_;
    RegisterWidget *registerWidget_;
};

#endif
