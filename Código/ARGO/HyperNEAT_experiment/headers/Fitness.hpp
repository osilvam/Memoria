#ifndef FITNESS_HPP
#define FITNESS_HPP

#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <ROBOTLIB>
#include "ArgoCharacteristics.hpp"
#include "Train.hpp"
#include "CalcFunctions.hpp"

#define FAILED_FITNESS 0.00001
#define FITNESS_BASE 0.0001

#define PERFECT_FREQUENCY WAVE_FREQUENCY*2.0

#define DISTANCE_OBJETIVE 1.0

#define AMPLITUDE 10.0
#define FREQUENCY_STDD 0.7
#define DISTANCE_STDD 0.4

#define FREQUENCY_FITNESS_F(X) (double)(exp(-pow((X - PERFECT_FREQUENCY)/FREQUENCY_STDD, 2.0)/2.0)*AMPLITUDE + 0.000001)
#define FREQUENCY_FITNESS(X) (double)((FREQUENCY_FITNESS_F(X) < 6.5 ) ? FREQUENCY_FITNESS_F(X) : 10.0)

#define DISTANCE_FITNESS_F(X) (double)(exp(-pow((X - DISTANCE_OBJETIVE)/DISTANCE_STDD, 2.0)/2.0)*AMPLITUDE + 0.000001)
#define DISTANCE_FITNESS(X) (double)((X < DISTANCE_OBJETIVE) ? DISTANCE_FITNESS_F(X) : AMPLITUDE + 0.000001)

class Fitness
{
	int jdcn;
	vector < int > jdcns;
	vector < double * > robot_position;

	vector < double > fitness;
	double distance;
	double frequency;
	double final_fitness;	
	
	vector < double > generation_fitness;
	vector < double > generation_frequency;
	vector < double > generation_distance;

public:

	Fitness();
	~Fitness();

	void measuringValues(vector < Joint * > joints, vector < double > position);
	double calcFitness();
	void resetPopulationValues();
	void resetGenerationValues();
	double getDistance();
	double getFrequency();
	double getFitness();
	vector < double > getGenerationDistance();
	vector < double > getGenerationFrequency();
	vector < double > getGenerationFitness();
	double getJointDirectionChangeNumber();
	string getFitnessResults();
	double getFrequencyThreshold();
};

#endif