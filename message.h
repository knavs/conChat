#pragma once
#include <string>
#include <vector>
#include <ctime>


class Message
{
    time_t m_date;
    std::string m_from;
    std::string m_to;
    std::string m_text;
    bool m_was_read;
public:
    Message(const std::string& from_user, const std::string& to_user, const std::string& a_text);
    Message(const std::string& from_user, const std::string& a_text);
    std::string text() const;
    std::string from() const;
    std::string to() const;
    std::string to_string() const;
    time_t date() const;
    bool getWasRead() const;
    void setWasRead();

    friend std::ostream& operator<< (std::ostream &out, const Message &msg);
};
