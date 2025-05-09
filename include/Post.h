#pragma once
#include "Comment.h"
#include <vector>
#include <string>
#include <ctime>

class Post {
    std::string author;
    std::string title;
    std::string content;
    std::time_t date;
    std::vector<Comment> comments;

public:
    Post(const std::string& author, const std::string& title, const std::string& content);
    void add_comment(const Comment& comment);
    void print() const;
    std::string get_author() const;
    std::string get_title() const;
    std::time_t get_date() const;
};
