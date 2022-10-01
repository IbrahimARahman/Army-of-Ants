#ifndef CREATURE_H
#define CREATURE_H
#include <iostream>
// base class
class Creature{
protected:
    // instance variables that apply to both ants and beetles
    bool hasMoved = false;
    bool madeThisTurn = true;
public:
    // abstract functions
    virtual char Move(int dirArray[4]) = 0;
    virtual bool Breed() = 0;
    virtual char whatAmI() = 0;

    // inline functions
    bool Moved(){return hasMoved;}
    bool bredThisTurn(){return madeThisTurn;}
    void setNotMoved(){hasMoved = false;}
    void setNotBreeded(){madeThisTurn = false;}

    // constructor and destructor
    Creature(){};
    virtual ~Creature(){};
};

#endif // Creature_H