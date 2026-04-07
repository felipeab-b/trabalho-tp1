#include "state.hpp"

void State::validate(std::string state){
    if (state != "A FAZER" && state != "FAZENDO" && state != "FEITO"){
        throw std::invalid_argument("Invalid State");      
    }
}
