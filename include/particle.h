#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"


static float particleDragCoefficient = 0.01f;

// Particle object
struct particle
{
	point3f position;
	vector3f velocity;
};
typedef struct particle particle;


// Allocates and initializes a dynamically allocated particle
particle* generateParticle(const point3f spawn_pos, float scale_vel)
{
	particle* p = (particle*)malloc(sizeof(particle));

	if (p == NULL) {
		// Memory allocation failure
		return NULL;
	}
	// Initializes the particle with the given mass and position
	p->position[0] = spawn_pos[0];
	p->position[1] = spawn_pos[1];
	p->position[2] = spawn_pos[2];

	// Velocity is random with each scalar in [-1, 1] -- `scale_val` scales the range to [-s, s]
	p->velocity[0] = scale_vel * 2.0f * ((float)rand() / RAND_MAX - 0.5f);
	p->velocity[1] = scale_vel * 2.0f * ((float)rand() / RAND_MAX - 0.5f);
	p->velocity[2] = scale_vel * 2.0f * ((float)rand() / RAND_MAX - 0.5f);

	return p;
}

// Accelerates the particle for the next time frame -- Newton's method
void accelerate3fv(particle* p, const vector3f acc, bool airResist)
{
	float vel_length;
	float acc_x = acc[0];
	float acc_y = acc[1];
	float acc_z = acc[2];

	if (airResist) {
		vel_length = vectorLength3f(p->velocity);
		acc_x -= particleDragCoefficient * vel_length * p->velocity[0];
		acc_y -= particleDragCoefficient * vel_length * p->velocity[1];
		acc_z -= particleDragCoefficient * vel_length * p->velocity[2];
	}
	// printf("acc = (%.3lf, %.3lf, %.3lf)\t vel = (%.3lf, %.3lf, %.3lf)\n", acc_x, acc_y, acc_z, p->velocity[0], p->velocity[1], p->velocity[2]);
	p->velocity[0] += acc_x * deltaTimeF;
	p->velocity[1] += acc_y * deltaTimeF;
	p->velocity[2] += acc_z * deltaTimeF;

	p->position[0] += p->velocity[0] * deltaTimeF;
	p->position[1] += p->velocity[1] * deltaTimeF;
	p->position[2] += p->velocity[2] * deltaTimeF;
}

void accelerate3f(particle* p, float acc_x, float acc_y, float acc_z, bool airResist)
{
	float vel_length;

	if (airResist) {
		vel_length = vectorLength3f(p->velocity);
		acc_x -= particleDragCoefficient * vel_length * p->velocity[0];
		acc_y -= particleDragCoefficient * vel_length * p->velocity[1];
		acc_z -= particleDragCoefficient * vel_length * p->velocity[2];
	}
	// printf("acc = (%.3lf, %.3lf, %.3lf)\t vel = (%.3lf, %.3lf, %.3lf)\n", acc_x, acc_y, acc_z, p->velocity[0], p->velocity[1], p->velocity[2]);

	p->velocity[0] += acc_x * deltaTimeF;
	p->velocity[1] += acc_y * deltaTimeF;
	p->velocity[2] += acc_z * deltaTimeF;

	p->position[0] += p->velocity[0] * deltaTimeF;
	p->position[1] += p->velocity[1] * deltaTimeF;
	p->position[2] += p->velocity[2] * deltaTimeF;
}

void printParticle(particle* p)
{
	printf("pos: (%.3f, %.3f, %.3f), vel: (%.3f, %.3f, %.3f)\n",
		p->position[0], p->position[1], p->position[2],
		p->velocity[0], p->velocity[1], p->velocity[2]
	);
}

bool isInsideWorldLimits(particle* p)
{
	return p->position[1] > -100.0f;
}