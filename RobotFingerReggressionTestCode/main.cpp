#include <stdio.h>
#include "ARMSDK\Kinematics.h"
#include "ARMSDK\RobotInfo.h"

using namespace armsdk;

typedef struct robotInfo{
	int Angle[6];
	int fingerAngle[3];
}RobotState;

int main(){
	armsdk::RobotInfo robot;
	Kinematics kin;

	veci angi(6);
	armsdk::Pose3D X,Y,Z;
	float pos[3*7];
	float fingerpos[3*3];
	RobotState sendData;
	//Leftarm
	robot.AddJoint(  0.0, -ML_PI_2,    0.0,      0.0, ML_PI, -ML_PI, 251000, -251000, ML_PI, -ML_PI, 2);
	robot.AddJoint(  0.0,  ML_PI_2,    0.0,      0.0, ML_PI, -ML_PI, 251000, -251000, ML_PI, -ML_PI, 4);
	robot.AddJoint( 30.0,  ML_PI_2,  246.0,      0.0, ML_PI, -ML_PI, 251000, -251000, ML_PI, -ML_PI, 6);
	robot.AddJoint(-30.0, -ML_PI_2,    0.0, -ML_PI_2, ML_PI, -ML_PI, 251000, -251000, ML_PI, -ML_PI, 8);
	robot.AddJoint(  0.0,  ML_PI_2,  216.0,      0.0, ML_PI, -ML_PI, 151875, -151875, ML_PI, -ML_PI, 10);
	robot.AddJoint(  0.0, -ML_PI_2,    0.0,      0.0, ML_PI, -ML_PI, 151875, -151875, ML_PI, -ML_PI, 12);

	kin.setRobotInfo(&robot);

	for(int i = 0; i < 6; i++)
		sendData.Angle[i] = 0;
	sendData.fingerAngle[0] = 2100;
	sendData.fingerAngle[1] = 2100;
	sendData.fingerAngle[2] = 2100;

	int totalAngle[9];
	Pose3D poseFinger[3], poseBody[7];
	for(int i = 0; i < 6; i++)		totalAngle[i] = sendData.Angle[i];
	for(int i = 6; i < 6+3; i++)	totalAngle[i] = sendData.fingerAngle[i-6];
	kin.ForwardWithFinger(totalAngle, poseBody, poseFinger);

	return 0;
}