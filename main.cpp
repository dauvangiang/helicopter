#include "GL/freeglut.h"

#define VIEW_WIDTH 1000.0
#define VIEW_HEIGHT (VIEW_WIDTH * 3.0 / 4.0)

float posX = -16.0, posY = -5.0, posZ = 0.0;

float angleAll = 0.0f;
float angleRotor = 0.0f;
float val = 0.0;
float scaleX = 1.0, scaleY = 1.0, scaleZ = 1.0;
float scale = 0.0;
GLfloat materialBody_color[] = { 0.627, 0.3215, 1.0, 1.0 };
//GLfloat materialRotor_color[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat materialRotor_color[] = { 0.627, 0.3215, 1.0, 1.0 };

void init();
void drawAxes();
void drawBody();
void drawTail();
void drawLandingGear();
void drawRotor(int numberOfRotor, float rotate);
void drawHelicopter();
void display();
void transformObj(float transX, float transY, float transZ, float rotateX, float rotateY, float rotateZ, float scaleX, float scaleY, float scaleZ);
void drawCube(float transX, float transY, float transZ, float rotateX, float rotateY, float rotateZ, float scaleX, float scaleY, float scaleZ, float size);
void drawCone(float transX, float transY, float transZ, float rotateX, float rotateY, float rotateZ, float scaleX, float scaleY, float scaleZ, float base, float height);
void drawCylinder(float transX, float transY, float transZ, float rotateX, float rotateY, float rotateZ, float scaleX, float scaleY, float scaleZ, float radius, float height);
void updateAll(int value);
void updateRotor(int value);
void specialKeys(int key, int x, int y);
void inputKeyboard(unsigned char key, int x, int y);


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(VIEW_WIDTH, VIEW_HEIGHT);
    glutCreateWindow("Helicopter by dvgiang");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(inputKeyboard);
    //glutTimerFunc(0, updateAll, 0);
    glutTimerFunc(0, updateRotor, 0);
    glutMainLoop();
    return 0;
}

void init() {
    glClearColor(0.8, 0.9, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[] = { 10.0, 15.0, 20.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            posX = val <= 0 ? posX : posX + 0.2;
            break;
        case GLUT_KEY_LEFT:
            posX = val <= 0 ? posX : posX - 0.2;
            break;
        case GLUT_KEY_UP:
            val = val >= 10.0 ? 10.0 : val + 0.2;
            if (val <= 4.0)
                posY = posY;
            else 
                posY = posY >= 7.0 ? 7.0 : posY + 0.2;
            break;
        case GLUT_KEY_DOWN:
            val = val <= 0.0 ? 0.0 : val - 0.05;
            posY = posY <= -5.0 ? -5.0 : posY - 0.1;
            break;
        default:
            break;
    }
    posX = posX <= 15 ? posX : -16;
    posX = posX >= -16 ? posX : 15;
    glutPostRedisplay();
}

void inputKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        //rotate
        case 'r':
            angleAll += 10.0;
            //updateAll(5);
            break;
        //scale
        case 's':
            if (scaleX >= 3.0) scale = -0.2;
            else if (scaleX <= 1.0) scale = 0.2;

            scaleX += scale; scaleY += scale; scaleZ += scale;
            break;
        //esc
        case 27:
            angleAll = 0.0;
            posX = -15.0;
            posY = -5.0;
            val = 0.0;
            scaleX = 1.0; scaleY = 1.0; scaleZ = 1.0;
            break;
        default: break;
    }
    
    if (angleAll > 360.0) angleAll -= 360.0;
    glutPostRedisplay();
}

void updateAll(int value) {
    angleAll += 0.5;
    if (angleAll > 360.0) {
        angleAll -= 360.0;
    }
    glutPostRedisplay();
    glutTimerFunc(16, updateAll, 0);
}

void updateRotor(int value) {
    angleRotor += val;
    if (angleRotor > 360.0) {
        angleRotor -= 360.0;
    }
    glutPostRedisplay();
    glutTimerFunc(16, updateRotor, 0); //Khoảng 60 FPS
}

void transformObj(float transX, float transY, float transZ, float rotateX, float rotateY, float rotateZ, float scaleX, float scaleY, float scaleZ) {
    glTranslatef(transX, transY, transZ);
    glRotatef(rotateX, 1.0, 0.0, 0.0);
    glRotatef(rotateY, 0.0, 1.0, 0.0);
    glRotatef(rotateZ, 0.0, 0.0, 1.0);
    glScalef(scaleX, scaleY, scaleZ);
}

void drawCube(float transX, float transY, float transZ, float rotateX, float rotateY, float rotateZ, float scaleX, float scaleY, float scaleZ, float size) {
    glPushMatrix();
    transformObj(transX, transY, transZ, rotateX, rotateY, rotateZ, scaleX, scaleY, scaleZ);
    glutSolidCube(size);
    glPopMatrix();
}

void drawCone(float transX, float transY, float transZ, float rotateX, float rotateY, float rotateZ, float scaleX, float scaleY, float scaleZ, float base, float height) {
    glPushMatrix();
    transformObj(transX, transY, transZ, rotateX, rotateY, rotateZ, scaleX, scaleY, scaleZ);
    glutSolidCone(base, height, 128, 128);
    glPopMatrix();
}

void drawCylinder(float transX, float transY, float transZ, float rotateX, float rotateY, float rotateZ, float scaleX, float scaleY, float scaleZ, float radius, float height) {
    glPushMatrix();
    transformObj(transX, transY, transZ, rotateX, rotateY, rotateZ, scaleX, scaleY, scaleZ);
    glutSolidCylinder(radius, height, 128, 128);
    glPopMatrix();
}

void drawTail() {
    //Đuôi chính
    drawCylinder(0.5, -0.1, 0.0, 0.0, -90.0, 0.0, 0.5, 0.75, 1.0, 0.5, 5.0);
    //Phần nhô cuối đuôi
    drawCone(-4.4, 1.0, 0.0, 90.0, 0.0, 0.0, 1.1, 0.5, 1.0, 0.2, 1.0);
    drawCone(-4.2, 0.0, 0.0, -90.0, 0.0, 0.0, 1.1, 0.5, 1.0, 0.2, 1.0);
}

void drawLandingGear() {
    float legTranslatesX[] = {0.75, 2.75};
    for (float value : legTranslatesX) {
        //Bên phải
        drawCube(value, -1.1, 0.75, 0.0, 0.0, 0.0, 0.2, 0.8, 0.1, 1.0);
        //Bên trái
        drawCube(value, -1.1, -0.75, 0.0, 0.0, 0.0, 0.2, 0.8, 0.1, 1.0);
    }

    float crossbarTranslatesZ[] = { -0.75, 0.75 };
    for (float value : crossbarTranslatesZ) {
        drawCube(1.75, -1.6, value, 0.0, 90.0, 0.0, 0.1, 0.2, 3.0, 1.0);
        drawCone(0.25, -1.3, value, 90.0, 0.0, 0.0, 1.1, 0.5, 0.5, 0.1, 0.8);
        drawCone(0.35, -1.7, value, -90.0, 0.0, 0.0, 1.1, 0.5, 0.5, 0.1, 0.8);
        drawCone(3.26, -1.3, value, 90.0, 0.0, 0.0, 1.1, 0.5, 0.5, 0.1, 0.8);
        drawCone(3.15, -1.7, value, -90.0, 0.0, 0.0, 1.1, 0.5, 0.5, 0.1, 0.8);
    }
}

void drawRotor(int numberOfRotor, float rotate) {
    GLfloat material_metal[] = { 0.627, 0.3215, 0.041, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_metal);

    //Trục lắp cánh
    drawCylinder(1.75, 1.75, 0.0, 90.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.075, 0.75);
    drawCylinder(1.75, 1.7, 0.0, 90.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.15, 0.1);

    glPushMatrix();
    glTranslatef(1.75, 0.0, 0.0);
    glRotatef(angleRotor, 0.0, 1.0, 0.0);
    glTranslatef(-1.75, 0.0, 0.0);

    //Cánh
    float deltaRotate = 360.0 / numberOfRotor;
    for (int i = 0; i < numberOfRotor / 2; i++) {
        drawCube(1.75, 1.6, 0.0, 0.0, rotate + deltaRotate * i, 0.0, 0.5, 0.01, 7.0, 1.0);
    }
    glPopMatrix();
}

void drawBody() {
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialBody_color);

    //Nửa trên
    drawCylinder(0.7, 0.35, 0.0, 0.0, 90.0, 0.0, 1.1, 0.8, 1.0, 1.0, 2.0);
    drawCone(2.7, 0.35, 0.0, 0.0, 90.0, 0.0, 1.1, 0.8, 1.0, 1.0, 0.5);
    drawCone(0.7, 0.35, 0.0, 0.0, -90.0, 0.0, 1.1, 0.8, 1.0, 1.0, 0.6);
    
    //Nửa dưới
    drawCylinder(0.2, -0.25, 0.0, 0.0, 90.0, 0.0, 1.2, 0.9, 1.0, 1.0, 3.0);
    drawCone(3.2, -0.25, 0.0, 0.0, 90.0, 0.0, 1.2, 0.9, 1.0, 1.0, 1.0);
    drawCone(0.2, -0.25, 0.0, 0.0, -90.0, 0.0, 1.2, 0.9, 1.0, 1.0, 0.6);

}

void drawHelicopter() {

    GLfloat material_color[] = { 0.0, 0.5, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_color);
    
    drawBody();
    
    drawTail();

    drawRotor(4, 30.0);

    //Canh o duoi
    glPushMatrix();
    glTranslatef(-4.7, 0.85, 0.78);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glScalef(0.18, 0.7, 0.18);
    drawRotor(4, 30.0);
    glPopMatrix();

    drawLandingGear();
}

void drawAxes() {
    glDisable(GL_LIGHTING);
    // Vẽ trục X
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, 0.0f); // Điểm bắt đầu
    glVertex3f(10.0f, 0.0f, 0.0f);  // Điểm kết thúc
    glEnd();

    // Vẽ trục Y
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glEnd();

    // Vẽ trục Z
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

    glEnable(GL_LIGHTING);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, VIEW_WIDTH / VIEW_HEIGHT, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        7.0, 5.0, 35.0,
        0.0, 0.0, 0.0, 
        0.0, 1.0, 0.0
    );
 
    //drawAxes();

    glTranslatef(posX, posY, posZ);

    glRotatef(angleAll, 0.0, 1.0, 0.0);

    glScalef(scaleX, scaleY, scaleZ);
    
    drawHelicopter();

    glutSwapBuffers();
}