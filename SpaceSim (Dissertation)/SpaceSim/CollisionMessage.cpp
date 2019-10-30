#include "CollisionMessage.h"


CollisionMessage::CollisionMessage(GameObject* x, GameObject* y)
	: Message("collision"),
	_x(x),
	_y(y)
{
}


CollisionMessage::~CollisionMessage()
{
}
