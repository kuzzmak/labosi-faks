#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "bresenham.h"
#include <sstream>
#include <math.h>
#include <glm/glm.hpp>

using namespace std;

typedef struct {
	float x;
	float y;
	float z;
	float h;
}iTocka3D;

// vektor sa svim tockama 
vector<iTocka3D> poljeTocaka;

GLuint width = 800;
GLuint height = 600;


// funkcija za podjelu linije na dijelove koja vraca vektor s prvom vrijednoscu v(tocka) i 3 koordinate tocke ili
// f(poligon) i 3 tocke koje pripadaju tom poligon
vector<string> split(const string& s, char delimiter)
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

void ucitajObjekt(string path) {
	string line;
	ifstream myfile(path);
	if (myfile.is_open()) {
		while (myfile.good()) {
			getline(myfile, line);
			// vektor odijeljenih koordinata tocke ili poligona
			vector<string> splittedStrings = split(line, ' ');
			// ako nismo dosli do kraja datoteke
			if (splittedStrings.size() > 0) {
				// ako je prva komponenta vektora v to znaci da je procitan redak s tockom
				if (splittedStrings[0] == "v") {
					// stvaranje strukture tocke i slanje u vektor tocaka
					iTocka3D v;
					v.x = strtod(splittedStrings[1].c_str(), NULL);
					v.y = strtod(splittedStrings[2].c_str(), NULL);
					v.z = strtod(splittedStrings[3].c_str(), NULL);
					v.h = 1;
					poljeTocaka.push_back(v);
				}
			}
		}
		myfile.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}
}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(1.0);
	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glColor3f(0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(200, 200);

	glutCreateWindow("Vj6 - Krivulja");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}