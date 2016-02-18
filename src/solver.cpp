//
// Created by nathan on 11/02/16.
//

#include <iostream>
#include "../headers/solver.h"


solver::solver() {

}

void solver::AStarIDS(rCube *cubeToSolve, int depth) {



    //The aim is to take a cube, create a list of all possible moves at this level
    //Use A* to evaluate those moves and then take the next best likely course of action.

    // f(n) = h(n) + g(n)
    // f being the value to evaluate, h being the heuristic value and g being the distance currently traveled. (moves made)


    std::cout << depth << std::endl;

    if(cubeToSolve->isComplete()){
        std::cout << "It completed \n";
        cubeToSolve->printCube();
        return;
    }



    getCurrentStates(*cubeToSolve);

    rCube tmp = frontier.top();
    frontier.pop();
    AStarIDS(&tmp, depth+1);




}

void solver::getCurrentStates(rCube &currentState) {

    rCube possibleMoves[12] = {currentState};

    //There are 12 states
    //Apply the 12 states to each of the possible moves
    for (int i = 0; i < 12; ++i) {

        possibleMoves[i].makeMove((moves) i);

        for(int k= 0; k < visited.size(); k++){



            //If they are the same
            if(visited.at(k).compare(possibleMoves[i])){
                continue;
            }
        }

        possibleMoves[i].setF(cubesOutOfPlace(possibleMoves[i]));

        frontier.push(possibleMoves[i]);

    }

}

int solver::MH3D(int x1, int y1, int z1,
                 int x2, int y2, int z2) {


    return (x1-x2)+(y1-y2)+(z1-z2);


}

int solver::cubesOutOfPlace(rCube &cube) {

    int numOOP = 0;

    for(int i = 0; i < 6; i++){

        for(int j = 0; j <  3; j++){

            for(int k = 0; k < 3; k++){

                if(cube.cube[i][j][k] == (Color) i){
                    continue;
                }else{
                    numOOP++;
                }

            }

        }

    }


    return numOOP;
}
