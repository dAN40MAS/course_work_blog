#include "../include/BlogConsole.h"
#include "../include/UserFactory.h"
#include <iostream>
#include <sstream>

BlogConsole::BlogConsole() {
    user_repo = std::make_shared<UserRepository>();
    auth_service = std::make_shared<AuthService>(user_repo);
    blog_service = std::make_shared<BlogService>(user_repo);

    UserFactory factory(user_repo);
    factory.create_user("admin", "admin", "Администратор", {"программирование"});
    factory.create_user("user", "123", "Обычный пользователь", {"книги", "музыка"});
}

void BlogConsole::print_main_menu() {
    std::cout << "\n═════════ Блог-платформа ═════════\n"
                 "1. Регистрация\n"
                 "2. Вход\n"
                 "3. Просмотр всех постов\n"
                 "4. Выход\n"
                 "Выбор: ";
}

void BlogConsole::handle_registration() {
    std::string username, password, bio, input;
    std::vector<std::string> interests;

    std::cout << "\n═════════ Регистрация ═════════\nЛогин: ";
    std::cin >> username;
    std::cout << "Пароль: ";
    std::cin >> password;

    std::cin.ignore();
    std::cout << "О себе: ";
    std::getline(std::cin, bio);

    std::cout << "Интересы (через запятую): ";
    std::getline(std::cin, input);

    std::istringstream iss(input);
    while (std::getline(iss, input, ','))
        interests.push_back(input.substr(0, input.find_first_not_of(" ")));

    UserFactory factory(user_repo);
    factory.create_user(username, password, bio, interests);
    std::cout << "Регистрация успешна!\n";
}

void BlogConsole::handle_login() {
    std::string username, password;
    std::cout << "\n═════════ Вход ═════════\nЛогин: ";
    std::cin >> username;
    std::cout << "Пароль: ";
    std::cin >> password;

    current_user = auth_service->authenticate(username, password);
    if (current_user) user_session();
    else std::cout << "Ошибка входа!\n";
}

void BlogConsole::user_session() {
    int choice;
    do {
        std::cout << "\n═════════ Личный кабинет ═════════\n"
                     "1. Мой профиль\n"
                     "2. Новый пост\n"
                     "3. Мои посты\n"
                     "4. Все посты\n"
                     "5. Оставить комментарий\n"
                     "6. Выход\n"
                     "Выбор: ";
        std::cin >> choice;
        std::cin.ignore();

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
                int n; std::cin >> n; std::cin.ignore();
                std::cout << "Текст комментария: ";
                std::string text; std::getline(std::cin, text);
                std::cout << (blog_service->add_comment(current_user->get_username(), n, text)
                          ? "Комментарий добавлен!\n" : "Ошибка!\n");
                break;
            }
        }
    } while (choice != 6);
}

void BlogConsole::run() {
    int choice;
    do {
        print_main_menu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: handle_registration(); break;
            case 2: handle_login(); break;
            case 3: blog_service->print_all_posts(); break;
        }
    } while (choice != 4);
}
