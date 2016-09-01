#include "Train.hpp"

int main(int argc, char* argv[])
{	
	srand (time(0));
	
	RobotVREP * vrep = new RobotVREP();
	
	if(argc != 3)
	{
		cerr << "ERROR: The number of arguments is incorrect" << endl;
		return -1;	
	} 

	// ============= VREP INITIALIZATIONS ============= //			

	vector < Joint * > joints;

	double max_angle_limit[] = MAX_ANGLE_LIMIT;
	double min_angle_limit[] = MIN_ANGLE_LIMIT;
	double initial_angles[] = INITIAL_ANGLES;
	
	for(int k = 0; k < N_LEGS*GRA_LIB + GRA_LIB_EXT; k++)
	{
		stringstream joint_name;
		joint_name << "joint" << k << "#";
		Joint * joint = new Joint((char*)"SCALE", (char*)joint_name.str().c_str(), max_angle_limit[k], min_angle_limit[k], initial_angles[k]);
		joints.push_back(joint);
		vrep->addJoint(joint);
		
	}
		
	// ================================================ //

	// ========== HYPERNEAT INITIALIZATIONS =========== //

	vector < double * > next;
	vector < double * > pass;

	for(int i = 0; i < N_LEGS*GRA_LIB + GRA_LIB_EXT; i++)
	{
		double joint_pos = joints.at(i)->getJointInitialPosition();

		double * next_pos = new double(joint_pos);
		double * pass_pos = new double(joint_pos);

		next.push_back(next_pos);
		pass.push_back(pass_pos);
	}

	for(int i = 0; i < ADITIONAL_HYPERNEAT_INPUTS; i++)
	{
		double * aux_pass = new double(SIN(0,i));
		pass.push_back(aux_pass);
	}

	HyperNeat * hyperneat = new HyperNeat(pass, next, argv[1]);

	// ================================================ //	
				
	double sim_time = 0;					
	int step = 0;
	vector < double > sum_next ((int)joints.size(),0.0);

	Genetic_Encoding * organism = new Genetic_Encoding;
	organism->load(argv[2]);

	if(!hyperneat->createSubstrateConnections(organism))
	{
		clog << "ERROR: Neat organism has not created substrate connections successfully" << endl;
		return(0);
	} 

	for(int i = 0; i < (int)joints.size(); i++)
	{
		double joint_pos = joints.at(i)->getJointInitialPosition();
		*next.at(i) = joint_pos;
		*pass.at(i) = joint_pos;
	}

	vrep->startSimulation(simx_opmode_oneshot_wait);

	while(sim_time < TIME_SIMULATION)
	{						
		for(int i = 0; i < ADITIONAL_HYPERNEAT_INPUTS; i++)
		{
			*pass.at((int)joints.size()+i) = SIN(sim_time,i);
		}

		hyperneat->evaluateSubstrateConnections();

		for(int i = 0; i < (int)joints.size(); i++)
		{
			sum_next.at(i) = sum_next.at(i) + *next.at(i);
			*pass.at(i) = *next.at(i);
		}		
		step++;
		
		if(step >= STEP_CALC)
		{

			for(int i = 0; i < (int)joints.size(); i++)
			{
				joints.at(i)->setJointNextPosition((double)sum_next.at(i)/STEP_CALC);
				sum_next.at(i) = 0;
			}
			vrep->moveJoints();

			step = 0;
		}

		usleep((int)(DELTA_T*1000000.0));
		sim_time += DELTA_T;
	}

	vrep->stopSimulation(simx_opmode_oneshot_wait);

	delete(vrep);
	delete(hyperneat);
	
	return(0);

}