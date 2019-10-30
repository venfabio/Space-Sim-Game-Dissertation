#pragma once
#include "Message.h"

class GameObject;

class TransactionMessage :
	public Message
{
private:
	bool buy;		// If true, the listener is buying, otherwise is selling.
	int key;		// The primary key of the "Bag" struct in InventoryComponent.h
	int price;
	GameObject* other;

public:
	TransactionMessage(bool b, int id, int p, GameObject* go);
	virtual ~TransactionMessage();

	bool GetAction()			{ return buy; }
	int GetItemID()				{ return key; }
	int GetPrice()				{ return price; }
	GameObject* GetOther()		{ return other; }
};

