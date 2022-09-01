#pragma once
#include "state.h"
#include "message.h"

class StrangerState : public State
{
public:
    StrangerState(Chat* owner);

    void interact() override;
    void help() override;
    void welcome() override;
    void send(Message*) override;
    void leave() override;
private:
    int CountDown;
};
