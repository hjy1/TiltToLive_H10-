#include "constants.h"

//constants
static const double rate = 2.0;

const double MAP_SIZE_L = rate *            360;
const double MAP_SIZE_W = rate *            640;

const double ONE_TIK_TIME =                 30;      /* ms */

const double INITIAL_REDPOINT_SIZE = rate * 5;
const double REDPOINT_ACCELERATION =        10;
const double REDPOINT_DECCELERATION =       100;
const double REDPOINT_SPEED_MAX = rate *    50;
const double REDPOINT_CREATION_CHANCE =     0.1;    /* for each tick game engine has a chance of REDPOINT_CREATION_CHANCE to create a redpoint*/
const double REDPOINT_MAX_NUMBER =          20;

const double ARROW_SIZE = rate *            10;
const double ARROW_SPEED = rate *           100;

