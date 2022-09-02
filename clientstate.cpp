#include <iostream>
#include <chat.h>
#include <message.h>
#include "strangerstate.h"
#include "clientstate.h"
#include "utils.h"

ClientState::ClientState(Chat* owner)
    : State(owner)
{
    welcome();
}


void ClientState::interact()
{
    // Основной спагетти код с каллбеками идет тут
    // Вроде на этот случай мог бы подойти паттерн команда. Но решил не городить вроде и так простой код.
    std::string text = "text";


    std::cout << "> ";

    std::getline(std::cin, text);

    auto [cmd, rest] = Chat::parseCommand(text);

    if (cmd.at(0) == '@') { //send message
        pChat->send(pChat->getCurrentUser()->getLogin(), (cmd == "@all" ? "" : cmd.substr(1)), rest);

    } else { // run command
        if ("/whoami" == cmd) {
            std::cout << pChat->getCurrentUser()->getLogin() <<std::endl;

        } else if ("/users" == cmd) {
            std::cout << utils::bold("Total: ") << pChat->getUsers().size() << std::endl;
            for (const auto& user : pChat->getUsers()) {
                if (user.getLogin() == pChat->getCurrentUser()->getLogin())
                    std::cout << utils::fg_green(utils::bold(user.getLogin()) + " (you)") << std::endl;
                else
                    std::cout << user.getLogin() << std::endl;
            }


        } else if ("/help" == cmd) {
            help();

        } else if ("/exit" == cmd || "/logout" == cmd) {
            pChat->leave();
            // Be very carefull... now you are actually are a StrangerState object!
            // But you are still running code in here what the face?
            return; // void
        } else if ("/" == cmd || "/inbox" == cmd){
            std::cout << *pChat;
        } else if ("/personal" == cmd || "/private" == cmd) {
            for (const auto& msg : pChat->getMessages())
                if (msg.to() == pChat->getCurrentUser()->getLogin()) std::cout << msg;
        } else {
            throw std::domain_error("Unknown command");
        }

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
    std::cout << "Welcome, you are logged in as " << pChat->getCurrentUser()->getLogin() << "@" << pChat->getCurrentUser()->getPassword() << "!" << std::endl;
    help();
}

void ClientState::send(Message * msg)
{
    pChat->send(msg->from(), msg->to(), msg->text());
}

void ClientState::leave()
{
    pChat->ChangeCurrentState<StrangerState>();
}
