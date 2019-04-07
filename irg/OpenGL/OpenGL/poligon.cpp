////*********************************************************************************
////	Iscrtavanje linije 0-45, usporedba s glLine naredbom.
////	Pocetna i krajnja koordinata se zadaju lijevom tiplom misa, desnom se brise.
////	r, g, b, k s tastature mijenja boju.
////
////	Zadatak: Treba preraditi void myLine(GLint xa, GLint ya, GLint xb, GLint yb)
////	tako da radi ispravno za sve kutove
////
////  Potreban je glut - http://freeglut.sourceforge.net/
////  Za MSVC skinuti: 
////  http://files.transmissionzero.co.uk/software/development/GLUT/freeglut-MSVC.zip
////  postaviti - Properties - Configuration properties VC++Directories - Include Dir
////                                                                    - Library Dir
////*********************************************************************************
//#include <GL/glut.h>
//#include <stdio.h>
//#include "bresenham.h"
//#include <vector> 
//#include <stdlib.h>
//#include <iostream>
//
//using namespace std;
//
//typedef struct {
//	int x;
//	int y;
//}iTocka2D;
//
//typedef struct {
//	int a;
//	int b;
//	int c;
//	bool lijevi;
//}iBrid2D;
//
//typedef struct {
//	iTocka2D Vrh;
//	iBrid2D Brid;
//	bool lijevi;
//}iPolyElem;
//
//// polje unesenih tocaka
//vector<iTocka2D> poljeTocaka = {};
//vector<iBrid2D> poljeBridova = {};
//vector<iPolyElem> poljePoligona = {};
//int a = 0;
//
//
////*********************************************************************************
////	Pocetna tocka Lx[1], Ly[1] Krajnja tocke Lx[2], Ly[2] linije.
////	Ix - stanje (zadana 1 ili 2 tocka)
////*********************************************************************************
//
//GLdouble Lx[2], Ly[2];
//GLint Ix;
//
////*********************************************************************************
////	Pokazivac na glavni prozor i pocetna velicina.
////*********************************************************************************
//
//GLuint window;
//GLuint width = 400, height = 400;
//
////*********************************************************************************
////	Function Prototypes.
////*********************************************************************************
//
//void myDisplay();
//void myReshape(int width, int height);
//void myMouse(int button, int state, int x, int y);
//void myKeyboard(unsigned char theKey, int mouseX, int mouseY);
//void myLine(GLint xa, GLint ya, GLint xb, GLint yb);
//void CrtajPoligonKonv();
//void RacunajKoefPoligonKonv();
//void PopuniPoligonKonv();
//void computePolyCoeff(void);
//
//int main(int argc, char ** argv)
//{
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowSize(width, height);
//	glutInitWindowPosition(200, 200);
//	glutInit(&argc, argv);
//
//	window = glutCreateWindow("Glut OpenGL Linija");
//	glutReshapeFunc(myReshape);
//	glutDisplayFunc(myDisplay);
//	glutMouseFunc(myMouse);
//	glutKeyboardFunc(myKeyboard);
//	printf("Lijevom tipkom misa zadaj tocke - algoritam Bresenham-a\n");
//	printf("Tipke r, g, b, k mijenjaju boju.\n");
//
//	glutMainLoop();
//	return 0;
//}
//
//void myDisplay()
//{
//	if (poljeTocaka.size() > 2) {
//		CrtajPoligonKonv();
//		//RacunajKoefPoligonKonv();
//		computePolyCoeff();
//		PopuniPoligonKonv();
//	}
//	//printf("Pozvan myDisplay()\n");
//	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //  boja pozadine
//	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //brisanje nakon svake iscrtane linije
//	glFlush();
//}
//
//void myReshape(int w, int h)
//{
//	//printf("Pozvan myReshape()\n");
//	width = w; height = h;               //promjena sirine i visine prozora
//	Ix = 0;								//	indeks tocke 0-prva 1-druga tocka
//	glViewport(0, 0, width, height);	//  otvor u prozoru
//
//	glMatrixMode(GL_PROJECTION);		//	matrica projekcije
//	glLoadIdentity();					//	jedinicna matrica
//	glOrtho(0, w, 0, h, -1, 1); 	//	okomita projekcija
//	glMatrixMode(GL_MODELVIEW);			//	matrica pogleda
//	glLoadIdentity();					//	jedinicna matrica
//
//	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // boja pozadine
//	glClear(GL_COLOR_BUFFER_BIT);		//	brisanje pozadine
//	glPointSize(1.0);					//	postavi velicinu tocke za liniju
//	glColor3f(0.0f, 0.0f, 0.0f);		//	postavi boju linije
//	//glScalef(1, -1, 1);           /* Invert Y axis so increasing Y goes down. */
//	//glTranslatef(0, -h, 0);       /* Shift origin up to upper-left corner. */
//}
//
//
//void myMouse(int button, int state, int x, int y)
//{
//	//	Lijeva tipka - crta pocetnu tocku ili liniju.
//	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//
//	{
//		//	Pamti krajnju tocke linije.
//		Lx[Ix] = x;							//	upisi tocku
//		Ly[Ix] = height - y;
//		Ix = Ix ^ 1;						//	flip - druga tocka
//
//		iTocka2D tocka; tocka.x = x;  tocka.y = y;
//		poljeTocaka.push_back(tocka);
//		printf("Koordinate tocke %d: %d %d \n", Ix ^ 1, x, y);
//		glFlush();
//	}
//
//	//	Desna tipka - brise canvas.
//	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
//	{
//		myReshape(width, height);
//		::poljeTocaka.clear();
//	}
//}
//
//// pritiskom na tipku "c" nacrta se poligon kojem su tocke zadane preko klika misa
//void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
//{
//	if (theKey == 'c') {
//		
//	}
//	else if (theKey == 't') {
//		int x, y, n;
//		n = poljePoligona.size();
//		x = poljePoligona[n - 1].Vrh.x;
//		y = poljePoligona[n - 1].Vrh.y;
//		bool sveManje = true;
//		printf("izabrana tocka: %d %d\n", x, y);
//		for (int i = 0; i < n; i++) {
//			int temp = x * poljePoligona[i].Brid.a + y * poljePoligona[i].Brid.b + poljePoligona[i].Brid.c;
//			if (temp > 0) sveManje = false;
//			break;
//		}
//		if (sveManje) {
//			cout << "Tocka je unutar poligona.\n" << endl;
//		}
//		else {
//			cout << "Tocka je izvan poligona.\n" << endl;
//		}
//	}
//	glFlush();
//}
//
//// metoda za crtati poligon preko bresenhamova algoritma
//void CrtajPoligonKonv() {
//	int n = poljeTocaka.size();
//	int i0 = n - 1;
//	
//	for (int i = 0; i < n; i++) {
//		bresenham_nacrtaj_cjelobrojni(poljeTocaka.at(i0).x, height - poljeTocaka.at(i0).y,
//			poljeTocaka.at(i).x, height - poljeTocaka.at(i).y);
//		i0 = i;
//	}
//}
//
//void RacunajKoefPoligonKonv(){
//	int i0 = poljeTocaka.size() - 1;
//	poljeBridova.clear();
//	//vector<iPolyElem> polel_temp = *polel;
//	/*for (int i = 0; i < poljePoligona.size(); i++) {
//		printf("dobijena tocka %d: %d %d\n", i, polel[i].Vrh.x, polel[i].Vrh.y);
//	}*/
//	for (int i = 0; i < poljeTocaka.size(); i++) {
//		iBrid2D brid;
//		brid.a = poljeTocaka.at(i0).y - poljeTocaka.at(i).y;
//		brid.b = -(poljeTocaka.at(i0).x - poljeTocaka.at(i).x);
//		brid.c = poljeTocaka.at(i0).x * poljeTocaka.at(i).y - poljeTocaka.at(i0).y * poljeTocaka.at(i).x;
//		brid.lijevi = poljeTocaka.at(i0).y < poljeTocaka.at(i).y;
//		poljeBridova.push_back(brid);
//		i0 = i;
//	}
//	for (int i = 0; i < poljeBridova.size(); i++) {
//		printf("edge a: %d, b: %d, c: %d\n", poljeBridova.at(i).a, poljeBridova.at(i).b, poljeBridova.at(i).c);
//	}
//
//}
//
//void computePolyCoeff(void) {
//	int i, i0;
//
//	poljeBridova.clear();
//
//	i0 = poljeTocaka.size() - 1;
//	for (i = 0; i < poljeTocaka.size(); i++) {
//		iBrid2D tmp;
//		tmp.a = poljeTocaka.at(i0).y - poljeTocaka.at(i).y;
//		if (tmp.a == 0)
//			cout << "DEKLARIRAM u " << poljeBridova.size() << " a = 0 za i0 = " << i0 << "i = " << i << " " << poljeTocaka.at(i0).y << " " << poljeTocaka.at(i).y << endl;
//		tmp.b = -(poljeTocaka.at(i0).x - poljeTocaka.at(i).x);
//		tmp.c = poljeTocaka.at(i0).x * poljeTocaka.at(i).y - poljeTocaka.at(i0).y * poljeTocaka.at(i).x;
//		tmp.lijevi = (poljeTocaka.at(i0).y < poljeTocaka.at(i).y);
//		poljeBridova.push_back(tmp);
//		i0 = i;
//	}
//	for (i = 0; i < poljeBridova.size(); i++) {
//		printf("edge a: %d, b: %d, c: %d\n", poljeBridova.at(i).a, poljeBridova.at(i).b, poljeBridova.at(i).c);
//	}
//}
//
//
//void PopuniPoligonKonv() {
//	int i, i0, y;
//	int xmin, xmax, ymin, ymax;
//	double L, D, x;
//
//	xmin = xmax = poljeTocaka.at(0).x;
//	ymin = ymax = poljeTocaka.at(0).y;
//	for (i = 1; i < poljeTocaka.size(); i++) {
//		if (xmin > poljeTocaka.at(i).x) xmin = poljeTocaka.at(i).x;
//		if (xmax < poljeTocaka.at(i).x) xmax = poljeTocaka.at(i).x;
//		if (ymin > poljeTocaka.at(i).y) ymin = poljeTocaka.at(i).y;
//		if (ymax < poljeTocaka.at(i).y) ymax = poljeTocaka.at(i).y;
//	}
//
//	for (y = ymin; y <= ymax; y++) {
//		L = xmin; D = xmax;
//		i0 = poljeTocaka.size() - 1;
//		for (i = 0; i < poljeTocaka.size(); i0 = i++) {
//			if (poljeBridova.at(i0).a == 0) {
//				if (poljeTocaka.at(i0).y == y) {
//					if (poljeTocaka.at(i0).x >= poljeTocaka.at(i).x) {
//						L = poljeTocaka.at(i0).x;
//						D = poljeTocaka.at(i).x;
//					}
//					else {
//						L = poljeTocaka.at(i).x;
//						D = poljeTocaka.at(i0).x;
//					}
//					break;
//				}
//			}
//			else {
//				x = (-(poljeBridova.at(i).b * y + poljeBridova.at(i).c)) / (double)poljeBridova.at(i).a;
//				//printf("x: %f\n", x);
//				if (poljeBridova.at(i).lijevi) {
//					if (L < x) L = x;
//					//printf("L: %f\n", L);
//				}
//				else {
//					if (D > x) D = x;
//				}
//			}
//		}
//		bresenham_nacrtaj_cjelobrojni(L, height - y, D, height - y);
//	}
//}
