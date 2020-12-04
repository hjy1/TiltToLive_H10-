#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>
#include "vector.h"

//constants
extern double MAP_SIZE_L;
extern double MAP_SIZE_W;

extern const double ONE_TIK_TIME;

extern const double INITIAL_REDPOINT_SIZE;
extern const double REDPOINT_ACCELERATION;
extern const double REDPOINT_DECCELERATION;
extern const double REDPOINT_SPEED_MAX;
extern const double REDPOINT_SPEED_MIN;
extern const double REDPOINT_CREATION_CHANCE;
extern const double REDPOINT_MAX_NUMBER;
extern const double REDPOINT_WAIT_TIME;

extern const double INITIAL_BULLET_SIZE;
extern const double INITIAL_BULLET_SPEED;
extern const double INITIAL_BULLET_AMOUNT;

extern const double INITIAL_Swirl_SIZE;
extern const double Swirl_MAX_SIZE;
extern const double Swirl_R_CHANGE_SPEED;
extern const double Swirl_TIME;
extern Vector n_target;

extern const int INVINCE_MAX_TIME;

extern const int FREEZE_MAX_TIME;

extern const double SAFE_TIME;

extern const double ARROW_SIZE;
extern const double ARROW_SPEED;

extern const QColor REDPOINT_COLOR;
extern const QColor ARROW_COLOR;
extern const QColor GUNBULLET_COLOR;
extern const QColor Swirl_COLOR;
extern const QColor WAVE_COLOR;

extern const double EPSILON;

extern const double TOOL_SIZE;
extern const double TOOL_MAX_NUMBER;
extern const double TOOL_CREATION_CHANCE;
extern const double TOOL_SPEED;
extern const double TOOL_LIFE_SPAN;
extern const double TOOL_EMPTY_TIME;

extern const double WAVELENTH;
extern const double WAVESPEED;



//code
#define NUM(x)  QString::number(x)
#define ISZERO(x) (fabs(x) < EPSILON)

#endif
