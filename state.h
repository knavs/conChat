#pragma once
#include <iostream>
#include "message.h"

class Chat;

class State {
public:
  explicit State(Chat *owner) : pChat(owner){}; // explicit !?
  virtual ~State() = default;

  //virtual void interact() = 0;
  virtual void interact(std::string_view svin, std::ostream& sout = std::cout) = 0;
  virtual void leave() = 0;
  virtual void send(const std::string &input_string) = 0;
  virtual std::string help() = 0;
  virtual std::string welcome() = 0;

protected:
  Chat *pChat;
};
