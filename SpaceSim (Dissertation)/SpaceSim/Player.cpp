#include "Player.h"

#include "InputPlayer.h"
#include "InputPlayerGamepad.h"
#include "InventoryComponent.h"
#include "SphereCollisionComponent.h"

#include "Message.h"
#include "DamageMessage.h"

Player::Player()
{
	_id = 1;	// Player's ID

	new InputPlayer(this);
	new InputPlayerGamepad(this);
	_status = new StatusComponent(this, 50);
	new SphereCollisionComponent(this, 0.5f);	// 2.5 ???
	ic = new InventoryComponent(this, 0);
}


Player::~Player()
{

}

void Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void Player::OnMessage(Message* m)
{
	GameObject::OnMessage(m);

	// da togliere
	//if (m->GetMessageType() == "collision")
	//	_alive = false;

	if (m->GetMessageType() == "damage")
	{
		DamageMessage* dm = (DamageMessage*)m;
		int dmg = dm->GetDamage();

		_status->SetHp(_status->GetHp() - dmg);
		if (_status->GetHp() == 0)
		{
			_alive = false;
			// TODO: manda un messaggio di morte alla scena
		}
	}

	if (m->GetMessageType() == "transaction")
	{
		ic->OnMessage(m);
	}
}