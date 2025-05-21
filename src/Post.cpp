#include "../include/Post.h"
#include <ctime>
#include <iomanip>

Post::Post(const std::string& author, const std::string& title, const std::string& content)
    : author(author), title(title), content(content), creation_date(std::time(nullptr)) {}

void Post::add_comment(const Comment& comment) {
    comments.push_back(comment);
}

void Post::print() const {
    char time_str[100];
    std::strftime(time_str, sizeof(time_str), "%H:%M %d/%m/%Y", std::localtime(&creation_date));
    std::cout << "\n════════ " << title << " ════════\n"
              << "Автор: " << author << "\n"
              << "Дата: " << time_str << "\n\n"
              << content << "\n";
}

Json::Value Post::toJson() const {
    Json::Value json;
    json["author"] = author;
    json["title"] = title;
    json["content"] = content;
    json["date"] = static_cast<Json::Int64>(get_date());
    
    Json::Value commentsJson;
    for (const auto& c : comments) {
        commentsJson.append(c.toJson());
    }
    json["comments"] = commentsJson;
    return json;
}

Post Post::fromJson(const Json::Value& json) {
    Post post(
        json["author"].asString(),
        json["title"].asString(),
        json["content"].asString()
    );
    
    for (const auto& c : json["comments"]) {
        post.add_comment(Comment::fromJson(c));
    }
    return post;
}