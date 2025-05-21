#include "../include/BlogConsole.h"
#include <iostream>
#include <limits>
#include <sstream>
#include "../include/AuthService.h"
#include "../include/BlogService.h"
#include "../include/UserFactory.h"

BlogConsole::BlogConsole() {
    user_repo = std::make_shared<UserRepository>();
    auth_service = std::make_shared<AuthService>(user_repo);
    blog_service = std::make_shared<BlogService>(user_repo);
    user_repo->loadFromFile("blog_data.json");
}

int BlogConsole::read_int() {
    std::string input;
    std::getline(std::cin, input);
    try { return std::stoi(input); } catch (...) { return -1; }
}

void BlogConsole::print_main_menu() {
    std::cout << "\n═════════ Блог-платформа ═════════\n1. Регистрация\n2. Вход\n3. Просмотр всех постов\n4. Выход\nВыбор: ";
}

void BlogConsole::handle_registration() {
    std::string username, password, bio, input;
    std::vector<std::string> interests;
    std::cout << "\n═════════ Регистрация ═════════\nЛогин: ";
    std::getline(std::cin, username);
    std::cout << "Пароль: ";
    std::getline(std::cin, password);
    std::cout << "О себе: ";
    std::getline(std::cin, bio);
    std::cout << "Интересы (через запятую): ";
    std::getline(std::cin, input);
    std::istringstream iss(input);
    while (std::getline(iss, input, ',')) interests.push_back(input.substr(0, input.find_first_not_of(" ")));
    UserFactory factory(user_repo);
    factory.create_user(username, password, bio, interests);
    std::cout << "Регистрация успешна!\n";
}

void BlogConsole::handle_login() {
    std::string username, password;
    std::cout << "\n═════════ Вход ═════════\nЛогин: ";
    std::getline(std::cin, username);
    std::cout << "Пароль: ";
    std::getline(std::cin, password);
    current_user = auth_service->authenticate(username, password);
    if (current_user) user_session();
    else std::cout << "Ошибка входа!\n";
}

void BlogConsole::user_session() {
    int choice;
    do {
        std::cout << "\n═════════ Личный кабинет ═════════\n1. Мой профиль\n2. Новый пост\n3. Мои посты\n4. Все посты\n5. Оставить комментарий\n6. Выход\nВыбор: ";
        choice = read_int();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
            case 1: current_user->print_info(); break;
            case 2: {
                std::string title, content;
                std::cout << "Заголовок: ";
                std::getline(std::cin, title);
                std::cout << "Текст поста:\n";
                std::getline(std::cin, content);
                blog_service->create_post(current_user->get_username(), title, content);
                std::cout << "Пост опубликован!\n";
                break;
            }
            case 3: current_user->get_blog().print_posts(); break;
            case 4: blog_service->print_all_posts(); break;
            case 5: {
                blog_service->print_post_numbers();
                std::cout << "Номер поста: ";
                int n = read_int();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if(n <= 0) { std::cout << "Неверный номер поста!\n"; break; }
                std::cout << "Текст комментария: ";
                std::string text; 
                std::getline(std::cin, text);
                std::cout << (blog_service->add_comment(current_user->get_username(), n, text) ? "Комментарий добавлен!\n" : "Ошибка!\n");
                break;
            }
            case 6: break;
            default: std::cout << "Неверный выбор!\n";
        }
    } while (choice != 6);
}

void BlogConsole::run() {
    int choice;
    do {
        print_main_menu();
        choice = read_int();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
            case 1: handle_registration(); break;
            case 2: handle_login(); break;
            case 3: blog_service->print_all_posts(); break;
            case 4: std::cout << "Выход из системы...\n"; break;
            default: std::cout << "Неверный выбор!\n";
        }
    } while (choice != 4);
    
    user_repo->saveToFile("blog_data.json");
}