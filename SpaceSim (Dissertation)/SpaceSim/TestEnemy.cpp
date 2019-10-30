#include "TestEnemy.h"
#include "SphereCollisionComponent.h"

#include "Message.h"
#include "DamageMessage.h"

TestEnemy::TestEnemy()
{
	_status = new StatusComponent(this, 50);
	new SphereCollisionComponent(this, 0.5f);	
}


TestEnemy::~TestEnemy()
{
}

void TestEnemy::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void TestEnemy::OnMessage(Message* m)
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
}