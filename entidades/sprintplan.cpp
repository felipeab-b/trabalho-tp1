#include "sprintplan.hpp"

SprintPlan::SprintPlan(Code c) { 
    code = c; 
}

void SprintPlan::setObjective(Text o) { 
    objective = o; 
}

void SprintPlan::setCapacity(Time c) { 
    capacity = c; 
}

Code SprintPlan::getCode() const { 
    return code; 
}

Text SprintPlan::getObjective() const { 
    return objective; 
}

Time SprintPlan::getCapacity() const { 
    return capacity; 
}

void SprintPlan::setProject(Code p) { 
    project = p; 
}

Code SprintPlan::getProject() const { 
    return project; 
}
