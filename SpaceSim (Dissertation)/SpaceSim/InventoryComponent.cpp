#include "InventoryComponent.h"
#include "GameObject.h"
#include "Message.h"
#include "TransactionMessage.h"

InventoryComponent::InventoryComponent(GameObject* x, int param)
	: Component("inventory", x)
{
	_money = 0; // :(

	switch (param)
	{
	case 1: TypeOneInventory();
		break;
	case 2: TypeTwoInventory();
		break;
	case 3: TypeThreeInventory();
		break;
	case 4: TypeFourInventory();
		break;
	case 5: TypeFiveInventory();
		break;
	case 6: TypeSixInventory();
		break;
	default: EmptyInventory();
	}
}


InventoryComponent::~InventoryComponent()
{
}

void InventoryComponent::Start()
{
	_parent->RegisterListener("transaction", this);
}

void InventoryComponent::Update(float deltaTime)
{
	// No need to update
}

void InventoryComponent::OnMessage(Message* m)
{
	// Transaction Message
	if (m->GetMessageType() == "transaction")
	{
		TransactionMessage* tm = static_cast<TransactionMessage*>(m);
		int k = tm->GetItemID();
		for (int i = 0; i < 10; i++)
		{
			if (bag[i].id == k)
			{
				// Apply the transaction
				if (tm->GetAction() == true)
				{
					GameObject* temp = tm->GetOther();
					InventoryComponent* ic = static_cast<InventoryComponent*>(temp->GetComponent("inventory"));
					std::vector<Bag> tempbag = ic->GetBag();
					if (_money > bag[i].price && tempbag[i].amount >= 0) // Hardfix the solves the problem "partially"
					{
						bag[i].amount++;
						_money = _money - bag[i].price;
					}
				}
				else
				{
					//GameObject* temp = tm->GetOther();
					//InventoryComponent* ic = static_cast<InventoryComponent*>(temp->GetComponent("inventory"));
					//std::vector<Bag> tempbag = ic->GetBag();
					if (bag[i].amount > 0)
					{
						bag[i].amount--;
						_money = _money + bag[i].price;		// TODO: non-sense.
					}
				}
			}
		}
	}
}

void InventoryComponent::End()
{
	_parent->UnregisterListener("transactionv", this);
}

void InventoryComponent::EmptyInventory()
{
	_money = 100;

	b.id = 0;
	b.name = "Bananas \n";
	b.price = 5;	// Cheap!
	b.amount = 0;
	bag.push_back(b);
	b.id = 1;
	b.name = "Wood \n";
	b.price = 12;
	b.amount = 0;
	bag.push_back(b);
	b.id = 2;
	b.name = "Asteroid Shard \n";
	b.price = 25;
	b.amount = 0;
	bag.push_back(b);
	b.id = 3;
	b.name = "Watermelon \n";
	b.price = 18;
	b.amount = 0;
	bag.push_back(b);
	b.id = 4;
	b.name = "Nitrogen Crystal \n";
	b.price = 22;
	b.amount = 0;
	bag.push_back(b);
	b.id = 5;
	b.name = "Space Iron Bar \n";
	b.price = 20;
	b.amount = 0;
	bag.push_back(b);
	b.id = 6;
	b.name = "Adamantite Bar \n";
	b.price = 34;
	b.amount = 0;
	bag.push_back(b);
	b.id = 7;
	b.name = "Elementium Bar \n";
	b.price = 45;
	b.amount = 0;
	bag.push_back(b);
	b.id = 8;
	b.name = "Shard of Azzinoth \n";	// You are not prepared.
	b.price = 60;
	b.amount = 0;
	bag.push_back(b);
	b.id = 9;
	b.name = "Light Essence \n";
	b.price = 85;
	b.amount = 0;
	bag.push_back(b);
}

void InventoryComponent::TypeOneInventory()
{
	_money = 10000;

	b.id = 0;
	b.name = "Bananas \n";
	b.price = 5;	// Cheap!
	b.amount = 20;
	bag.push_back(b);
	b.id = 1;
	b.name = "Wood \n";
	b.price = 12;
	b.amount = 16;
	bag.push_back(b);
	b.id = 2;
	b.name = "Asteroid Shard \n";
	b.price = 25;
	b.amount = 6;
	bag.push_back(b);
	b.id = 3;
	b.name = "Watermelon \n";
	b.price = 18;
	b.amount = 30;
	bag.push_back(b);
	b.id = 4;
	b.name = "Nitrogen Crystal \n";
	b.price = 22;
	b.amount = 0;
	bag.push_back(b);
	b.id = 5;
	b.name = "Space Iron Bar \n";
	b.price = 20;
	b.amount = 0;
	bag.push_back(b);
	b.id = 6;
	b.name = "Adamantite Bar \n";
	b.price = 34;
	b.amount = 0;
	bag.push_back(b);
	b.id = 7;
	b.name = "Elementium Bar \n";
	b.price = 45;
	b.amount = 0;
	bag.push_back(b);
	b.id = 8;
	b.name = "Shard of Azzinoth \n";	// You are not prepared.
	b.price = 60;
	b.amount = 0;
	bag.push_back(b);
	b.id = 9;
	b.name = "Light Essence \n";
	b.price = 85;
	b.amount = 0;
	bag.push_back(b);
}

void InventoryComponent::TypeTwoInventory()
{
	_money = 100000;

	b.id = 0;
	b.name = "Bananas \n";
	b.price = 5;	// Cheap!
	b.amount = 0;
	bag.push_back(b);
	b.id = 1;
	b.name = "Wood \n";
	b.price = 12;
	b.amount = 0;
	bag.push_back(b);
	b.id = 2;
	b.name = "Asteroid Shard \n";
	b.price = 25;
	b.amount = 10;
	bag.push_back(b);
	b.id = 3;
	b.name = "Watermelon \n";
	b.price = 18;
	b.amount = 0;
	bag.push_back(b);
	b.id = 4;
	b.name = "Nitrogen Crystal \n";
	b.price = 22;
	b.amount = 6;
	bag.push_back(b);
	b.id = 5;
	b.name = "Space Iron Bar \n";
	b.price = 20;
	b.amount = 10;
	bag.push_back(b);
	b.id = 6;
	b.name = "Adamantite Bar \n";
	b.price = 34;
	b.amount = 1;
	bag.push_back(b);
	b.id = 7;
	b.name = "Elementium Bar \n";
	b.price = 45;
	b.amount = 0;
	bag.push_back(b);
	b.id = 8;
	b.name = "Shard of Azzinoth \n";	// You are not prepared.
	b.price = 60;
	b.amount = 0;
	bag.push_back(b);
	b.id = 9;
	b.name = "Light Essence \n";
	b.price = 85;
	b.amount = 0;
	bag.push_back(b);
}

void InventoryComponent::TypeThreeInventory()
{
	_money = 100000;

	b.id = 0;
	b.name = "Bananas \n";
	b.price = 5;	// Cheap!
	b.amount = 0;
	bag.push_back(b);
	b.id = 1;
	b.name = "Wood \n";
	b.price = 12;
	b.amount = 0;
	bag.push_back(b);
	b.id = 2;
	b.name = "Asteroid Shard \n";
	b.price = 25;
	b.amount = 30;
	bag.push_back(b);
	b.id = 3;
	b.name = "Watermelon \n";
	b.price = 18;
	b.amount = 0;
	bag.push_back(b);
	b.id = 4;
	b.name = "Nitrogen Crystal \n";
	b.price = 22;
	b.amount = 0;
	bag.push_back(b);
	b.id = 5;
	b.name = "Space Iron Bar \n";
	b.price = 20;
	b.amount = 0;
	bag.push_back(b);
	b.id = 6;
	b.name = "Adamantite Bar \n";
	b.price = 34;
	b.amount = 10;
	bag.push_back(b);
	b.id = 7;
	b.name = "Elementium Bar \n";
	b.price = 45;
	b.amount = 8;
	bag.push_back(b);
	b.id = 8;
	b.name = "Shard of Azzinoth \n";	// You are not prepared.
	b.price = 60;
	b.amount = 5;
	bag.push_back(b);
	b.id = 9;
	b.name = "Light Essence \n";
	b.price = 85;
	b.amount = 3;
	bag.push_back(b);
}

void InventoryComponent::TypeFourInventory()
{
	_money = 10000;

	b.id = 0;
	b.name = "Bananas \n";
	b.price = 5;	// Cheap!
	b.amount = 20;
	bag.push_back(b);
	b.id = 1;
	b.name = "Wood \n";
	b.price = 12;
	b.amount = 5;
	bag.push_back(b);
	b.id = 2;
	b.name = "Asteroid Shard \n";
	b.price = 25;
	b.amount = 6;
	bag.push_back(b);
	b.id = 3;
	b.name = "Watermelon \n";
	b.price = 18;
	b.amount = 0;
	bag.push_back(b);
	b.id = 4;
	b.name = "Nitrogen Crystal \n";
	b.price = 22;
	b.amount = 4;
	bag.push_back(b);
	b.id = 5;
	b.name = "Space Iron Bar \n";
	b.price = 20;
	b.amount = 0;
	bag.push_back(b);
	b.id = 6;
	b.name = "Adamantite Bar \n";
	b.price = 34;
	b.amount = 1;
	bag.push_back(b);
	b.id = 7;
	b.name = "Elementium Bar \n";
	b.price = 45;
	b.amount = 0;
	bag.push_back(b);
	b.id = 8;
	b.name = "Shard of Azzinoth \n";	// You are not prepared.
	b.price = 60;
	b.amount = 0;
	bag.push_back(b);
	b.id = 9;
	b.name = "Light Essence \n";
	b.price = 85;
	b.amount = 0;
	bag.push_back(b);
}

void InventoryComponent::TypeFiveInventory()
{
	_money = 10000;

	b.id = 0;
	b.name = "Bananas \n";
	b.price = 5;	// Cheap!
	b.amount = 0;
	bag.push_back(b);
	b.id = 1;
	b.name = "Wood \n";
	b.price = 12;
	b.amount = 0;
	bag.push_back(b);
	b.id = 2;
	b.name = "Asteroid Shard \n";
	b.price = 25;
	b.amount = 6;
	bag.push_back(b);
	b.id = 3;
	b.name = "Watermelon \n";
	b.price = 18;
	b.amount = 5;
	bag.push_back(b);
	b.id = 4;
	b.name = "Nitrogen Crystal \n";
	b.price = 22;
	b.amount = 0;
	bag.push_back(b);
	b.id = 5;
	b.name = "Space Iron Bar \n";
	b.price = 20;
	b.amount = 0;
	bag.push_back(b);
	b.id = 6;
	b.name = "Adamantite Bar \n";
	b.price = 34;
	b.amount = 0;
	bag.push_back(b);
	b.id = 7;
	b.name = "Elementium Bar \n";
	b.price = 45;
	b.amount = 0;
	bag.push_back(b);
	b.id = 8;
	b.name = "Shard of Azzinoth \n";	// You are not prepared.
	b.price = 60;
	b.amount = 4;
	bag.push_back(b);
	b.id = 9;
	b.name = "Light Essence \n";
	b.price = 85;
	b.amount = 3;
	bag.push_back(b);
}

void InventoryComponent::TypeSixInventory()
{
	_money = 10000;

	b.id = 0;
	b.name = "Bananas \n";
	b.price = 5;	// Cheap!
	b.amount = 0;
	bag.push_back(b);
	b.id = 1;
	b.name = "Wood \n";
	b.price = 12;
	b.amount = 30;
	bag.push_back(b);
	b.id = 2;
	b.name = "Asteroid Shard \n";
	b.price = 25;
	b.amount = 4;
	bag.push_back(b);
	b.id = 3;
	b.name = "Watermelon \n";
	b.price = 18;
	b.amount = 0;
	bag.push_back(b);
	b.id = 4;
	b.name = "Nitrogen Crystal \n";
	b.price = 22;
	b.amount = 10;
	bag.push_back(b);
	b.id = 5;
	b.name = "Space Iron Bar \n";
	b.price = 20;
	b.amount = 6;
	bag.push_back(b);
	b.id = 6;
	b.name = "Adamantite Bar \n";
	b.price = 34;
	b.amount = 0;
	bag.push_back(b);
	b.id = 7;
	b.name = "Elementium Bar \n";
	b.price = 45;
	b.amount = 10;
	bag.push_back(b);
	b.id = 8;
	b.name = "Shard of Azzinoth \n";	// You are not prepared.
	b.price = 60;
	b.amount = 2;
	bag.push_back(b);
	b.id = 9;
	b.name = "Light Essence \n";
	b.price = 85;
	b.amount = 0;
	bag.push_back(b);
}
