#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/freeglut.h>

bool s_finished = false;
int PROGRAM_CONTROL_VAR = 1;

int main1(int argc, char* argv[]);
int main2(int argc, char* argv[]);


int main(int argc, char* argv[])
{
	while (!s_finished)
	{
		printf("> Transferring control to Question (%d)\n", PROGRAM_CONTROL_VAR);

		if (PROGRAM_CONTROL_VAR == 1)
			main1(argc, argv);
		else
			main2(argc, argv);
	}
	printf("> Exiting\n");

	return EXIT_SUCCESS;
}
