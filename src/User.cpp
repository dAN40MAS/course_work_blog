#include "../include/User.h"

User::User(const std::string& username, const std::string& password, const Profile& profile)
    : username(username), password(password), profile(profile),
      blog(std::make_unique<Blog>(username)) {}

bool User::check_password(const std::string& pwd) const { return password == pwd; }

Blog& User::get_blog() { return *blog; }
Profile& User::get_profile() { return profile; }
std::string User::get_username() const { return username; }

void User::print_info() const {
    std::cout << "\n═════════ Профиль " << username << " ═════════\n";
    profile.print();
}
