#include <iostream>
#include <chat.h>
#include <message.h>
#include "strangerstate.h"
#include "clientstate.h"
#include "utils.h"

ClientState::ClientState(Chat *owner) : State(owner), m_current_user(nullptr) {
    std::cout << welcome();
}

//void ClientState::interact() {
//    interact(std::cout);
//}

void ClientState::interact(std::string_view svin, std::ostream &sout)
{
    if (svin.front() == '@' or svin.front() != '/') { // send personal or public message (aka it's not a command)
        pChat->send(std::string{svin});

    } else { // run command
      run_command(svin, sout);
    }
}

std::string ClientState::help()
{
    return      utils::fg_blue("Справка") + "\r\n/help - покзать справку\r\n"
"/exit /logout - покинуть чат чат\r\n"
"@username - написать личное сообщение пользователю `username`\r\n"
"/inbox - показать все сообщения чата\r\n"
"/personal - показать все личные сообщения\r\n"
"/users - показать список пользователей\r\n";
}

std::string ClientState::welcome()
{
  return "Welcome, you are logged in as "
         + pChat->getCurrentUser()->getLogin() + "@"
         + pChat->getCurrentUser()->getPassword() + "!"
         + help();
}

void ClientState::send(const std::string &input_string) {
  auto [address, text_message] = Chat::parseCommand(input_string);

  pChat->addMessage(pChat->getCurrentUser()->getLogin(),
                    (address == "@all" ? "" : address.substr(1)), text_message);
}

void ClientState::leave() { pChat->ChangeCurrentState<StrangerState>(); }

void ClientState::run_command(std::string_view text, std::ostream& sout) {
  // Основной спагетти код с каллбеками идет тут
  // Вроде на этот случай мог бы подойти паттерн команда. Но решил не городить
  // вроде и так простой код.
  auto [cmd, rest] = Chat::parseCommand(text);

  if ("/whoami" == cmd) {
    sout << pChat->getCurrentUser()->getLogin() << utils::endl;

  } else if ("/users" == cmd) {
    sout << utils::bold("Total: ") << pChat->getUsers().size()
              << utils::endl;
    for (const auto &user : pChat->getUsers()) {
      if (user.getLogin() == pChat->getCurrentUser()->getLogin())
        sout << utils::fg_green(utils::bold(user.getLogin()) + " (you)")
                  << utils::endl;
      else
        sout << user.getLogin() << utils::endl;
    }

  } else if ("/help" == cmd) {
    sout << help();

  } else if ("/exit" == cmd || "/logout" == cmd) {
    sout << "logged out";
    leave();

    // Be very carefull... now you are actually are a StrangerState object!
    // But you are still running code in here what the face?
    return; // void

  } else if ("/inbox" == cmd || cmd == "/") {
      sout << *pChat;

  } else if ("/personal" == cmd || "/private" == cmd) {
    for (const auto &msg : pChat->getMessages())
      if (msg.to() == pChat->getCurrentUser()->getLogin())
          sout << msg;

  } else {
    throw std::domain_error("Unknown command");
  }
}
