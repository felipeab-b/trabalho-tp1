#include "state.hpp"

void State::validate(string state){
    if (state != "A FAZER" && state != "FAZENDO" && state != "FEITO"){
        throw invalid_argument("Invalid State");      
    }
}

void State::set(string state){
    validate(state);
    this->state = state;
}

string State::get() const {
    return this->state;
}