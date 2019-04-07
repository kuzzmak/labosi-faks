//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <GL/glut.h>
//
//int kut = 0;
//
//void idle() {
//	kut++;
//	if (kut >= 360) kut = 0;
//	glutPostRedisplay();
//}
//
//void drawSquare() {
//	glBegin(GL_QUADS);
//	glVertex2f(0.0, 0.0);
//	glVertex2f(10.0, 0.0);
//	glVertex2f(10.0, 10.0);
//	glVertex2f(0.0, 10.0);
//	glEnd();
//}
//
//void renderScene() {
//	glPointSize(1);
//
//	glColor3f(0.5, 0.5, 0.5);
//	for (int j = 0; j < 20; j++) {
//		for (int i = 0; i < 20; i++) {
//			glColor3f(0.05 * i, 0.05 * j, 0.05 * i * j);
//			if (i % 2 == 0) {
//				glPushMatrix();
//				glTranslatef(i * 20 + 10, j * 20 + 10, 0.0);
//				glScalef(1.5, 1.5, 1.0);
//				glRotatef((float)kut, 0.0, 0.0, 1.0);
//				glTranslatef(-5.0, -5.0, 0.0);
//				drawSquare();
//				glPopMatrix();
//			}
//			else {
//				glPushMatrix();
//				glTranslatef(i * 20 + 10, j * 20 + 10, 0.0);
//				glScalef(1.5, 1.5, 1.0);
//				glRotatef(-(float)kut, 0.0, 0.0, 1.0);
//				glTranslatef(-5.0, -5.0, 0.0);
//				drawSquare();
//				glPopMatrix();
//			}
//		}
//	}
//}
//
//void reshape(int width, int height) {
//	glDisable(GL_DEPTH_TEST);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0, width - 1, 0, height - 1, 0, 1);
//	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
//	glMatrixMode(GL_MODELVIEW);
//}
//
//void display() {
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glLoadIdentity();
//	renderScene();
//	glutSwapBuffers();
//}
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE);
//	glutInitWindowSize(600, 300);
//	glutInitWindowPosition(0, 0);
//	glutCreateWindow("Primjer animacije.");
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//	glutIdleFunc(idle);
//	glutMainLoop();
//}
