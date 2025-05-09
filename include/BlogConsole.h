#pragma once
#include "UserRepository.h"
#include "AuthService.h"
#include "BlogService.h"
#include <memory>

class BlogConsole {
    std::shared_ptr<UserRepository> user_repo;
    std::shared_ptr<AuthService> auth_service;
    std::shared_ptr<BlogService> blog_service;
    std::shared_ptr<User> current_user;

public:
    BlogConsole();
    void run();

private:
    void print_main_menu();
    void handle_registration();
    void handle_login();
    void user_session();
};
