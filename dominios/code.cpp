#include "code.hpp"

void Code::validate(string code){
    if (code.length() != 5) {
        throw invalid_argument("Invalid size");
    }
    if (!isupper(code[0]) || !isupper(code[1])){
        throw invalid_argument("Invalid code");
    }
    if (!isdigit(code[2]) || !isdigit(code[3]) || !isdigit(code[4])){
        throw invalid_argument("Invalid code");
    }
}

void Code::set(string code){
    validate(code);
    this->code = code;
}

string Code::get() const{
    return this->code;
}