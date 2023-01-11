#include "World.h"

World::World(float clearRed, float clearGreen, float clearBlue, const ltex_t* back0, const ltex_t* back1,
    const ltex_t* back2, const ltex_t* back3)
{
    background[0] = back0;
    background[1] = back1;
    background[2] = back2;
    background[3] = back3;
}