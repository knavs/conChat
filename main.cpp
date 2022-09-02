#include <iostream>
#include "chat.h"
#include <memory>
#include <vector>
#include <map>
#include <string>
#include "utils.h"


/*
 *
 * Создайте чат со следующим функционалом:

* консольная программа
* регистрация пользователей - логин, пароль, имя
* вход в чат по логину/паролю
* отправка сообщений конкретному пользователю
* обмен сообщениями между всеми пользователями чата одновременно
* Обязательным условием является использование классов.
 */


std::unique_ptr<Chat> initChat() {
    static const std::vector<std::vector<std::string>> offtop = {
        {"Alucard", "вот что бездушный запад с вами сделал, вы перестали верить в любовь и уважение\nвсе у вас пропаганда и куплено\nзабыли искренные чувства", ""},
        {"verbrecher20", "Слово инвалид раньше означало ветеран, возможно это издержки словарей старых", ""},
        {"verbrecher20", "Геральт ронин получился какой то\n Он конечно такой но не внешне", "Alucard"},
        {"Speck", "Kasardzjan\nVolodja roflit\nnad nim", "Napoléon Bonaparte"},
        {"Speck", "smotri on tebja viebat mojet", "verbrecher20"},
        {"verbrecher20", "Проверял?", "Speck"},
        {"Napoleon", "Стоимость майнинга одного биткойна в разных странах на карте мира. Основные расходы на добычу биткойна — электроэнергия.",""},
        {"Napoleon",  "Из-за разницы в её цене, доходность майнинга по миру различается в 176 раз. Дешевле всего майнить в Кувейте — биткойн обойдётся вам всего в $1394.",""},
        {"Napoleon",  "Самое дорогое место на земле для майнинга - Венесуэла, здесь придётся затратить $246,531. Россия находится в «умеренном» для майнеров диапазоне — в среднем на добычу 1 биткойна здесь уходит $16130.", ""},
        {"verbrecher20", "кек", ""},
        {"Alucard","интересно сколько лет потребуется трендом на суши ролы заменить жуками и смогут ли звезды продавить новую моду )",""},
        {"r0mjk3", "Институт исследования войны сообщает что за последние 1.5месяца максимальное продвижение ВС РФ на донбассе  не более 10 км", ""},
        {"x3demon", "верберчер опять бухает?\n побочное действие - агрессия", ""},
        {"verbrecher20", "агрессия от работы)", ""},
        {"ag3nt", "на студентках/школьницах не можешь срывать, срываешь на нас?", "verbrecher20"},
        {"verbrecher20", "так я только на вату срываюсь", "ag3nt"},
        {"ag3nt", "а у нас тут такие есть разве?", ""},
        {"sg", "hello world", ""}
    };


    static const std::map<std::string, std::string> bots = {
        {"Alucard", "2wa5ds"},
        {"Napoleon", "JVNygc"},
        {"Speck", "SLw8Mk"},
        {"ag3nt", "eUrqfg"},
        {"r0mjk3", "7LLwLS"},
        {"verbrecher20", "3HuDg5"},
        {"x3demon", "yg6hkB"},
        {"sg", "XjMr6E"},
        {"demo", "demo"}
    };


    auto ptr = std::make_unique<Chat>();
    ptr->ChangeCurrentState<StrangerState>(); //assume we are users now


    for (const auto& msg : offtop) ptr->send(msg[0], msg[2], msg[1]);


    for (const auto& bot : bots) ptr->addUser(bot.first, bot.second);

    std::cout << "::CHAT INIT DONE::";
    //system("cls");
    std::cout << utils::clear_escape_code;

    ptr->ChangeCurrentState<StrangerState>();
    return ptr;
}



int main()
{
    //setlocale(LC_ALL, "Russian");
    system("chcp 65001"); // с этой магической командой у меня под виндой таки показывает текст по-русски
    auto chatroom =  initChat();



    for (int i = 1; i <= 100; ++i)
        chatroom->interact();


    return 0;
}
