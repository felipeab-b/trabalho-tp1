#ifndef IAUTH_SERVICE_HPP
#define IAUTH_SERVICE_HPP

#include "../dominios/derivados/email.hpp"
#include "../dominios/derivados/password.hpp"

class IAuthService {
public:
    virtual bool autenticar(Email email, Password senha) = 0;
    virtual ~IAuthService() {}
};

#endif