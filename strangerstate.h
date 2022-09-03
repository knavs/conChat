#pragma once
#include "state.h"
#include "message.h"

class StrangerState : public State
{
public:
  explicit StrangerState(Chat *owner);

  void interact() override;
    void help() override;
    void welcome() override;
    void send(const std::string &input_string) override;
    void leave() override;
};
