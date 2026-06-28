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
    
    Code project; 

public:
    SprintPlan(Code);

    void setObjective(Text);
    void setCapacity(Time);
    
    void setProject(Code); 
    Code getProject() const; 

    Code getCode() const;
    Text getObjective() const;
    Time getCapacity() const;
};

#endif
