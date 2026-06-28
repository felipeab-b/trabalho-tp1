#include "CtrlAuthService.hpp"
#include <stdexcept>

bool CntrAuthService::autenticar(Email email, Password senha) {
    try {
        Person p = personService_->lerPessoa(email);
        
        if (p.getPassword().get() == senha.get()) {
            return true;
        }
    } catch (const std::exception& e) {
        return false;
    }
    return false;
}