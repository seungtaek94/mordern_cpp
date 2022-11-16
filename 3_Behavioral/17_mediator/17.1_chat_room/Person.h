#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "chat_room.h"

struct Person
{
    std::string name;
    ChatRoom* room = nullptr;
    std::vector<std::string> chat_log;

public:
    Person(const std::string& name):name(name) {}

    void resceive(const std::string& origin, const std::string& message)
    {
        std::string s{ origin + ": \"" + message + "\""};
        std::cout << "[" << name << "'s chat session] " << s << "\n";
        chat_log.emplace_back(s);
    }

    void say(const std::string& message) const
    {
        room->broadcast(name, message);
    }

    void pm(const std::string& who, const std::string& message) const
    {
        room->message(name, who, message);
    }
};