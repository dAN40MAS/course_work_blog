#pragma once

#include <memory>
#include <string>
#include <json/json.h>
#include "Profile.h"
#include "Blog.h"

class User {
    std::string username;
    std::string password;
    Profile profile;
    std::unique_ptr<Blog> blog;

public:
    User(const std::string& username, const std::string& password, const Profile& profile);
    bool check_password(const std::string& pwd) const;
    Blog& get_blog();
    std::string get_username() const;
    void print_info() const;
    
    Json::Value toJson() const;
    static std::shared_ptr<User> fromJson(const Json::Value& json);
};