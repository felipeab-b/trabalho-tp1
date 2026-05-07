#ifndef SPRINTPLAN_HPP
#define SPRINTPLAN_HPP
#include "../dominios/derivados/code.hpp"
#include "../dominios/derivados/text.hpp"
#include "../dominios/derivados/time.hpp"

class SprintPlan {
private:
  Code code;
  Text objective;
  Time capacity;

public:
  SprintPlan(Code);

  void setObjective(Text);
  void setCapacity(Time);

  Code getCode() const;
  Text getObjective() const;
  Time getCapacity() const;
};

inline SprintPlan::SprintPlan(Code c) { code = c; }

inline void SprintPlan::setObjective(Text o) { objective = o; }
inline void SprintPlan::setCapacity(Time c) { capacity = c; }

inline Code SprintPlan::getCode() const { return code; }
inline Text SprintPlan::getObjective() const { return objective; }
inline Time SprintPlan::getCapacity() const { return capacity; }

#endif
