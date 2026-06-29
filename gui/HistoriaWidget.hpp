#ifndef HISTORIAWIDGET_HPP
#define HISTORIAWIDGET_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QComboBox>
#include <vector>
#include "../controllers/CtrlUserStoryService.hpp"

class HistoriaWidget : public QWidget {
    Q_OBJECT

public:
    explicit HistoriaWidget(IUserStoryService& service, const QString& currentUserRole = QString(), QWidget *parent = nullptr);
    void setProjectCode(const QString& code);

private slots:
    void onAdicionarClicked();
    void onAtualizarClicked();
    void onRemoverClicked();
    void onBuscarClicked();
    void onAssociarClicked();
    void onRemoverAssociacaoClicked();
    void onMoverSprintClicked();
    void onAlterarEstadoClicked();
    void onTabelaSelecao();
    void onLimparClicked();

private:
    void setupUI();
    void exibirMensagem(const QString& titulo, const QString& mensagem, bool sucesso = true);
    void aplicarPermissoes();
    void carregarHistorias();
    void exibirListaHistorias(const std::vector<Code>& codigos);

    IUserStoryService& service_;
    QString currentProjectCode_;
    QString currentUserRole_;

    QLineEdit *codigoInput_;
    QLineEdit *tituloInput_;
    QLineEdit *papelInput_;
    QLineEdit *acaoInput_;
    QLineEdit *valorInput_;
    QLineEdit *estimativaInput_;
    QComboBox *prioridadeCombo_;
    QLineEdit *projetoInput_;
    QLineEdit *desenvolvedorInput_;
    QLineEdit *planoSprintInput_;
    QComboBox *estadoCombo_;
    QTableWidget *tabelaHistorias_;
    QPushButton *btnAdicionar_;
    QPushButton *btnAtualizar_;
    QPushButton *btnRemover_;
    QPushButton *btnBuscar_;
    QPushButton *btnAssociar_;
    QPushButton *btnRemoverAssociacao_;
    QPushButton *btnMoverSprint_;
    QPushButton *btnAlterarEstado_;
    QPushButton *btnLimpar_;

    QString codigoSelecionado_;
};

#endif
