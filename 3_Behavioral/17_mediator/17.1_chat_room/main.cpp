#pragma once

#include <iostream>

#include "Person.h"
#include "chat_room.h"




int main()
{
    ChatRoom room;

    Person john{ "john" };
    Person jane{ "jane" };
    room.join(&john);
    room.join(&jane);
    john.say("hi room");
    jane.say("oh, hey john");

    Person simon("simon");
    room.join(&simon);
    simon.say("hi everyone!");

    jane.pm("simon", "glad you could join us, simon");

    getchar();
    return 0;
}