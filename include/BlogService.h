#pragma once
#include "IUserRepository.h"
#include <memory>
#include <utility>

class BlogService {
    std::shared_ptr<IUserRepository> user_repo;

    std::pair<std::string, int> find_post(int global_index);

public:
    BlogService(std::shared_ptr<IUserRepository> repo);
    bool create_post(const std::string& username, const std::string& title, const std::string& content);
    void print_all_posts();
    bool add_comment(const std::string& commenter, int post_index, const std::string& text);
    void print_post_numbers();
};
