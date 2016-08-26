#include <unistd.h> // For use usleep
#include <ROBOTLIB> // For use the RobotLib library

using namespace std;

int main(int argc, char* argv[])
{	
	RobotVREP vrep(false); // Create a controller
	Joint * joint = new Joint((char*)"DEG",(char*)"joint"); // Create a motor
	CollisionObject * cylinder = new CollisionObject((char*)"Collision"); // Create a collisionable object
	vrep.addJoint(joint); // Add the motor to controller
	vrep.addCollisionObject(cylinder); // Add the collisionable object to controller

	double vel = 0.0;
	int notCollision = 0;
	
	vrep.startSimulation(simx_opmode_oneshot_wait); // Start the simulation

	while (notCollision < 2)
	{	
		notCollision = (vrep.readCollision(cylinder)) ? 0 : notCollision + 1; // Read collision state
		vel = vel + 0.2;
		vrep.setJointTargetVelocity(joint, vel); // Set the joint velocity
		usleep(500000);			
	}

	while (vel >= 0.2)
	{
		vel = vel - 0.2;
		vrep.setJointTargetVelocity(joint, vel); // Set the joint velocity		
		usleep(500000);	
	}	

	vrep.stopSimulation(simx_opmode_oneshot_wait);	// Stop the simulation

	delete(joint);
	delete(cylinder);
	
	return(0);
}
