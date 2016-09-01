#include "Train.hpp"

int cantidadDeVreps;
vector <RobotVREP * > vreps;

vector < Fitness * > fitnesss;

SimFiles * simfile;
vector < SimFiles2 * > simfiles2s;

int g;

vector <HyperNeat *> hyperneats;
vector < vector < double * > > nexts;
vector < vector < double * > > passs;
Population * cppn_neat;

vector < vector < Joint * > > jointss;
vector < vector < CollisionObject * > > body_partss;
vector < Object *> center_dummys;

// Data used for each generation
vector < double > generationBestFitness;
vector < int > populationOfGenerationBestFitness;

void * calcOrganismFitness(void * arg)
{
	int segmento = *((int *)(arg));

	for(int p = segmento*(cppn_neat->POPULATION_MAX/cantidadDeVreps); p < segmento*(cppn_neat->POPULATION_MAX/cantidadDeVreps)+cppn_neat->POPULATION_MAX/cantidadDeVreps; p++)
	{
		double sim_time = 0;					
		int step = 0;
		bool flag = true;
		stringstream message1, message2;

		vector < double > sum_next ((int)jointss.at(segmento).size(),0.0);

		fitnesss.at(segmento)->resetPopulationValues();

		simfiles2s.at(segmento)->openNewJointsPositionFile(g, p);
		simfiles2s.at(segmento)->openNewRobotPositionFile(g, p);

		if(!hyperneats.at(segmento)->createSubstrateConnections( &cppn_neat->organisms.at( p ) )   ) continue;

		for(int i = 0; i < (int)jointss.at(segmento).size(); i++)
		{						
			jointss.at(segmento).at(i)->setInitialValues();
			double joint_pos = jointss.at(segmento).at(i)->getJointInitialPosition();
			*nexts.at(segmento).at(i) = joint_pos;
			*passs.at(segmento).at(i) = joint_pos;
		}
		
		vreps.at(segmento)->moveJointsToInitialPosition();
		
		vreps.at(segmento)->startSimulation(simx_opmode_oneshot_wait);

		message1 << "Generation " << g << " Population " << p;
		vreps.at(segmento)->addStatusbarMessage((char*)message1.str().c_str() , simx_opmode_oneshot_wait);

		while(sim_time < TIME_SIMULATION && flag)
		{				
			simfiles2s.at(segmento)->addFileJointsPosition(vreps.at(segmento), jointss.at(segmento), sim_time);		
			for(int i = 0; i < ADITIONAL_HYPERNEAT_INPUTS; i++)
			{
				*passs.at(segmento).at((int)jointss.at(segmento).size()+i) = SIN(sim_time,i);
			}

			hyperneats.at(segmento)->evaluateSubstrateConnections();

			for(int i = 0; i < (int)jointss.at(segmento).size(); i++)
			{
				sum_next.at(i) = sum_next.at(i) + *nexts.at(segmento).at(i);
				*passs.at(segmento).at(i) = *nexts.at(segmento).at(i);
			}

			step++;
			
			if(step >= STEP_CALC)
			{				
				for(int i = 0; i < (int)jointss.at(segmento).size(); i++)
				{
					jointss.at(segmento).at(i)->setJointNextPosition((double)sum_next.at(i)/STEP_CALC);
					sum_next.at(i) = 0;
				}

				vreps.at(segmento)->moveJoints();

				usleep((int)(4.0*DELTA_T*1000000.0));
			
				if(vreps.at(segmento)->checkAllCollisions()) flag = false;

				if(sim_time > TIME_INIT_MEASURING)
				{
					vector < double > position = vreps.at(segmento)->getObjectPosition(center_dummys.at(segmento));

					fitnesss.at(segmento)->measuringValues(jointss.at(segmento), position);

					simfiles2s.at(segmento)->addFileJointsPosition(vreps.at(segmento), jointss.at(segmento), sim_time);
					simfiles2s.at(segmento)->addFileRobotPosition(position , sim_time);
				}							

				step = 0;
			}

			//usleep((int)(DELTA_T*1000000.0));
			sim_time += DELTA_T;			
		}

		vreps.at(segmento)->stopSimulation(simx_opmode_oneshot_wait);

		simfiles2s.at(segmento)->closeJointsPositionFile();
		simfiles2s.at(segmento)->closeRobotPositionFile();

		if( flag )
		{			
			cppn_neat->organisms.at(p).fitness = fitnesss.at( segmento )->calcFitness();

			clog << "=======  G" << g << " P" << p << "  =======  " << endl;            
			clog << fitnesss.at( segmento )->getFitnessResults() << endl;

			if(generationBestFitness.at(segmento) < fitnesss.at(segmento)->getFitness())
			{
				generationBestFitness.at(segmento) = fitnesss.at(segmento)->getFitness();
				populationOfGenerationBestFitness.at(segmento) = p;
			}

			stringstream hcf_filename;
			hcf_filename << "HyperNeat_conf_files/HCF_G" << g << "_P" << p << ".txt";

			hyperneats.at(segmento)->printConnectionFile(&cppn_neat->organisms.at( p ), (char*)hcf_filename.str().c_str());
		}
		else
		{	
			cppn_neat->organisms.at(p).fitness = FAILED_FITNESS;
		}
	}

	return NULL;
}

class VrepClients{
public:
	VrepClients(string ruta)
	{
		std::ifstream input( ruta.c_str() );
		input >> amountOfClients;

		for (int i = 0; i < amountOfClients; i++)
		{
			string _ip;
			int _port;
			input >> _ip >> _port;
			ip.push_back(_ip);
			ports.push_back(_port);
		}
	};

	int getAmountOfClients()
	{
		return amountOfClients;
	};

	string getIpAt(int place)
	{
		return ip.at(place);
	};

	int getPortAt(int place)
	{
		return ports.at(place);
	};

private:

	vector < int > ports;
	vector < string > ip;
	int amountOfClients;
};





int main(int argc, char * argv[])
{	
	srand (time(0));
	
	if(argc != 5)
	{
		cerr << "ERROR: The number of arguments is incorrect" << endl;
		return -1;	
	}

	VrepClients vrepclients = VrepClients(argv[4]);

	cantidadDeVreps = vrepclients.getAmountOfClients();

	for (int i = 0; i < cantidadDeVreps; i++)
	{
		string ip = vrepclients.getIpAt(i);
		int port = vrepclients.getPortAt(i);
		cout << "ip:\t" << ip << "\tport:\t" << port << endl;
	}

	// =============== VARIABLE INITIALIZATION

	cppn_neat = new Population(argv[2],argv[3], (char*)"NEAT", (char*)"./NEAT_organisms/", cantidadDeVreps);

	simfile = new SimFiles(); 

	for (int i = 0; i < cantidadDeVreps; i++)
	{		
		RobotVREP * vrep =  new RobotVREP(false, vrepclients.getPortAt(i), vrepclients.getIpAt(i).c_str());
		vreps.push_back(vrep);

		SimFiles2 * simfiles2 = new SimFiles2();
		simfiles2s.push_back(simfiles2);

		Fitness * fitness = new Fitness();
		fitnesss.push_back(fitness);

		// ============= VREP INITIALIZATIONS ============= //			

		Object * center_dummy = new Object((char*)"ArgoV2_reference");
		vreps.back()->addObject(center_dummy);
		center_dummys.push_back(center_dummy);

		vector < Joint * > joints;
		double max_angle_limit[] = MAX_ANGLE_LIMIT;
		double min_angle_limit[] = MIN_ANGLE_LIMIT;
		double initial_angles[] = INITIAL_ANGLES;

		for(int k = 0; k < N_LEGS*GRA_LIB + GRA_LIB_EXT; k++)
		{
			stringstream joint_name;
			joint_name << "joint" << k+1  << "#";
			Joint * joint = new Joint((char*)"SCALE", (char*)joint_name.str().c_str(), max_angle_limit[k], min_angle_limit[k], initial_angles[k]);
			joints.push_back(joint);
			vreps.back()->addJoint(joint);
		}
		
		jointss.push_back(joints);

		vector < CollisionObject * > body_parts;

		for(int k = 0; k < 13; k++)
		{
			stringstream body_part_name;
			body_part_name << "Collision" << k << "#";
			CollisionObject * collision = new CollisionObject((char*)body_part_name.str().c_str());
			body_parts.push_back(collision);
			vreps.back()->addCollisionObject(collision);
		}

		body_partss.push_back(body_parts);

		// ================================================ //

		// ========== HYPERNEAT INITIALIZATIONS =========== //

		vector < double * > next;
		vector < double * > pass;

		for(int k = 0; k < N_LEGS*GRA_LIB + GRA_LIB_EXT; k++)
		{
			double joint_pos = joints.at(k)->getJointInitialPosition();
			double * next_pos = new double(joint_pos);
			double * pass_pos = new double(joint_pos);
			next.push_back(next_pos);
			pass.push_back(pass_pos);
		}

		for(int k = 0; k < ADITIONAL_HYPERNEAT_INPUTS; k++)
		{
			double * aux_pass = new double( SIN(0 , k) );
			pass.push_back(aux_pass);
		}

		HyperNeat * hyperneat = new HyperNeat(pass, next, argv[1]);

		nexts.push_back(next);
		passs.push_back(pass);
		hyperneats.push_back(hyperneat);

		// ================================================ //		
	}	

	double bestFitness = 0.0;
	int bestGeneration = 0;
	int bestPopulation = 0;

	for(g = 0; g < cppn_neat->GENERATIONS; g++)
	{
		generationBestFitness = vector < double > (cantidadDeVreps, 0.0);
		populationOfGenerationBestFitness = vector < int > (cantidadDeVreps, 0);		

		pthread_t tid[cantidadDeVreps];

		for (int i = 0; i < cantidadDeVreps; i++)
		{
			int * segm = new int(i);
			pthread_create(&tid[i], NULL, calcOrganismFitness, segm);
		}

		for (int i = 0; i < cantidadDeVreps; i++)
		{
			pthread_join(tid[i], NULL);
		}

		simfile->addFileFitness(fitnesss, g);

		for (int i = 0; i < (int)fitnesss.size(); i++)
			fitnesss.at(i)->resetGenerationValues();
		
		cppn_neat->epoch();	

		int generationBestFitnessIndex;
		double generationBestFitness_value = max(generationBestFitness,&generationBestFitnessIndex);

		stringstream generation_champion_filename;
        generation_champion_filename << "NEAT_organisms/Champion_G" << g << "P" << populationOfGenerationBestFitness.at(generationBestFitnessIndex) << ".txt";

        cppn_neat->organisms.at(populationOfGenerationBestFitness.at(generationBestFitnessIndex)).save((char*)generation_champion_filename.str().c_str());

        if(bestFitness < generationBestFitness_value)
        {
        	bestFitness = generationBestFitness_value;
        	bestGeneration = g;
        	bestPopulation = populationOfGenerationBestFitness.at(generationBestFitnessIndex);
        }

        simfile->addFileChampions(generationBestFitness_value, g, populationOfGenerationBestFitness.at(generationBestFitnessIndex));
	}

	stringstream cp_champion_filename;
    
    cp_champion_filename << "cp NEAT_organisms/Champion_G" << bestGeneration << "P" << bestPopulation << ".txt ./NEAT_organisms/Champion.txt";
    
    if(system((char*)cp_champion_filename.str().c_str()) == -1)
    {
        cerr << "TRAIN ERROR:\tFailed to copy the Champion Organism File" << endl;
    }
	
	hyperneats.at(0)->printConnectionFile((char*)"NEAT_organisms/Champion.txt",(char*)"HyperNeat_conf_files/HCF_Champion.txt");

	sleep(1);

	for (int i = 0; i < (int)vreps.size(); i++)
	{
		delete(vreps.at(i));
	}
	
	return(0);
}