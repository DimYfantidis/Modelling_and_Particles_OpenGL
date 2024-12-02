#include "animation_utils.h"


int main1(int argc, char* argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(0, 0);

    glutInitWindowSize(1000, 1000);

    windowID = glutCreateWindow("Dog Animation -- (Evangelos Spatharis - 3949 & Dimitrios Yfantidis - 3938)");
    menuID = glutCreateMenu(menu);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    //glutAddMenuEntry("Toggle : test",1);
    glutAddMenuEntry("Toggle : idle", 2);
    glutAddMenuEntry("Ready", 3);
    glutAddMenuEntry("Take a Treat", 4);
    glutAddMenuEntry("Bow Down / Head Up ", 5);
    glutAddMenuEntry("Jump", 6);
    glutAddMenuEntry("Reset", 7);
    glutAddMenuEntry("Proceed to 2nd Question", 8);
    glutAddMenuEntry("EXIT", 9);

    glutAttachMenu(GLUT_RIGHT_BUTTON);


    glutDisplayFunc(display);

    glutSpecialFunc(keyboard);
    glutKeyboardFunc(keyboard2);
    glutMouseFunc(mouse);
    glutMouseWheelFunc(NULL);
    glutCloseFunc(close);
    glutReshapeFunc(NULL);
    glutTimerFunc(0, timer, 0);

    init();

    glutMainLoop();

    return EXIT_SUCCESS;
}

void close()
{
    printf("\t> Deallocating dog's components\n");

    free(FLB);
    free(FLL);
    free(FLU);

    free(FRB);
    free(FRL);
    free(FRU);

    free(BLB);
    free(BLL);
    free(BLU);

    free(BRB);
    free(BRL);
    free(BRU);

    free(tailE);
    free(tailM);
    free(tailS);

    free(earL);
    free(earR);
    free(head);
    free(neck);
    free(torso);

    printf("\t> Destroying window system 1\n");

    glutDestroyMenu(menuID);
    glutDestroyWindow(windowID);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor((GLfloat)1.0, (GLfloat)1.0, (GLfloat)1.0, (GLfloat)0.0);
    glColor3f((GLfloat)1.0, (GLfloat)0.0, (GLfloat)0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double hrad = c_angle * 3.14159 / 180;
    glOrtho(-dim, dim, -dim, dim, -dim - 40, dim + 40);
    gluLookAt(c_R * sin(hrad), 0, c_R * cos(hrad), 0, 0, 0, 0, 1, 0);

    buildBody(1);

    glutPostRedisplay();
}

void menu(int id) {
    switch (id) {
    case 1:
        //test
        if (test == 0)
            test = 1;
        else
            test = 0;
        break;
    case 2:
        //idle
        bow = 0;
        if (idle == 0) {
            idleS = rand() % 100;
            idelB = rand() % 2;
            if (!idelB)
                idelB = -1;
            idle = 1;
        }
        else
            idle = 0;
        break;
    case 3:
        //ready
        if (ready == 0) {
            ready = 1;
        }
        if (ready == 2) {
            ready = 3;
        }
        break;
    case 4:
        //treat
        if (treat == 0 || treat == 3) {
            bow = 1;
            theta[0] = 0;
            theta[1] = 0;
            theta[2] = 0;
            theta[3] = 0;
            treat = 1;
            legBreak = 1;
        }
        if (treat == 2) {
            treat = 3;
            legBreak = 3;
        }
        break;
    case 5:
        //bow
        if (bow == 0 || bow == 3) {
            idle = 0;
            theta[0] = 0;
            theta[1] = 0;
            theta[2] = 0;
            theta[3] = 0;
            bow = 1;
        }
        if (bow == 2)
            bow = 3;
        break;
    case 6:
        //jump
        idle = 0;
        theta[0] = 0;
        theta[1] = 0;
        theta[2] = 0;
        theta[3] = 0;
        theta2[0] = 0;
        theta2[1] = 0;
        theta2[2] = 0;
        jump = 1;
        move = 1;
        break;
    case 7:
        //reset
        idle = 0;
        theta[0] = 0;
        theta[1] = 0;
        theta[2] = 0;
        theta[3] = 0;
        theta2[0] = 0;
        theta2[1] = 0;
        theta2[2] = 0;
        dd[0] = 0;
        dd[1] = 0;
        dd[2] = 0;
        bow = 0;
        treat = 0;
        jump = 0;
        move = 0;
        ready = 0;
        legBreak = 0;
        break;
    case 8:
        PROGRAM_CONTROL_VAR = 2;
        glutLeaveMainLoop();
        break;
    case 9:
        s_finished = true;
        glutLeaveMainLoop();
        break;
    default:
        break;
    }
}

void timer(int x) 
{
    if (PROGRAM_CONTROL_VAR != 1) {
        return;
    }
    glutTimerFunc(1000 / 60, timer, 0);

    //test
    if (test == 1) {
        if (testF == 0) {
            theta[0] = theta[0] + 0.8;
            if (theta[0] > 20)
                testF = 1;
        }
        if (testF == 1) {
            theta[0] = theta[0] - 0.8;
            if (theta[0] <= 0)
                testF = 0;
        }
    }

    //idle
    if (idle == 1) {
        if (idleT >= 500 + idleS) {
            if (theta[1] > 0) {
                theta[1] = theta[1] - 0.8;
            }
            else {
                if (theta[2] <= 20 && idleT <= 500 + idleS + 80) {
                    theta[2] = theta[2] + 0.4;
                }
                else if (idleT <= 500 + idleS + 80) {
                    idleT++;
                }
                else if (idleT >= 500 + idleS + 80 && theta[2] > 0) {
                    theta[2] = theta[2] - 0.4;
                }
                else {
                    idleT = 0;
                    idleS = rand() % 100;
                    idelB = rand() % 2;
                    if (!idelB)
                        idelB = -1;
                }
            }
        }
        else {
            idleT++;
            if (idleF == 0) {
                theta[1] = theta[1] + 0.8;
                if (theta[1] > 20)
                    idleF = 1;
            }
            else if (idleF == 1) {
                theta[1] = theta[1] - 0.8;
                if (theta[1] <= 0)
                    idleF = 0;
            }
            if (idelTF == 0) {
                theta[3] = theta[3] + 0.6;
                if (theta[3] > 20) {
                    idelTF = 1;
                }
            }
            else if (idelTF == 1) {
                theta[3] = theta[3] - 0.6;
                if (theta[3] < -20) {
                    idelTF = 0;
                }
            }

        }
    }

    //bow
    if (bow == 1 && theta[1] < 20) {
        theta[1] = theta[1] + 0.8 / (1 + treat * 1.1);
        if (theta[1] >= 20) {
            bow = 2;
        }
    }
    else if (bow == 3 && theta[1] > 0) {
        theta[1] = theta[1] - 0.8;
    }

    //treat
    if (treat == 1) {
        theta2[0] = theta2[0] + 1.0f;
        if (theta2[0] >= 35) {
            treat = 2;
        }
    }
    else if (treat == 3) {
        theta2[0] = theta2[0] - 1.0f;
        if (theta2[0] <= 0) {
            treat = 0;
        }
    }

    //jump
    if (jump == 1) {
        theta2[0] = theta2[0] + 1.0f;
        theta2[2] = theta2[2] + 1.0f;
        theta2[1] = theta2[1] + 1.0f;
        if (theta2[0] >= 25) {
            jump = 2;
        }
    }
    else if (jump == 2) {
        theta2[0] = theta2[0] - 1.0f;
        if (theta2[0] <= 0) {
            jump = 3;
        }
    }
    else if (jump == 3) {
        theta2[0] = theta2[0] - 1.0f;
        if (theta2[0] <= -20) {
            jump = 4;
        }
    }
    else if (jump == 4) {
        theta2[0] = theta2[0] + 1.0f;
        theta2[2] = theta2[2] - 1.25f;
        theta2[1] = theta2[1] - 1.25f;
        if (theta2[0] >= 0) {
            jump = 5;
        }
    }
    if (move == 1) {
        dd[1] = dd[1] + 0.08;
        dd[2] = dd[2] + 0.08;
        if (dd[1] >= 2.5) {
            move = 2;
        }
    }
    if (move == 2) {
        dd[1] = dd[1] - 0.08;
        dd[2] = dd[2] + 0.08;
        if (dd[1] <= 0) {
            move = 3;
        }
    }

    //ready
    if (ready == 1) {
        theta2[1] = theta2[1] + 1.2f;
        if (theta2[1] >= 35) {
            ready = 2;
        }
    }
    else if (ready == 3) {
        theta2[1] = theta2[1] - 1.2f;
        if (theta2[1] <= 0) {
            ready = 0;
        }
    }

    //legBreak for treat
    if (legBreak == 1) {
        theta2[2] = theta2[2] + 0.8f;
        theta2[1] = theta2[1] + 0.8f;
        if (theta2[2] >= 35) {
            legBreak = 2;
        }
    }
    else if (legBreak == 3) {
        theta2[2] = theta2[2] - 0.8f;
        theta2[1] = theta2[1] - 0.8f;
        if (theta2[2] <= 0) {
            legBreak = 0;
        }
    }
    glutPostRedisplay();

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    buildBody(0);
    traverse(torso, 0);
    glutSwapBuffers();
}

void keyboard(int key, int x, int y) {

    //LEFT - RIGHT rotate camera in a circle around the surface
    if (key == GLUT_KEY_RIGHT) {
        c_angle += 2;
    }
    if (key == GLUT_KEY_LEFT) {
        c_angle -= 2;
    }

    //UP-DOWN - The y cord of the center of the circle
    if (key == GLUT_KEY_UP) {
        if (height < 40) {
            height = height + 10;
        }

    }
    if (key == GLUT_KEY_DOWN) {
        if (height > -20) {
            height = height - 10;
        }
    }

    //ZOOM IN
    if (key == GLUT_KEY_PAGE_UP) {
        dim--;
    }
    //ZOOM OUT
    if (key == GLUT_KEY_PAGE_DOWN) {
        dim++;
    }

    if (key == GLUT_KEY_F1) {
        spx++;
        printf("%f,%f,%f\n", spx, spy, spz);
    }
    if (key == GLUT_KEY_F4) {
        spx--;
        printf("%f,%f,%f\n", spx, spy, spz);
    }
    if (key == GLUT_KEY_F2) {
        spy++;
        printf("%f,%f,%f\n", spx, spy, spz);
    }
    if (key == GLUT_KEY_F5) {
        spy--;
        printf("%f,%f,%f\n", spx, spy, spz);
    }
    if (key == GLUT_KEY_F3) {
        spz++;
        printf("%f,%f,%f\n", spx, spy, spz);
    }
    if (key == GLUT_KEY_F6) {
        spz--;
        printf("%f,%f,%f\n", spx, spy, spz);
    }
    if (key == GLUT_KEY_F7) {
        spa += 5;
        printf("%f\n", spa);
    }
    if (key == GLUT_KEY_F8) {
        spa -= 5;
        printf("%f\n", spa);
    }



    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double hrad = c_angle * 3.14159 / 180;
    glOrtho(-dim, dim, -dim, dim, -dim - 40, dim + 40);
    gluLookAt(c_R * sin(hrad), height, c_R * cos(hrad), 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();


}

void keyboard2(unsigned char key, int x, int y) {

    //D - A rotate camera in a circle around the surface
    if (key == 'd') {
        c_angle += 2;
    }
    if (key == 'a') {
        c_angle -= 2;
    }

    //W - S The y cord of the center of the circle
    if (key == 'w') {
        if (height < 40) {
            height = height + 10;
        }

    }
    if (key == 's') {
        if (height > -20) {
            height = height - 10;
        }
    }


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double hrad = c_angle * 3.14159 / 180;
    glOrtho(-dim, dim, -dim, dim, -dim - 40, dim + 40);
    gluLookAt(c_R * sin(hrad), height, c_R * cos(hrad), 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();


}

void mouse(int button, int state, int x, int y)
{
    //ZOOM IN - OUT
    if (button == 3) {
        dim--;
    }
    if (button == 4) {
        dim++;
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double hrad = c_angle * 3.14159 / 180;
    glOrtho(-dim, dim, -dim, dim, -dim - 40, dim + 40);
    gluLookAt(c_R * sin(hrad), height, c_R * cos(hrad), 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();
}

///Build the tree of the body
void buildBody(int initial) {
    //Create the pointers to the different parts of the body
    if (initial == 1) {
        printf("\t> Allocating dog's components\n");
        torso = (Part*)malloc(sizeof(Part));
        neck = (Part*)malloc(sizeof(Part));
        head = (Part*)malloc(sizeof(Part));
        earR = (Part*)malloc(sizeof(Part));
        earL = (Part*)malloc(sizeof(Part));
        tailS = (Part*)malloc(sizeof(Part));
        tailM = (Part*)malloc(sizeof(Part));
        tailE = (Part*)malloc(sizeof(Part));

        BRU = (Part*)malloc(sizeof(Part));
        BRL = (Part*)malloc(sizeof(Part));
        BRB = (Part*)malloc(sizeof(Part));

        BLU = (Part*)malloc(sizeof(Part));
        BLL = (Part*)malloc(sizeof(Part));
        BLB = (Part*)malloc(sizeof(Part));

        FRU = (Part*)malloc(sizeof(Part));
        FRL = (Part*)malloc(sizeof(Part));
        FRB = (Part*)malloc(sizeof(Part));

        FLU = (Part*)malloc(sizeof(Part));
        FLL = (Part*)malloc(sizeof(Part));
        FLB = (Part*)malloc(sizeof(Part));


        //Connect the tree
        torso->f = GenBody;
        torso->child = neck;
        torso->sibling = NULL;

        neck->f = GenNeck;
        neck->child = head;
        neck->sibling = BRU;

        BRU->f = GenLegUpper;
        BRU->child = BRL;
        BRU->sibling = BLU;

        BLU->f = GenLegUpper;
        BLU->child = BLL;
        BLU->sibling = FLU;

        FLU->f = GenLegUpper;
        FLU->child = FLL;
        FLU->sibling = FRU;

        FRU->f = GenLegUpper;
        FRU->child = FRL;
        FRU->sibling = tailS;

        head->f = GenHead;
        head->child = earR;
        head->sibling = NULL;

        earR->f = GenEarR;
        earR->child = NULL;
        earR->sibling = earL;

        earL->f = GenEarL;
        earL->child = NULL;
        earL->sibling = NULL;

        tailS->f = GenTail;
        tailS->child = tailM;
        tailS->sibling = NULL;

        tailM->f = GenTail;
        tailM->child = tailE;
        tailM->sibling = NULL;

        tailE->f = GenTailEnd;
        tailE->child = NULL;
        tailE->sibling = NULL;

        BRL->f = GenLegLower;
        BRL->child = BRB;
        BRL->sibling = NULL;

        FRL->f = GenLegLower;
        FRL->child = FRB;
        FRL->sibling = NULL;

        FLL->f = GenLegLower;
        FLL->child = FLB;
        FLL->sibling = NULL;

        BLL->f = GenLegLower;
        BLL->child = BLB;
        BLL->sibling = NULL;

        BRB->f = GenLegBase;
        BRB->child = NULL;
        BRB->sibling = NULL;

        FRB->f = GenLegBase;
        FRB->child = NULL;
        FRB->sibling = NULL;

        BLB->f = GenLegBase;
        BLB->child = NULL;
        BLB->sibling = NULL;

        FLB->f = GenLegBase;
        FLB->child = NULL;
        FLB->sibling = NULL;

    }

    //Set the Modelview matrices for the different parts of the body
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //move in jump
    glTranslatef(dd[0], dd[1], dd[2]);
    glTranslatef(0, 3.0f, -3.0f);
    //take a treat rotate up - translate down
    glTranslatef(0, -theta2[0] / 35, 0);
    glRotatef(-theta2[0], 1, 0, 0);
    glScalef(2.0f, 1.0f, 5);
    glGetFloatv(GL_MODELVIEW_MATRIX, torso->m);
    glLoadIdentity();


    glScalef(-2.0f / 4.0f, -1.0f, -1.0f / 5);
    glTranslatef(0, -3.0f, 3.0f);
    glTranslatef(0, 1.0f, -8.5f);
    glGetFloatv(GL_MODELVIEW_MATRIX, neck->m);
    glLoadIdentity();


    glScalef(-2, -2, -1.0f / 3);
    //head tilt in idle
    glRotatef(idelB * theta[2], 0, 0, 1);
    //head bow
    glRotatef(90 + theta[1], 1, 0, 0);
    glRotatef(-90, 0, 1, 0);
    glRotatef(45, 00, 0, 1);
    glTranslatef(-1, -1, -1.0f / 2);
    glGetFloatv(GL_MODELVIEW_MATRIX, head->m);
    glLoadIdentity();

    glTranslatef(1, 0, 0);
    // ears in idle
    glRotatef(theta[1] / 4, 1, 0, 0);
    glTranslatef(-1, 0, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX, earR->m);
    glLoadIdentity();

    glTranslatef(1, 0, -0.1f);
    // ears in idle
    glRotatef(theta[1] / 4, 1, 0, 0);
    glTranslatef(-1, 1.2f, 1.6f);
    glScalef(1, -1, 1);
    glGetFloatv(GL_MODELVIEW_MATRIX, earL->m);
    glLoadIdentity();


    glScalef(0.2f, 1.5f, 0.1f);
    glTranslatef(-3.0f, -2.5f, 8.0f);
    //ready move of the leg
    glTranslatef(0, (6.0f / 4) * (theta2[2] / 35), (18.0f / 4) * (theta2[2] / 35));
    glScalef(1 + (2.0f / 10) * (theta2[2] / 35), 1 + (-1.0f / 10) * (theta2[2] / 35), 1 + (-1.0f / 10) * (theta2[2] / 35));
    glScalef(1, 1 - (2.0f / 4) * (theta2[2] / 35), 1 + (5.0f / 4) * (theta2[2] / 35));
    glRotatef(-70 * theta2[2] / 35, 1, 0, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1, 4.0f / 5);
    glTranslatef(0, 0, -2);
    glGetFloatv(GL_MODELVIEW_MATRIX, FLU->m);
    glLoadIdentity();


    glScalef(0.2f, 1.5f, 0.1f);
    glTranslatef(3.0f, -2.5f, 8.0f);
    //ready move of the leg
    glTranslatef(0, (6.0f / 4) * (theta2[1] / 35), (18.0f / 4) * (theta2[1] / 35));
    glScalef(1 + (2.0f / 10) * (theta2[1] / 35), 1 + (-1.0f / 10) * (theta2[1] / 35), 1 + (-1.0f / 10) * (theta2[1] / 35));
    glScalef(1, 1 - (2.0f / 4) * (theta2[1] / 35), 1 + (5.0f / 4) * (theta2[1] / 35));
    glRotatef(-70 * theta2[1] / 35, 1, 0, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1, 4.0f / 5);
    glTranslatef(0, 0, -2);
    glGetFloatv(GL_MODELVIEW_MATRIX, FRU->m);
    glLoadIdentity();


    glScalef(0.2f, 1.5f, 0.1f);
    glTranslatef(-3.0f, -2.5f, 1.0f);
    //take a treat - back legs stay
    glRotatef(theta2[0] / 2, 1, 0, 0);
    glTranslatef(0, theta2[0] / 70, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1, 4.0f / 5);
    glTranslatef(0, 0, -2);
    glGetFloatv(GL_MODELVIEW_MATRIX, BLU->m);
    glLoadIdentity();


    glScalef(0.2f, 1.5f, 0.1f);
    glTranslatef(3.0f, -2.5f, 1.0f);
    //take a treat - back legs stay
    glRotatef(theta2[0] / 2, 1, 0, 0);
    glTranslatef(0, theta2[0] / 70, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1, 4.0f / 5);
    glTranslatef(0, 0, -2);
    glGetFloatv(GL_MODELVIEW_MATRIX, BRU->m);
    glLoadIdentity();

    glTranslatef(0, 0, 1);
    //theta2[0] treat related movement - theta2[2] ready related movement only for treat
    glRotatef(theta2[0] + theta2[2], 1, 0, 0);
    glTranslatef(0, 0, (-2.0f / 5) * theta2[0] / 35 + (-2.0f / 5) * theta2[2] / 35);
    glTranslatef(0, 0, (4.0f / 5) * (theta2[2] / 35));
    glScalef(1, 1 + (-1.0f / 10) * (theta2[2] / 35), 4.0f / 5 + (3.0f / 10) * (theta2[2] / 35));
    glGetFloatv(GL_MODELVIEW_MATRIX, FLL->m);
    glLoadIdentity();

    glTranslatef(0, 0, 1);
    //theta2[0] treat related movement - theta2[1] ready related movement
    glRotatef(theta2[0] + theta2[1], 1, 0, 0);
    glTranslatef(0, 0, (-2.0f / 5) * theta2[0] / 35 + (-2.0f / 5) * theta2[1] / 35);
    glTranslatef(0, 0, (4.0f / 5) * (theta2[1] / 35));
    glScalef(1, 1 + (-1.0f / 10) * (theta2[1] / 35), 4.0f / 5 + (3.0f / 10) * (theta2[1] / 35));
    glGetFloatv(GL_MODELVIEW_MATRIX, FRL->m);
    glLoadIdentity();

    glTranslatef(0, 0, 1);
    glScalef(1, 1, 4.0f / 5);
    //treat back lower left
    glRotatef(theta2[0] / 2, 1, 0, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX, BLL->m);
    glLoadIdentity();

    glTranslatef(0, 0, 1);
    glScalef(1, 1, 4.0f / 5);
    //treat back lower right
    glRotatef(theta2[0] / 2, 1, 0, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX, BRL->m);
    glLoadIdentity();

    //treat movement of the leg base
    glScalef(1, 1 - 1 * theta2[0] / 175, 1);
    glRotatef(theta2[0] / 4, 1, 0, 0);
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 1, 0);
    glTranslatef(-1.2f, -2.0f, -1.0f);
    glScalef(2, 0.7f, 2);
    glGetFloatv(GL_MODELVIEW_MATRIX, FLB->m);
    glLoadIdentity();

    //treat movement of the leg base
    glScalef(1, 1 - 1 * theta2[0] / 175, 1);
    glRotatef(theta2[0] / 4, 1, 0, 0);
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 1, 0);
    glTranslatef(-1.2f, -2.0f, -1.0f);
    glScalef(2, 0.7f, 2);
    glGetFloatv(GL_MODELVIEW_MATRIX, FRB->m);
    glLoadIdentity();

    //treat movement of the leg base
    glRotatef(-90 - theta2[0] / 2, 1, 0, 0);
    glRotatef(-90, 0, 1, 0);
    glTranslatef(-1.2f, -2.0f, -1.0f);
    glScalef(2, 0.7f, 2);
    glGetFloatv(GL_MODELVIEW_MATRIX, BLB->m);
    glLoadIdentity();

    //treat movement of the leg base
    glRotatef(-90 - theta2[0] / 2, 1, 0, 0);
    glRotatef(-90, 0, 1, 0);
    glTranslatef(-1.2f, -2.0f, -1.0f);
    glScalef(2, 0.7f, 2);
    glGetFloatv(GL_MODELVIEW_MATRIX, BRB->m);
    glLoadIdentity();

    //tail rotate - idle
    glRotatef(theta[3], 0, 1, 0);
    glScalef(1.0f / 2, 1, 1.0f / 2);
    glRotatef(90, 0, 0, 1);
    glRotatef(-90, 1, 0, 0);
    glTranslatef(-1 + 3.0f / 4, -1 + 3.0f / 4, -1 + 1.0f / 2);
    glGetFloatv(GL_MODELVIEW_MATRIX, tailS->m);
    glLoadIdentity();


    //tail rotate - idle
    glRotatef(theta[3] * 0.3, 0, 0, 1);
    glScalef(0.7f, 1, 0.7f);
    glTranslatef(1.0f / 4, 0.4f, 1.0f / 4);
    glGetFloatv(GL_MODELVIEW_MATRIX, tailM->m);
    glLoadIdentity();


    //tail rotate - idle
    glRotatef(theta[3] * 0.3, 1, 0, 0);
    glScalef(1.5f / 2, 3.0f / 2, 1.5f / 2);
    glTranslatef(1.0f / 2 - 1.0f / 3, 0.5f - 1.0f / 5, 1.0f / 2 - 1.0f / 3);
    glGetFloatv(GL_MODELVIEW_MATRIX, tailE->m);
    glLoadIdentity();



}

///Create the head mesh
void GenHead(int debug) {
    glColor3f((GLfloat)0.6, (GLfloat)0.3, (GLfloat)0.0);

    if (debug == 1)
        glColor3f((GLfloat)0, (GLfloat)0, (GLfloat)1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 2, 0);
    glVertex3f(0, 2, 1);
    glVertex3f(0, 0, 1);
    glEnd();

    if (debug == 1)
        glColor3f((GLfloat)0.0, (GLfloat)1.0, (GLfloat)0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(3, 0, 0);
    glVertex3f(3.5f, 0.7f, 0);
    glVertex3f(2, 1.3f, 0);
    glVertex3f(1.7f, 2, 0);
    glVertex3f(0, 2, 0);
    glEnd();

    if (debug == 1)
        glColor3f((GLfloat)1.0, (GLfloat)0.0, (GLfloat)0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 1);
    glVertex3f(3, 0, 1);
    glVertex3f(3.5f, 0.7f, 1);
    glVertex3f(2, 1.3f, 1);
    glVertex3f(1.7f, 2, 1);
    glVertex3f(0, 2, 1);
    glEnd();

    if (debug == 1)
        glColor3f((GLfloat)1.0, (GLfloat)1.0, (GLfloat)0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glVertex3f(3, 0, 1);
    glVertex3f(3, 0, 0);
    glEnd();

    //cyan
    if (debug == 1)
        glColor3f((GLfloat)0.0, (GLfloat)1.0, (GLfloat)1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 2, 0);
    glVertex3f(0, 2, 1);
    glVertex3f(1.7f, 2.0f, 1);
    glVertex3f(1.7f, 2.0f, 0);
    glEnd();

    if (debug == 1)
        glColor3f((GLfloat)0.0, (GLfloat)1.0, (GLfloat)1.0);
    glBegin(GL_POLYGON);
    glVertex3f(1.7f, 2.0f, 1);
    glVertex3f(1.7f, 2.0f, 0);
    glVertex3f(2.0f, 1.3f, 0);
    glVertex3f(2.0f, 1.3f, 1);
    glEnd();

    if (debug == 1)
        glColor3f((GLfloat)0.0, (GLfloat)1.0, (GLfloat)1.0);
    glBegin(GL_POLYGON);
    glVertex3f(2.0f, 1.3f, 0);
    glVertex3f(2.0f, 1.3f, 1);
    glVertex3f(3.5f, 0.7f, 1);
    glVertex3f(3.5f, 0.7f, 0);
    glEnd();

    if (debug == 1)
        glColor3f((GLfloat)1.0, (GLfloat)0.0, (GLfloat)1.0);
    glBegin(GL_POLYGON);
    glVertex3f(3.5f, 0.7f, 0);
    glVertex3f(3, 0, 0);
    glVertex3f(3, 0, 1);
    glVertex3f(3.5f, 0.7f, 1);
    glEnd();

}

///Create the right ear mesh
void GenEarR(int debug) {
    glColor3f(0.55f, 0.35f, 0);

    if (debug == 1)
        glColor3f(0, 0, 1);

    glBegin(GL_POLYGON);
    glVertex3f(0.8f, 1.4f, 0);
    glVertex3f(1.5f, 1.4f, 0);
    glVertex3f(1.5f, 1.4f, -0.4f);
    glVertex3f(0.8f, 1.4f, -0.4f);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex3f(0.8f, -0.2f, -0.2f);
    glVertex3f(1.5f, -0.2f, -0.2f);
    glVertex3f(1.5f, -0.2f, -0.6f);
    glVertex3f(0.8f, -0.2f, -0.6f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.8f, 1.4f, 0);
    glVertex3f(0.8f, -0.2f, -0.2f);
    glVertex3f(1.5f, -0.2f, -0.2f);
    glVertex3f(1.5f, 1.4f, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.8f, 1.4f, -0.4f);
    glVertex3f(0.8f, -0.2f, -0.6f);
    glVertex3f(1.5f, -0.2f, -0.6f);
    glVertex3f(1.5f, 1.4f, -0.4f);
    glEnd();

    if (debug == 1)
        glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3f(0.8f, 1.4f, 0);
    glVertex3f(0.8f, 1.4f, -0.4f);
    glVertex3f(0.8f, -0.2f, -0.6f);
    glVertex3f(0.8f, -0.2f, -0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.5f, 1.4f, 0);
    glVertex3f(1.5f, 1.4f, -0.4f);
    glVertex3f(1.5f, -0.2f, -0.6f);
    glVertex3f(1.5f, -0.2f, -0.2f);
    glEnd();
}

///Create the left ear mesh
void GenEarL(int debug) {
    glColor3f(0.55f, 0.35f, 0);

    if (debug == 1)
        glColor3f(0, 0, 1);

    glBegin(GL_POLYGON);
    glVertex3f(0.8f, 1.4f, 0);
    glVertex3f(1.5f, 1.4f, 0);
    glVertex3f(1.5f, 1.4f, -0.4f);
    glVertex3f(0.8f, 1.4f, -0.4f);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex3f(0.8f, -0.2f, -0.2f);
    glVertex3f(1.5f, -0.2f, -0.2f);
    glVertex3f(1.5f, -0.2f, -0.6f);
    glVertex3f(0.8f, -0.2f, -0.6f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.8f, 1.4f, 0);
    glVertex3f(0.8f, -0.2f, -0.2f);
    glVertex3f(1.5f, -0.2f, -0.2f);
    glVertex3f(1.5f, 1.4f, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.8f, 1.4f, -0.4f);
    glVertex3f(0.8f, -0.2f, -0.6f);
    glVertex3f(1.5f, -0.2f, -0.6f);
    glVertex3f(1.5f, 1.4f, -0.4f);
    glEnd();

    if (debug == 1)
        glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3f(0.8f, 1.4f, 0);
    glVertex3f(0.8f, 1.4f, -0.4f);
    glVertex3f(0.8f, -0.2f, -0.6f);
    glVertex3f(0.8f, -0.2f, -0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.5f, 1.4f, 0);
    glVertex3f(1.5f, 1.4f, -0.4f);
    glVertex3f(1.5f, -0.2f, -0.6f);
    glVertex3f(1.5f, -0.2f, -0.2f);
    glEnd();
}

///Create the base mesh of the foot
void GenLegBase(int debug) {
    if (debug == 1) {
        glColor3f(0, 1, 0);
    }
    else {
        glColor3f(0.6f, 0.5f, 0);
    }

    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(1.8f, 0, 0);
    glVertex3f(1.3f, 0.8f, 0);
    glVertex3f(0, 0.8f, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 1);
    glVertex3f(1.8f, 0, 1);
    glVertex3f(1.3f, 0.8f, 1);
    glVertex3f(0, 0.8f, 1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0.8f, 0);
    glVertex3f(0, 0.8f, 1);
    glVertex3f(0, 0, 1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0, 0.8f, 0);
    glVertex3f(1.3f, 0.8f, 0);
    glVertex3f(1.3f, 0.8f, 1);
    glVertex3f(0, 0.8f, 1);
    glEnd();
    if (debug == 1) {
        glColor3f(1, 0, 0);
    }
    glBegin(GL_POLYGON);
    glVertex3f(1.8f, 0, 0);
    glVertex3f(1.3f, 0.8f, 0);
    glVertex3f(1.3f, 0.8f, 1);
    glVertex3f(1.8f, 0, 1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(1.8f, 0, 0);
    glVertex3f(1.8f, 0, 1);
    glVertex3f(0, 0, 1);
    glEnd();



}

///Create the mesh for the lower part of the foot
void GenLegLower(int debug) {
    GLUquadricObj* quad;
    if (debug == 1)
        glColor3f(0, 0, 1);
    else {
        glColor3f(0.7f, 0.5f, 0);
    }
    quad = gluNewQuadric();
    glTranslatef(0, 0, 1);
    gluSphere(quad, 1, 20, 20);
    gluDeleteQuadric(quad);

    quad = gluNewQuadric();
    glTranslatef(0, 0, -1);
    gluSphere(quad, 1, 20, 20);
    gluDeleteQuadric(quad);
    quad = gluNewQuadric();
    gluCylinder(quad, 1, 1, 1, 50, 2);
    gluDeleteQuadric(quad);
}

///Create the mesh for the upper part of the foot
void GenLegUpper(int debug) {
    GLUquadricObj* quad;
    if (debug == 1)
        glColor3f(1, 0, 0);
    else {
        glColor3f(0.7f, 0.5f, 0);
    }
    glTranslatef(0, 0, 1);
    quad = gluNewQuadric();
    gluSphere(gluNewQuadric(), 1, 20, 20);
    gluDeleteQuadric(quad);
    glTranslatef(0, 0, -1);
    quad = gluNewQuadric();
    gluSphere(quad, 1, 20, 20);
    gluDeleteQuadric(quad);
    quad = gluNewQuadric();
    gluCylinder(quad, 1, 1, 1, 50, 2);
    gluDeleteQuadric(quad);
}

///Create the mesh for the body
void GenBody(int debug) {
    GLUquadricObj* quad;
    if (debug == 0) {
        glColor3f((GLfloat)0.66, (GLfloat)0.3, (GLfloat)0.0);
    }
    else {
        glColor3f(1, 1, 0);
    }

    glTranslatef(0, 0, 1);
    quad = gluNewQuadric();
    gluDisk(quad, 0, 1, 50, 2);
    gluDeleteQuadric(quad);
    glTranslatef(0, 0, -1);
    quad = gluNewQuadric();
    gluDisk(quad, 0, 1, 50, 2);
    gluDeleteQuadric(quad);
    quad = gluNewQuadric();
    gluCylinder(quad, 1, 1, 1, 50, 2);
    gluDeleteQuadric(quad);
}

///Create the mesh for the neck
void GenNeck(int debug) {
    GLUquadricObj* quad;
    if (debug == 1) {
        glColor3f(1, 0, 1);
    }
    else {
        glColor3f((GLfloat)0.6, (GLfloat)0.3, (GLfloat)0.0);
    }

    glRotatef(-40 - theta[1] / 10, 1, 0, 0);
    glScalef(1.0f / 2, 1.0f / 2, 2.5);
    glTranslatef(0, 0, 1);
    quad = gluNewQuadric();
    gluDisk(quad, 0, 1, 50, 2);
    gluDeleteQuadric(quad);
    glTranslatef(0, 0, -1);
    quad = gluNewQuadric();
    gluDisk(quad, 0, 1, 50, 2);
    gluDeleteQuadric(quad);
    quad = gluNewQuadric();
    gluCylinder(quad, 1, 1, 1, 50, 2);
    gluDeleteQuadric(quad);
}

///Create the mesh for the start of the tail
void GenTail(int debug) {
    if (debug == 1) {
        glColor3f(0, 1, 1);
    }
    else {
        glColor3f((GLfloat)0.60, (GLfloat)0.35, (GLfloat)0.0);
    }

    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 0, 0);
    glEnd();



    glBegin(GL_POLYGON);
    glVertex3f(0.2f, 0.6f, 0.2f);
    glVertex3f(0.2f, 0.6f, 0.8f);
    glVertex3f(0.8f, 0.6f, 0.8f);
    glVertex3f(0.8f, 0.6f, 0.2f);
    glEnd();



    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0.2f, 0.6f, 0.2f);
    glVertex3f(0.2f, 0.6f, 0.8f);
    glVertex3f(0, 0, 1);
    glEnd();



    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0.2f, 0.6f, 0.2f);
    glVertex3f(0.8f, 0.6f, 0.2f);
    glVertex3f(1, 0, 0);
    glEnd();



    glBegin(GL_POLYGON);
    glVertex3f(1, 0, 1);
    glVertex3f(0.8f, 0.6f, 0.8f);
    glVertex3f(0.8f, 0.6f, 0.2f);
    glVertex3f(1, 0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1, 0, 1);
    glVertex3f(0.8f, 0.6f, 0.8f);
    glVertex3f(0.2f, 0.6f, 0.8f);
    glVertex3f(0, 0, 1);
    glEnd();

}

///Create the mesh for the end of the tail
void GenTailEnd(int debug) {
    if (debug == 1) {
        glColor3f(0, 1, 0);
    }

    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 0, 0);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glVertex3f(0.5f, 0.6f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 0, 1);
    glVertex3f(0.5f, 0.6f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1, 0, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(0.5f, 0.6f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(0.5f, 0.6f, 0.5f);
    glEnd();
}

///Traverse the body tree
void axes(void)
{
    glColor3f(0.0f, 0.0f, 0.6f);

    glBegin(GL_LINES);
    {
        glColor3f(0.6f, 0.0f, 0.0f);
        glVertex3s(-0x0, 0x00, 0x00);
        glVertex3s(0x20, 0x00, 0x00);

        glColor3f(0.0f, 0.6f, 0.0f);
        glVertex3s(0x00, -0x0, 0x00);
        glVertex3s(0x00, 0x20, 0x00);

        glColor3f(0.0f, 0.0f, 0.6f);
        glVertex3s(0x00, 0x00, -0x0);
        glVertex3s(0x00, 0x00, 0x20);
    }
    glEnd();
}

///Traverse the body tree
void traverse(Part* root, int debug) {
    if (root == NULL) return;
    glPushMatrix();
    glMultMatrixf(root->m);
    root->f(debug);
    if (root->child != NULL) traverse(root->child, debug);
    glPopMatrix();
    if (root->sibling != NULL) traverse(root->sibling, debug);
}
