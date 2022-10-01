#include "Beetle.h"
#include <vector>
#include <algorithm>
using namespace std;

// takes in an array with the distances and surrounding ants of the closest ants in all 4 cardinal directions and returns which direction the Beetle should move
char Beetle :: Move(int dirArray[4]){
    hasMoved = true;
    bool antExists = false;
    int minimum = 10;
    int maxSurroundAnts = 0;
    for(int i = 0; i < 4; i++){
        if(dirArray[i]/10 > 0 && dirArray[i]/10 <= minimum){
            minimum = dirArray[i]/10;
            maxSurroundAnts = max(maxSurroundAnts, dirArray[i]%10);
            antExists = true;
        }
    }
    // if there is an ant
    if(antExists){
        vector<char> direction;
        if(minimum == dirArray[0]/10){
            direction.push_back('N');
        }
        if(minimum == dirArray[1]/10){
            direction.push_back('E');
        }
        if(minimum == dirArray[2]/10){
            direction.push_back('S');
        }
        if(minimum == dirArray[3]/10){
            direction.push_back('W');
        }
        if(direction.size() > 1){
            for(int i = 0; (unsigned)i < direction.size(); i++){
                if(direction[i] == 'N' && maxSurroundAnts == dirArray[0]%10)
                    return 'N';
                if(direction[i] == 'E' && maxSurroundAnts == dirArray[1]%10)
                    return 'E';
                if(direction[i] == 'S' && maxSurroundAnts == dirArray[2]%10)
                    return 'S';
                if(direction[i] == 'W' && maxSurroundAnts == dirArray[3]%10)
                    return 'W';
            }
        }
        return direction[0];
    }// if there isn't an ant
    else{
        int disToNorth = i;
        int disToEast = 9-j;
        int disToSouth = 9-i;
        int disToWest = j;
        int maxDis = max(max(max(disToNorth, disToEast), disToSouth), disToWest);
        vector<char> direction;
        if(maxDis == disToNorth)
            direction.push_back('N');
        if(maxDis == disToEast)
            direction.push_back('E');
        if(maxDis == disToSouth)
            direction.push_back('S');
        if(maxDis == disToWest)
            direction.push_back('W');
        return direction[0];
    }
}

// returns a bool about whether to breed or not
bool Beetle :: Breed(){
    madeThisTurn = true;
    return madeThisTurn;
}

// returns a bool about whether to starve or not
bool Beetle :: Starve(){
    if(starveCount == 4){
        return true;
    }
    starveCount++;
    return false;
}

// used to input coordinates to they can be used in move
void Beetle :: coord(int i, int j){
    this->i = i;
    this->j = j;
}

// constructor and destructor
Beetle :: Beetle(char beetleChar) : Creature(){
    this->beetleChar = beetleChar;
}
Beetle :: ~Beetle(){}