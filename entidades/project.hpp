#ifndef PROJECT_HPP
#define PROJECT_HPP

#include "dominios/derivados/code.hpp"
#include "dominios/derivados/date.hpp"
#include "dominios/derivados/name.hpp"

class Project {
    private:
        Code code;
        Name name;
        Date beginning;
        Date ending;

    public:
        Project(Code code);

        Code getCode() const;
        void setName(Name);
        Name getName() const;
        void setBeginning(Date);
        Date getBeginning() const;
        void setEnding(Date);
        Date getEnding() const;
};

#endif