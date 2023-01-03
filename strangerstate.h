#pragma once
#include "state.h"
#include "message.h"

class StrangerState : public State
{
public:
  explicit StrangerState(Chat *owner);

    //void interact() override;
    void interact(std::string_view svin, std::ostream& sout = std::cout) override;
    std::string help() override;
    std::string welcome() override;
    void send(const std::string &input_string) override;
    void leave() override;
};
