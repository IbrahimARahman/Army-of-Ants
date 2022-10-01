#include "Creature.h"
//derived Beetle Class
class Beetle : public Creature{
private:
    int i = 0;
    int j = 0;
    char beetleChar;
    int starveCount = 0;
    bool ateThisTurn = false;
public:
    char Move(int dirArray[4]);
    bool Breed();
    bool Starve();
    void Eat(){starveCount = -1;}
    void coord(int i, int j);

    // returns the character for Beetle
    char whatAmI(){return beetleChar;}

    // constructor and destructor
    Beetle(char beetleChar);
    ~Beetle();
};