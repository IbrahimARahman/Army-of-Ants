#include "Creature.h"
// derived ant class
class Ant : public Creature{
private:
    char antChar;
public:
    char Move(int dirArray[4]);
    bool Breed();

    // returns the character for Ant
    char whatAmI(){return antChar;}

    // constructor and destructor
    Ant(char antChar);
    ~Ant();
};