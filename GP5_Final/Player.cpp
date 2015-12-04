#include "Player.h"

Player::Player() : GameObject() {
	position.Load(0.0f, 1.5f, 0.0f);
	mass = 1.0f;
	jumpVel = 2.0f;
}

Player::~Player(){

}