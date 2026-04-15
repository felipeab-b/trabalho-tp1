#include "project.hpp"

Project::Project(Code code) {
    this->code = code;
};

Code Project::getCode() const {
    return code;
};

void Project::setName(Name name) {
    this->name = name;
};

Name Project::getName() const {
    return name;
};

void Project::setBeginning(Date beginning) {
    this->beginning = beginning;
};

Date Project::getBeginning() const {
    return beginning;
};

void Project::setEnding(Date ending) {
    this->ending = ending;
};

Date Project::getEnding() const {
    return ending;
};