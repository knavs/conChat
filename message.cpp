#include "message.h"
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include "utils.h"


std::string Message::text() const
{
    return m_text;
}

std::string Message::from() const
{
    return m_from;
}

std::string Message::to() const
{
    return m_to;
}

std::string Message::to_string() const
{
    std::string out;
    // Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
    out = utils::fg_reverse(from());
    out += "\n";
    out += (to().empty() ? "" : utils::fg_green("@" + to()) + ", ") + text();
    out += "\n";

    return out;
}



time_t Message::date() const
{
    return m_date;
}

std::ostream& operator<< (std::ostream &out, const Message &msg)
{
    out << msg.to_string();
    return out;
}


Message::Message(const std::string& from_user, const std::string& to_user, const std::string& a_text) : m_date(time(0)), m_from(from_user), m_to(to_user), m_text(a_text), m_was_read(false)
{

}

Message::Message(const std::string& from_user, const std::string& a_text) : m_date(time(0)), m_from(from_user), m_to(""), m_text(a_text), m_was_read(false)
{

};
