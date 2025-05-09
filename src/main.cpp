#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <memory>

// Класс комментария
class Comment {
private:
    std::string author;
    std::time_t date;
    std::string text;
public:
    Comment(const std::string& author, const std::string& text)
        : author(author), text(text), date(std::time(nullptr)) {}

    void print() const {
        std::cout << author << " (" << std::ctime(&date) << "): " << text << "\n";
    }
};

// Класс поста
class Post {
private:
    std::string author;
    std::string title;
    std::string content;
    std::time_t date;
    std::vector<Comment> comments;
    bool commentsAllowed;
public:
    Post(const std::string& author, const std::string& title, const std::string& content)
        : author(author), title(title), content(content), date(std::time(nullptr)), commentsAllowed(true) {}

    void addComment(const Comment& comment) {
        if (commentsAllowed) {
            comments.push_back(comment);
        }
    }

    void print() const {
        std::cout << "\n=== " << title << " ===\n";
        std::cout << "Author: " << author << "\n";
        std::cout << "Date: " << std::ctime(&date);
        std::cout << content << "\n\nComments:\n";
        for (const auto& comment : comments) {
            comment.print();
        }
    }

    void toggleComments() { commentsAllowed = !commentsAllowed; }
};

// Класс профиля
class Profile {
private:
    std::string bio;
    std::vector<std::string> interests;
public:
    Profile(const std::string& bio = "", const std::vector<std::string>& interests = {})
        : bio(bio), interests(interests) {}

    void print() const {
        std::cout << "\nBio: " << bio << "\n";
        std::cout << "Interests: ";
        for (const auto& interest : interests) {
            std::cout << interest << ", ";
        }
        std::cout << "\n";
    }
};

// Класс пользователя
class User {
private:
    std::string username;
    std::string password;
    Profile profile;
    std::vector<Post> posts;
public:
    User(const std::string& username, const std::string& password, const Profile& profile)
        : username(username), password(password), profile(profile) {}

    bool checkPassword(const std::string& pwd) const { return password == pwd; }

    void addPost(const Post& post) {
        posts.push_back(post);
    }

    void printPosts() const {
        for (const auto& post : posts) {
            post.print();
        }
    }

    void printInfo() const {
        std::cout << "\n=== " << username << " ===\n";
        profile.print();
    }

    std::string getUsername() const { return username; }
};

// Класс репозитория пользователей
class UserRepository {
private:
    std::vector<User> users;
public:
    void addUser(const User& user) {
        users.push_back(user);
    }

    User* findUser(const std::string& username) {
        for (auto& user : users) {
            if (user.getUsername() == username) {
                return &user;
            }
        }
        return nullptr;
    }

    const std::vector<User>& getAllUsers() const {
        return users;
    }
};

// Класс консольного интерфейса
class BlogConsole {
private:
    UserRepository userRepo;
    User* currentUser;

    void printMainMenu() {
        std::cout << "\n=== Blog System ===\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. View all posts\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";
    }

    void printUserMenu() {
        std::cout << "\n=== Welcome, " << currentUser->getUsername() << " ===\n";
        std::cout << "1. View profile\n";
        std::cout << "2. Create post\n";
        std::cout << "3. View my posts\n";
        std::cout << "4. View all posts\n";
        std::cout << "5. Logout\n";
        std::cout << "Choice: ";
    }

    void registerUser() {
        std::string username, password, bio;
        std::vector<std::string> interests;

        std::cout << "\nUsername: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        std::cin.ignore();
        std::cout << "Bio: ";
        std::getline(std::cin, bio);

        std::cout << "Enter interests (comma separated): ";
        std::string interestsStr;
        std::getline(std::cin, interestsStr);

        size_t pos = 0;
        while ((pos = interestsStr.find(',')) != std::string::npos) {
            interests.push_back(interestsStr.substr(0, pos));
            interestsStr.erase(0, pos + 1);
        }
        interests.push_back(interestsStr);

        Profile profile(bio, interests);
        User user(username, password, profile);
        userRepo.addUser(user);
        std::cout << "User registered successfully!\n";
    }

    void login() {
        std::string username, password;
        std::cout << "\nUsername: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        currentUser = userRepo.findUser(username);
        if (currentUser && currentUser->checkPassword(password)) {
            std::cout << "Login successful!\n";
            userSession();
        } else {
            std::cout << "Invalid credentials!\n";
        }
    }

    void userSession() {
        int choice;
        do {
            printUserMenu();
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
                case 1:
                    currentUser->printInfo();
                    break;
                case 2: {
                    std::string title, content;
                    std::cout << "Post title: ";
                    std::getline(std::cin, title);
                    std::cout << "Post content: ";
                    std::getline(std::cin, content);
                    currentUser->addPost(Post(currentUser->getUsername(), title, content));
                    std::cout << "Post created!\n";
                    break;
                }
                case 3:
                    std::cout << "\n=== My Posts ===\n";
                    currentUser->printPosts();
                    break;
                case 4:
                    std::cout << "\n=== All Posts ===\n";
                    for (const auto& user : userRepo.getAllUsers()) {
                        user.printPosts();
                    }
                    break;
                case 5:
                    currentUser = nullptr;
                    std::cout << "Logged out.\n";
                    break;
                default:
                    std::cout << "Invalid choice.\n";
            }
        } while (currentUser && choice != 5);
    }

public:
    void run() {
        int choice;
        do {
            printMainMenu();
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
                case 1: registerUser(); break;
                case 2: login(); break;
                case 3:
                    std::cout << "\n=== All Posts ===\n";
                    for (const auto& user : userRepo.getAllUsers()) {
                        user.printPosts();
                    }
                    break;
                case 4: std::cout << "Goodbye!\n"; break;
                default: std::cout << "Invalid choice.\n";
            }
        } while (choice != 4);
    }
};

int main() {
    BlogConsole console;
    console.run();
    return 0;
}
