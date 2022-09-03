#pragma once
#include <iostream>
#include "message.h"

class Chat;

class State {
public:
  explicit State(Chat *owner) : pChat(owner){}; // explicit !?
  virtual ~State() = default;

  virtual void interact() = 0;
  virtual void leave() = 0;
  virtual void send(const std::string &input_string) = 0;
  virtual void help() = 0;
  virtual void welcome() = 0;

protected:
  Chat *pChat;
};
