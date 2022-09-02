#pragma once
#include <message.h>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "user.h"
#include "state.h"
#include "clientstate.h"
#include "strangerstate.h"

class State;
class StrangerState;
class ClientState;



class Chat {
public:
    Chat();
    ~Chat();

    //
    // STATE BASED FUNCTIONS
    //
    void interact();
    void welcome();
    void help();
    void send(const std::string& from, const std::string& to, const std::string& text);
    void leave();

    template <typename T>
    void ChangeCurrentState();

    // ALL THE OTHER FUNCTIONS

    std::shared_ptr<User> getCurrentUser() const;
    void setCurrentUser(std::shared_ptr<User> current_user);

    const std::vector<User>& getUsers() const;
    const std::vector<Message>& getMessages() const;

    void addUser(const std::string& username, const std::string& password);


    // Helper TUI functions
    static std::pair<std::string, std::string> parseCommand(const std::string& command); // -> (cmdname, parameter)
    static std::pair<std::string, std::string> inputCredentials();

    friend std::ostream& operator<< (std::ostream &out, const Chat &channel);

private:
    State *m_current_state;
    std::shared_ptr<User> m_current_user = nullptr;
    std::vector<User> m_users;
    std::vector<Message> m_messages;
};

template <typename T>
void Chat::ChangeCurrentState()
{
    delete m_current_state;
    m_current_state = new T(this);
}


