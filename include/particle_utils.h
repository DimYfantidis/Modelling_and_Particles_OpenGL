#pragma once

#include <math.h>
#include <stdbool.h>
#include <GL/glut.h>


// Point typedefs
typedef GLfloat point3f[3];
typedef GLdouble point3d[3];
typedef GLint point3i[3];

// Vector typedefs
typedef GLfloat vector3f[3];
typedef GLdouble vector3d[3];
typedef GLint vector3i[3];

// window dimensions
int WINDOW_WIDTH = 1200;
int WINDOW_HEIGHT = 900;

// half of each window dimension
int WINDOW_WIDTH_HALF;
int WINDOW_HEIGHT_HALF;

// Id of the main menu (used for menus).
int window_menu_id;
// Id of the extra menu (used for menus).
int window_id;
// Set to the number of the exercise (1, 2, 3 or 4)
int current_frame;


bool airResistance = true;
char airResistanceStr[15] = "Enabled";

static double deltaTime = 0.01;
static float deltaTimeF = 0.01f;

// Get the distance of two 3D points of float data-type coordinates
float pointDistance3f(point3f p1, point3f p2)
{
	float diff_x = p2[0] - p1[0];
	float diff_y = p2[1] - p1[1];
	float diff_z = p2[2] - p1[2];
	return sqrtf(diff_x * diff_x + diff_y * diff_y + diff_z * diff_z);
}

// Get the distance of two 3D points of double data-type coordinates
double pointDistance3d(point3d p1, point3d p2)
{
	double diff_x = p2[0] - p1[0];
	double diff_y = p2[1] - p1[1];
	double diff_z = p2[2] - p1[2];
	return sqrt(diff_x * diff_x + diff_y * diff_y + diff_z * diff_z);
}

/* Returns the minimum element of an array along with its index
 * Input:
 *	- arr: The array
 *  - n: Length of array
 *  - index: index of minimum element is returned by reference
 *
 * Returns: the minimum element */
float getMinFloatWithIndex(float arr[], int n, int* index)
{
	float min = arr[0];
	*index = 0;

	for (int i = 1; i < n; ++i)
	{
		if (arr[i] < min)
		{
			min = arr[i];
			*index = i;
		}
	}
	return min;
}

// Absolute value function for float data type
float absf(float x)
{
	return (x >= 0.0f ? x : -x);
}

// Sign value function for float data type
float sgnf(float x)
{
	return (x >= 0.0f ? 1.0f : -1.0f);
}

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are collinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(const point3f p, const point3f q, const point3f r)
{
	float val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
	if (val == 0.0f) {
		// collinear 
		return 0;
	}
	// clock or counterclock wise 
	return (val > 0.0f) ? 1 : 2;
}

/* Code that I stole from here: https://www.geeksforgeeks.org/convex-hull-using-jarvis-algorithm-or-wrapping/.
 * Computes the convex hull of a set of points.
 * Input:
 *	- hull: Array of references to the input points that make up the convex hull.
 *			Should have as much memory capacity as the input points' set (= n).
 *	- hull_length: The number of points that make up the convex hull
 *	- points: The input points' set
 *	- n: Number of input points
 */
void getConvexHull(const point3f** hull, int* hull_length, const point3f* points, int n)
{
	// There must be at least 3 points 
	if (n < 3) {
		*hull_length = 0;
		return;
	}

	// Find the leftmost point 
	int l = 0;
	for (int i = 1; i < n; i++)
		if (points[i][0] < points[l][0])
			l = i;

	int k = 0;
	// Start from leftmost point, keep moving counterclockwise 
	// until reach the start point again.  This loop runs O(h) 
	// times where h is number of points in result or output. 
	int p = l, q;
	do
	{
		// Add current point to result 
		hull[k++] = &points[p];

		// Search for a point 'q' such that orientation(p, q, 
		// x) is counterclockwise for all points 'x'. The idea 
		// is to keep track of last visited most counterclock- 
		// wise point in q. If any point 'i' is more counterclock- 
		// wise than q, then update q. 
		q = (p + 1) % n;
		for (int i = 0; i < n; i++)
		{
			// If i is more counterclockwise than current q, then 
			// update q 
			if (orientation(points[p], points[i], points[q]) == 2)
				q = i;
		}
		// Now q is the most counterclockwise with respect to p 
		// Set p as q for next iteration, so that q is added to 
		// result 'hull' 
		p = q;
	} while (p != l);  // While we don't come to first point 

	// Return hull's size by reference
	*hull_length = k;
}


/* Renders a string on the screen
 * Input:
 *	- x, y: Screen coordinates as floats
 *	- font: The font type of the string, preferably: GLUT_BITMAP_9_BY_15
 *	- string: The string to be rendered
 *	- r, g, b: The color of the string
 */
void renderString2f(float x, float y, void* font, const char* string, float r, float g, float b)
{
	GLint previousMatrixMode;
	glPushAttrib(GL_COLOR_BUFFER_BIT);
	{
		glDisable(GL_DEPTH_TEST);
		glGetIntegerv(GL_MATRIX_MODE, &previousMatrixMode);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(.0, (double)WINDOW_WIDTH, .0, (double)WINDOW_HEIGHT);

		glColor3f(r, g, b);
		glRasterPos2f(x, WINDOW_HEIGHT - y);
		for (int i = 0; string[i] != '\0'; ++i)
			glutBitmapCharacter(font, string[i]);

		glPopMatrix();
		glMatrixMode(previousMatrixMode);
		glEnable(GL_DEPTH_TEST);
	}
	glPopAttrib();
}


/* Renders a string in the world
 * Input:
 *	- x, y, z: World coordinates as floats
 *	- font: The font type of the string, preferably: GLUT_BITMAP_9_BY_15
 *	- string: The string to be rendered
 *	- r, g, b: The color of the string
 */
void renderString3f(float x, float y, float z, void* font, const char* string, float r, float g, float b)
{
	glPushAttrib(GL_COLOR_BUFFER_BIT);
	{
		glColor3f(r, g, b);
		glRasterPos3f(x, y, z);
		for (int i = 0; string[i] != '\0'; ++i)
			glutBitmapCharacter(font, string[i]);
	}
	glPopAttrib();
}


float innerProduct3fv(const float v[3], const float u[3])
{
	return v[0] * u[0] + v[1] * u[1] + v[2] * u[2];
}

double innerProduct3dv(const double v[3], const double u[3])
{
	return v[0] * u[0] + v[1] * u[1] + v[2] * u[2];
}

void crossProduct(vector3f result, const vector3f a, const vector3f b)
{
	result[0] = a[1] * b[2] - a[2] * b[1];
	result[1] = a[2] * b[0] - a[0] * b[2];
	result[2] = a[0] * b[1] - a[1] * b[0];
}

float vectorLength3f(const vector3f v)
{
	return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

double vectorLength3d(const vector3d v)
{
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}


void normalizeVector3f(vector3f v)
{
	float length = vectorLength3f(v);

	v[0] /= length;
	v[1] /= length;
	v[2] /= length;
}

inline bool floatEquals(float a, float b)
{
	return fabs((double)(a - b)) < 0.005;
}

inline bool doubleEquals(double a, double b)
{
	return fabs(a - b) < 0.01;
}