#include <iostream>
#include "chat.h"
//#include "strangerstate.h"
#include <utility>


Chat::Chat()
    : m_current_state(new StrangerState(this))
{
    // Nothing here
}

Chat::~Chat()
{
    std::cout << "Chats's DESTRUCTOR CALLED" << std::endl;
}

//void Chat::interact() {
//    try {
//        m_current_state->interact();
//    } catch (const std::exception& e) {
//        std::cout << "Warning" << e.what() << std::endl;
//    }
//}

void Chat::interact(std::string_view svin, std::ostream &sout)
{
    try {
        m_current_state->interact(svin, sout);
    } catch (const std::exception& e) {
        std::cout << "Warning" << e.what() << std::endl;
    }
}

std::string Chat::welcome() { return m_current_state->welcome(); }

std::string Chat::help() { return m_current_state->help(); }

void Chat::send(const std::string &input_string) {
  m_current_state->send(input_string);
}

void Chat::addMessage(const std::string &from, const std::string &to,
                      const std::string &text) {
    m_messages.push_back(Message(from, to, text));
}

bool Chat::authUser(const std::string &login, const std::string &password, const std::intptr_t)
{
    for (const auto &user : getUsers()) {
      if (!login.compare(user.getLogin()) && !password.compare(user.getPassword())) {
        this->setCurrentUser(std::make_shared<User>(login, password));
        return true;
      }
    }

    return false;

}

void Chat::leave() { m_current_state->leave(); }

std::pair<std::string, std::string> Chat::parseCommand(std::string_view text_view)
{
    std::string text{text_view};
    std::pair<std::string, std::string> parsed;


    // One of 3 possible message types
    // 1 - chat command
    // 2 - private message
    // 3 - public message
    if (text.length() > 1 && (text.at(0) == '/' || text.at(0) == '@')) {     // 1-2. chat command or private message
        auto ws_pos = text.find(' ');

        std::string command = text.substr(0, ws_pos);
        std::string arguments = (ws_pos != std::string::npos ? text.substr(++ws_pos) : "");

        parsed = std::make_pair(command, arguments);

    } else {                                          // 3. public message
        parsed =  std::make_pair("@all", text);
    }

    return parsed;
}

std::pair<std::string, std::string> Chat::inputCredentials(std::string text)
{
    auto a_pos = text.find('@');

    std::string login = text.substr(0, a_pos);
    std::string password = (a_pos != std::string::npos ? text.substr(++a_pos) : "");

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
    out << utils::endl << "____________________________________________________________" << utils::endl;

    //out << "\ESC [1mBold\ESC [0m non-bold" << utils::endl; // displays Bold in bold
    out << "Welcome to chat channel: #" << utils::bold("skillfactory_homework");
    out << utils::endl <<  "____________________________________________________________" << utils::endl;
    out << utils::endl << utils::endl << utils::endl;


    std::string all_messages;

    for (const auto& msg : channel.m_messages) {
        all_messages += msg.to_string() + "\n";
    }
    out << all_messages;

    return out;
}


