#ifndef CTRL_AUTH_SERVICE_HPP
#define CTRL_AUTH_SERVICE_HPP

#include "IAuthService.hpp"
#include "IPersonService.hpp"

class CntrAuthService : public IAuthService {
private:
    IPersonService* personService_;

public:
    CntrAuthService(IPersonService* ps) : personService_(ps) {}
    bool autenticar(Email email, Password senha) override;
};

#endif