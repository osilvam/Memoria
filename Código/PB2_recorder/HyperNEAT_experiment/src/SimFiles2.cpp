#ifndef SIMFILES2_CPP
#define SIMFILES2_CPP

#include "SimFiles2.hpp"


using namespace std;

SimFiles2::SimFiles2()
{
	if(system("mkdir -p simulation_files") == -1)
	{
		cerr << "SIMFILES ERROR:\tFailed to create folder 'simulation_files'" << endl;
		exit(0);
	}

	if(system("mkdir -p simulation_files/joints_position") == -1)
	{
		cerr << "SIMFILES ERROR:\tFailed to create folder 'simulation_files/joints_position'" << endl;
		exit(0);
	}

	if(system("mkdir -p simulation_files/joints_real_position") == -1)
	{
		cerr << "SIMFILES ERROR:\tFailed to create folder 'simulation_files/joints_real_position'" << endl;
		exit(0);
	}

	if(system("mkdir -p simulation_files/robot_position") == -1)
	{
		cerr << "SIMFILES ERROR:\tFailed to create folder 'simulation_files/robot_position'" << endl;
		exit(0);
	}

	if(system("rm -f ./simulation_files/joints_position/*.txt") == -1)
	{
		cerr << "SIMFILES ERROR:\tFailed to remove files inside of './simulation_files/joints_position' folder" << endl;
		exit(0);
	}

	if(system("rm -f ./simulation_files/joints_real_position/*.txt") == -1)
	{
		cerr << "SIMFILES ERROR:\tFailed to remove files inside of './simulation_files/joints_real_position' folder" << endl;
		exit(0);
	}

	if(system("rm -f ./simulation_files/robot_position/*.txt") == -1)
	{
		cerr << "SIMFILES ERROR:\tFailed to remove files inside of './simulation_files/robot_position' folder" << endl;
		exit(0);
	}	
}

SimFiles2::~SimFiles2()
{

}


void SimFiles2::openNewJointsPositionFile(int generation, int population)
{
	stringstream file_name;
	file_name << "simulation_files/joints_position/jointsPosition_G" << generation << "P" << population << ".txt";
	file_joints_position.open((char*)file_name.str().c_str());

	stringstream file_name2;
	file_name2 << "simulation_files/joints_real_position/jointsPosition_G" << generation << "P" << population << ".txt";
	file_joints_real_position.open((char*)file_name2.str().c_str());
}

void SimFiles2::closeJointsPositionFile()
{
	file_joints_position.close();
	file_joints_real_position.close();
}

void SimFiles2::addFileJointsPosition(RobotVREP * vrep, vector < Joint * > joints, double simulation_time)
{
	file_joints_real_position << simulation_time;

	for(int i = 0; i < (int)joints.size(); i++)
		file_joints_real_position << "\t" << vrep->getJointPosition(joints.at(i));

	file_joints_real_position << endl;

	file_joints_position << simulation_time;

	for(int i = 0; i < (int)joints.size(); i++)
		file_joints_position << "\t" << joints.at(i)->getNextPositionRad();

	file_joints_position << endl;
}

void SimFiles2::openNewRobotPositionFile(int generation, int population)
{
	stringstream file_name;
	file_name << "simulation_files/robot_position/robotPosition_G" << generation << "_P" << population << ".txt";
	file_robot_position.open((char*)file_name.str().c_str());
}

void SimFiles2::closeRobotPositionFile()
{
	file_robot_position.close();	
}

void SimFiles2::addFileRobotPosition(vector < double > position, double simulation_time)
{
	file_robot_position << simulation_time;

	for(int i = 0; i < 3; i++)
		file_robot_position << "\t" << position.at(i);

	file_robot_position << endl;
}

#endif