#include <iostream>
#include <chat.h>
#include <message.h>
#include "strangerstate.h"
#include "clientstate.h"
#include "utils.h"

ClientState::ClientState(Chat *owner) : State(owner), m_current_user(nullptr) {
    welcome();
}

void ClientState::interact() {
  std::string text = "text";
  std::cout << "> ";
  std::getline(std::cin, text);

  if (text.front() == '@' or
      text.front() !=
          '/') { // send personal or public message (aka it's not a command)
    pChat->send(text);

  } else { // run command
    run_command(text);
  }
}

void ClientState::help()
{
    std::cout << "/help - покзать справку\n"
                "/exit /logout - покинуть чат чат\n"
                "@username - написать личное сообщение пользователю `username`\n"
                "/inbox - показать все сообщения чата\n"
                "/personal - показать все личные сообщения\n"
                "/users - показать список пользователей\n";
}

void ClientState::welcome()
{
  std::cout << "Welcome, you are logged in as "
            << pChat->getCurrentUser()->getLogin() << "@"
            << pChat->getCurrentUser()->getPassword() << "!" << std::endl;
  help();
}

void ClientState::send(const std::string &input_string) {
  auto [address, text_message] = Chat::parseCommand(input_string);

  pChat->addMessage(pChat->getCurrentUser()->getLogin(),
                    (address == "@all" ? "" : address.substr(1)), text_message);
}

void ClientState::leave() { pChat->ChangeCurrentState<StrangerState>(); }

void ClientState::run_command(const std::string &text) {
  // Основной спагетти код с каллбеками идет тут
  // Вроде на этот случай мог бы подойти паттерн команда. Но решил не городить
  // вроде и так простой код.
  auto [cmd, rest] = Chat::parseCommand(text);

  if ("/whoami" == cmd) {
    std::cout << pChat->getCurrentUser()->getLogin() << std::endl;

  } else if ("/users" == cmd) {
    std::cout << utils::bold("Total: ") << pChat->getUsers().size()
              << std::endl;
    for (const auto &user : pChat->getUsers()) {
      if (user.getLogin() == pChat->getCurrentUser()->getLogin())
        std::cout << utils::fg_green(utils::bold(user.getLogin()) + " (you)")
                  << std::endl;
      else
        std::cout << user.getLogin() << std::endl;
    }

  } else if ("/help" == cmd) {
    help();

  } else if ("/exit" == cmd || "/logout" == cmd) {
    leave();
    // Be very carefull... now you are actually are a StrangerState object!
    // But you are still running code in here what the face?
    return; // void

  } else if ("/inbox" == cmd || cmd == "/") {
    std::cout << *pChat;

  } else if ("/personal" == cmd || "/private" == cmd) {
    for (const auto &msg : pChat->getMessages())
      if (msg.to() == pChat->getCurrentUser()->getLogin())
        std::cout << msg;

  } else {
    throw std::domain_error("Unknown command");
  }
}
