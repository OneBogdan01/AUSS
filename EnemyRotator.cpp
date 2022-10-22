#include "EnemyRotator.h"

EnemyRotator::EnemyRotator(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar rVar, int* frame, MoveToADirection* mover, EnemySpawner* spawner)
	: Rotator(pos, dir, rVar, frame, mover),
	spawner(spawner)
{

}
void EnemyRotator::Call() {
	RotateToPlayer();
}
void EnemyRotator::RotateToPlayer()
{
	RotateToDirection(spawner->GetPlayerPos());
}
EnemyRotator::~EnemyRotator()
{
}
