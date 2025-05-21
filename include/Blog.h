#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "Post.h"

class Blog {
    std::string owner;
    std::vector<Post> posts;

public:
    Blog(const std::string& owner);
    void add_post(const Post& post);
    void print_posts() const;
    std::vector<Post>& get_posts();
    std::string get_owner() const;
    
    Json::Value toJson() const;
    static Blog fromJson(const Json::Value& json);
};