#include "user.h"
#include <algorithm>
#include <stdexcept>
#include <regex>
#include <iostream>

User::User(const std::string &login, const std::string &password) : m_login(login), m_password(password)
{

}


const std::string& User::getPassword() const
{
    return m_password;
}


void User::setPassword(const std::string &password)
{
    assert_valid_password(password);
    m_password = password;
}


const std::string& User::getLogin() const
{
    return m_login;
}


bool containsOnlyAlphaAndUdnerscore(std::string const &str) {
    return std::regex_match(str, std::regex("^[A-z][A-Za-z0-9_]+$"));
}


bool containsOnlyAlphaAndSpecialChars(std::string const &str) {
    return std::regex_match(str, std::regex("^[A-Za-z0-9_@&-{}]+$"));
}


void User::assert_valid_username(const std::string &login)
{
    if(!containsOnlyAlphaAndUdnerscore(login))
        throw std::runtime_error("Username must start with a latin letter and contain only letters, numbers and `_`");

    if (login.length() < 2 or login.length() > 12)
        throw std::length_error("Username must be 2 to 12 chars long");
}


void User::assert_valid_password(const std::string &password)
{
    if(!containsOnlyAlphaAndSpecialChars(password))
        throw std::runtime_error("Username must start with a latin letter and contain only letters, numbers and `_`");

    if (password.length() < 4 or password.length() > 10)
        throw std::length_error("Password must be 4 to 10 chars long");
}
