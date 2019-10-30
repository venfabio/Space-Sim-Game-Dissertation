#include "Camera.h"
#include "CameraController.h"

#include <GLM\gtc\matrix_transform.hpp>

Camera::Camera()
{
	_position.x = 0.0f;
	_position.y = 2.0f;
	_position.z = -2.5f;

	// In this scope, angle doesn't really matters
	_angle.x = -0.5f;
	_angle.y = 0.0f;
	_angle.z = 0.0f;

	_orientation = glm::quat(_angle);
}


Camera::~Camera()
{
}

D3DXMATRIX Camera::SetProjectionMatrix(float width, float height)
{
	// create a projection matrix
	D3DXMatrixPerspectiveFovLH(&_projectionMatrix,
		(FLOAT)D3DXToRadian(45),						// field of view
		width / height,									// aspect ratio
		0.01f,											// near view-plane
		200.0f);										// far view-plane

	return _projectionMatrix;
}

D3DXMATRIX Camera::SetViewMatrix()
{
	// https://www.reddit.com/r/opengl/comments/2k8tj6/my_quaternionbased_camera_is_moving_relative_to/
	_VM = glm::mat4_cast(_orientation);
	_VM = glm::translate(_VM, -_position);

	_viewMatrix._11 = _VM[0][0];
	_viewMatrix._12 = _VM[0][1];
	_viewMatrix._13 = _VM[0][2];
	_viewMatrix._14 = _VM[0][3];

	_viewMatrix._21 = _VM[1][0];
	_viewMatrix._22 = _VM[1][1];
	_viewMatrix._23 = _VM[1][2];
	_viewMatrix._24 = _VM[1][3];

	_viewMatrix._31 = _VM[2][0];
	_viewMatrix._32 = _VM[2][1];
	_viewMatrix._33 = _VM[2][2];
	_viewMatrix._34 = _VM[2][3];

	_viewMatrix._41 = _VM[3][0];
	_viewMatrix._42 = _VM[3][1];
	_viewMatrix._43 = _VM[3][2];
	_viewMatrix._44 = _VM[3][3];

	return _viewMatrix;
}

void Camera::SetCameraPosition(glm::vec3 pos)
{
	// Not in use
	_position.x = pos.x;
	_position.y = (pos.y - 5) * -1;
	_position.z = pos.z - 5;
}

void Camera::SetCameraTarget(glm::vec3 target)
{
	_orientation = glm::quat(target);
}

void Camera::SetCameraTarget(GameObject* g)
{
	_target = g;
	_position = _target->GetPos();
	//_position.x = _position.x;
	_position.y = _position.y + 2;
	_position.z = _position.z - 2.5f;

	_angle = g->GetAngle();
	_angle.x = _angle.x - 0.5f;

	_orientation = glm::quat(_angle);
}

void Camera::Update(float dt)
{
	GameObject::Update(dt);

	if (_target != NULL && _isManual == false)
	{
		_position = _target->GetPos();

		_position.y = _position.y + 2;
		_position.z = _position.z - 2.5f;

		_angle = _target->GetAngle();
		_angle.x = _angle.x - 0.5f;
		_angle.y = _angle.y * -1;
		_angle.z = _angle.z * -1;

		_orientation = glm::quat(_angle);
	}
}

void Camera::SwitchType(bool b)
{
	if (b)
	{
		_isManual = true;
		new CameraController(this);
	}
	else
	{
		_isManual = false;
	}
}

void Camera::Reset()
{
	_position.x = 0.0f;
	_position.y = 0.0f;
	_position.z = 0.0f;

	// In this scope, angle doesn't really matters
	_angle.x = 0.0f;
	_angle.y = 0.0f;
	_angle.z = 0.0f;

	_orientation = glm::quat(_angle);
}