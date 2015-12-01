#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector.h"

class Physics
{
public:

	inline static float LinearAcceleration(const float& F, const float& m){
		return (F / m); //returning a
	}
	inline static float LinearVelocity(const float& vi, const float& a, const float& t){
		return (vi + (a * t)); //returning vf
	}
	inline static float LinearPosition(const float& yi, const float& vi, const float& deltaT, const float& a){
		return (yi + (vi * deltaT) + ((a / 2) * (deltaT * deltaT)));  //returning yf
	}
	inline static float Inertia(const float& m, const float& l){
		return ((m * (l * l)) / 12);
	}
	inline static float AngularAcceleration(const float& m, const float& l, const float& T){
		return (T / Inertia(m, l));
	}
	inline static float AngularVelocity(const float& wi, const float& a, const float& t){
		return (wi + (a*t));
	}
	inline static float RotationalAngle(const float& angle_init, const float& wi, const float& t, const float& a){
		return (angle_init + (wi * t) + ((a / 2) * (t * t)));
	}
	inline static float Revolutions(const float& a){
		return (a / (2 * M_PI));
	}
	inline static float Force(const float& T, const float& r){
		return(T / r);
	}
	inline static const Vec3 WorldSpace(const float& angle, const Vec3& F){
		return Vec3((F.x * (cos(angle))) + (F.y * (-1 * (sin(angle)))),
			(F.x * (sin(angle))) + (F.y * (cos(angle))),
			0.0f);
	}
};

