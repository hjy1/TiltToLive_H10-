#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>

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

extern const double SAFE_TIME;

extern const double ARROW_SIZE;
extern const double ARROW_SPEED;

extern const QColor REDPOINT_COLOR;
extern const QColor ARROW_COLOR;

extern const double EPSILON;

extern const double TOOL_MAX_NUMBER;
extern const double TOOL_CREATION_CHANCE;
extern const double TOOL_SPEED;
//code
#define NUM(x)  QString::number(x)

#endif
