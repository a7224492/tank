#ifndef MOVE_H
#define MOVE_H

struct _MyTank;
typedef struct _MyTank MyTank;
typedef int BOOL;

void moveMyTank(int ms);
BOOL moveMyBullet(MyTank *myTank, int i, int ms);

#endif // MOVE_H

