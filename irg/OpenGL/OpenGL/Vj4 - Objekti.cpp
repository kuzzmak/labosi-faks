//#include <fstream>
//#include <stdio.h>
//#include <iostream>
//#include <string>
//#include <vector>
//#include "bresenham.h"
//#include <sstream>
//
//using namespace std;
//
//typedef struct {
//	float x;
//	float y;
//	float z;
//}iTocka3D;
//
//typedef struct {
//	iTocka3D t1;
//	iTocka3D t2;
//	iTocka3D t3;
//	int a;
//	int b;
//	int c;
//	int d;
//}iPoly;
//
//// vektor sa svim tockama 
//vector<iTocka3D> poljeTocaka;
//// vektor sa indeksima tocaka od kojih se sastoji svaki poligon
//vector<iPoly> poljePoly;
//// vektor poligona za crtanje
//vector<iPoly> poljePolygona;
//
//vector<float> boja;
//
//void reshape(int width, int height);
//void display(void);
//void ucitajObjekt(string path);
//void CrtajPoligonKonv(void);
//
//GLuint width = 1378;
//GLuint height = 768;
//
//
//int main(int argc, char *argv[]) {
//
//	// ucitavanje odredjene datoteke koja sadrzi tocke i poligone objekta
//	ucitajObjekt("C:\\Users\\kuzmi\\Downloads\\faks\\IRG\\labosi\\porsche.obj");
//	boja.push_back(0.1);
//	boja.push_back(0.2);
//	boja.push_back(0.3);
//	boja.push_back(0.4);
//	boja.push_back(0.5);
//	boja.push_back(0.6);
//	boja.push_back(0.7);
//	boja.push_back(0.8);
//	boja.push_back(0.9);
//	
//	/*int x, y, z;
//	printf("Unesi koordinatu za koju zelis provjeriti nalazi li se u tijelu u obliku x y z\n");
//	cin >> x >> y >> z;
//
//	for (int i = 0; i < poljePolygona.size(); i++) {
//		iTocka3D t1 = poljePolygona.at(i).t1;
//		iTocka3D t2 = poljePolygona.at(i).t2;
//		iTocka3D t3 = poljePolygona.at(i).t3;
//		int a = (t2.y - t1.y) * (t3.z - t1.z) - (t2.z - t1.z) * (t3.y - t1.y);
//		int b = -(t2.x - t1.x) * (t3.z - t1.z) + (t2.z - t1.z) * (t3.x - t1.x);
//		int c = (t2.x - t1.x) * (t3.y - t1.y) - (t2.y - t1.y) * (t3.x - t1.x);
//		int d = -t1.x * a - t1.y * b - t1.z * c;
//		poljePolygona.at(i).a = a;
//		poljePolygona.at(i).b = b;
//		poljePolygona.at(i).c = c;
//		poljePolygona.at(i).d = d;
//	}
//
//	bool sveManje = true;
//	for (int i = 0; i < poljePolygona.size(); i++) {
//		if (poljePolygona.at(i).a * x + poljePolygona.at(i).b * y + poljePolygona.at(i).c * z + poljePolygona.at(i).d > 0) {
//			sveManje = false;
//			break;
//		}
//	}
//
//	sveManje == true ? printf("Tocka (%d, %d %d) je unutar poligona.\n", x, y, z) : printf("Tocka (%d, %d %d) je izvan poligona.\n", x, y, z);*/
//	
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(width, height);
//	glutInitWindowPosition(200, 200);
//
//	glutCreateWindow("Vj4 - Objekti");
//
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//	glutMainLoop();
//
//}
//
//void display() {
//	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glPointSize(1.0);
//	CrtajPoligonKonv();
//	glutSwapBuffers();
//	glFlush();
//}
//
//void reshape(int w, int h) {
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0, w, 0, h);
//	glColor3f(0.0f, 0.0f, 0.0f);
//	glMatrixMode(GL_MODELVIEW);
//}
//
//
//
//
//// funkcija za crtanje poligona iz ucitane datoteke
//void CrtajPoligonKonv() {
//
//	for (int j = 0; j < poljePolygona.size(); j++) {
//		// pomocni vektor koji sadrzi tocke poligona koji se crta
//		vector<iTocka3D> tocke;
//		tocke.push_back(poljePolygona.at(j).t1);
//		tocke.push_back(poljePolygona.at(j).t2);
//		tocke.push_back(poljePolygona.at(j).t3);
//		
//		int i0 = 2;
//		for (int i = 0; i < 3; i++) {
//			// teddy    //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 10 + 689, tocke.at(i0).y*10 + 300, tocke.at(i).x * 10 + 689, tocke.at(i).y * 10 + 300);
//			// porsche  //
//			bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 1300 + 689, tocke.at(i0).y * 1300  + 300, tocke.at(i).x * 1300 + 689, tocke.at(i).y * 1300 + 300);
//			// teapot   //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 100 + 689, tocke.at(i0).y * 100 + 300, tocke.at(i).x * 100 + 689, tocke.at(i).y * 100 + 300);
//			// all      //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 600 + 689, tocke.at(i0).y * 600 + 600, tocke.at(i).x * 600 + 689, tocke.at(i).y * 600 + 600);
//			// frog     //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 80 + 689, tocke.at(i0).y * 80 + 200, tocke.at(i).x * 80 + 689, tocke.at(i).y * 80 + 200);
//			// arena    //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 500 + 689, tocke.at(i0).y * 500 + 350, tocke.at(i).x * 500 + 689, tocke.at(i).y * 500 + 350);
//			// bird     //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 500 + 689, tocke.at(i0).y * 500 + 500, tocke.at(i).x * 500 + 689, tocke.at(i).y * 500 + 500);
//			// dragon   //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 900 + 689, tocke.at(i0).y * 900 + 350, tocke.at(i).x * 900 + 689, tocke.at(i).y * 900 + 350);
//			// skll     //bresenham_nacrtaj_cjelobrojni(tocke.at(i0).x * 800 + 689, tocke.at(i0).y * 800 + 350, tocke.at(i).x * 800 + 689, tocke.at(i).y * 800 + 350);
//			i0 = i;
//		}
//		tocke.clear();
//		glFlush();
//	}
//}
//
//// funkcija za podjelu linije na dijelove koja vraca vektor s prvom vrijednoscu v(tocka) i 3 koordinate tocke ili
//// f(poligon) i 3 tocke koje pripadaju tom poligon
//vector<string> split(const string& s, char delimiter)
//{
//	vector<string> tokens;
//	string token;
//	istringstream tokenStream(s);
//	while (getline(tokenStream, token, delimiter))
//	{
//		tokens.push_back(token);
//	}
//	return tokens;
//}
//
//// funkcija za ucitavanje objekta i popunjavanje vektora s polgonima koje treba nacrtati
//void ucitajObjekt(string path) {
//	string line;
//	ifstream myfile(path);
//	if (myfile.is_open()) {
//		while (myfile.good()) {
//			getline(myfile, line);
//			// vektor odijeljenih koordinata tocke ili poligona
//			vector<string> splittedStrings = split(line, ' ');
//			// ako nismo dosli do kraja datoteke
//			if (splittedStrings.size() > 0) {
//				// ako je prva komponenta vektora v to znaci da je procitan redak s tockom
//				if (splittedStrings[0] == "v") {
//					// stvaranje strukture tocke i slanje u vektor tocaka
//					iTocka3D v;
//					v.x = strtod(splittedStrings[1].c_str(), NULL);
//					v.y = strtod(splittedStrings[2].c_str(), NULL);
//					v.z = strtod(splittedStrings[3].c_str(), NULL);
//					poljeTocaka.push_back(v);
//				}
//				// ako je prva komponenta vektora f to znaci da je procitan redak s poligonom
//				else if (splittedStrings[0] == "f") {
//					// stvaranje strukture poligona i slanje u vektor poligona
//					iPoly p;
//					p.a = atoi(splittedStrings[1].c_str());
//					p.b = atoi(splittedStrings[2].c_str());
//					p.c = atoi(splittedStrings[3].c_str());
//					poljePoly.push_back(p);
//				}
//			}
//		}
//		myfile.close();
//	}
//	else {
//		cout << "Unable to open file" << endl;
//	}
//
//	// stvaranje poligona s tockama koje pripadaju pojedinom poligonu
//	iPoly poly;
//	for (int i = 0; i < poljePoly.size(); i++) {
//		// dohvacanje tocaka koje pripadaju odredjenom poligonu
//		int a = poljePoly[i].a;
//		int b = poljePoly[i].b;
//		int c = poljePoly[i].c;
//		// -1 zbog toga jer tocke pocinju s 1, a ne s 0
//		iTocka3D t1 = poljeTocaka.at(a - 1);
//		iTocka3D t2 = poljeTocaka.at(b - 1);
//		iTocka3D t3 = poljeTocaka.at(c - 1);
//
//		iPoly poly;
//		poly.t1 = t1;
//		poly.t2 = t2;
//		poly.t3 = t3;
//		// slanje u polje poligona koje sluzi za crtanje
//		poljePolygona.push_back(poly);
//	}
//}