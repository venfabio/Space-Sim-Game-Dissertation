#pragma once

#include <d3d11.h>
#include <map>

#include "Mesh.h"
#include "Texture.h"
#include <GLM\glm.hpp>
#include <GLM\gtc\quaternion.hpp>


class Component;
class Message;

typedef std::map<std::string, Component*> ComponentMap;
typedef std::map<std::string, Component*>::iterator ComponentMapIterator;
typedef std::map<std::string, std::vector<Component*> > ListenerMap;	// msg
typedef std::map<std::string, std::vector<Component*> >::iterator ListenerMapIterator;
typedef std::vector<Component*>::iterator ComponentListIterator;

class GameObject
{
public:
	GameObject();
	~GameObject();

protected:

	Mesh*			_mesh;		// Vertex info

	Texture*		_tex;		// Texture info

	float			_scale;		// 1 = normal

	int				_id;		// useful for handling collisions

	bool			_isTransparent;	// Transparency (not really in use in this game)
	bool			_alive;			// If it's alive, draw it and perform checks

	glm::vec3		_position;
	glm::vec3		_angle;

	glm::quat		_quaternion;

	ComponentMap	_components;
	ListenerMap		_listeners;

public:

	glm::quat GetQuaternion();

	// Component related functions
	bool AddComponent(Component *c);
	bool RemoveComponent(Component *c);
	bool RemoveComponent(std::string componentType);
	Component* GetComponent(std::string type);
	void RegisterListener(std::string m, Component* c);
	void UnregisterListener(std::string m, Component* c);

	virtual void Update(float deltaTime);
	virtual void OnMessage(Message* m);
	virtual void End();

	Mesh* GetMesh()			const	{ return _mesh; }
	void SetMesh(Mesh* m)			{ _mesh = m; }

	float GetScale()		const	{ return _scale; }
	void SetScale(float v)			{ _scale = v; }

	Texture* GetTexture()		const	{ return _tex; }
	void SetTexture(Texture* t)			{ _tex = t; }

	bool GetTransparency()		const	{ return _isTransparent; }
	void SetTransparency(bool t)			{ _isTransparent = t; }

	glm::vec3 GetAngle()	const	{ return _angle; }

	float GetAngleX()		const	{ return _angle.x; }
	void SetAngleX(float x)			{ _angle.x =  x; }
	float GetAngleY()		const	{ return _angle.y; }
	void SetAngleY(float y)			{ _angle.y = y; }
	float GetAngleZ()		const	{ return _angle.z; }
	void SetAngleZ(float z)			{ _angle.z = z; }

	glm::vec3 GetPos()		const	{ return _position; }
	void SetPos(float a, float b, float c)
	{
		_position.x = a;
		_position.y = b;
		_position.z = c;
	}
	void SetPos(glm::vec3 pos)			{ _position = pos; }
	void SetAngle(glm::vec3 angle)		{ _angle = angle; }

	float GetPosX()		    const	{ return _position.x; }
	void SetPosX(float x)				{ _position.x = x; }
	float GetPosY()			const	{ return _position.y; }
	void SetPosY(float y)				{ _position.y = y; }
	float GetPosZ()			const	{ return _position.z; }
	void SetPosZ(float z)				{ _position.z = z; }

	int GetId()							const	{ return _id; }

	bool IsAlive()						const	{ return _alive; }

	void SetAlive(bool v)						{ _alive = v; }
};

