#include "role.hpp"

void Role::validate(std::string role){
    if (role != "DESENVOLVEDOR" && role != "MESTRE SCRUM" && role != "PROPRIETARIO DE PRODUTO") {
        throw std::invalid_argument("Invalid Role");
    }
}
