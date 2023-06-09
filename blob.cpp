#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <math.h>

//For Display TEXT
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;

//Variable for clicks
int clicks = 15;

//variable for transition bet. menu and levels
int start = 0;
int lose = 0;

//variable for transition bet. levels
int level = 1;

//variable for tracking score (score is hidden from user)
int score;

//variable for tracking coins that's collected
int coins[20] = { 0 };

//variables for window and ortho graphics
static int windowSizeX = 700, windowSizeY = 900;
static int orthoSizeX = 400, orthoSizeY = 400;

//variables for moving the blob
float posX = 0.0f, posY = 0.0f;
float move_unit = 25.0f;

char s[30];

void init() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowSizeY, windowSizeX);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Be Careful With Your Clicks");
}

//Function to display strings on screen
void displayString(float x, float y, void* font, const char* string) {
    const char* c;
    glPushMatrix();
        glRasterPos2f(x, y);
        for (c = string; *c != '\0'; c++) {
            glutBitmapCharacter(font, *c);
        }
    glPopMatrix();
}

void menu() {

    glColor3f(1.000, 1.000, 0.000);
    displayString(-200, 200, (void*)font1, "BE CAREFUL WITH YOUR CLICKS");

    glColor3f(0.000, 1.000, 0.000);
    displayString(-200, 150 + 10, (void*)font2, "You're a lone Blob trying to collect coins");
    displayString(-200, 150 - 30 + 10, (void*)font2, "However, You've angered the devs so they gave you limited clicks");
    displayString(-200, 150 - 60 + 10, (void*)font2, "Try collect the coins with the limited clicks");
    displayString(-200, 150 - 90 + 10, (void*)font2, "SPACE to start");
    displayString(-200, 150 - 120 + 10, (void*)font2, "Press ESC to Exit");

    glColor3f(1.000, 1.000, 1.000);
    displayString(-150, 150 - 150 + 10, (void*)font3, "Press arrow keys to move The Blob");


    glColor3f(0.000, 1.000, 1.000);
    displayString(-150, 150 - 200, (void*)font3, "Project By:");
    displayString(-90, 150 - 230, (void*)font3, "Youssef Moustafa");
    displayString(-90, 150 - 260, (void*)font3, "Anas Magdy");
    displayString(-90, 150 - 290, (void*)font3, "Khaled Ehab");
    displayString(-90, 150 - 320, (void*)font3, "Youssef Hatem");

    if (lose == 1) {
        glColor3f(1.000, 0.000, 0.000);
        displayString(-200, 150 - 380 + 10, (void*)font2, "You Failed..Try again :)");
    }
    if (lose == 2) {
        glColor3f(1.000, 0.000, 0.000);
        displayString(-200, 150 - 380 + 10, (void*)font2, "Don't trust anything that you see :)");
    }
    if (lose == 3) {
        glColor3f(1.000, 0.000, 0.000);
        displayString(-200, 150 - 380 + 10, (void*)font2, "You could've just skipped the level ^_^");
    }
    if (lose == -1) {
        glColor3f(0.000, 1.000, 0.000);
        displayString(-200, 150 - 380 + 10, (void*)font2, "Thank you for saving the blob ^-^");
    }
}

void drawBlob(int x, int y) {
    glPushMatrix();
    
    glTranslatef(x + posX, y + posY, 0);
    
    glBegin(GL_QUADS);
    float red, green, blue;
    red = (float)rand() / RAND_MAX;
    green = (float)rand() / RAND_MAX;
    blue = (float)rand() / RAND_MAX;
    glColor3f(red, green, blue);
    glVertex2f(-20, 20);
    glVertex2f(20, 20);
    glVertex2f(20, -20);
    glVertex2f(-20, -20);
    glEnd();
    
    glPopMatrix();
}

void drawCoin(float x1, float y1) {
    float x2, y2, radius = 15.0f, angle;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0, 0.0);
    for (angle = 1.0f; angle < 361.0f; angle += 1) {
        x2 = x1 + sin(angle) * radius;
        y2 = y1 + cos(angle) * radius;
        glVertex2f(x2, y2);
    }
    glEnd();
}

void loadLevel1() {
    snprintf(s,sizeof(s),"%d clicks left",clicks);
    displayString(-90, 300, (void*)font2, s);
    displayString(-100, 350, (void*)font2, "Good Luck ^_^");

    glColor3f(0.0, 1.0, 0.0);
    displayString(120, -150, (void*)font2, "The blob");

    //drawing coins
    if (coins[0] == 0) {
        drawCoin(0,0);
    }
    if (coins[1] == 0) {
        drawCoin(-60,0);

    }
    if (coins[2] == 0) {
        drawCoin(-120, 0);

    }
    if (coins[3] == 0) {
        drawCoin(60,0);

    }
    if (coins[4] == 0) {
        drawCoin(120,0);

    }
}

void loadLevel2() {
    snprintf(s, sizeof(s), "%d clicks left", clicks);
    displayString(-90, 300, (void*)font2, s);
    displayString(-100, 350, (void*)font2, "Seems like luck was on your side...");

    //drawing coins
    if (coins[5] == 0) {
        drawCoin(60, 0);
    }
    if (coins[6] == 0) {
        drawCoin(-100, 50);

    }
    if (coins[7] == 0) {
        drawCoin(-100, -35);

    }
    if (coins[8] == 0) {
        drawCoin(60, 100);

    }
}

void loadLevel3() {
    snprintf(s, sizeof(s), "%d clicks left", clicks);
    displayString(-90, 300, (void*)font2, s);
    displayString(-100, 350, (void*)font2, "Are you not going to give up?");

    //drawing coins
    if (coins[9] == 0) {
        drawCoin(0, 100);

    }
    if (coins[10] == 0) {
        drawCoin(-50, 40);

    }
    if (coins[11] == 0) {
        drawCoin(-70,-50);

    }
}

void loadLevel4() {
    snprintf(s, sizeof(s), "%d clicks left", clicks);
    displayString(-90, 300, (void*)font2, s);
    displayString(-100, 350, (void*)font2, "JUST GIVE UP!");

    glColor3f(0.0, 1.0, 0.0);
    displayString(-50, -200, (void*)font2, "Skip Level");

    glColor3f(0.0, 1.0, 0.0);
    displayString(-300, 0, (void*)font2, "Skip Level");

    //drawing coins
    if (coins[12] == 0) {
        drawCoin(0, 150);

    }
    if (coins[13] == 0) {
        drawCoin(-50, 70);

    }
}

void loadLevel5() {
    snprintf(s, sizeof(s), "%d clicks left", clicks);
    displayString(-90, 300, (void*)font2, s);
    displayString(-100, 350, (void*)font2, "I DARE YOU TO WIN THIS");
    snprintf(s, sizeof(s), "score = %d", score);
    displayString(-90, 250, (void*)font2, s);

    /*drawCoin(-375, 0);
    drawCoin(-375, -250);
    drawCoin(-125, -250);
    drawCoin(300, 175);*/
}

void display() {
    if (start == 0) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        menu();
        

        glutSwapBuffers();
        glFlush();
    }
    else {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (level == 1) { //load level 1
            drawBlob(150,-100);
            glColor3f(1.0, 1.0, 1.0);
            loadLevel1();

        }
        else if (level == 2) { //load level 2
            drawBlob(0,0);
            glColor3f(1.0, 1.0, 1.0);
            loadLevel2();

        }
        else if (level == 3) { //load level 3 
            drawBlob(0, 250);
            glColor3f(1.0, 1.0, 1.0);
            loadLevel3();
        }
        else if (level == 4) { // load level 4
            drawBlob(0, 0);
            glColor3f(1.0, 1.0, 1.0);
            loadLevel4();
        }
        else if (level == 5) { //load level 5
            drawBlob(0, 0);
            glColor3f(1.0, 1.0, 1.0);
            loadLevel5();
        }

        glutSwapBuffers();
        glFlush();
    }
}

//checks for level and return available clicks
int checkClicks() {
    switch (level) {
        case 1:
            return 20;
            break;
        case 2:
            return 18;
            break;
        case 3:
            return 16;
            break;
        case 4:
            return 14;
            break;
        case 5:
            return 71;
            break;
        default:
            return 0;
    }
}

//decrement clicks
void decrementClicks() {
    clicks--;
    if (clicks == 0) {
        start = 0;
        lose = 1;
        posX = 0;
        posY = 0;
    }
}

//calculate euclidean/pythagorean distance between two points
int calcDistance(double x1, double y1, double x2, double y2) {
    double term1 = pow(x2 - x1, 2);
    double term2 = pow(y2 - y1, 2);
    int dist = sqrt(term1 + term2);
    return dist;
}

//checks if blob won the level
void checkScore() {
    if (level == 1 && score == 5) {
        score = 0;
        level++;
        clicks = checkClicks();
        posX = 0; posY = 0;
    }
    if (level == 2 && score == 4) {
        score = 0;
        level++;
        clicks = checkClicks();
        posX = 0; posY = 0;
    }
    if (level == 3 && score == 3) {
        score = 0;
        level++;
        clicks = checkClicks();
        posX = 0; posY = 0;
    }
    if (level == 4 && score == 2) {
        score = 0;
        level++;
        posX = 0; posY = 0;
        clicks = checkClicks();
    }
    if (level == 4 && score == -2) {
        lose = 3;
        start = 0;
    }
    if (level == 5 && score == 4) {
        start = 0;
        score = 0;
        lose = -1;
        posX = 0; posY = 0;
    }
}

//calculate the score for the blob
void calcScore() {
    int dist;
    double x1, y1, x2, y2;
    if (level == 1) {
        x1 = 150.0 + posX, y1 = -100.0 + posY;//coordinates of the blob
        
        //coin 1
        x2 = 0, y2 = 0;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[0]==0) { //added 10 for margin of error
            coins[0] = 1;
            score++;
            checkScore();
        }

        //coin 2
        x2 = -60, y2 = 0;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[1] == 0) {
            coins[1] = 1;
            score++;
            checkScore();
        }

        x2 = -120, y2 = 0;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[2] == 0) {
            coins[2] = 1;
            score++;
            checkScore();
        }

        x2 = 60, y2 = 0;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[3] == 0) {
            coins[3] = 1;
            score++;
            checkScore();
        }

        x2 = 120, y2 = 0;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <=10 && coins[4] == 0) {
            coins[4] = 1;
            score++;
            checkScore();
        }
    }

    if (level == 2) {
        x1 = 0.0 + posX, y1 = 0.0 + posY;//coordinates of the blob

        //coin 1
        x2 = 60, y2 = 0;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[5] == 0) { //added 10 for margin of error
            coins[5] = 1;
            score++;
            checkScore();
        }

        //coin 2
        x2 = -100, y2 = 50;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[6] == 0) {
            coins[6] = 1;
            score++;
            checkScore();
        }

        x2 = -100, y2 = -35;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[7] == 0) {
            coins[7] = 1;
            score++;
            checkScore();
        }

        x2 = 60, y2 = 100;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[8] == 0) {
            coins[8] = 1;
            score++;
            checkScore();
        }

    }

    if (level == 3) {
        x1 = 0.0 + posX, y1 = 250.0 + posY;//coordinates of the blob

        //coin 1
        x2 = 0, y2 = 100;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[9] == 0) { //added 10 for margin of error
            coins[9] = 1;
            score++;
            checkScore();
        }

        //coin 2
        x2 = -50, y2 = 40;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[10] == 0) {
            coins[10] = 1;
            score++;
            checkScore();
        }

        x2 = -70, y2 = -50;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[11] == 0) {
            coins[11] = 1;
            score++;
            checkScore();
        }

    }

    if (level == 4) {
        x1 = 0.0 + posX, y1 = 0.0 + posY;//coordinates of the blob

        //coin 1
        x2 = 0, y2 = 150;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[12] == 0) { //added 10 for margin of error
            coins[12] = 1;
            score--;
            checkScore();
        }

        //coin 2
        x2 = -50, y2 = 70;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[13] == 0) {
            coins[13] = 1;
            score--;
            checkScore();
        }

        x2 = 0, y2 = -200; //skip level coordinates
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 20) {
            lose = 2;
            start = 0;
        }

        x2 = -300, y2 = 0;//hashtag coordinates
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 20) {
            score += 2;
            checkScore();
        }

    }

    if (level == 5) {
        x1 = 0.0 + posX, y1 = 0.0 + posY;//coordinates of the blob

        //coin 1
        x2 = -375.0, y2 = 0.0;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[14] == 0) { //added 10 for margin of error
            coins[14] = 1;
            score++;
            checkScore();
        }

        //coin 2
        x2 = -375.0, y2 = -250.0;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 10 && coins[15] == 0) {
            coins[15] = 1;
            score++;
            checkScore();
        }

        x2 = -125.0, y2 = -250;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 20 && coins[16] == 0) {
            coins[16] = 1;
            score++;
            checkScore();
        }

        x2 = 300, y2 = 175.0;
        dist = calcDistance(x1, y1, x2, y2);
        if (dist >= 0 && dist <= 20 && coins[17] == 0) {
            coins[17] = 1;
            score ++;
            checkScore();
        }

    }
}


//keyboard input function for moving the blob
void keyboardInput(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_RIGHT:
        posX += move_unit;
        calcScore();
        decrementClicks();
        break;
    case GLUT_KEY_LEFT:
        posX -= move_unit;
        calcScore();
        decrementClicks();
        break;
    case GLUT_KEY_UP:
        posY += move_unit;
        calcScore();
        decrementClicks();
        break;
    case GLUT_KEY_DOWN:
        posY -= move_unit;
        calcScore();
        decrementClicks();
        break;
    default:
        break;
    }
    printf("score = %d \n",score); //for debugging
    printf("%f  %f\n", (posX), posY); //for debugging
    glutPostRedisplay();
}

void resetCoins() {
    for (int i = 0; i < 20; i++) {
        coins[i] = 0;
    }
}

//keyboard input function for transitioning from menu to level
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case ' ':
        if (start == 0) {
            start = 1;
            lose = 0;
            score = 0;
            level = 1;
            posX = 0; posY = 0;
            //reset clicks
            clicks = checkClicks();
            //reset coins
            resetCoins();
        }
        break;
    // menu on esc
    case 27: //27 = esc
        start = 0;
        lose = 0;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

// reshape the display
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-orthoSizeX, orthoSizeX, -orthoSizeY, orthoSizeY, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardInput);

    glutMainLoop();
}
