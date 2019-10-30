#include "GameplayScene.h"
#include "Renderer.h"
#include "AudioPlayer.h"
#include "Player.h"
#include "Planet.h"
#include "Camera.h"
#include "Skybox.h"
#include "TextHandler.h"
#include "Message.h"
#include "InventoryComponent.h"
#include "LandedMessage.h"
#include "Cursor.h"
#include "TransactionMessage.h"
#include "LaserBeam.h"
#include "TestEnemy.h"

GameplayScene::GameplayScene(Renderer* renderer)
	: Scene(renderer)
{
}


GameplayScene::~GameplayScene()
{
}

void GameplayScene::Load()
{
	_cameraOne = _r->GetCamera();

	TextHandler* t = new TextHandler();
	_writer = t->GetWrapper(_r->GetDevice());

	// Player
	_meshPlayer.LoadFromFile("KizunaShip.txt");
	_meshPlayer.CreateVBO(_r);
	_texPlayer.Initialize(_r->GetDevice(), L"TextureC1.jpg");
	_player = new Player();
	_player->SetMesh(&_meshPlayer);
	_player->SetTexture(&_texPlayer);
	_player->SetAlive(true);

	_gameObjects.push_back(_player);

	// Planets
	_meshPlanet.LoadFromFile("PlanetMesh.txt");
	_meshPlanet.CreateVBO(_r);
	t_planetWatermelon.Initialize(_r->GetDevice(), L"WatermelonTexture.jpg");
	p_Watermelon = new Planet(glm::vec3(3, -4, 6), 1);
	p_Watermelon->SetMesh(&_meshPlanet);
	p_Watermelon->SetTexture(&t_planetWatermelon);
	p_Watermelon->SetAlive(true);

	t_planetMoltenCore.Initialize(_r->GetDevice(), L"MoltenCore.jpg");
	p_MoltenCore = new Planet(glm::vec3(-5, 2, 18), 2);
	p_MoltenCore->SetMesh(&_meshPlanet);
	p_MoltenCore->SetTexture(&t_planetMoltenCore);
	p_MoltenCore->SetAlive(true);

	t_planetFrozenCore.Initialize(_r->GetDevice(), L"FrozenCore.jpg");
	p_FrozenCore = new Planet(glm::vec3(8, -2, 27), 3);
	p_FrozenCore->SetMesh(&_meshPlanet);
	p_FrozenCore->SetTexture(&t_planetFrozenCore);
	p_FrozenCore->SetAlive(true);

	t_planetFelCore.Initialize(_r->GetDevice(), L"FelCore.jpg");
	p_FelCore = new Planet(glm::vec3(0, 0, -10), 4);
	p_FelCore->SetMesh(&_meshPlanet);
	p_FelCore->SetTexture(&t_planetFelCore);
	p_FelCore->SetAlive(true);

	t_planetByousoku.Initialize(_r->GetDevice(), L"Byousoku.jpg");
	p_Byousoku = new Planet(glm::vec3(10, -3, -12), 5);
	p_Byousoku->SetMesh(&_meshPlanet);
	p_Byousoku->SetTexture(&t_planetByousoku);
	p_Byousoku->SetAlive(true);

	t_planetCuivien.Initialize(_r->GetDevice(), L"Cuivien.jpg");
	p_Cuivien = new Planet(glm::vec3(-10, 4, -20), 6);
	p_Cuivien->SetMesh(&_meshPlanet);
	p_Cuivien->SetTexture(&t_planetCuivien);
	p_Cuivien->SetAlive(true);

	t_planetIsrevial.Initialize(_r->GetDevice(), L"Isrevial.jpg");
	p_Isrevial = new Planet(glm::vec3(-20, 2, 6), 1);
	p_Isrevial->SetMesh(&_meshPlanet);
	p_Isrevial->SetTexture(&t_planetIsrevial);
	p_Isrevial->SetAlive(true);

	_gameObjects.push_back(p_Watermelon);
	_gameObjects.push_back(p_MoltenCore);
	_gameObjects.push_back(p_FrozenCore);
	_gameObjects.push_back(p_FelCore);
	_gameObjects.push_back(p_Byousoku);
	_gameObjects.push_back(p_Cuivien);
	_gameObjects.push_back(p_Isrevial);

	_texEnemy.Initialize(_r->GetDevice(), L"TextureC2.jpg");
	_enemy = new TestEnemy();
	_enemy->SetMesh(&_meshPlayer);
	_enemy->SetTexture(&_texEnemy);
	_enemy->SetAlive(true);
	_enemy->SetPos(glm::vec3(-5, 0, 10));
	_gameObjects.push_back(_enemy);

	_meshLaser.LoadFromFile("LaserMesh.txt");
	_meshLaser.CreateVBO(_r);
	_texLaser.Initialize(_r->GetDevice(), L"TextureC1.jpg");
	for (int i = 0; i < 4; i++)
	{
		_beams[i] = new LaserBeam();
		_beams[i]->SetMesh(&_meshLaser);
		_beams[i]->SetTexture(&_texLaser);
		_beams[i]->SetAlive(false);
		_gameObjects.push_back(_beams[i]);
	}

	_meshSkybox.LoadFromFile("SkyboxMesh.txt");
	_meshSkybox.CreateVBO(_r);
	_texSkybox.Initialize(_r->GetDevice(), L"Skybox.jpg");
	_sb = new Skybox();
	_sb->SetMesh(&_meshSkybox);
	_sb->SetTexture(&_texSkybox);
	//_sb->SetScale(3);
	_sb->SetFocus(_cameraOne);
	//_sb->SetPos(glm::vec3(0.0f, 0.0f, -0.5f));

	_meshMenu.LoadFromFile("PanelMesh.txt");
	_meshMenu.CreateVBO(_r);
	_texPanel.Initialize(_r->GetDevice(), L"MenuBase.jpg");
	_subMenu = new GameObject();
	_subMenu->SetPos(-0.5, 0, 0);
	_subMenu->SetMesh(&_meshMenu);
	_subMenu->SetTexture(&_texPanel);

	_meshCursor.LoadFromFile("CursorMesh.txt");
	_meshCursor.CreateVBO(_r);
	_texCursor.Initialize(_r->GetDevice(), L"Cursor.jpg");
	_cursor = new Cursor();
	_cursor->SetMesh(&_meshCursor);
	_cursor->SetTexture(&_texCursor);

	_gameObjects.push_back(_cursor);

	_cameraOne->SetCameraTarget(_player);
	_cameraOne->SwitchType(true);

	_audioPlayer = new AudioPlayer();
	_audioPlayer->CreateSound(&_sound, "era-of-space.ogg");
	_audioPlayer->PlaySoundW(_sound, true);

	subMenuCounter = 0;

	_onFlight = true;
	_landCooldown = 0;

	_sceneState = Running;
}

void GameplayScene::Unload()
{
	_audioPlayer->ReleaseSound(_sound);

	Scene::Unload();
}

void GameplayScene::Update(float dt)
{

	if (_sceneState == Running)
	{
		if (!_onFlight)	// landed on the planet
		{
			_cursor->SetAlive(true);
			_cursor->Update(dt);
		}

		else            // flying in the starry night <3
		{
			if (_cursor->IsAlive())
				_cursor->SetAlive(false);
			_player->Update(dt);
			_cameraOne->Update(dt);
			for (int i = 0; i < 4; i++)
				if (_beams[i]->IsFired())
				{
					_beams[i]->Update(dt);
					//_beams[i]->SetAlive(true); // hardfix
				}
			if (_landCooldown > 0)
				_landCooldown = _landCooldown - dt;
		}

		_sb->Update();
	}
}

void GameplayScene::Draw()
{
	_r->ClearScreen();

	//_cameraOne->SetCameraPosition(_player->GetPos());

	_r->RenderFrame();

	_r->DrawGO(_sb);

	if (!_onFlight)
	{
		_r->DrawGUI(_subMenu);
		_r->DrawGUI(_cursor);

		if (subMenuCounter == 1)
		{
			_writer->DrawString(
				_r->GetContext(),
				L"Buy",// String
				40.0f,// Font size
				500,// X offset
				300,// Y offset
				0xff0099ff,// Text color, 0xAaBbGgRr
				FW1_CENTER | FW1_VCENTER | FW1_RESTORESTATE// Flags
				);
			_writer->DrawString(
				_r->GetContext(),
				L"Sell",// String
				40.0f,// Font size
				500,// X offset
				400,// Y offset
				0xff0099ff,// Text color, 0xAaBbGgRr
				FW1_CENTER | FW1_VCENTER | FW1_RESTORESTATE// Flags
				);
		}
	}

	if (subMenuCounter == 2)
	{
		int yOffset = 100;
		int j = 0;

		// UI
		_writer->DrawString(
			_r->GetContext(),
			L"Item Name",// String
			30.0f,// Font size
			500,// X offset
			50,// Y offset
			0xffff9900,// Text color, 0xAaBbGgRr
			FW1_RESTORESTATE// Flags
			);
		_writer->DrawString(
			_r->GetContext(),
			L"Price",// String
			30.0f,// Font size
			850,// X offset
			50,// Y offset
			0xffff9900,// Text color, 0xAaBbGgRr
			FW1_RESTORESTATE// Flags
			);
		_writer->DrawString(
			_r->GetContext(),
			L"Availability",// String
			30.0f,// Font size
			1050,// X offset
			50,// Y offset
			0xffff9900,// Text color, 0xAaBbGgRr
			FW1_RESTORESTATE// Flags
			);

		for (int i = 0; i < tempBag.size(); i++)
		{
			if (i == selections[j])
			{
				// Print item name
				std::wstring widestr = std::wstring(tempBag[i].name.begin(), tempBag[i].name.end());
				const wchar_t* widecstr = widestr.c_str();

				_writer->DrawString(
					_r->GetContext(),
					widecstr,// String
					40.0f,// Font size
					500,// X offset
					yOffset,// Y offset
					0xff0099ff,// Text color, 0xAaBbGgRr
					FW1_RESTORESTATE// Flags
					);

				// Print the price
				std::string str = std::to_string(tempBag[i].price);
				widestr = std::wstring(str.begin(), str.end());
				widecstr = widestr.c_str();

				_writer->DrawString(
					_r->GetContext(),
					widecstr,// String
					40.0f,// Font size
					850,// X offset
					yOffset,// Y offset
					0xff0099ff,// Text color, 0xAaBbGgRr
					FW1_RESTORESTATE// Flags
					);

				// Print the availability
				str = std::to_string(tempBag[i].amount);
				widestr = std::wstring(str.begin(), str.end());
				widecstr = widestr.c_str();

				_writer->DrawString(
					_r->GetContext(),
					widecstr,// String
					40.0f,// Font size
					1050,// X offset
					yOffset,// Y offset
					0xff0099ff,// Text color, 0xAaBbGgRr
					FW1_RESTORESTATE// Flags
					);

				j++;
				yOffset = yOffset + 90;
			}
		}
	}

	if (subMenuCounter == 3)
	{
		int yOffset = 100;
		int j = 0;

		// UI
		_writer->DrawString(
			_r->GetContext(),
			L"Item Name",// String
			30.0f,// Font size
			500,// X offset
			50,// Y offset
			0xffff9900,// Text color, 0xAaBbGgRr
			FW1_RESTORESTATE// Flags
			);
		_writer->DrawString(
			_r->GetContext(),
			L"Price",// String
			30.0f,// Font size
			850,// X offset
			50,// Y offset
			0xffff9900,// Text color, 0xAaBbGgRr
			FW1_RESTORESTATE// Flags
			);
		_writer->DrawString(
			_r->GetContext(),
			L"Availability",// String
			30.0f,// Font size
			1050,// X offset
			50,// Y offset
			0xffff9900,// Text color, 0xAaBbGgRr
			FW1_RESTORESTATE// Flags
			);

		for (int i = 0; i < tempPlayerBag.size(); i++)
		{
			if (i == player_selections[j])
			{
				// Print item name
				std::wstring widestr = std::wstring(tempPlayerBag[i].name.begin(), tempPlayerBag[i].name.end());
				const wchar_t* widecstr = widestr.c_str();

				_writer->DrawString(
					_r->GetContext(),
					widecstr,// String
					40.0f,// Font size
					500,// X offset
					yOffset,// Y offset
					0xff0099ff,// Text color, 0xAaBbGgRr
					FW1_RESTORESTATE// Flags
					);

				// Print the price
				std::string str = std::to_string(tempPlayerBag[i].price);
				widestr = std::wstring(str.begin(), str.end());
				widecstr = widestr.c_str();

				_writer->DrawString(
					_r->GetContext(),
					widecstr,// String
					40.0f,// Font size
					850,// X offset
					yOffset,// Y offset
					0xff0099ff,// Text color, 0xAaBbGgRr
					FW1_RESTORESTATE// Flags
					);

				// Print the availability
				str = std::to_string(tempPlayerBag[i].amount);
				widestr = std::wstring(str.begin(), str.end());
				widecstr = widestr.c_str();

				_writer->DrawString(
					_r->GetContext(),
					widecstr,// String
					40.0f,// Font size
					1050,// X offset
					yOffset,// Y offset
					0xff0099ff,// Text color, 0xAaBbGgRr
					FW1_RESTORESTATE// Flags
					);

				j++;
				yOffset = yOffset + 90;
			}
		}
	}

	else
	{
		// TODO: vision range
		for (int i = 0; i < _gameObjects.size(); i++)
			if (_gameObjects[i]->IsAlive())
				_r->DrawGO(_gameObjects[i]);
	}


	// Text must be rendered after everything else
	// Must be remvoed
	InventoryComponent* ic = static_cast<InventoryComponent*>(_player->GetComponent("inventory"));
	int c = ic->GetMoney();
	std::string str = std::to_string(c);
	std::wstring widestr = std::wstring(str.begin(), str.end());
	credits = widestr.c_str();

	_writer->DrawString(
		_r->GetContext(),
		L"Credits: ",// String
		30.0f,// Font size
		100,// X offset
		50,// Y offset
		0xff0099ff,// Text color, 0xAaBbGgRr
		FW1_CENTER | FW1_VCENTER | FW1_RESTORESTATE// Flags
		);

	_writer->DrawString(
		_r->GetContext(),
		credits,// String
		30.0f,// Font size
		100,// X offset
		80,// Y offset
		0xff0099ff,// Text color, 0xAaBbGgRr
		FW1_CENTER | FW1_VCENTER | FW1_RESTORESTATE// Flags
		);

	_r->SwapBuffer();
}

void GameplayScene::OnMessage(Message* m)
{
	Scene::OnMessage(m);

	_cameraOne->OnMessage(m);

	if (m->GetMessageType() == "landed" && _landCooldown <= 0)
	{
		_onFlight = false;
		LandedMessage* mc = static_cast<LandedMessage*>(m);
		tempPlanet = mc->GetPlanet();
		LandingOperations();
	}

	if (m->GetMessageType() == "fire")
	{
		Fire();
	}
}

void GameplayScene::OnKeyboard(int key, bool down)
{
	Scene::OnKeyboard(key, down);

	if (key == 13 && down == true)
	{
		int x = _cursor->GetCurrPos();

		if (!_onFlight && subMenuCounter == 2)
		{
			int pos = _cursor->GetCurrPos();
			int x = selections[pos];
	
			TransactionMessage* tm = new TransactionMessage(false, tempBag[x].id, tempBag[x].price, _player);
			tempPlanet->OnMessage(tm);
			InventoryComponent* ic = static_cast<InventoryComponent*>(tempPlanet->GetComponent("inventory"));
			tempBag = ic->GetBag();
			TransactionMessage* tm2 = new TransactionMessage(true, tempPlayerBag[x].id, tempPlayerBag[x].price, tempPlanet);
			_player->OnMessage(tm2);
			InventoryComponent* ic2 = static_cast<InventoryComponent*>(_player->GetComponent("inventory"));
			tempPlayerBag = ic2->GetBag();

			UpdatePlayerBag();
			UpdateCreditsCount();
		}

		if (!_onFlight && subMenuCounter == 3)
		{
			int pos = _cursor->GetCurrPos();
			int x = player_selections[pos];

			TransactionMessage* tm = new TransactionMessage(false, tempPlayerBag[x].id, tempPlayerBag[x].price, tempPlanet);
			_player->OnMessage(tm);
			InventoryComponent* ic = static_cast<InventoryComponent*>(_player->GetComponent("inventory"));
			tempPlayerBag = ic->GetBag();
			TransactionMessage* tm2 = new TransactionMessage(true, tempBag[x].id, tempBag[x].price, _player);
			tempPlanet->OnMessage(tm2);
			InventoryComponent* ic2 = static_cast<InventoryComponent*>(tempPlanet->GetComponent("inventory"));
			tempBag = ic2->GetBag();

			UpdatePlayerBag();
			UpdateCreditsCount();
		}

		if (!_onFlight && subMenuCounter == 1 && x == 2)
		{
			int j = 0;
			subMenuCounter = 2;
			for (int i = 0; i < 9; i++)
			{
				if (selections[i] != 0)
					j++;
			}
			_cursor->SetMaximumPos(j);
		}

		if (!_onFlight && subMenuCounter == 1 && x == 3)
		{
			int j = 0;
			subMenuCounter = 3;
			for (int i = 0; i < 9; i++)
			{
				if (player_selections[i] != 0)
					j++;
			}
			_cursor->SetMaximumPos(j);
		}
	}
	if (key == 8 && down == true && subMenuCounter == 1)
	{
		_onFlight = true;
		_landCooldown = 10;
		subMenuCounter = 0;
	}
	if (key == 8 && down == true && subMenuCounter > 1)
	{
			subMenuCounter = 1;
	}
}

void GameplayScene::LandingOperations()
{
	subMenuCounter = 1;
	InventoryComponent* ic = static_cast<InventoryComponent*>(tempPlanet->GetComponent("inventory"));
	tempBag = ic->GetBag();
	// Prendere le scelte valide
	int j = 0;
	for (int i = 0; i < tempBag.size(); i++)
	{
		if (tempBag[i].amount > 0)
		{
			selections[j] = i;	// tempBag[i] is a valid choice and thus must be shown.
			j++;
		}
	}

	UpdatePlayerBag();
}

void GameplayScene::UpdatePlayerBag()
{
	InventoryComponent* ic = static_cast<InventoryComponent*>(_player->GetComponent("inventory"));
	tempPlayerBag = ic->GetBag();
	// Prendere le scelte valide
	int j = 0;
	for (int i = 0; i < tempPlayerBag.size(); i++)
	{
		if (tempPlayerBag[i].amount > 0)
		{
			player_selections[j] = i;	// 
			j++;
		}
	}
}

void GameplayScene::UpdateCreditsCount()
{
	InventoryComponent* ic = static_cast<InventoryComponent*>(_player->GetComponent("inventory"));
	int c = ic->GetMoney();
	std::string str = std::to_string(c);
	std::wstring widestr = std::wstring(str.begin(), str.end());
	credits = widestr.c_str();
}

void GameplayScene::Fire()
{
	int j = 0;
	for (int i = 0; i < 4 && j < 1; i++)
	{
		if (_beams[i]->IsFired() == false)
		{
			_beams[i]->SetAlive(true);
			_beams[i]->Fire(_player->GetPos(), _player->GetAngle());
			j = 1;
		}
	}
}