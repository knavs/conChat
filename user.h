#pragma once
#include <string>
#include <string_view>
#include "message.h"
//#include "userstate.h"

class User
{
public:
    explicit User(const std::string& login, const std::string& password, const intptr_t handle = 0);

    const std::string& getLogin() const;

    const std::string& getPassword() const;
    void setPassword(const std::string &password);


    static void assert_valid_username(const std::string& login);
    static void assert_valid_password(const std::string& password);

    intptr_t getHandle() const;
    void setHandle(const intptr_t &handle);

private:
    std::string m_login;
    std::string m_password;
    intptr_t m_handle = 0;
};

