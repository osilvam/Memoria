#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <time.h>
#include <sys/time.h>
#include <fstream>
#include <HYPERNEAT>
#include <ROBOTLIB>
#include <NEAT>
#include "CalcFunctions.hpp"
#include "Fitness.hpp"
#include "SimFiles.hpp"
#include "SimFiles2.hpp"
#include "ArgoCharacteristics.hpp"

using namespace std;
using namespace ANN_USM;

#define TIME_SIMULATION 6.0
#define TIME_INIT_MEASURING 1.0

#define ADITIONAL_HYPERNEAT_INPUTS 2

#define FRECUENCY_CMD 160.0
#define STEP_CALC 4.0

#define DELTA_T (double)(1.0/FRECUENCY_CMD)

#define WAVE_FREQUENCY 1.32//0.64
#define SIN(X,PHI) (double)sin(2.0*M_PI*WAVE_FREQUENCY*X + PHI*M_PI/2.0)

#endif