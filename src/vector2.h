#pragma once

class vector2 
{
	private:
		float magnitud = 0;
	public:
		float x;
		float y;

		vector2(vector2* vec) {}
		vector2(float xx, float yy) : x(xx), y(yy) {
			generarMagnitud();
		}

		float getMagnitud();
		void generarMagnitud();
		void normalizar();
		void multiEscalar(float esc);
		void dividirEscalar(float esc);

		void operator =(vector2 v2) {
			x = v2.x;
			y = v2.y;
			generarMagnitud();
		}
		vector2 operator+(vector2 const &v1);
		vector2& operator+=(vector2 const& v1);
		vector2 operator-(vector2 const& v1);

		static vector2 truncar(vector2, float);
		static vector2 resta(vector2 v1, vector2 v2);
};