#include "../include/UserFactory.h"

UserFactory::UserFactory(std::shared_ptr<IUserRepository> repo) : repo(repo) {}

std::shared_ptr<User> UserFactory::create_user(
    const std::string& username,
    const std::string& password,
    const std::string& bio,
    const std::vector<std::string>& interests
) {
    auto user = std::make_shared<User>(username, password, Profile(bio, interests));
    repo->add_user(user);
    return user;
}
