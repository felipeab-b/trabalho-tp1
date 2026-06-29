#ifndef CTRL_SPRINT_PLAN_SERVICE_HPP
#define CTRL_SPRINT_PLAN_SERVICE_HPP

#include "../interfaces/ISprintPlanService.hpp"
#include "../interfaces/IProjectService.hpp"
#include "../database/sqlite_connection.hpp"
#include <vector>
#include <stdexcept>
#include <string>

class CntrServicoPlanoSprint : public ISprintPlanService {
private:
    std::vector<SprintPlan> containerPlanos;
    SQLiteConnection database_;
    std::string currentUserEmail_;
    std::string currentUserRole_;
    
    IProjectService* servicoProjeto = nullptr; 

    void inicializarBanco();
    void carregarPlanos();
    void validarPermissao(const std::string& operacao) const;
    void inserirPlanoNoBanco(const SprintPlan& plano);
    void atualizarPlanoNoBanco(const SprintPlan& plano);
    void removerPlanoNoBanco(const std::string& code);
    std::string escaparTexto(const std::string& valor) const;

public:
    explicit CntrServicoPlanoSprint(const std::string& dbPath = "scrum.db");

    void setCurrentUser(const std::string& email, const std::string& role) {
        currentUserEmail_ = email;
        currentUserRole_ = role;
    }

    void setProjectService(IProjectService* servico) {
        this->servicoProjeto = servico;
    }

    void criarPlanoDeSprint(Code code, Text objective, Time capacity, Code project) override;
    SprintPlan lerPlanoDeSprint(Code code) const override;
    void atualizarPlanoDeSprint(Code code, Text objective, Time capacity) override;
    void excluirPlanoDeSprint(Code code) override;
    std::vector<Code> listarPlanosDeSprintDeProjeto(Code project) const override;
};

#endif