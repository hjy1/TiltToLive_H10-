#ifndef CONSTANTS_H
#define CONSTANTS_H

//constants
#define MAP_SIZE_L                  360
#define MAP_SIZE_W                  640

#define ONE_TIK_TIME                30      /* ms */

#define INITIAL_REDPOINT_SIZE       5
#define REDPOINT_ACCELERATION       10
#define REDPOINT_DECCELERATION  	100
#define REDPOINT_SPEED_MAX          50
#define REDPOINT_CREATION_CHANCE    0.1    /* for each tick game engine has a chance of REDPOINT_CREATION_CHANCE to create a redpoint*/
#define REDPOINT_MAX_NUMBER         20

#define ARROW_SIZE                  10
#define ARROW_SPEED                 100

//code
#define NUM(x)  QString::number(x)
#endif
