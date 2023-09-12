#include <simplecpp>
// A header file containg all the main game variables used
// Since all the variables defined are constant, hence their is no issue of multiple definitions acroos various files

// Header guard becuase this header file is used across many other header files
#ifndef VARIABLES_H
#define VARIABLES_H

/* Game Window Variables */
const int WINDOW_X = 500;
const int WINDOW_Y = 500;

/* Simulation Variables */
const int UNIT_TIME_INVERSE = 45; // inverse of value of one unit of time, about the same as the reciprocal of STEP_TIME
const double STEP_TIME = 0.02;

/* Game Variables */
const int PLAY_Y_HEIGHT = 450;
const int LEFT_MARGIN = 0.2*WINDOW_X;
const int RIGHT_MARGIN = 0.8*WINDOW_X;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = PLAY_Y_HEIGHT+TOP_MARGIN;

const int LENGTH = 0.2*WINDOW_X;
const int WIDTH = 15;

const int GROUND_HEIGHT = WINDOW_Y-PLAY_Y_HEIGHT;

const int SPACE = 20;
const int MAXIMUM_SCORE = 460;
#endif
