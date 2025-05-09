#include "../include/Post.h"
#include <iostream>
#include <ctime>

Post::Post(const std::string& author, const std::string& title, const std::string& content)
    : author(author), title(title), content(content), date(std::time(nullptr)) {}

void Post::add_comment(const Comment& comment) {
    comments.push_back(comment);
}

void Post::print() const {
    char time_str[100];
    std::strftime(time_str, sizeof(time_str), "%H:%M %d/%m/%Y", std::localtime(&date));

    std::cout << "\n════════ " << title << " ════════\n"
              << "Автор: " << author << "\n"
              << "Дата: " << time_str << "\n\n"
              << content << "\n\n"
              << "Комментарии (" << comments.size() << "):\n";

    for (const auto& c : comments) c.print();
}

std::string Post::get_author() const { return author; }
std::string Post::get_title() const { return title; }
std::time_t Post::get_date() const { return date; }
