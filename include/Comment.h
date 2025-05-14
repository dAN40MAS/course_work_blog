#pragma once
#include <string>
#include <ctime>

class Comment {
    std::string author;
    std::string text;
    std::time_t date;

public:
    Comment(const std::string& author, const std::string& text);
    void print() const;
};
