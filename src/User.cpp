#include "../include/User.h"

User::User(const std::string& username, const std::string& password, const Profile& profile)
    : username(username), password(password), profile(profile),
      blog(std::make_unique<Blog>(username)) {}

bool User::check_password(const std::string& pwd) const { return password == pwd; }
Blog& User::get_blog() { return *blog; }
std::string User::get_username() const { return username; }

void User::print_info() const {
    std::cout << "\n═════════ Профиль " << username << " ═════════\n";
    profile.print();
}

Json::Value User::toJson() const {
    Json::Value json;
    json["username"] = username;
    json["password"] = password;
    json["profile"] = profile.toJson();
    json["blog"] = blog->toJson();
    return json;
}

std::shared_ptr<User> User::fromJson(const Json::Value& json) {
    auto user = std::make_shared<User>(
        json["username"].asString(),
        json["password"].asString(),
        Profile::fromJson(json["profile"])
    );
    user->blog = std::make_unique<Blog>(Blog::fromJson(json["blog"]));
    return user;
}