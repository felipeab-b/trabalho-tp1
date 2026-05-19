// userstory.hpp
#ifndef USERSTORY_HPP
#define USERSTORY_HPP

#include "dominios/derivados/code.hpp"
#include "dominios/derivados/text.hpp"
#include "dominios/derivados/time.hpp"
#include "dominios/derivados/priority.hpp"
#include "dominios/derivados/state.hpp"

class UserStory {
    private:
        Code code;
        Text title;
        Text role;
        Text action;
        Text value;
        Time estimation;
        Priority priority;
        State state;

    public:
        UserStory(Code code);
        Code getCode() const;
        void setTitle(Text);
        Text getTitle() const;
        void setRole(Text);
        Text getRole() const;
        void setAction(Text);
        Text getAction() const;
        void setValue(Text);
        Text getValue() const;
        void setEstimation(Time);
        Time getEstimation() const;
        void setPriority(Priority);
        Priority getPriority() const;
        void setState(State);
        State getState() const;
};

#endif
