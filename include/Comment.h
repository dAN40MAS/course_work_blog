#pragma once
#include <string>
#include <ctime>

class Comment {
    std::string author;
    std::time_t date;
    std::string text;

public:
    Comment(const std::string& author, const std::string& text);
    void print() const;
};
