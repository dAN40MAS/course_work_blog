#pragma once
#include "Post.h"
#include <vector>
#include <string>

class Blog {
    std::string owner;
    std::vector<Post> posts;

public:
    Blog(const std::string& owner);
    void add_post(const Post& post);
    void print_posts() const;
    std::vector<Post>& get_posts();
    std::string get_owner() const;
};
