// UserStory.cpp
#include "userstory.hpp"

UserStory::UserStory(Code code){
    this->code = code;
}

Code UserStory::getCode() const{
    return this->code;
}

void UserStory::setTitle(Text title){
    this->title = title;
}

Text UserStory::getTitle() const{
    return this->title;
}

void UserStory::setRole(Text role){
    this->role = role;
}

Text UserStory::getRole() const{
    return this->role;
}

void UserStory::setAction(Text action){
    this->action = action;
}

Text UserStory::getAction() const{
    return this->action;
}

void UserStory::setValue(Text value){
    this->value = value;
}

Text UserStory::getValue() const{
    return this->value;
}

void UserStory::setEstimation(Time estimation){
    this->estimation = estimation;
}

Time UserStory::getEstimation() const{
    return this->estimation;
}

void UserStory::setPriority(Priority priority){
    this->priority = priority;
}

Priority UserStory::getPriority() const{
    return this->priority;
}

void UserStory::setState(State state){
    this->state = state;
}

State UserStory::getState() const{
    return this->state;
}
