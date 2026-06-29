#ifndef REGISTERWIDGET_HPP
#define REGISTERWIDGET_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QString>
#include "../controllers/CtrlPersonService.hpp"

class RegisterWidget : public QWidget {
    Q_OBJECT
public:
    explicit RegisterWidget(IPersonService& personService, QWidget *parent = nullptr);

signals:
    void registerSuccess(const QString& email);

private slots:
    void onRegistrarClicked();

private:
    IPersonService& personService_;
    QLineEdit *emailInput_;
    QLineEdit *nomeInput_;
    QLineEdit *senhaInput_;
    QComboBox *papelCombo_;
    QPushButton *btnRegistrar_;
};

#endif
