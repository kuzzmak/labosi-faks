#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "bresenham.h"

using namespace std;

void reshape(int width, int height);
void display();
void mouse(int button, int state, int x, int y);

// struktura tocke
typedef struct {
	int x;
	int y;
}iTocka2D;

// struktura brida
typedef struct {
	int a;
	int b;
	int c;
	bool lijevi; // oznacava je li brid lijevi(dio poligona gdje 
}iBrid2D;		 // vrhovi rastu prema vecim y-vrijednostima)

// polje tocaka
vector<iTocka2D> poljeTocaka;

// polje bridova 
vector<iBrid2D> poljeBridova;

// pocetne vrijednosti velicine prozora
GLuint width = 400;
GLuint height = 400;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(200, 200);

	glutCreateWindow("Vj3 - Poligon");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();
}

// funkcija za crtanje poligona preko bresenhamova algoritma
void CrtajPoligonKonv(void) {
	int i, i0;
	i0 = poljeTocaka.size() - 1;
	for (i = 0; i < poljeTocaka.size(); i++) {
		bresenham_nacrtaj_cjelobrojni(poljeTocaka.at(i0).x,  poljeTocaka.at(i0).y, poljeTocaka.at(i).x,  poljeTocaka.at(i).y);
		i0 = i;
	}
}

// funkcija za izracunavanje koeficijenata pravaca bridova
void RacunajKoefPoligonKonv(void) {
	int i, i0;
	poljeBridova.clear();
	i0 = poljeTocaka.size() - 1;
	for (i = 0; i < poljeTocaka.size(); i++) {
		iBrid2D tmp;
		tmp.a = poljeTocaka.at(i0).y - poljeTocaka.at(i).y;
		tmp.b = -(poljeTocaka.at(i0).x - poljeTocaka.at(i).x);
		tmp.c = poljeTocaka.at(i0).x * poljeTocaka.at(i).y - poljeTocaka.at(i0).y * poljeTocaka.at(i).x;
		tmp.lijevi = (poljeTocaka.at(i0).y < poljeTocaka.at(i).y);
		poljeBridova.push_back(tmp);
		i0 = i;
	}
}

// funkcija za popunjavanje poligona
void PopuniPoligonKonv(void) {
	int i, i0, y;
	int xmin, xmax, ymin, ymax;
	double L, D, x;

	// trazenje minimalnih i maksimalnih koordinata
	xmin = xmax = poljeTocaka.at(0).x;
	ymin = ymax = poljeTocaka.at(0).y;

	for (i = 1; i < poljeTocaka.size(); i++) {
		if (xmin > poljeTocaka.at(i).x) xmin = poljeTocaka.at(i).x;
		if (xmax < poljeTocaka.at(i).x) xmax = poljeTocaka.at(i).x;
		if (ymin > poljeTocaka.at(i).y) ymin = poljeTocaka.at(i).y;
		if (ymax < poljeTocaka.at(i).y) ymax = poljeTocaka.at(i).y;
	}

	// bojanje poligona za svaki y od ymin do ymax, liniju po liniju
	for (y = ymin; y <= ymax; y++) {
		L = xmin; D = xmax;
		i0 = poljeTocaka.size() - 1;
		for (i = 0; i < poljeTocaka.size(); i0 = i++) {
			// ako je brid vodoravan
			if (poljeBridova.at(i).a == 0) {
				if (poljeTocaka.at(i).y == y) {
					if (poljeTocaka.at(i0).x >= poljeTocaka.at(i).x) {
						L = poljeTocaka.at(i0).x;
						D = poljeTocaka.at(i).x;
					}
					else {
						L = poljeTocaka.at(i).x;
						D = poljeTocaka.at(i0).x;
					}
					break;
				}
			}
			// ako je brid regularan trazi se sjeciste
			else { 
				x = (-poljeBridova.at(i).b * y - poljeBridova.at(i).c) / (double)poljeBridova.at(i).a;
				bool tmp = poljeBridova.at(i).lijevi;
				if (tmp) {
					if (L < x) L = x;
				}
				else {
					if (D > x) D = x;
				}
			}
		}
		// crtanje linije
		bresenham_nacrtaj(L, y, D, y);
	}
}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(1.0);
	// ako postoji vise od dvije tocke u vektoru, iscrtava se poligon
	if (poljeTocaka.size() > 2) {
		CrtajPoligonKonv();
		RacunajKoefPoligonKonv();
		PopuniPoligonKonv();
	}
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

void mouse(int button, int state, int x, int y) {
	// pritisokm na ijevu tipku misa, dodaje se nova tocka u vektor tocaka
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		iTocka2D tocka = {x, height - y};
		poljeTocaka.push_back(tocka);
		glFlush();
	}
	// pritiskom na desnu tipku misa provjerava se pripadnost tocke poligonu
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		iTocka2D tocka = {x, height - y}; 
		bool unutar = true;
		for (int i = 0; i < poljeBridova.size(); i++) {
			if (tocka.x * poljeBridova.at(i).a + tocka.y * poljeBridova.at(i).b + poljeBridova.at(i).c > 0) {
				unutar = false;
				break;
			}
		}
		unutar == true ? printf("Tocka (%d, %d) je unutar poligona.\n", x, y) : printf("Tocka (%d, %d) je izvan poligona.\n", x, y);
		glutSwapBuffers();
		glFlush();
	}	
}
