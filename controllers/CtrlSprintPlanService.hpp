#ifndef CTRL_SPRINT_PLAN_SERVICE_HPP
#define CTRL_SPRINT_PLAN_SERVICE_HPP

#include "ISprintPlanService.hpp"
#include <vector>
#include <stdexcept>

class CntrServicoPlanoSprint : public ISprintPlanService {
private:
    std::vector<SprintPlan> containerPlanos;

public:
    void criarPlanoDeSprint(Code code, Text objective, Time capacity, Code project) override;
    SprintPlan lerPlanoDeSprint(Code code) const override;
    void atualizarPlanoDeSprint(Code code, Text objective, Time capacity) override;
    void excluirPlanoDeSprint(Code code) override;
    std::vector<Code> listarPlanosDeSprintDeProjeto(Code project) const override;
};

#endif