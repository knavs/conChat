#pragma once
#include <string>
#include <vector>
#include <string_view>


namespace utils {

static const std::string clear_escape_code = "\033[H\033[2J";
static const std::string endl = "\r\n"; // crossplatform endline. хз как это нормально сделать :LUL:


//строку в массив с разбиением по разделителю delimiter
//static std::vector<std::string> splt(const std::string& s, std::string delimiter) {
//    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
//    std::string token;
//    std::vector<std::string> res;

//    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
//        token = s.substr (pos_start, pos_end - pos_start);
//        pos_start = pos_end + delim_len;
//        res.push_back (token);
//    }

//    res.push_back(s.substr(pos_start));
//    return res;
//}


static std::string bg(std::string_view str) {
    static char esc_char = 27;
    std::string formatted_str;

    formatted_str.push_back(esc_char);
    formatted_str.append("[100m");
    formatted_str.append(str);
    formatted_str.push_back(esc_char);
    formatted_str+= "[0m";

    return formatted_str;
}

static std::string fg_reverse(std::string_view str) {
    static char esc_char = 27;
    std::string formatted_str;

    formatted_str.push_back(esc_char);
    formatted_str.append("[7m");
    formatted_str.append(str);
    formatted_str.push_back(esc_char);
    formatted_str+= "[0m";

    return formatted_str;
}

static std::string fg_blue(std::string_view str) {
    static char esc_char = 27;
    std::string formatted_str;

    formatted_str.push_back(esc_char);
    formatted_str.append("[34m");
    formatted_str.append(str);
    formatted_str.push_back(esc_char);
    formatted_str+= "[0m";

    return formatted_str;
}


static std::string fg_green(std::string_view str) {
    static char esc_char = 27;
    std::string formatted_str;

    formatted_str.push_back(esc_char);
    formatted_str.append("[32m");
    formatted_str.append(str);
    formatted_str.push_back(esc_char);
    formatted_str+= "[0m";

    return formatted_str;
}


static std::string bold(std::string_view str) {
    static char esc_char = 27;
    std::string formatted_str;

    formatted_str.push_back(esc_char);
    formatted_str.append("[1m");
    formatted_str.append(str);
    formatted_str.push_back(esc_char);
    formatted_str+= "[0m";

    return formatted_str;
}

};
