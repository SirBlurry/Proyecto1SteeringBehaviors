#include "vector2.h"
#include "math.h"

/*
Regresa la magnitud del vector
*/
float vector2::getMagnitud() {
	return magnitud;
}

/*
Actualiza la magnitud del vector
*/
void vector2::generarMagnitud() {
	magnitud = sqrt((x*x)+(y*y));
}

/*
Normaliza el vector
*/
void vector2::normalizar() {
	x = x / magnitud;
	y = y / magnitud;
	generarMagnitud();
}

/**
 * Multiplicación por un escalar
 * @param esc es el escalar para la multiplicación
*/
void vector2::multiEscalar(float esc) {
	x *= esc;
	y *= esc;
	generarMagnitud();
}

/**
 * División por un escalar
 * @param esc es el escalar para la división
*/
void vector2::dividirEscalar(float esc) {
	x /= esc;
	y /= esc;
	generarMagnitud();
}

/**
 * Trunca el primer vector por la magnitud del segundo
*/
vector2 vector2::truncar(vector2 original, float referencia) {
	if (original.magnitud > referencia) {
		original.normalizar();
		original.multiEscalar(referencia);
	}
	return original;
}

/*
Sobrecarga del operador + suma de dos vectores
*/
vector2 vector2::operator+(vector2 const &v1) {
	return vector2(x + v1.x, y + v1.y);
}

/*
Sobrecarga del operador += suma de dos vectores
*/
vector2& vector2::operator+=(vector2 const& v1) {
	this->x += v1.x;
	this->y += v1.y;
	return *this;
}

/*
Resta de dos vectores
*/
vector2 vector2::resta(vector2 v1, vector2 v2) {
	return vector2(v1.x - v2.x, v1.y - v2.y);
}

/*
Sobrecarga del operador - resta de dos vectores
*/
vector2 vector2::operator-(vector2 const& v1) {
	return vector2(x - v1.x, y - v1.y);
}