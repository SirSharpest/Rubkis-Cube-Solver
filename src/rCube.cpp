//
// Created by nathan on 05/02/16.
//

#include <iostream>
#include "../headers/rCube.h"

#define debug

/*
 * When referencing the cube, the front face will be 0, the back will be 3
 * The east side face will be 1, the west will be 4
 * The top side face will be 2, the bottom 5
 *
 *
 */


/* Just for reference these are the proposed faces of completion:
 *
 *
 * 0 = white = front face (ALWAYS All relative to this state)
 * 1 = red = top face
 * 2 = green = east face
 * 3 = blue = west face
 * 4 = orange = bottom face
 * 5 = yellow = back face
 *
 */


rCube::rCube() {


    this->initCompletedCube();


}

rCube::rCube(const rCube &toCpy) {

    //For each face
    for(int i = 0; i < 6; i++){

        //for each row
        for(int j = 0; j < 3; j++){

            for(int k = 0; k < 3; k++){

                this->cube[i][j][k] = toCpy.cube[i][j][k];

            }

        }

    }

}



void rCube::initCompletedCube() {

    //for each face:
    for(int i = 0; i < 6; i++){


        Color tmpColor;

        switch (i){
            case 0:
                tmpColor = white;
                break;
            case 1:
                tmpColor = red;
                break;
            case 2:
                tmpColor = green;
                break;
            case 3:
                tmpColor = blue;
                break;
            case 4:
                tmpColor = orange;
                break;
            case 5:
                tmpColor = yellow;
                break;
            default:
                std::cout << "Couldn't assign a color" << std::endl;
                return;
         }

        //for each row of that face:
        for(int j = 0; j < 3; j++){


            cube[i][j][0] = tmpColor;
            cube[i][j][1] = tmpColor;
            cube[i][j][2] = tmpColor;

        }

    }

}

void rCube::printCube() {

    std::cout << "  --- \t\t\t  ---" << std::endl;


    //for each face
    for(int i = 0; i < 3; i++ ){

        //for each row
        for(int j = 0; j < 3; j++){


            std::cout << "| ";

            std::cout << cube[i][j][0];
            std::cout << cube[i][j][1];
            std::cout << cube[i][j][2];

            std::cout << " | ";

            std::cout << "\t\t";

            std::cout << "| ";

            std::cout << cube[i+3][j][0];
            std::cout << cube[i+3][j][1];
            std::cout << cube[i+3][j][2];

            std::cout << " |"

            << std::endl;

        }

        //Break up the faces when printing
        std::cout << "  --- \t\t\t  ---" << std::endl;

    }

}

void rCube::makeMove(moves direction) {


    switch (direction){

        //Rotate the white face top row to the east (right)
        case TOP_CLOCKWISE:
            rotateHorizontalRows(0, 0, 2, 2, 5, 5, 3, 3, 0);
            rotateOnPivotPoint(1, true);
            break;
        //Rotate the white face
        case TOP_ANTICLOCKWISE:
            rotateHorizontalRows(0, 0, 3, 3, 5, 5, 2, 2, 0);
            rotateOnPivotPoint(1, false);
            break;
        case RIGHT_CLOCKWISE:
            rotateVerticalCols(2, 0, 1, 1, 5, 5, 4, 4, 0);
            rotateOnPivotPoint(2, true);
            break;
        case RIGHT_ANTICLOCKWISE:
            rotateVerticalCols(2, 0, 4, 4, 5, 5, 1, 1, 0);
            rotateOnPivotPoint(2, false);
            break;
        case BOTTOM_CLOCKWISE:
            rotateHorizontalRows(2, 0, 2, 2, 5, 5, 3, 3, 0);
            rotateOnPivotPoint(4, true);
            break;
        case BOTTOM_ANTICLOCKWISE:
            rotateHorizontalRows(2, 0, 3, 3, 5, 5, 2, 2, 0);
            rotateOnPivotPoint(4, false);
            break;
        case LEFT_CLOCKWISE:
            rotateVerticalCols(0, 0, 1, 1, 5, 5, 4, 4, 0);
            rotateOnPivotPoint(3, true);
            break;
        case LEFT_ANTICLOCKWISE:
            rotateVerticalCols(0, 0, 4, 4, 5, 5, 1, 1, 0);
            rotateOnPivotPoint(3, false);
            break;
        case FRONT_CLOCKWISE:
            rotateHorizontalRows(2, 1, 2, 2, 4, 4, 3, 3, 1);
            rotateOnPivotPoint(0, true);
            break;
        case FRONT_ANTICLOCKWISE:
            rotateHorizontalRows(2, 1, 3, 3, 4, 4, 2, 2, 1);
            rotateOnPivotPoint(0, false);
            break;
        case BACK_CLOCKWISE:
            rotateHorizontalRows(0, 1, 2, 2, 4, 4, 3, 3, 1);
            rotateOnPivotPoint(5, true);
            break;
        case BACK_ANTICLOCKWISE:
            rotateHorizontalRows(0, 1, 3, 3, 4, 4, 2, 2, 1);
            rotateOnPivotPoint(5, false);
            break;
        default:
            std::cout << "Error that is not a valid movement" << std::endl;
            return;
        }

}

bool rCube::isComplete() {
    return evaluateCube();
}


void rCube::rotateHorizontalRows(int row, int faceOld1, int faceNew1, int faceOld2, int faceNew2, int faceOld3,
                                 int faceNew3, int faceOld4, int faceNew4) {


    //tmp cube to hold original values
    rCube tmpCube(*this);

    //do first swap
    cube[faceNew1][row][0] = tmpCube.cube[faceOld1][row][0];
    cube[faceNew1][row][1] = tmpCube.cube[faceOld1][row][1];
    cube[faceNew1][row][2] = tmpCube.cube[faceOld1][row][2];


    //do second swap
    cube[faceNew2][row][0] = tmpCube.cube[faceOld2][row][0];
    cube[faceNew2][row][1] = tmpCube.cube[faceOld2][row][1];
    cube[faceNew2][row][2] = tmpCube.cube[faceOld2][row][2];


    //do third swap
    cube[faceNew3][row][0] = tmpCube.cube[faceOld3][row][0];
    cube[faceNew3][row][1] = tmpCube.cube[faceOld3][row][1];
    cube[faceNew3][row][2] = tmpCube.cube[faceOld3][row][2];


    //do fourth swap
    cube[faceNew4][row][0] = tmpCube.cube[faceOld4][row][0];
    cube[faceNew4][row][1] = tmpCube.cube[faceOld4][row][1];
    cube[faceNew4][row][2] = tmpCube.cube[faceOld4][row][2];

}


void rCube::rotateOnPivotPoint(int faceToRotate, bool isClockwise) {

    //tmp cube to hold original values
    rCube tmpCube(*this);

    //if we are moving in the clockwise direction
    if(isClockwise){

        //TODO: Calculate new positions when movement is complete

        //Top Row goes:
            //0,0 -> 2,0
            //1,0 -> 2,1
            //2,0 -> 2,2

        cube[faceToRotate][2][0] = tmpCube.cube[faceToRotate][0][0];
        cube[faceToRotate][2][1] = tmpCube.cube[faceToRotate][1][0];
        cube[faceToRotate][2][2] = tmpCube.cube[faceToRotate][2][0];


        //Middle row goes:
            //0,1 -> 1,0
            //1,1 -> 1,1
            //2,1 -> 1,2

        cube[faceToRotate][1][0] = tmpCube.cube[faceToRotate][0][1];
        cube[faceToRotate][1][1] = tmpCube.cube[faceToRotate][1][1];
        cube[faceToRotate][1][2] = tmpCube.cube[faceToRotate][2][1];


        //Bottom row goes:
            //0,2 -> 0,0
            //1,2 -> 0,1
            //2,2 -> 0,2

        cube[faceToRotate][0][0] = tmpCube.cube[faceToRotate][0][2];
        cube[faceToRotate][0][1] = tmpCube.cube[faceToRotate][1][2];
        cube[faceToRotate][0][2] = tmpCube.cube[faceToRotate][2][2];


    }else{

        //Top Row goes:
            //0,0 -> 0,2
            //1,0 -> 0,1
            //2,0 -> 0,0
        cube[faceToRotate][0][2] = tmpCube.cube[faceToRotate][0][0];
        cube[faceToRotate][0][1] = tmpCube.cube[faceToRotate][1][0];
        cube[faceToRotate][0][0] = tmpCube.cube[faceToRotate][2][0];


        //Middle row goes:
            //0,1 -> 1,2
            //1,1 -> 1,1
            //2,1 -> 1,0
        cube[faceToRotate][1][2] = tmpCube.cube[faceToRotate][0][1];
        cube[faceToRotate][2][1] = tmpCube.cube[faceToRotate][1][1];
        cube[faceToRotate][1][0] = tmpCube.cube[faceToRotate][2][1];


        //Bottom Row goes to:
            //0,2 -> 2,2
            //1,2 -> 2,1
            //2,2 -> 2,0
        cube[faceToRotate][2][0] = tmpCube.cube[faceToRotate][0][2];
        cube[faceToRotate][2][1] = tmpCube.cube[faceToRotate][1][2];
        cube[faceToRotate][2][0] = tmpCube.cube[faceToRotate][2][2];


    }

}

bool rCube::evaluateCube(){

    //Check each face
    for(int i = 0; i < 6; i++){

        //Check each row and column
        for(int j = 0; j < 3; j++){

            for(int k = 0; k < 3; k++){

                if(cube[i][j][k] == (Color) i){
                    continue;
                }else{
                    return false;
                }
            }

        }

    }
    return true;
}

void rCube::rotateVerticalCols(int column, int faceOld1, int faceNew1, int faceOld2, int faceNew2, int faceOld3,
                               int faceNew3, int faceOld4, int faceNew4) {


    //tmp cube to hold original values
    rCube tmpCube(*this);

    //do first swap
    cube[faceNew1][0][column] = tmpCube.cube[faceOld1][0][column];
    cube[faceNew1][1][column] = tmpCube.cube[faceOld1][1][column];
    cube[faceNew1][2][column] = tmpCube.cube[faceOld1][2][column];


    //do second swap
    cube[faceNew2][0][column] = tmpCube.cube[faceOld2][0][column];
    cube[faceNew2][1][column] = tmpCube.cube[faceOld2][1][column];
    cube[faceNew2][2][column] = tmpCube.cube[faceOld2][2][column];


    //do third swap
    cube[faceNew3][0][column] = tmpCube.cube[faceOld3][0][column];
    cube[faceNew3][1][column] = tmpCube.cube[faceOld3][1][column];
    cube[faceNew3][2][column] = tmpCube.cube[faceOld3][2][column];


    //do fourth swap
    cube[faceNew4][0][column] = tmpCube.cube[faceOld4][0][column];
    cube[faceNew4][1][column] = tmpCube.cube[faceOld4][1][column];
    cube[faceNew4][2][column] = tmpCube.cube[faceOld4][2][column];


}

int rCube::getF() {
    return this->f;
}

void rCube::setF(int newF) {
    this->f = newF;
}

bool rCube::compare(rCube cube) {

    for(int i = 0; i < 6; i++){

        for( int j = 0; j < 3; j++){

            for (int k = 0; k < 3; k++){

                if(this->cube[i][j][k] == cube.cube[i][j][k]){
                    continue;
                }else{
                    return false;
                }


            }

        }

    }


    return true;

}
