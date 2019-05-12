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

typedef struct {
	iTocka3D t1;
	iTocka3D t2;
	iTocka3D t3;
	int a;
	int b;
	int c;
	int d;
}iPoly;

// vektor sa svim tockama 
vector<iTocka3D> poljeTocaka;
// vektor sa indeksima tocaka od kojih se sastoji svaki poligon
vector<iPoly> poljePoly;
// vektor poligona za crtanje
vector<iPoly> poljePolygona;

void myMouse(int, int, int, int);
void reshape(int width, int height);
void display(void);
void ucitajObjekt(string path);
void CrtajPoligonKonv(void);

GLuint width = 800;
GLuint height = 600;

// ociste i glediste
iTocka3D g;
iTocka3D o;

// funkcije za formatirani ispis matrice 4x4
void matrix_print(glm::mat4x4 matrix) {
	printf("\n");
	printf(" _                                            _\n");
	printf("| %10f %10f %10f %10f  |\n", matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3]);
	printf("| %10f %10f %10f %10f  |\n", matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3]);
	printf("| %10f %10f %10f %10f  |\n", matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3]);
	printf("|_%10f %10f %10f %10f _|\n", matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);
	printf("\n");
}

glm::mat4x4 transformation_matrix() {
	// pomak ishodista koordinatnog sustava oka u ishodiste scene
	glm::mat4x4 T1 = glm::mat4x4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-o.x, -o.y, -o.z, 1);

	iTocka3D g1;
	g1.x = g.x - o.x;
	g1.y = g.y - o.y;
	g1.z = g.z - o.z;
	g1.h = 1;

	// rotacija oko osi z
	float sina = g1.y / sqrt(pow(g1.x, 2) + pow(g1.y, 2));
	float cosa = g1.x / sqrt(pow(g1.x, 2) + pow(g1.y, 2));

	glm::mat4x4 T2 = glm::mat4x4(cosa, -sina, 0, 0,
		sina, cosa, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	iTocka3D g2;
	g2.x = sqrt(pow(g1.x, 2) + pow(g1.y, 2));
	g2.y = 0;
	g2.z = g1.z;
	g2.h = 1;

	// rotacija oko osi y
	float sinb = g2.x / sqrt(pow(g2.x, 2) + pow(g2.z, 2));
	float cosb = g2.z / sqrt(pow(g2.x, 2) + pow(g2.z, 2));

	glm::mat4x4 T3 = glm::mat4x4(cosb, 0, sinb, 0,
		0, 1, 0, 0,
		-sinb, 0, cosb, 0,
		0, 0, 0, 1);

	iTocka3D g3;
	g3.x = 0;
	g3.y = 0;
	g3.z = sqrt(pow(g2.x, 2) + pow(g2.z, 2));
	g3.h = 1;

	// rotacija za kut 90 oko osi z
	glm::mat4x4 T4 = glm::mat4x4(0, -1, 0, 0,
		1, 0, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	// zrcaljenje osi x
	glm::mat4x4 T5 = glm::mat4x4(-1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	glm::mat4x4 T = glm::transpose(glm::transpose(T1)
		* glm::transpose(T2)
		* glm::transpose(T3)
		* glm::transpose(T4)
		* glm::transpose(T5));

	return T;
}

int main(int argc, char *argv[]) {

	////unos gledista i ocista
	//printf("Unesi koordinate gledista: (x, y, z)\n");
	//cin >> g.x >> g.y >> g.z;
	//printf("Unesi koordinate ocista: (x, y, z)\n");
	//cin >> o.x >> o.y >> o.z;

	//ucitavanje odredjene datoteke koja sadrzi tocke i poligone objekta
	ucitajObjekt("C:\\Users\\kuzmi\\Downloads\\faks\\IRG\\labosi\\labosi\\lab5\\teddy.obj.txt");
	

	o.x = 20; o.y = -10; o.z = 30; o.h = 1;
	g.x = -10; g.y = -10; g.z = 0; g.h = 1;
	
	// matrica transformacije
	glm::mat4x4 T = transformation_matrix();
	// udaljenost ravnine projekcije od ocista
	float H = sqrt(pow((o.x - g.x), 2) + pow((o.y - g.y), 2) + pow((o.z - g.z), 2));
	// matrica perspektivne projekcije
	glm::mat4x4 P = glm::mat4x4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 1 / H,
		0, 0, 0, 0);

	for (int i = 0; i < poljeTocaka.size(); i++) {
		
		glm::vec4 tocka_vec = glm::vec4(poljeTocaka[i].x, poljeTocaka[i].y, poljeTocaka[i].z, poljeTocaka[i].h);
		// umnozak tocke i matrice transformacije
		tocka_vec = tocka_vec * glm::transpose(T);
		if (tocka_vec[3] != 1) {
			tocka_vec[0] /= tocka_vec[3];
			tocka_vec[1] /= tocka_vec[3];
			tocka_vec[2] /= tocka_vec[3];
		}
		tocka_vec[3] = 1;

		// umnozak tocke i matrice perspektivne projekcije
		tocka_vec = tocka_vec * glm::transpose(P);
		if (tocka_vec[3] != 1) {
			tocka_vec[0] /= tocka_vec[3];
			tocka_vec[1] /= tocka_vec[3];
			tocka_vec[2] /= tocka_vec[3];
		}
		tocka_vec[3] = 1;

		// azuriranje koordinata tocaka
		poljeTocaka[i] = { tocka_vec[0], tocka_vec[1], tocka_vec[2], tocka_vec[3] };
	}
	
	// stvaranje poligona s tockama koje pripadaju pojedinom poligonu
	iPoly poly;
	for (int i = 0; i < poljePoly.size(); i++) {
		// dohvacanje tocaka koje pripadaju odredjenom poligonu
		int a = poljePoly[i].a;
		int b = poljePoly[i].b;
		int c = poljePoly[i].c;
		// -1 zbog toga jer tocke pocinju s 1, a ne s 0
		iTocka3D t1 = poljeTocaka.at(a - 1);
		iTocka3D t2 = poljeTocaka.at(b - 1);
		iTocka3D t3 = poljeTocaka.at(c - 1);

		iPoly poly;
		poly.t1 = t1;
		poly.t2 = t2;
		poly.t3 = t3;
		// slanje u polje poligona koje sluzi za crtanje
		poljePolygona.push_back(poly);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(200, 200);

	glutCreateWindow("Vj5 - Projekcije");
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(myMouse);
	glutMainLoop();

}

void myMouse(int button, int state, int x, int y)
{
	//	Lijeva tipka - crta pocetnu tocku ili liniju.
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		
	}
}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(1.0);
	CrtajPoligonKonv();
	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(-1, 1, 1, -1);
	gluOrtho2D(0, w, 0, h);
	glColor3f(0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
}

// funkcija za crtanje poligona iz ucitane datoteke
void CrtajPoligonKonv() {
	for (int j = 0; j < poljePolygona.size(); j++) {
		// pomocni vektor koji sadrzi tocke poligona koji se crta
		vector<iTocka3D> tocke;
		tocke.push_back(poljePolygona.at(j).t1);
		tocke.push_back(poljePolygona.at(j).t2);
		tocke.push_back(poljePolygona.at(j).t3);

		int i0 = 2;
		for (int i = 0; i < 3; i++) {
			// teddy    //
			bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 10 + 300, tocke.at(i0).y * 10 + 300, tocke.at(i).x * 10 + 300, tocke.at(i).y * 10 + 300);
			// porsche  //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 1300 + 689, tocke.at(i0).y * 1300  + 300, tocke.at(i).x * 1300 + 689, tocke.at(i).y * 1300 + 300);
			// teapot   //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 100 + 689, tocke.at(i0).y * 100 + 300, tocke.at(i).x * 100 + 689, tocke.at(i).y * 100 + 300);
			// all      //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 600 + 689, tocke.at(i0).y * 600 + 600, tocke.at(i).x * 600 + 689, tocke.at(i).y * 600 + 600);
			// frog     //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 80 + 689, tocke.at(i0).y * 80 + 200, tocke.at(i).x * 80 + 689, tocke.at(i).y * 80 + 200);
			// arena    //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 500 + 689, tocke.at(i0).y * 500 + 350, tocke.at(i).x * 500 + 689, tocke.at(i).y * 500 + 350);
			// bird     //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 500 + 689, tocke.at(i0).y * 500 + 500, tocke.at(i).x * 500 + 689, tocke.at(i).y * 500 + 500);
			// dragon   //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 900 + 689, tocke.at(i0).y * 900 + 350, tocke.at(i).x * 900 + 689, tocke.at(i).y * 900 + 350);
			// skll     //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 800 + 689, tocke.at(i0).y * 800 + 350, tocke.at(i).x * 800 + 689, tocke.at(i).y * 800 + 350);
			i0 = i;
		}
		tocke.clear();
		glFlush();
	}
}

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

// funkcija za ucitavanje objekta i popunjavanje vektora s polgonima koje treba nacrtati
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
				// ako je prva komponenta vektora f to znaci da je procitan redak s poligonom
				else if (splittedStrings[0] == "f") {
					// stvaranje strukture poligona i slanje u vektor poligona
					iPoly p;
					p.a = atoi(splittedStrings[1].c_str());
					p.b = atoi(splittedStrings[2].c_str());
					p.c = atoi(splittedStrings[3].c_str());
					poljePoly.push_back(p);
				}
			}
		}
		myfile.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}
}