// person.hpp
#ifndef PERSON_HPP
#define PERSON_HPP

#include "dominios/derivados/email.hpp"
#include "dominios/derivados/name.hpp"
#include "dominios/derivados/role.hpp"
#include "dominios/derivados/password.hpp"

class Person {
private:
    Email email;
    Name name;
    Password password;
    Role role;

public:
    Person(Email email);  

    Email getEmail() const;
    void setName(Name);
    Name getName() const;
    void setPassword(Password);
    Password getPassword() const;
    void setRole(Role);
    Role getRole() const;
};

#endif