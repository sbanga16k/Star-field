// Code for definitions of functions related to stars
// defined in 'Star.h'

#include<iostream>
#include<stdlib.h>
#include"fssimplewindow.h"
#include "Star.h"

using namespace std;

// Translates model coordinates to screen coordinates such that origin lies in center of graphics window
void getScreenCoords(double modelX, double modelY, double &screenX, double &screenY)
{
	double screenOriginX = 400, screenOriginY = 300;		/* Coordinates of origin of model in pixels */

	// Conversion to transform model coordinates to pixel coordinates
	screenX = (modelX + screenOriginX);
	screenY = (modelY + screenOriginY);
}

// Draws filled circle at specified location with specified radius
void drawCircle(double centerX, double centerY, double radius)
{
	double screenX, screenY;			// Variables for pixel coordinates

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);

	// Drawing an approximate circle using the below coordinates
	for (int i = 0; i < 60; i++) {
		double angle = double(i) * PI / 30.0;
		double x = double(centerX) + cos(angle)*double(radius);
		double y = double(centerY) + sin(angle)*double(radius);

		getScreenCoords(x, y, screenX, screenY);
		glVertex2d(screenX, screenY);
	}

	glEnd();
}

void Star::setParams(int randX, int randY, int randZ, int speed_, int starRadius)
{
	x = double(randX);
	y = double(randY);
	z = randZ;
	speed = speed_;
	circleRadius = starRadius;
	
	width = 800; height = 600;
}

void Star::update()
{
	z -= speed;
	if (z < 1) {
		x = rand() % width - (width / 2);
		y = rand() % height - (height / 2);
		z = rand() % width / 2 + width / 2;
	}
}

void Star::draw()
{
	// Coordinates of the stars after scaling to move to new positions
	double movingX = (x / z) * (width / 2);
	double movingY = (y / z) * (height / 1.5);

	// Scaling of radius of stars to make closer stars appear bigger than farther ones
	double radius = (circleRadius/2 * (2 - z/(width/4)));
	
	if (radius > 0.1)
		drawCircle(movingX, movingY, radius+0.75);

	double prevZ = z + 20;

	double prevX = (x / prevZ) * (width / 2);
	double prevY = (y / prevZ) * (height / 1.5);
		
	// Screen coordinates for above points for drawing line 
	double screenPrevX, screenPrevY, screenMovingX, screenMovingY;

	getScreenCoords(prevX, prevY, screenPrevX, screenPrevY);
	getScreenCoords(movingX, movingY, screenMovingX, screenMovingY);
	glBegin(GL_LINES);
	glVertex2d(screenPrevX, screenPrevY);
	glVertex2d(screenMovingX, screenMovingY);
	glEnd();
}