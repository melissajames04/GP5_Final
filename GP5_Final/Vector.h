#pragma once

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

struct Vec4 : public Vec3{
	float w;

	inline Vec4(float s = float(0.0)) {
		x = s; 
		y = s;
		z = s;
		w = s;
	}
	inline Vec4(float _x, float _y, float _z,  float _w){
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	inline Vec4(const Vec4& v){
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}
	inline Vec4(const Vec3& v){
		x = v.x;
		y = v.y;
		z = v.z;
		w = 1.0f;
	}
	inline Vec4& operator = (const Vec4& v){
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}
	inline float& operator [] (int index){
		return *(&x + index);
	}
	inline const float operator [] (int i) const{
		return *(&x + i);
	}
	inline Vec4 operator + (const Vec4& v) const{
		return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	inline Vec4& operator += (const Vec4& v){
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	inline Vec4 operator - () const{
		return Vec4(-x, -y, -z, -w);
	}
	inline Vec4 operator - (const Vec4& v) const{
		return Vec4(x - v.x, y - v.y, z - v.z, v.w - w);
	}
	inline Vec4& operator -= (const Vec4& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	inline Vec4& operator *= (const float s){
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}
	friend Vec4 operator * (const float s, const Vec4& v){
		return v * s;
	}
	inline Vec4 operator / (const float s) const {
		float r = 1.0f / s;
		return *this * r;
	}
	inline Vec4& operator /= (const float s){
		float r = 1.0f / s;
		*this *= r;
		return *this;
	}
	inline void print(){
		printf("%f %f %f %f\n", x, y, z, w);
	}
	inline operator const float* () const{
		return static_cast<const float*> (&x);
	}
	inline operator float* () {
		return static_cast<float*>(&x);
	}
};