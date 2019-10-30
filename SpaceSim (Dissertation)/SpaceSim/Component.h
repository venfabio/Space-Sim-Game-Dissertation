#pragma once
#include <string>

class GameObject;
class Message;

class Component
{
public:
	Component(std::string type, GameObject* parent);
	virtual ~Component();

protected:
	GameObject* _parent;
	std::string _componentType;

private:
	Component(const Component&);
	Component& operator=(const Component&);

public:
	GameObject* GetGameObject()			const	{ return _parent; }
	std::string GetComponentType()		const	{ return _componentType; }

	// Setup function -- called when parent object is initialised (using its own Start method)
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void OnMessage(Message* m) = 0;
	virtual void End() = 0;
	void Broadcast(Message* m);
};
