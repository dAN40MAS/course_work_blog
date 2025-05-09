#pragma once
#include "Profile.h"
#include "Blog.h"
#include <memory>
#include <string>
#include <iostream>

class User {
    std::string username;
    std::string password;
    Profile profile;
    std::unique_ptr<Blog> blog;

public:
    User(const std::string& username, const std::string& password, const Profile& profile);
    bool check_password(const std::string& pwd) const;
    Blog& get_blog();
    Profile& get_profile();
    std::string get_username() const;
    void print_info() const;
};
