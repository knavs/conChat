#pragma once
#include <iostream>
#include "message.h"

class Chat;



class State
{
public:
    explicit State(Chat* owner); // explicit !?
    virtual ~State();
    virtual void interact() = 0;

    virtual void leave() = 0;
    virtual void send(Message*) = 0;
    virtual void help() = 0;
    virtual void welcome() = 0;

protected:
    Chat* pChat;
};
