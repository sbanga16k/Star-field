// Program for ...

#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include"fssimplewindow.h"
#include "Star.h"

using namespace std;

int main() {

	int winWidth = 800, winHeight = 600;	// Height and width of graphics window

	const int numStars = 800;		// Specifies number of stars to display
	double randX, randY;			// Randomly initialized x, y coordinates for the stars
	int randZ;					// Randomly initialized dummy z coordinates for the stars
	int speed = 4;				// Speed of flow

	vector<Star> allStars(numStars);	// Container for all stars
	
	srand((unsigned int)time(NULL));	// Seeds random number generator
	
	// Set random locations for stars with center of screen as reference
	for (int i = 0; i < numStars; i++) {
		randX = rand() % winWidth - (winWidth/2);
		randY = rand() % winHeight - (winHeight/2);
		randZ = rand() % winWidth/2 + winWidth/2;

		//cout << "X " << randX << " Y " << randY << " Z " << randZ << endl;
		allStars[i].setParams(randX, randY, randZ, speed);
	}
	// Parameters used for program control
	bool terminate = false;		// Flag for terminating the program

	FsOpenWindow(16, 16, winWidth, winHeight, 1);		// Using double buffer for animation
	glClearColor(0.0, 0.0, 0.0, 0.0);		// Set background color for graphics window to black
	
	while (!terminate) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		FsPollDevice();
		if (FsGetKeyState(FSKEY_ESC))
			terminate = true;

		for (int i = 0; i < numStars; i++) {
			allStars[i].update();
			allStars[i].draw();
		}

		FsSleep(10);
		FsSwapBuffers();
	}

	return 0;
}