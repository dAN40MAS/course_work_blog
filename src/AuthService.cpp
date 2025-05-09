#include "AuthService.h"

AuthService::AuthService(std::shared_ptr<IUserRepository> repo) : user_repo(repo) {}

std::shared_ptr<User> AuthService::authenticate(const std::string& username, const std::string& password) {
    auto user = user_repo->find_user(username);
    return (user && user->check_password(password)) ? user : nullptr;
}
