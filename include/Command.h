#pragma once
#include "Vec2.h"

class Command {
public:
    enum CommandType { MOVE, SHOOT };

    CommandType type;
    Vec2 pos;

    Command(CommandType type, float x, float y);
};
