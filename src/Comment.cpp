#include "../include/Comment.h"
#include <ctime>
#include <iostream>

Comment::Comment(const std::string& author, const std::string& text) 
    : author(author), text(text), date(std::time(nullptr)) {}

void Comment::print() const {
    char time_str[100];
    std::strftime(time_str, sizeof(time_str), "%H:%M %d/%m/%Y", std::localtime(&date));
    std::cout << author << " [" << time_str << "]: " << text << "\n";
}

Json::Value Comment::toJson() const {
    Json::Value json;
    json["author"] = author;
    json["text"] = text;
    json["date"] = static_cast<Json::Int64>(date);
    return json;
}

Comment Comment::fromJson(const Json::Value& json) {
    return Comment(
        json["author"].asString(),
        json["text"].asString()
    );
}