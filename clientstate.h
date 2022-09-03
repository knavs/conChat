#pragma once
#include "state.h"
#include "message.h"
#include "user.h"

class ClientState : public State {
public:
  explicit ClientState(Chat *owner);

  // State functions override
  void interact() override;
  void help() override;
  void welcome() override;
  void send(const std::string &input_string) override;
  void leave() override;

private:
  User *m_current_user;

  // Helper functions
  void run_command(const std::string &input_string);
};
