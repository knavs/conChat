#include <iostream>
#include <memory>
#include "chat.h"
#include "strangerstate.h"
#include "clientstate.h"
#include "utils.h"


StrangerState::StrangerState(Chat* owner)
    : State(owner)
{
    std:: cout << welcome();
}

void StrangerState::interact(std::string_view svin, std::ostream &sout)
{

    auto [cmd, args] = Chat::parseCommand(svin);

    if ("/login" == cmd) {
        auto [login, password] = Chat::inputCredentials(args);

        if (pChat->authUser(login, password)) {
            //pChat->getCurrentUser()->setHandle(ser)
            sout << "Logged in as " << utils::fg_green(pChat->getCurrentUser()->getLogin()) << utils::endl;
            pChat->ChangeCurrentState<ClientState>();

            // Be very carefull... now you are actually are a ClientState
            // object! But you are still running code in here what the face?
            return;
        }

    } else if ("/register" == cmd) {
        auto [login, password] = Chat::inputCredentials(args);
        pChat->addUser(login, password);
        for (const auto& user : pChat->getUsers())
                sout << user.getLogin() << utils::endl;

    } else if ("/help" == cmd) {
            sout << help();
    } else {
            sout << utils::bg("Внимание!") << utils::endl;
            sout << "You need to be logged in to view or write to chat\r\n";
    }
}

std::string StrangerState::help()
{
    return utils::fg_blue("Справка") + "\n\r/register - зарегистрировать новый аккаунт\n\r"
"/login - авторизоваться с существующим аккаунтом (тестовый: demo@demo)\n\r"
"/help - показать помощь\n\r";
}

std::string StrangerState::welcome()
{
    return  utils::fg_blue("Welcome")
            + " stranger!" + utils::endl
            + help();
}

void StrangerState::send(const std::string &input_message) {
  throw std::domain_error("You must be logged in to send messages");
}

void StrangerState::leave()
{
    throw std::domain_error("Please authorize first in to leave the chat.");
}



