#include "../include/Blog.h"
#include <algorithm>
#include <iostream>

Blog::Blog(const std::string& owner) : owner(owner) {}

void Blog::add_post(const Post& post) {
    posts.push_back(post);
    std::sort(posts.begin(), posts.end(),
        [](const Post& a, const Post& b) { return a.get_date() > b.get_date(); });
}

void Blog::print_posts() const {
    std::cout << "\n═════════ Посты пользователя " << owner << " ═════════\n";
    for (const auto& p : posts) p.print();
}

std::vector<Post>& Blog::get_posts() { return posts; }
std::string Blog::get_owner() const { return owner; }
