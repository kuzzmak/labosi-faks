#include <GL/glut.h>

void line_nacrtaj(int xa, int ya, int xb, int yb) {
	glBegin(GL_LINES);
	{
		glVertex2i(xa, ya + 20);			//	crtanje gotove linije
		glVertex2i(xb, yb + 20);
	}
	glEnd();
}

void bresenham_nacrtaj(int xs, int ys, int xe, int ye) {
	int x, yc;
	double a, yf;
	//line_nacrtaj(xs, ys, xe, ye);
	a = (ye - ys) / (double)(xe - xs);

	yc = ys;
	yf = -0.5;

	glBegin(GL_POINTS);
	for (x = xs; x <= xe; x++) {
		glVertex2i(x, yc);
		yf = yf + a;
		if (yf >= 0) {
			yf = yf - 1.0;
			yc = yc + 1;
		}
	}
	glEnd();
}

void bresenham_nacrtaj_cjelobrojni1(int xs, int ys, int xe, int ye) {
	int x, yc, korekcija;
	int a, yf;

	a = 2 * (ye - ys);

	yc = ys;
	yf = -(xe - xs);
	korekcija = -2 * (xe - xs);

	glBegin(GL_POINTS);
	for (x = xs; x <= xe; x++) {
		glVertex2i(x, yc);
		yf = yf + a;
		if (yf >= 0) {
			yf = yf + korekcija;
			yc = yc + 1;
		}
	}
	glEnd();
}

void bresenham_nacrtaj_cjelobrojni2(int xs, int ys, int xe, int ye) {
	int x, yc, korekcija;
	int a, yf;

	if (ye - ys <= xe - xs) {

		//line_nacrtaj(xs, ys, xe, ye);
		a = 2 * (ye - ys);

		yc = ys;
		yf = -(xe - xs);
		korekcija = -2 * (xe - xs);

		glBegin(GL_POINTS);
		for (x = xs; x <= xe; x++) {
			glVertex2i(x, yc);
			yf = yf + a;
			if (yf >= 0) {
				yf = yf + korekcija;
				yc = yc + 1;
			}
		}
		glEnd();
	}
	else {
		
		//line_nacrtaj(xs, ys, xe, ye);
		x = xe; xe = ye; ye = x;
		x = xs; xs = ys; ys = x;
		
		a = 2 * (ye - ys);

		yc = ys;
		yf = -(xe - xs);
		korekcija = -2 * (xe - xs);

		glBegin(GL_POINTS);
		for (x = xs; x <= xe; x++) {
			glVertex2i(yc, x);
			yf = yf + a;
			if (yf >= 0) {
				yf = yf + korekcija;
				yc = yc + 1;
			}
		}
		glEnd();
	}
}

void bresenham_nacrtaj_cjelobrojni3(int xs, int ys, int xe, int ye) {
	int x, yc, korekcija;
	int a, yf;

	if (-(ye - ys) <= xe - xs) {
		//line_nacrtaj(xs, ys, xe, ye);
		a = 2 * (ye - ys);
		yc = ys;
		yf = xe - xs;
		korekcija = 2 * (xe - xs);

		glBegin(GL_POINTS);
		for (x = xs; x <= xe; x++) {
			glVertex2i(x, yc);
			yf = yf + a;
			if (yf <= 0) {
				yf = yf + korekcija;
				yc = yc - 1;
			}
		}
		glEnd();
	}
	else {
		//line_nacrtaj(xs, ys, xe, ye);
		x = xe; xe = ys; ys = x;
		x = xs; xs = ye; ye = x;

		a = 2 * (ye - ys);
		yc = ys;
		yf = xe - xs;
		korekcija = 2 * (xe - xs);

		glBegin(GL_POINTS);
		for (x = xs; x <= xe; x++) {
			glVertex2i(yc, x);
			yf = yf + a;
			if (yf <= 0) {
				yf = yf + korekcija;
				yc = yc - 1;
			}
		}
		glEnd();
	}
}

void bresenham_nacrtaj_cjelobrojni(int xs, int ys, int xe, int ye) {
	if (xs <= xe) {
		if (ys <= ye) {
			bresenham_nacrtaj_cjelobrojni2(xs, ys, xe, ye);
		}
		else {
			bresenham_nacrtaj_cjelobrojni3(xs, ys, xe, ye);
		}
	}
	else {
		if (ys >= ye) {
			bresenham_nacrtaj_cjelobrojni2(xe, ye, xs, ys);
		}
		else {
			bresenham_nacrtaj_cjelobrojni3(xe, ye, xs, ys);
		}
	}
}