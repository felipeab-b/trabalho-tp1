#ifndef CTRL_SERVICO_PROJETO_HPP
#define CTRL_SERVICO_PROJETO_HPP

#include "IProjectService.hpp"
#include <vector>
#include <stdexcept>

class CntrServicoProjeto : public IProjectService {
private:
    std::vector<Project> containerProjetos;

public:
    void criarProjeto(Code code, Name name, Date beginning, Date ending, Email scrumMaster) override;
    Project lerProjeto(Code code) const override;
    void atualizarProjeto(Code code, Name name, Date beginning, Date ending) override;
    void excluirProjeto(Code code) override;
    std::vector<Code> listarProjetosDePessoa(Email person) const override;
};

#endif
