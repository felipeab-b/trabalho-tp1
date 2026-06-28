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

#endif
