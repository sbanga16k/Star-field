#pragma once

// Program with code for simulating wind stream visibily blowing
const double PI = 3.14159265359;

class Star {
private:
	int width, height;	// Width, height of graphics window
	double x, y;			// x, y are Coordinates for stars generated
	int z;					// z is dummy variable for scaling
	int speed;				// Speed of flow
	double circleRadius;	// Radius of the circles being drawn

public:
	Star() {};
	void setParams(int randX, int randY, int randZ, int speed_ = 2, int starRadius = 2);
	void update();
	void draw();
};