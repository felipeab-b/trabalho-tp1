#ifndef PROJETOWIDGET_HPP
#define PROJETOWIDGET_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "controllers/CtrlProjectService.hpp"

class ProjetoWidget : public QWidget {
    Q_OBJECT

public:
    explicit ProjetoWidget(IProjectService& service, const QString& currentUserEmail = QString(), const QString& currentUserRole = QString(), QWidget *parent = nullptr);

signals:
    void projetoSelecionado(const QString& code);

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
    void carregarProjetosDoUsuario();
    void aplicarPermissoes();

    IProjectService& service_;
    QString currentUserEmail_;
    QString currentUserRole_;
    
    QLineEdit *codigoInput_;
    QLineEdit *nomeInput_;
    QLineEdit *dataInicioInput_;
    QLineEdit *dataFimInput_;
    QLineEdit *scrumInput_;
    QTableWidget *tabelaProjetos_;
    QPushButton *btnAdicionar_;
    QPushButton *btnAtualizar_;
    QPushButton *btnRemover_;
    QPushButton *btnBuscar_;
    QPushButton *btnLimpar_;
    
    QString codigoSelecionado_;
};

#endif
