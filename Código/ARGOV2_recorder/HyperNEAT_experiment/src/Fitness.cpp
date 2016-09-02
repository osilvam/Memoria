#ifndef FITNESS_CPP
#define FITNESS_CPP

#include "Fitness.hpp"

using namespace std;

Fitness::Fitness()
{
	jdcn = 0;
	jdcns = vector < int > ((int)(N_LEGS + GRA_LIB_EXT),0);
	fitness = vector < double > (2,FAILED_FITNESS);

	final_fitness = FAILED_FITNESS;
}

Fitness::~Fitness()
{

}

void Fitness::measuringValues(vector < Joint * > joints, vector < double > position)
{
	double * aux = new double[3];

	for(int i = 0; i < 3; i++)
		aux[i] = position.at(i);

	robot_position.push_back(aux);

	for(int i = 0; i < (int)joints.size(); i++)
		if(joints.at(i)->getJointChangeDirection())
		{
			jdcns.at((unsigned int)i/3)++;
			jdcn++;
		}
}

double Fitness::calcFitness()
{	
	if(jdcn != 0)
	{
		double * final_location = robot_position.back();
		double * initial_location = robot_position.front();
				
		vector < double > freq_fitness ((int)(N_LEGS + GRA_LIB_EXT),0.0);
		vector < double > freq ((int)(N_LEGS + GRA_LIB_EXT),0.0);

		for(int i = 0; i < N_LEGS; i++)
		{
			freq.at(i) = (double)(jdcns.at(i)/GRA_LIB);
			freq_fitness.at(i) = FREQUENCY_FITNESS(freq.at(i)/(TIME_SIMULATION - TIME_INIT_MEASURING));
		}

		if(GRA_LIB_EXT == 1)
		{
			freq.back() = (double)jdcns.back();
			freq_fitness.back() = FREQUENCY_FITNESS(freq.back()/(TIME_SIMULATION - TIME_INIT_MEASURING));
		}

		distance = sqrt(pow(final_location[0] - initial_location[0],2) + pow(final_location[1] - initial_location[1], 2));
		frequency = mean(freq);

		fitness.at(0) = DISTANCE_FITNESS(distance);
		fitness.at(1) = mean(freq_fitness);
		
		final_fitness = min(fitness);

		generation_distance.push_back(fitness.at(0));
		generation_frequency.push_back(fitness.at(1));
		generation_fitness.push_back(final_fitness);

	}
	else final_fitness = FAILED_FITNESS;

	return final_fitness;		
}

void Fitness::resetPopulationValues()
{
	jdcn = 0;
	jdcns = vector < int > ((int)(N_LEGS + GRA_LIB_EXT),0);
	fitness = vector < double > (2,FAILED_FITNESS);

	distance = 0.0;
	frequency = 0.0;
	final_fitness = FAILED_FITNESS;
	robot_position.clear(); 
} 

void Fitness::resetGenerationValues() 
{
	generation_fitness.clear();
	generation_frequency.clear();
	generation_distance.clear();
}

double Fitness::getDistance()
{
	return distance;
}

double Fitness::getFrequency()
{
	return frequency;
}

double Fitness::getFitness()
{
	return final_fitness;
}

vector < double > Fitness::getGenerationDistance()
{
	return generation_distance;
}

vector < double > Fitness::getGenerationFrequency()
{
	return generation_frequency;
}

vector < double > Fitness::getGenerationFitness()
{
	return generation_fitness;
}

double Fitness::getJointDirectionChangeNumber()
{
	return jdcn;
}

string Fitness::getFitnessResults()
{
	stringstream results;

	results << "Distance:\t" << distance << "\tDistance Fitness\t" << fitness.at(0) << endl;
	results << "Frequency:\t" << frequency << "\tFrequency Fitness\t" << fitness.at(1) << endl;
	results << "Final Fitness:\t" << final_fitness << endl << endl;		

	return results.str();
}

double Fitness::getFrequencyThreshold()
{
	return PERFECT_FREQUENCY;
}

#endif