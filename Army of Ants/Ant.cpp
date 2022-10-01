#include "Ant.h"
#include <vector>
using namespace std;

// takes in an array with the distance to the closest beetle in all 4 cardinal directions and returns the direction the ant should move in
char Ant :: Move(int dirArray[4]){
    hasMoved = true;
    int minimum = 10;
    for(int i = 0; i < 4; i++){
        if(dirArray[i] > 0 && dirArray[i] < minimum)
            minimum = dirArray[i];
    }
    if(minimum == 10){
        return 'X';
    }
    // if one beetle
    vector<char> direction;
    if(minimum == dirArray[2])
        direction.push_back('N');
    if(minimum == dirArray[3])
        direction.push_back('E');
    if(minimum == dirArray[0])
        direction.push_back('S');
    if(minimum == dirArray[1])
        direction.push_back('W');
    if(direction.size() == 1)
        return direction[0];
    else{
        // if multiple beetles
        if(dirArray[0] == 0)
            return 'N';
        if(dirArray[1] == 0)
            return 'E';
        if(dirArray[2] == 0)
            return 'S';
        if(dirArray[3] == 0)
            return 'W';
        // if 4 beetles
        int maximum = 0;
        for(int i = 0; i < 4; i++){
            if(dirArray[i] > maximum)
                maximum = dirArray[i];
        }
        direction.clear();
        if(maximum == dirArray[0])
            direction.push_back('N');
        if(maximum == dirArray[1])
            direction.push_back('E');
        if(maximum == dirArray[2])
            direction.push_back('S');
        if(maximum == dirArray[3])
            direction.push_back('W');
        return direction[0];
    }
}

// returns a bool about whether to breed or not
bool Ant :: Breed(){
    madeThisTurn = true;
    return madeThisTurn;
}

// constructor and destructor
Ant :: Ant(char antChar) : Creature(){
    this->antChar = antChar;
}
Ant :: ~Ant(){}