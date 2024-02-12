#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "globals.h"


// 2D Surface object -- declare vertices clockwise
struct surface {
	point3f vertices[4];
	vector3f normal;
	float max[3];
	float min[3];
};
typedef struct surface surface;


surface* initSurface12f(surface* S, 
	float x1, float y1, float z1, 
	float x2, float y2, float z2, 
	float x3, float y3, float z3, 
	float x4, float y4, float z4)
{
	// Vertices declared clockwise
	S->vertices[0][0] = x1; S->vertices[0][1] = y1; S->vertices[0][2] = z1;
	S->vertices[1][0] = x2; S->vertices[1][1] = y2; S->vertices[1][2] = z2;
	S->vertices[2][0] = x3; S->vertices[2][1] = y3; S->vertices[2][2] = z3;
	S->vertices[3][0] = x4; S->vertices[3][1] = y4; S->vertices[3][2] = z4;

	// P3 - P2
	vector3f edge1 = {
		S->vertices[2][0] - S->vertices[1][0],
		S->vertices[2][1] - S->vertices[1][1],
		S->vertices[2][2] - S->vertices[1][2],
	};
	// P1 - P2
	vector3f edge2 = {
		S->vertices[0][0] - S->vertices[1][0],
		S->vertices[0][1] - S->vertices[1][1],
		S->vertices[0][2] - S->vertices[1][2],
	};

	// Compute Normal
	crossProduct(S->normal, edge2, edge1);
	normalizeVector3f(S->normal);

	S->max[0] = max(max(S->vertices[0][0], S->vertices[1][0]), max(S->vertices[2][0], S->vertices[3][0]));
	S->max[1] = max(max(S->vertices[0][1], S->vertices[1][1]), max(S->vertices[2][1], S->vertices[3][1]));
	S->max[2] = max(max(S->vertices[0][2], S->vertices[1][2]), max(S->vertices[2][2], S->vertices[3][2]));
	
	S->min[0] = min(min(S->vertices[0][0], S->vertices[1][0]), min(S->vertices[2][0], S->vertices[3][0]));
	S->min[1] = min(min(S->vertices[0][1], S->vertices[1][1]), min(S->vertices[2][1], S->vertices[3][1]));
	S->min[2] = min(min(S->vertices[0][2], S->vertices[1][2]), min(S->vertices[2][2], S->vertices[3][2]));

	return S;
}

// Display surface in OpenGL's world
void drawSurface(surface* S)
{
	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3fv(S->vertices[0]);
		glVertex3fv(S->vertices[1]);
		glVertex3fv(S->vertices[3]);
		glVertex3fv(S->vertices[2]);
	}
	glEnd();
}

// Debug -- Draw normal in the middle of the surface
void drawNormal(surface* S)
{
	point3f midPoint = {
		(S->vertices[0][0] + S->vertices[1][0] + S->vertices[2][0] + S->vertices[3][0]) / 4.0f,
		(S->vertices[0][1] + S->vertices[1][1] + S->vertices[2][1] + S->vertices[3][1]) / 4.0f,
		(S->vertices[0][2] + S->vertices[1][2] + S->vertices[2][2] + S->vertices[3][2]) / 4.0f,
	};
	glBegin(GL_LINES);
	{
		glVertex3fv(midPoint);

		midPoint[0] += S->normal[0];
		midPoint[1] += S->normal[1];
		midPoint[2] += S->normal[2];

		glVertex3fv(midPoint);
	}
	glEnd();
}