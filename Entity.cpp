#include "Entity.h"

Entity::Entity(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos) :
	sprite(sprite),
	pos(pos)
{}

Entity::~Entity()
{
	delete sprite;
	delete pos;
}




