#include "person.hpp"

Person::Person(Email email) {
    this->email = email;
}

Email Person::getEmail() const {
    return this->email;
}

void Person::setName(Name name) {
    this->name = name;
}

Name Person::getName() const {
    return this->name;
}

void Person::setPassword(Password password) {
    this->password = password;
}

Password Person::getPassword() const {
    return this->password;
}

void Person::setRole(Role role) {
    this->role = role;
}

Role Person::getRole() const {
    return this->role;
}