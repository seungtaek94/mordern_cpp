#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "Person.h"



struct ChatRoom
{
    std::vector<Person*> people;

public:
    void join(Person* p)
    {
        std::string join_msg = p->name + " join the chat";
        this->broadcast("room", join_msg);
        p->room = this;
        people.push_back(p);
    }

    void broadcast(const std::string& origin, const std::string& message)
    {
        for (auto p : people)
        {
            if(p->name != origin)
            {
                p->resceive(origin, message);
            }
        }
    }

    void message(const std::string& origin, const std::string& who, const std::string& message)
    {
        auto target = std::find_if(std::begin(people), std::end(people),
                                   [&](const Person* p) {return  p->name == who; });

        if(target != std::end(people))
        {
            (*target)->resceive(origin, message);
        }
    }
};