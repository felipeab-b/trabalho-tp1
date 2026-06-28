#ifndef SPRINTWIDGET_HPP
#define SPRINTWIDGET_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "controllers/CtrlSprintPlanService.hpp"

class SprintWidget : public QWidget {
    Q_OBJECT

public:
    explicit SprintWidget(ISprintPlanService& service, QWidget *parent = nullptr);

private slots:
    void onAdicionarClicked();
    void onAtualizarClicked();
    void onRemoverClicked();
    void onBuscarClicked();
    void onTabelaSelecao();
    void onLimparClicked();

private:
    void setupUI();
    void exibirMensagem(const QString& titulo, const QString& mensagem, bool sucesso = true);

    ISprintPlanService& service_;
    
    QLineEdit *codigoInput_;
    QLineEdit *objetivoInput_;
    QLineEdit *capacidadeInput_;
    QLineEdit *projetoInput_;
    QTableWidget *tabelaSprints_;
    QPushButton *btnAdicionar_;
    QPushButton *btnAtualizar_;
    QPushButton *btnRemover_;
    QPushButton *btnBuscar_;
    QPushButton *btnLimpar_;
    
    QString codigoSelecionado_;
};

#endif
