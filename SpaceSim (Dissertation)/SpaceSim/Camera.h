#pragma once

#include <time.h>
#include <math.h>

#include <GLM\glm.hpp>

#include "GameObject.h"
#include <d3dx10.h>	// For D3DMATRIX -.-

class Camera :
	public GameObject
{
private:

	bool _isManual;

	GameObject* _target;

	D3DXMATRIX _projectionMatrix;
	D3DXMATRIX _viewMatrix;
	D3DXMATRIX _rotationMatrix;

	glm::quat _orientation;
	glm::mat4 _VM;


	//Debug
	D3DXMATRIX matRotateX, matRotateY, matRotateZ;

	double							_currentTime;		// Current time for delta time purposes
	double							_deltaTime;

public:
	Camera();
	~Camera();

	D3DXMATRIX SetProjectionMatrix(float width, float height);
	D3DXMATRIX SetViewMatrix();

	void SetCameraPosition(glm::vec3 pos);
	void SetCameraTarget(glm::vec3 target);
	void SetCameraTarget(GameObject* g);
	void SetCameraRotation(glm::quat q)							{ _orientation = _orientation * q; }
	void Reset();

	glm::quat GetOrientation()									{ return _orientation; }
	GameObject* GetCameraTarget()								{ return _target; }

	virtual void Update(float dt);

	void SwitchType(bool b);
};

