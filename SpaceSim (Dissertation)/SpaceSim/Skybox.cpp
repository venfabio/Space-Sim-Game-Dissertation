#include "Skybox.h"
#include "GameObject.h"

Skybox::Skybox()
{
}


Skybox::~Skybox()
{
}

void Skybox::SetFocus(GameObject* x)
{
	_focus = x;
}

void Skybox::Update()
{
	_position = _focus->GetPos() + glm::vec3(0, 0, 0);
}