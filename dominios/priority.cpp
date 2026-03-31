#include "priority.hpp"

void Priority::validade(string priority){
    if(priority != "ALTA" && priority != "MEDIA" && priority != "BAIXA"){
        throw invalid_argument("Invalid priority");
    }
}

void Priority::set(string priority){
    validade(priority);
    this->priority = priority;
}

string Priority::get(){
    return priority;
}
