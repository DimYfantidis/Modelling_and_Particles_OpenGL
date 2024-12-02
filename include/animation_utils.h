#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/freeglut.h>


extern int PROGRAM_CONTROL_VAR;
extern bool s_finished;

int windowID;
int menuID;

typedef struct Part
{
    GLfloat m[16];
    void (*f)(int a);
    struct Part *sibling;
    struct Part *child;
}
Part;


int test = 0 ;
int testF = 0 ;
int bow = 0 ;
int treat = 0 ;
int jump = 0;
int move = 0 ;
int ready = 0 ;
int legBreak = 0 ;

int idle = 0 ;
int idleF = 0 ;
int idleT = 0 ;
int idleS = 0 ;
int idelB = 0 ;
int idelTF = 0 ;

int dim = 7 ;
int height = 10 ;
int c_angle = 0 ;
double c_R = 10 ;

double  spx , spy , spz , spa = 0 ;

Part *torso ;
Part *neck ;
Part *head ;
Part *earL ;
Part *earR ;
Part *tailS ;
Part *tailM ;
Part *tailE ;
Part *BRU  ;
Part *BRL  ;
Part *BRB  ;
Part *BLU  ;
Part *BLL  ;
Part *BLB  ;
Part *FRU  ;
Part *FRL  ;
Part *FRB  ;
Part *FLU  ;
Part *FLL  ;
Part *FLB  ;

//1 - testing //2,3,4 idle : - up-down - rot Head - tail
double theta[4] = {0,0,0,0};
//1 - treat // 2 - ready right // 3 ready left
double theta2[3]  = {0,0,0};
//jump - dx - dy - dz
double dd[3] = {0,0,0};

void traverse(Part * root,int debug);
void init();
void menu(int id);
void timer(int x);
void display();
void close();
void keyboard(int key,int x,int y);
void keyboard2(unsigned char key,int x,int y);
void mouse(int button, int state, int x, int y);
void axes();
void buildBody(int initial);
void GenLegBase(int debug);
void GenLegLower(int debug);
void GenLegUpper(int debug);
void GenBody(int debug);
void GenNeck(int debug);
void GenHead(int debug);
void GenEarR(int debug);
void GenEarL(int debug);
void GenTail(int debug);
void GenTailEnd(int debug);
