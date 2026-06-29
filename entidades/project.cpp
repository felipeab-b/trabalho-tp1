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

void Project::setProductOwner(Email productOwner) {
    this->productOwner = productOwner;
}

Email Project::getProductOwner() const {
    return this->productOwner;
}

void Project::setScrumMaster(Email scrumMaster) {
    this->scrumMaster = scrumMaster;
}

Email Project::getScrumMaster() const {
    return this->scrumMaster;
}