#include <iostream>
#include "chat.h"
#include "strangerstate.h"
#include <utility>
#include "utils.h"


Chat::Chat()
    : m_current_state(new StrangerState(this))
{
    // Nothing here
}

Chat::~Chat()
{
    std::cout << "Chats's DESTRUCTOR CALLED" << std::endl;
}

void Chat::interact() {
    try {
        m_current_state->interact();
    } catch (const std::exception& e) {
        std::cout << "Warning" << e.what() << std::endl;
    }
}

void Chat::welcome()
{
    m_current_state->welcome();
}


void Chat::help()
{
    m_current_state->help();
}

void Chat::send(const std::string& from, const std::string& to, const std::string& text)
{
    m_messages.push_back(Message(from, to, text));
}


void Chat::leave()
{
    m_current_state->leave();
}




std::pair<std::string, std::string> Chat::parseCommand(const std::string& text)
{

    std::pair<std::string, std::string> parsed;


    // One of 3 possible message types
    // 1 - chat command
    // 2 - private message
    // 3 - public message
    if (text.length() > 1 && text.at(0) == '/') {     // 1. chat command
        parsed = std::make_pair(text, "");
    } else if (text.length() > 1 && text.at(0) == '@') {  // 2. private message
        auto ws_pos = text.find(' ');

        std::string address = text.substr(0, ws_pos);
        std::string rest = (ws_pos ? text.substr(ws_pos) : "");

        parsed = std::make_pair(address, rest);

    } else {                                          // 3. public message
        parsed =  std::make_pair("@all", text);
    }

    return parsed;
}

std::pair<std::string, std::string> Chat::inputCredentials()
{
    std::string login, password;
    std::cout << "Login: ";
    std::getline(std::cin, login);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    return std::make_pair(login, password);
}

std::shared_ptr<User> Chat::getCurrentUser() const
{
    return m_current_user;
}

void Chat::setCurrentUser(std::shared_ptr<User> current_user)
{
    m_current_user = current_user;
}

const std::vector<User> &Chat::getUsers() const
{
    return m_users;
}

const std::vector<Message> &Chat::getMessages() const
{
    return m_messages;
}

void Chat::addUser(const std::string &login, const std::string &password)
{
    User::assert_valid_password(password);
    User::assert_valid_username(login);

    if (login == "all") throw std::logic_error("Sorry `all` is a reserved username");

    for (const auto& u : m_users)
        if (u.getLogin() == login) throw std::domain_error("User already exists");

    m_users.push_back(User(login, password));
}



std::ostream& operator<<(std::ostream &out, const Chat &channel)
{
    out << std::endl << "____________________________________________________________" << std::endl;

    //out << "\ESC [1mBold\ESC [0m non-bold" << std::endl; // displays Bold in bold
    out << "Welcome to chat channel: #" << utils::bold("skillfactory_homework");
    out << std::endl <<  "____________________________________________________________" << std::endl;
    out << std::endl << std::endl << std::endl;


    std::string all_messages;

    for (const auto& msg : channel.m_messages)  all_messages += msg.to_string() + "\n";

    out << all_messages;

    return out;
}


