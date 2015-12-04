#include <SDL/SDL.h>
#include <string>
#include "GameObject.h"
#include "Vector.h"

using namespace MATH;

class Player:public GameObject{
	

	public:
		Player();
		~Player();

		Player(const Player&) = delete;
		Player(Player&&) = delete;
		Player& operator = (const Player&) = delete;
		Player& operator = (Player&&) = delete;
		
		Vec3 position;
		Vec3 velocity;
		float mass;
		float jumpVel;


		bool isAlive;
};