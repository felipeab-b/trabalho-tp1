#include "priority.hpp"

void Priority::validate(std::string priority){
    if(priority != "ALTA" && priority != "MEDIA" && priority != "BAIXA"){
        throw std::invalid_argument("Invalid priority");
    }
};