// person.hpp
#ifndef PERSON_HPP
#define PERSON_HPP

#include "dominios/email.hpp"
#include "dominios/name.hpp"
#include "dominios/role.hpp"
#include "dominios/password.hpp"

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