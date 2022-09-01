#pragma once
#include "state.h"
#include "message.h"
#include "user.h"

class ClientState : public State
{
public:
    ClientState(Chat* owner);

    void interact() override;
    void help() override;
    void welcome() override;
    void send(Message*) override;
    void leave() override;
private:
    int CountDown;
    User* m_current_user;
};
