#pragma once

#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include "Comment.h"

class Blog;
class Comment;

class Post {
    std::string author;
    std::string title;
    std::string content;
    std::time_t creation_date;
    std::vector<Comment> comments;

public:
    Post(const std::string& author, const std::string& title, const std::string& content);
    void add_comment(const Comment& comment);
    void print() const;
    
    std::time_t get_date() const { return creation_date; }
    std::string get_title() const { return title; }
    std::string get_author() const { return author; }
    std::string get_content() const { return content; }
    
    Json::Value toJson() const;
    static Post fromJson(const Json::Value& json);
};