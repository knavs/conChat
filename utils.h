#pragma once
#pragma once
#include <string>
#include <string_view>


namespace utils {

const std::string clear_escape_code = "\033[H\033[2J";

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
