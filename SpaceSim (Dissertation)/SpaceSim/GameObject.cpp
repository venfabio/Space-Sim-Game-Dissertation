#include "GameObject.h"
#include "Component.h"
#include "Message.h"

GameObject::GameObject()
{
	_position.x = 0;
	_position.y = 0;
	_position.z = 0;
	_angle.x = 0;
	_angle.y = 0;
	_angle.z = 0;
	_scale = 1;
	_isTransparent = false;
}

GameObject::~GameObject()
{
}

glm::quat GameObject::GetQuaternion()
{
	_quaternion = glm::quat(_angle);
	return _quaternion;
}

bool GameObject::AddComponent(Component *c)
{
	if(_components.find(c->GetComponentType()) != _components.end())
	{
		return false;
	}
	_components[c->GetComponentType()] = c;

	return true;
}

bool GameObject::RemoveComponent(Component* c)
{
	return RemoveComponent(c->GetComponentType());
}

bool GameObject::RemoveComponent(std::string type)
{
	ComponentMapIterator i = _components.find(type);
	if (i != _components.end())
	{
		_components.erase(i);
		i->second->End();
		delete i->second;

		return true;
	}

	return false;
}

Component* GameObject::GetComponent(std::string type)
{
	ComponentMapIterator i = _components.find(type);
	if (i != _components.end())
	{
		return i->second;
	}

	return NULL;
}

void GameObject::RegisterListener(std::string m, Component* c)
{
	// Da rivedere
	ListenerMapIterator i = _listeners.find(m);

	// Add it
	if (i == _listeners.end())
	{
		_listeners[m] = std::vector<Component*>();
		_listeners[m].push_back(c);
	}
	else
	{
		_listeners[m].push_back(c);
	}
}

void GameObject::UnregisterListener(std::string m, Component* c)
{
	ListenerMapIterator i = _listeners.find(m);

	// Go find it boy.
	if (i != _listeners.end())
	{
		std::vector<Component*>& list = i->second;

		for (ComponentListIterator j = list.begin();
			j != list.end();
			++j)
		{
			if (*j == c)
			{
				// Bye bye.
				list.erase(j);
				break;
			}
		}
	}
}

void GameObject::Update(float deltaTime)
{
	for (ComponentMapIterator i = _components.begin();
		i != _components.end();
		++i)
	{
		i->second->Update(deltaTime);
	}
}

void GameObject::OnMessage(Message* m)
{
	// Dispatch message to all registered listeners
	ListenerMapIterator i = _listeners.find(m->GetMessageType());

	// If we have registered listeners for this message
	if (i != _listeners.end())
	{
		std::vector<Component*>& list = i->second;

		for (ComponentListIterator j = list.begin();
			j != list.end();
			++j)
		{
			// Send listener the message
			(*j)->OnMessage(m);
		}
	}
}

void GameObject::End()
{
	// End all objects
	for (ComponentMapIterator i = _components.begin();
		i != _components.end();
		++i)
	{
		i->second->End();
		delete i->second;
	}

	// Clear list
	_components.clear();
}