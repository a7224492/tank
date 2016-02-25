TARGET = tank
CONFIG += console
LIBS += -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf

SOURCES +=\
		  main.cpp \
    BombEffect.cpp \
    bullet.cpp \
    BulletState.cpp \
    C2DMatrix.cpp \
    enemy_bullet.cpp \
    enemy_tank.cpp \
    game.cpp \
    GameObject.cpp \
    MoveObjectState.cpp \
    my_bullet.cpp \
    mytank.cpp \
    MyTankState.cpp \
    ResourceManager.cpp \
    tank.cpp \
    TankState.cpp \
    utils.cpp \
    Vector2d.cpp \
    move_object.cpp \
    enemytankstate.cpp

HEADERS += \
    BombEffect.h \
    bullet.h \
    BulletState.h \
    C2DMatrix.h \
    enemy_bullet.h \
    enemy_tank.h \
    game.h \
    GameObject.h \
    MoveObjectState.h \
    my_bullet.h \
    mytank.h \
    MyTankState.h \
    ResourceManager.h \
    State.h \
    StateMachine.h \
    tank.h \
    TankState.h \
    utils.h \
    Vector2D.h \
    move_object.h \
    enemytankstate.h
