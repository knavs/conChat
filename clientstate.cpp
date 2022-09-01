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
            std::cout << Utils::bold("Total: ") << pChat->getUsers().size() << std::endl;
            for (auto user : pChat->getUsers())
                std::cout << user.getLogin() << (user.getLogin() == pChat->getCurrentUser()->getLogin() ? Utils::bold(" (you)") : "")<< std::endl;

        } else if ("/help" == cmd) {
            help();

        } else if ("/exit" == cmd || "/logout" == cmd) {
            pChat->leave();
            // Be very carefull... now you are actually are a JumpState object!
            // But you are still running code in here what the face?
            return;
        } else if ("/" == cmd || "/inbox" == cmd){
            std::cout << *pChat;
        } else if ("/personal" == cmd || "/private" == cmd) {
            for (auto msg : pChat->getMessages())
                if (msg.to() == pChat->getCurrentUser()->getLogin()) std::cout << msg;
        } else {
            throw std::domain_error("Unknown command");
        }

    }

}

void ClientState::help()
{
    std::cout << "/help - покзать справку\n";
    std::cout << "/exit /logout - покинуть чат чат\n";
    std::cout << "@username - написать личное сообщение пользователю `username`\n";
    std::cout << "/inbox - показать все сообщения чата\n";
    std::cout << "/personal - показать все личные сообщения\n";
    std::cout << "/users - показать список пользователей\n";
}

void ClientState::welcome()
{
    std::cout << "Welcome, you are logged in as " << pChat->getCurrentUser()->getLogin() << "@" << pChat->getCurrentUser()->getPassword() << "!" << std::endl;
    help();
}

void ClientState::send(Message *)
{
    std::cout << "SEND";
}

void ClientState::leave()
{
    pChat->ChangeCurrentState<StrangerState>();
    return;
}
