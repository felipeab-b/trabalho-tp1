#ifndef CTRL_USER_STORY_SERVICE_HPP
#define CTRL_USER_STORY_SERVICE_HPP

#include "../interfaces/IUserStoryService.hpp"
#include "../interfaces/ISprintPlanService.hpp"
#include "../database/sqlite_connection.hpp"
#include <vector>
#include <stdexcept>
#include <string>

class CntrServicoHistoriaUsuario : public IUserStoryService {
private:
    std::vector<UserStory> containerHistorias;
    SQLiteConnection database_;

    ISprintPlanService* servicoPlanoSprint = nullptr;

    void inicializarBanco();
    void carregarHistorias();
    void inserirHistoriaNoBanco(const UserStory& historia);
    void atualizarHistoriaNoBanco(const UserStory& historia);
    void removerHistoriaNoBanco(const std::string& code);
    void inserirAssociacao(const std::string& historia, const std::string& pessoa);
    void removerAssociacao(const std::string& historia, const std::string& pessoa);
    std::string escaparTexto(const std::string& valor) const;

public:
    explicit CntrServicoHistoriaUsuario(const std::string& dbPath = "scrum.db");

    void setSprintPlanService(ISprintPlanService* servico) {
        this->servicoPlanoSprint = servico;
    }

    void criarHistoriaDeUsuario(Code code, Text title, Text role, Text action,
                                Text value, Time estimation, Priority priority,
                                Code project) override;

    UserStory lerHistoriaDeUsuario(Code code) const override;

    void atualizarHistoriaDeUsuario(Code code, Text title, Text role, Text action,
                                    Text value, Time estimation, Priority priority) override;

    void excluirHistoriaDeUsuario(Code code) override;

    void associarPessoaAHistoriaDeUsuario(Code userStory, Email person) override;
    void removerAssociacaoPessoaHistoriaDeUsuario(Code userStory, Email person) override;

    std::vector<Code> listarHistoriasDeUsuarioDeProjeto(Code project) const override;
    std::vector<Code> listarHistoriasDeUsuarioDePlanoDeSprint(Code sprintPlan) const override;
    std::vector<Code> listarHistoriasDeUsuarioDePessoa(Email person) const override;

    void moverHistoriaDeUsuarioParaPlanoDeSprint(Code userStory, Code project, Code sprintPlan) override;
    void alterarEstadoHistoriaDeUsuario(Code userStory, State state) override;
};

#endif