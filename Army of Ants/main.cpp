// Ibrahim Abdel Rahman: IXA210020
#include "Creature.h"
#include "Ant.h"
#include "Beetle.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// prototypes
int countSurroundingAnts(Creature *grid[10][10], int i, int j);
void PrintGrid(Creature *grid[10][10], int turn);
void setHasMovedFalse(Creature *grid[10][10]);

int main(){

    // file name input for the grid
    string gridName;
    cin >> gridName;

    // input for the character for ant and beetle
    char antChar;
    char beetleChar;
    cin >> antChar;
    cin >> beetleChar;

    // getting number of turns
    int turns;
    cin >> turns;
    // creates and populates a grid of Creatures using the file
    ifstream readGrid(gridName); 
    Creature *grid[10][10];
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            char currChar;
            // looks at everything besides new like characters
            readGrid >> noskipws >> currChar;
            if(currChar!='\n'){
                if(currChar == 'a')
                    grid[i][j] = new Ant(antChar);
                else if(currChar == 'B')
                    grid[i][j] = new Beetle(beetleChar);
                else
                    grid[i][j] = nullptr;
            }
            else
                j--;
        }
    }

    for(int turn = 1; turn <= turns; turn++){
        // Beetles Move
        for(int j = 0; j < 10; j++){
            for(int i = 0; i < 10; i++){
                if(dynamic_cast<Beetle *>(grid[i][j]) && !dynamic_cast<Beetle *>(grid[i][j])->Moved()){
                    
                    // getting info for each ant to pass into move
                    int northAnt = 0;
                    for(int k = i; k >= 0; k--){
                        if(dynamic_cast<Ant *>(grid[k][j])){
                            northAnt += (i-k)*10;
                            northAnt += countSurroundingAnts(grid, k, j);
                            break;
                        }
                    }
                    int eastAnt = 0;
                    for(int k = j; k <= 9; k++){
                        if(dynamic_cast<Ant *>(grid[i][k])){
                            eastAnt += (k-j)*10;
                            eastAnt += countSurroundingAnts(grid, i, k);
                            break;
                        }
                    }
                    int southAnt = 0;
                    for(int k = i; k <= 9; k++){
                        if(dynamic_cast<Ant *>(grid[k][j])){
                            southAnt += (k-i)*10;
                            southAnt += countSurroundingAnts(grid, k, j);
                            break;
                        }
                    }
                    int westAnt = 0;
                    for(int k = j; k >= 0; k--){
                        if(dynamic_cast<Ant *>(grid[i][k])){
                            westAnt += (j-k)*10;
                            westAnt += countSurroundingAnts(grid, i, k);
                            break;
                        }
                    }
                    dynamic_cast<Beetle *>(grid[i][j])->coord(i, j);
                    int dirArray[4] = {northAnt, eastAnt, southAnt, westAnt};
                    char direction = grid[i][j]->Move(dirArray);
                    switch (direction)
                    {
                        case 'N':
                            if(i-1 >= 0){
                                if(dynamic_cast<Ant *>(grid[i-1][j])){
                                    dynamic_cast<Beetle *>(grid[i][j])->Eat();
                                    delete grid[i-1][j];
                                    grid[i-1][j] = grid[i][j];
                                    grid[i][j] = nullptr;

                                }
                                else if(grid[i-1][j] == nullptr){
                                    grid[i-1][j] = grid[i][j];
                                    grid[i][j] = nullptr;
                                }
                            }
                            break;
                        case 'E':
                            if(j+1 <= 9){
                                if(dynamic_cast<Ant *>(grid[i][j+1])){
                                    dynamic_cast<Beetle *>(grid[i][j])->Eat();
                                    delete grid[i][j+1];
                                    grid[i][j+1] = grid[i][j];
                                    grid[i][j] = nullptr;

                                }
                                else if(grid[i][j+1] == nullptr){
                                    grid[i][j+1] = grid[i][j];
                                    grid[i][j] = nullptr;
                                }
                            }
                            break;
                        case 'S':
                            if(i+1 <= 9){
                                if(dynamic_cast<Ant *>(grid[i+1][j])){
                                    dynamic_cast<Beetle *>(grid[i][j])->Eat();
                                    delete grid[i+1][j];
                                    grid[i+1][j] = grid[i][j];
                                    grid[i][j] = nullptr;

                                }
                                else if(grid[i+1][j] == nullptr){
                                    grid[i+1][j] = grid[i][j];
                                    grid[i][j] = nullptr;
                                }
                            }
                            break;
                        case 'W':
                            if(j-1 >= 0){
                                if(dynamic_cast<Ant *>(grid[i][j-1])){
                                    dynamic_cast<Beetle *>(grid[i][j])->Eat();
                                    delete grid[i][j-1];
                                    grid[i][j-1] = grid[i][j];
                                    grid[i][j] = nullptr;

                                }
                                else if(grid[i][j-1] == nullptr){
                                    grid[i][j-1] = grid[i][j];
                                    grid[i][j] = nullptr;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        
        // Ants Move
        for(int j = 0; j < 10; j++){
            for(int i = 0; i < 10; i++){
                if(dynamic_cast<Ant *>(grid[i][j]) && !dynamic_cast<Ant *>(grid[i][j])->Moved()){
                    // getting info for each beetle to pass into move
                    int northBeetle = 0;
                    for(int k = i; k >= 0; k--){
                        if(dynamic_cast<Beetle *>(grid[k][j])){
                            northBeetle += (i-k);
                            break;
                        }
                    }
                    int eastBeetle = 0;
                    for(int k = j; k <= 9; k++){
                        if(dynamic_cast<Beetle *>(grid[i][k])){
                            eastBeetle += (k-j);
                            break;
                        }
                    }
                    int southBeetle = 0;
                    for(int k = i; k <= 9; k++){
                        if(dynamic_cast<Beetle *>(grid[k][j])){
                            southBeetle += (k-i);
                            break;
                        }
                    }
                    int westBeetle = 0;
                    for(int k = j; k >= 0; k--){
                        if(dynamic_cast<Beetle *>(grid[i][k])){
                            westBeetle += (j-k);
                            break;
                        }
                    }
                    int dirArray[4] = {northBeetle, eastBeetle, southBeetle, westBeetle};
                    char direction = grid[i][j]->Move(dirArray);
                    switch (direction)
                    {
                        case 'N':
                            if(i-1 >= 0 && grid[i-1][j] == nullptr){
                                grid[i-1][j] = grid[i][j];
                                grid[i][j] = nullptr;
                            }
                            break;
                        case 'E':
                            if(j+1 <= 9 && grid[i][j+1] == nullptr){
                                grid[i][j+1] = grid[i][j];
                                grid[i][j] = nullptr;
                            }
                            break;
                        case 'S':
                            if(i+1 <= 9 && grid[i+1][j] == nullptr){
                                grid[i+1][j] = grid[i][j];
                                grid[i][j] = nullptr;
                            }
                            break;
                        case 'W':
                            if(j-1 >= 0 && grid[i][j-1] == nullptr){
                                grid[i][j-1] = grid[i][j];
                                grid[i][j] = nullptr;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        
        // Beetles Starve
        for(int j = 0; j < 10; j++){
            for(int i = 0; i < 10; i++){
                if(dynamic_cast<Beetle *>(grid[i][j]) && dynamic_cast<Beetle *>(grid[i][j])->Starve()){
                    delete grid[i][j];
                    grid[i][j] = nullptr;
                }
            }
        }
        
        // Ants Breed
        if(turn % 3 == 0){
            for(int j = 0; j < 10; j++){
                for(int i = 0; i < 10; i++){
                    if(dynamic_cast<Ant *>(grid[i][j]) && !dynamic_cast<Ant *>(grid[i][j])->bredThisTurn()){
                        grid[i][j]->Breed();
                        if(i-1 >= 0 && grid[i-1][j] == nullptr)
                            grid[i-1][j] = new Ant(antChar);
                        else if(j+1 <= 9 && grid[i][j+1] == nullptr)
                            grid[i][j+1] = new Ant(antChar);
                        else if(i+1 <= 9 && grid[i+1][j] == nullptr)
                            grid[i+1][j] = new Ant(antChar);
                        else if(j-1 >= 0 && grid[i][j-1] == nullptr)
                            grid[i][j-1] = new Ant(antChar);
                    }
                }
            }
        }
        
        // Beetles Breed
        if(turn % 8 == 0){
            for(int j = 0; j < 10; j++){
                for(int i = 0; i < 10; i++){
                    if(dynamic_cast<Beetle *>(grid[i][j]) && !dynamic_cast<Beetle *>(grid[i][j])->bredThisTurn()){
                        grid[i][j]->Breed();
                        if(i-1 >= 0 && grid[i-1][j] == nullptr)
                            grid[i-1][j] = new Beetle(beetleChar);
                        else if(j+1 <= 9 && grid[i][j+1] == nullptr)
                            grid[i][j+1] = new Beetle(beetleChar);
                        else if(i+1 <= 9 && grid[i+1][j] == nullptr)
                            grid[i+1][j] = new Beetle(beetleChar);
                        else if(j-1 >= 0 && grid[i][j-1] == nullptr)
                            grid[i][j-1] = new Beetle(beetleChar);
                    }
                }
            }
        }

        PrintGrid(grid, turn);
        setHasMovedFalse(grid);
    }
    
    return 0;
}

//counts around the ant for the surrounding ants
int countSurroundingAnts(Creature *grid[10][10], int x, int y){
    int count = 0;
    int checkArrayI[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int checkArrayJ[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for(int i = 0; i < 8; i++){
        if(0 <= x+checkArrayI[i] && x+checkArrayI[i] < 10 && 0 <= y+checkArrayJ[i] && y+checkArrayJ[i] < 10 && dynamic_cast<Ant *>(grid[x+checkArrayI[i]][y+checkArrayJ[i]]))
            count++;
    }
    return count;
}

//prints the grid
void PrintGrid(Creature *grid[10][10], int turn){
    cout << "TURN " << turn << endl;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(grid[i][j])
                cout << grid[i][j]->whatAmI();
            else
                cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// sets all of the creatures so that they haven't moved for the next one
void setHasMovedFalse(Creature *grid[10][10]){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(grid[i][j]){
                grid[i][j]->setNotMoved();
                grid[i][j]->setNotBreeded();
            }
        }
    }
}