#include "units.h"
#include "defs.h"

struct MoveUnit
{
    int x, y;
    SDL_Surface *img;
    enum Dir dir;
};


inline int getMoveUnitX(MoveUnit *unit)
{
    return unit->x;
}

inline void setMoveUnitX(MoveUnit *unit, int x)
{
    unit->x = x;
}

inline int getMoveUnitY(MoveUnit *unit)
{
    return unit->y;
}

inline void setMoveunitY(MoveUnit *unit, int y)
{
    unit->y = y;
}

inline DIR getMoveUnitDir(MoveUnit *unit)
{
    return unit->dir;
}

inline void setMoveUnit(MoveUnit *unit, DIR dir)
{
    unit->dir = dir;
}
inline SDL_Surface* getMoveUnitImg(MoveUnit *unit)
{
    return unit->img;
}
