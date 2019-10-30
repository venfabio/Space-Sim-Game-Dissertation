#pragma once

#include "GameObject.h"
#include "Mesh.h"
#include "Texture.h"
#include "GLM\glm.hpp"

class Skybox :
	public GameObject
{
private:

	GameObject*		_focus; // What to "follow"

public:
	Skybox();
	~Skybox();

	void SetFocus(GameObject* x);	// Should be overloaded to set the focus on something else other than GO, like camera.
	void Update();
};

