#pragma once
#include "state.h"
#include "message.h"
#include "user.h"

class ClientState : public State {
public:
  explicit ClientState(Chat *owner);

  // State functions override
  //void interact() override;
  void interact(std::string_view svin, std::ostream& sout = std::cout) override;
  std::string help() override;
  std::string welcome() override;
  void send(const std::string &input_string) override;
  void leave() override;

private:
  User *m_current_user;

  // Helper functions
  void run_command(std::string_view input_string, std::ostream& sout);
};
