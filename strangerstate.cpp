#include <iostream>
#include <memory>
#include "chat.h"
#include "strangerstate.h"
#include "clientstate.h"
#include "utils.h"



StrangerState::StrangerState(Chat* owner)
    : State(owner)
{
    welcome();
}

void StrangerState::interact()
{
    std::cout << "You need to be logged in to view chat\n";

    std::string input;

    std::cout << "> ";

    std::getline(std::cin, input);

    if ("/login" == input) {
        auto [login, password] = Chat::inputCredentials();


        for (const auto& user : pChat->getUsers()) {
            if (!login.compare(user.getLogin()) && !password.compare(user.getPassword())) {
                auto userObj = std::make_shared<User>(login, password);
                pChat->setCurrentUser(userObj);
                pChat->ChangeCurrentState<ClientState>();
                // Be very carefull... now you are actually are a ClientState object!
                // But you are still running code in here what the face?
                return;
            }
        }

    } else if ("/register" == input) {
        auto [login, password] = Chat::inputCredentials();
        pChat->addUser(login, password);
        for (const auto& user : pChat->getUsers())
                std::cout << user.getLogin() << std::endl;

    } else if ("/help" == input) {
            help();
    }

}

void StrangerState::help()
{
    std::cout << "/register - зарегистрировать новый аккаунт\n"
                 "/login - авторизоваться с существующим аккаунтом (тестовый: demo@demo)\n"
                 "/help - показать помощь\n";
}

void StrangerState::welcome()
{
    std::cout << utils::fg_blue("Welcome") << " stranger!\n";
    help();
}

void StrangerState::send(Message *)
{
    throw std::domain_error("You must be logged in to send messages");
}

void StrangerState::leave()
{
    throw std::domain_error("Please authorize first in to leave the chat.");
}



