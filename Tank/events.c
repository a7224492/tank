#include "events.h"
#include "tank.h"
#include "move.h"
#include "shot.h"

extern MyTank myTank;

void setMyTankKeyEvent(Uint8 *keystate)
{
    BOOL isMyTankMove = FALSE;

    if (keystate[SDLK_w])
    {
        setMyTankDir(&myTank, UP);
        isMyTankMove = TRUE;
    }if (keystate[SDLK_s])
    {
        setMyTankDir(&myTank, DOWN);
        isMyTankMove = TRUE;
    }if (keystate[SDLK_a])
    {
        setMyTankDir(&myTank, LEFT);
        isMyTankMove = TRUE;
    }if (keystate[SDLK_d])
    {
        setMyTankDir(&myTank, RIGHT);
        isMyTankMove = TRUE;
    }

    if (keystate[SDLK_j])
    {
        myTankShot();
    }
    if (isMyTankMove)
    {
        myTank.isMove = TRUE;
    }
}
