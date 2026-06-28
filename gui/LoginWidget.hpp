#ifndef LOGINWIDGET_HPP
#define LOGINWIDGET_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QString>
#include "interfaces/IAuthService.hpp"

class LoginWidget : public QWidget {
    Q_OBJECT
public:
    explicit LoginWidget(IAuthService& authService, QWidget *parent = nullptr);
    void setEmailPrefill(const QString& email);

signals:
    void loginSucesso(const QString& email);

private slots:
    void onEntrarClicked();

private:
    IAuthService& authService_;
    QLineEdit *emailInput_;
    QLineEdit *senhaInput_;
    QPushButton *btnEntrar_;
};

#endif