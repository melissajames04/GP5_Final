#pragma once


//A vector class to create vector(math) objects rather than C++'s version of a vector(arraylist)
//
//Everything inside is inlined and overloaded so it can be treated like a base variable, such as int or float, and allows us to not need 
//a main vector file


struct Vec3{
	float x, y, z;


	inline void init(float _x, float _y, float _z){
		x = _x; y = _y; z = _z;
	}

	inline Vec3(float _x, float _y, float _z){
		init(_x, _y, _z);
	}

	inline Vec3(float _s = float(0.0)){
		init(_s, _s, _s);
	}

	inline const Vec3 operator + (const Vec3& v) const{
		return Vec3(x + v.x, y + v.y, z + v.z);
	}

	inline Vec3& operator += (const Vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	inline const Vec3 operator * (const float s) const{
		return Vec3(s*x, s*y, s*z);
	}

	inline const Vec3 operator / (const float s) const{
		return Vec3(x / s, y / s, z / s);
	}

	inline Vec3& operator *= (const float s){
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	inline const Vec3 operator - () const{
		return Vec3(-x, -y, -z);
	}

	inline const Vec3 operator - (const Vec3& v) const{
		return Vec3(x - v.x, y - v.y, z - v.z);
	}

	inline const Vec3 operator -= (const Vec3& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
};