#include "Vec3.h"
#include <math.h>


//A simple file that lets us do vector math with the vectors we created with our vec3


class VMath{
	public:
		inline static float mag(const Vec3& v){
			return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		}

		inline static float dot(const Vec3& v1, const Vec3& v2){
			return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
		}

		inline static const Vec3 cross(const Vec3 &v1, const Vec3 &v2){
			return Vec3(v1.y * v2.z - v1.z * v2.y,
				v1.z * v2.x - v1.x * v2.z,
				v1.x * v2.y - v1.y * v2.x);
		}

		inline static Vec3 normalize(const Vec3& v){
			float m = VMath::mag(v);
			return (Vec3(v.x / m, v.y / m, v.z / m));
		}
};