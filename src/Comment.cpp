#include "../include/Comment.h"
#include <iostream>
#include <ctime>

Comment::Comment(const std::string& author, const std::string& text)
    : author(author), text(text), date(std::time(nullptr)) {}

void Comment::print() const {
    char time_str[100];
    std::strftime(time_str, sizeof(time_str), "%H:%M %d/%m/%Y", std::localtime(&date));
    std::cout << author << " [" << time_str << "]: " << text << "\n";
}
