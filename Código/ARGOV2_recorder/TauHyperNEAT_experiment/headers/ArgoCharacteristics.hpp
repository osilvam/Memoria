#ifndef ARGOCHARACTERISTICS_HPP
#define ARGOCHARACTERISTICS_HPP

#include <cmath>

#define RAD (double)M_PI/180.0

#define N_LEGS 4.0
#define GRA_LIB 3
#define GRA_LIB_EXT 0
#define INITIAL_ANGLE_1 0.0*RAD
#define INITIAL_ANGLE_2 0.0*RAD
#define INITIAL_ANGLE_3 0.0*RAD

#define INITIAL_ANGLES {INITIAL_ANGLE_1,	INITIAL_ANGLE_2,	INITIAL_ANGLE_3,	INITIAL_ANGLE_1,	INITIAL_ANGLE_2,	INITIAL_ANGLE_3,	INITIAL_ANGLE_1,	INITIAL_ANGLE_2,	INITIAL_ANGLE_3,	INITIAL_ANGLE_1,	INITIAL_ANGLE_2,	INITIAL_ANGLE_3}

#define MAX_ANGLE_1 45.0*RAD
#define MIN_ANGLE_1 -45.0*RAD
#define MAX_ANGLE_2 60.0*RAD
#define MIN_ANGLE_2 -60.0*RAD
#define MAX_ANGLE_3 35.0*RAD
#define MIN_ANGLE_3 -35.0*RAD

#define MAX_ANGLE_LIMIT {MAX_ANGLE_1,	MAX_ANGLE_2,	MAX_ANGLE_3,	MAX_ANGLE_1,	MAX_ANGLE_2,	MAX_ANGLE_3,	MAX_ANGLE_1,	MAX_ANGLE_2,	MAX_ANGLE_3,	MAX_ANGLE_1,	MAX_ANGLE_2,	MAX_ANGLE_3}
#define MIN_ANGLE_LIMIT {MIN_ANGLE_1,	MIN_ANGLE_2,	MIN_ANGLE_3,	MIN_ANGLE_1,	MIN_ANGLE_2,	MIN_ANGLE_3,	MIN_ANGLE_1,	MIN_ANGLE_2,	MIN_ANGLE_3,	MIN_ANGLE_1,	MIN_ANGLE_2,	MIN_ANGLE_3}

#endif