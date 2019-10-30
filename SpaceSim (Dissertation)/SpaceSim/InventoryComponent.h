#pragma once
#include <vector>
#include "Component.h"
#include "Bag.h"

class InventoryComponent :
	public Component
{
private:

	std::vector<Bag> bag;	
	Bag b;

	int _money;

	void EmptyInventory();
	void TypeOneInventory();
	void TypeTwoInventory();
	void TypeThreeInventory();
	void TypeFourInventory();
	void TypeFiveInventory();
	void TypeSixInventory();

public:
	InventoryComponent(GameObject* x, int param);
	~InventoryComponent();

	virtual void Start();

	virtual void Update(float deltaTime);

	virtual void OnMessage(Message* m);

	virtual void End();

	int GetMoney()		const	{ return _money; }		// money not found. :(
	void SetMoney(int x)		{ _money = x; }			// wish I could use it. :(

	std::vector<Bag> GetBag()				{ return bag; }
	void SetBag(std::vector<Bag> bg)			{ bag = bg; }
};

