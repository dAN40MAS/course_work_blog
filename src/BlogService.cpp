#include "../include/BlogService.h"
#include <iostream>

std::pair<std::string, int> BlogService::find_post(int global_index) {
    int counter = 1;
    for (auto& user : user_repo->get_all_users()) {
        auto& posts = user->get_blog().get_posts();
        for (size_t i = 0; i < posts.size(); ++i) {
            if (counter++ == global_index) return {user->get_username(), static_cast<int>(i)};
        }
    }
    return {"", -1};
}

BlogService::BlogService(std::shared_ptr<IUserRepository> repo) : user_repo(repo) {}

bool BlogService::create_post(const std::string& username, const std::string& title, const std::string& content) {
    if (auto user = user_repo->find_user(username)) {
        user->get_blog().add_post(Post(username, title, content));
        return true;
    }
    return false;
}

void BlogService::print_all_posts() {
    std::cout << "\n═════════ Все посты в системе ═════════\n";
    for (auto& user : user_repo->get_all_users()) {
        auto& posts = user->get_blog().get_posts();
        if (!posts.empty()) {
            std::cout << "\n═════════ Посты пользователя " << user->get_username() << " ═════════\n";
            for (const auto& post : posts) {
                post.print();
            }
        }
    }
}

bool BlogService::add_comment(const std::string& commenter, int post_index, const std::string& text) {
    auto [author, index] = find_post(post_index);
    if (author.empty()) return false;

    if (auto user = user_repo->find_user(author)) {
        auto& posts = user->get_blog().get_posts();
        if (index >= 0 && static_cast<size_t>(index) < posts.size()) {
            posts[index].add_comment(Comment(commenter, text));
            return true;
        }
    }
    return false;
}

void BlogService::print_post_numbers() {
    int counter = 1;
    for (auto& user : user_repo->get_all_users()) {
        for (const auto& post : user->get_blog().get_posts()) {
            std::cout << counter++ << ". " << post.get_title()
                      << " (" << user->get_username() << ")\n";
        }
    }
}
