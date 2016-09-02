#ifndef SIMFILES2_HPP
#define SIMFILES2_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <ROBOTLIB>
#include "Fitness.hpp"
#include "CalcFunctions.hpp"


class SimFiles2
{
	ofstream file_joints_position;	
	ofstream file_joints_real_position;
	ofstream file_robot_position;

public:

	SimFiles2();
	~SimFiles2();

	void openNewJointsPositionFile(int generation, int population);
	void closeJointsPositionFile();
	void addFileJointsPosition(RobotVREP * vrep, vector < Joint * > joints, double simulation_time);

	void openNewRobotPositionFile(int generation, int population);
	void closeRobotPositionFile();
	void addFileRobotPosition(vector < double > position, double simulation_time);
};

#endif