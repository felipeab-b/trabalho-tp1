#ifndef CTRL_SERVICO_PROJETO_HPP
#define CTRL_SERVICO_PROJETO_HPP

#include "../interfaces/IProjectService.hpp"
#include "../interfaces/ISprintPlanService.hpp"
#include "../interfaces/IUserStoryService.hpp"  
#include "../database/sqlite_connection.hpp"
#include <vector>
#include <stdexcept>
#include <string>

class CntrServicoProjeto : public IProjectService {
private:
    std::vector<Project> containerProjetos;
    SQLiteConnection database_;

    ISprintPlanService* servicoPlanoSprint = nullptr;
    IUserStoryService* servicoHistoriaUsuario = nullptr;

    void inicializarBanco();
    void carregarProjetos();
    void inserirProjetoNoBanco(const Project& projeto);
    void atualizarProjetoNoBanco(const Project& projeto);
    void removerProjetoNoBanco(const std::string& code);
    std::string escaparTexto(const std::string& valor) const;

public:
    explicit CntrServicoProjeto(const std::string& dbPath = "scrum.db");

    void setSprintPlanService(ISprintPlanService* servico) {
        this->servicoPlanoSprint = servico;
    }
    void setUserStoryService(IUserStoryService* servico) {
        this->servicoHistoriaUsuario = servico;
    }

    void criarProjeto(Code code, Name name, Date beginning, Date ending, Email scrumMaster) override;
    Project lerProjeto(Code code) const override;
    void atualizarProjeto(Code code, Name name, Date beginning, Date ending) override;
    void excluirProjeto(Code code) override;
    std::vector<Code> listarProjetosDePessoa(Email person) const override;
};

#endif