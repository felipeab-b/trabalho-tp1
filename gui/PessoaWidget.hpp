#ifndef PESSOAWIDGET_HPP
#define PESSOAWIDGET_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QComboBox>
#include "../controllers/CtrlPersonService.hpp"

class PessoaWidget : public QWidget {
    Q_OBJECT

public:
    explicit PessoaWidget(IPersonService& service, QWidget *parent = nullptr);

private slots:
    void onAdicionarClicked();
    void onAtualizarClicked();
    void onRemoverClicked();
    void onBuscarClicked();
    void onTabelaSelecao();
    void onLimparClicked();

private:
    void setupUI();
    void carregarDados();
    void exibirMensagem(const QString& titulo, const QString& mensagem, bool sucesso = true);

    IPersonService& service_;

    QLineEdit *emailInput_;
    QLineEdit *nomeInput_;
    QLineEdit *senhaInput_;
    QComboBox *papelCombo_;
    QTableWidget *tabelaPessoas_;
    QPushButton *btnAdicionar_;
    QPushButton *btnAtualizar_;
    QPushButton *btnRemover_;
    QPushButton *btnBuscar_;
    QPushButton *btnLimpar_;

    QString emailSelecionado_;
};

#endif
