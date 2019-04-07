//#include <glm/vec3.hpp>
//#include <glm/glm.hpp>
//#include <glm/geometric.hpp> 
//#include <stdio.h>
//#include <stdlib.h>
//#include <iostream>
//#define GLM_ENABLE_EXPERIMENTAL
//#include "glm/ext.hpp"
//#include <string>
//#include <glm/gtc/matrix_access.hpp>
//
//// funkcija za ispis matrice 3x3
//void matrix_print(glm::mat3x3 matrix) {
//	
//	printf("\n");
//	printf(" _                                 _\n");
//	printf("| %10f %10f %10f  |\n", matrix[0][0], matrix[0][1], matrix[0][2]);
//	printf("| %10f %10f %10f  |\n", matrix[1][0], matrix[1][1], matrix[1][2]);
//	printf("|_%10f %10f %10f _|\n", matrix[2][0], matrix[2][1], matrix[2][2]);
//	printf("\n");
//	printf("\n");
//	std::cout<<glm::to_string(matrix);
//	printf("\n");
//}
//
//
//int main() {
//
//	// zbroj vektora (2i + 3j -4k) i (-i + 4j -k)
//	glm::vec3 const v1 = glm::vec3(2, 3, -4) + glm::vec3(-1, 4, -1);
//	// skalarni umnožak v1 i (-i, 4j, -k)
//	int s = glm::dot(v1, glm::vec3(-1, 4, -1));
//	// vektorski umnožak v1 i (2i, 2j, 4k)
//	glm::vec3 const v2 = glm::cross(v1, glm::vec3(2, 2, 4));
//	// normirani vektor v2
//	glm::vec3 const v3 = glm::normalize(v2);
//	// vektor suprotnog smjera
//	glm::vec3 const v4 = -v2;
//
//	// ispis 
//	std::cout << "v1 = " + glm::to_string(v1) << std::endl;
//	std::cout << "s = " << s << std::endl;
//	std::cout << "v2 = " << glm::to_string(v2) << std::endl;
//	std::cout << "v3 = " << glm::to_string(v3) << std::endl;
//	std::cout << "v4 = " << glm::to_string(v4) << std::endl;
//
//	glm::mat3x3 m01 = glm::mat3x3(1.0, 2.0, 3.0,
//								  2.0, 1.0, 3.0,
//								  4.0, 5.0, 1.0);
//
//	glm::mat3x3 m02 = glm::mat3x3(-1.0, 2.0, -3.0,
//								   5.0, -2.0, 7.0,
//								  -4.0, -1.0, 3.0);
//
//	
//
//	// zbroj matrica m01 i m02
//	glm::mat3x3 m1 = m01 + m02;
//	// umnožak m01 i transponirane m02
//	glm::mat3x3 trans02 = glm::transpose(m02);
//	glm::mat3x3 m2 = glm::transpose(glm::transpose(m01) * m02);
//	// umnožak m01 i invertirane m02
//	glm::mat3x3 m3 = glm::transpose(glm::transpose(m01) * glm::transpose(glm::inverse(m02)));
//
//	// ispis
//	matrix_print(m1);
//	matrix_print(m2);
//	matrix_print(m3);
//
//	printf("Unesite koeficijnte 3 jednadzbe s 3 nepoznanice redom\n");
//	printf("x1 y1 z1 r1 x2 y2 z2 r2 x3 y3 z3 r3 i pritisnite tipku enter.\n");
//	printf("r1, r2, r3 predstavljaju rjesenja prve, druge i trece jednadzbe.");
//
//	float x1, y1, z1, r1,
//		x2, y2, z2, r2,
//		x3, y3, z3, r3;
//	// unos koeficijn
//	printf("\n");
//	std::cin >> x1 >> y1 >> z1 >> r1 >> x2 >> y2 >> z2 >> r2 >> x3 >> y3 >> z3 >> r3;
//	printf("\n");
//
//	glm::mat3x3 koeficijenti = glm::mat3x3(x1, y1, z1,
//		x2, y2, z2,
//		x3, y3, z3);
//
//	glm::vec3 rjesenja = glm::vec3(r1, r2, r3);
//	glm::vec3 xyz = rjesenja * glm::inverse(koeficijenti);
//	std::cout << "Rjesenja x: " << xyz[0] << ",y: " << xyz[1] << ",z: " << xyz[2] << std::endl;
//
//	float ax, ay, az,
//		bx, by, bz,
//		cx, cy, cz,
//		tx, ty, tz;
//
//	// unos koordinata tocaka
//	printf("Unesite koordinate točke A trokuta ABC u obliku x y z.\n");
//	std::cin >> ax >> ay >> az;
//	printf("\n");
//
//	printf("Unesite koordinate točke B trokuta ABC u obliku x y z.\n");
//	std::cin >> bx >> by >> bz;
//	printf("\n");
//
//	printf("Unesite koordinate točke A trokuta ABC u obliku x y z.\n");
//	std::cin >> cx >> cy >> cz;
//	printf("\n");
//
//	printf("Unesite koordinate točke T obzirom na koju zelite izracunati \n barocentricne koordinate u obliku x y z.\n");
//	std::cin >> tx >> ty >> tz;
//	printf("\n");
//
//	/*
//
//	ax * t1 + bx * t2 + cx * t3 = tx
//	ay * t1 + by * t2 + cy * t3 = ty
//	az * t1 + bz * t2 + cz * t3 = tz
//
//	t1 + t2 + t3 = 1
//	*/
//
//
//	// matrica komponenata tocka trokuta
//	glm::mat3x3 bar_mat = glm::mat3x3(ax, bx, cx,
//		ay, by, cy,
//		az, bz, cz);
//	// vektor tocke
//	glm::vec3 tocka = glm::vec3(tx, ty, tz);
//	// barocentricne koordinate
//	glm::vec3 bar_koord = glm::transpose(glm::inverse(bar_mat)) * tocka;
//	// ispis koordinata
//	std::cout << glm::to_string(bar_koord) << std::endl;
//	return 0;
//}
//	