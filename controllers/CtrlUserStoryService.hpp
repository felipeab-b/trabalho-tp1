#ifndef CTRL_USER_STORY_SERVICE_HPP
#define CTRL_USER_STORY_SERVICE_HPP

#include "IUserStoryService.hpp"
#include <vector>
#include <stdexcept>

class CntrServicoHistoriaUsuario : public IUserStoryService {
private:
    std::vector<UserStory> containerHistorias;

public:
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