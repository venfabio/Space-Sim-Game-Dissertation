#pragma once

#include <vector>
#include <FW1FontWrapper.h>
#include "Scene.h"
#include "Bag.h"
#include "AudioPlayer.h"

class Player;
class Planet;
class Camera;
class Skybox;
class Cursor;
class LaserBeam;
class TestEnemy;

class GameplayScene :
	public Scene
{
private:
	// Game objects
	Player*					_player;

	Planet*					p_Watermelon;
	Planet*					p_MoltenCore;
	Planet*					p_FrozenCore;
	Planet*					p_FelCore;
	Planet*					p_Stormcore;
	Planet*					p_Isrevial;
	Planet*					p_Byousoku;
	Planet*					p_Cuivien;

	Planet*					tempPlanet;

	LaserBeam*				_beams[4];

	TestEnemy*				_enemy;

	GameObject*				_subMenu;

	Cursor*					_cursor;

	Sound					_sound;
	AudioPlayer*			_audioPlayer;

	// Meshes
	Mesh					_meshPlayer;
	Mesh					_meshPlanet;
	Mesh					_meshSkybox;
	Mesh					_meshMenu;
	Mesh					_meshCursor;
	Mesh					_meshLaser;

	// Texture
	Texture					_texPlayer;
	Texture					t_planetWatermelon;
	Texture					t_planetMoltenCore;
	Texture					t_planetFrozenCore;
	Texture					t_planetFelCore;
	Texture					t_planetIsrevial;
	Texture					t_planetByousoku;
	Texture					t_planetCuivien;
	Texture					_texSkybox;
	Texture					_texPanel;
	Texture					_texCursor;
	Texture					_texLaser;
	Texture					_texEnemy;

	// Camera
	Camera*					_cameraOne;		// Default camera

	// Misc
	Skybox*					_sb;
	IFW1FontWrapper*		_writer;
	std::vector<Bag>		tempBag;
	std::vector<Bag>		tempPlayerBag;

	int						selections[9];
	int						player_selections[9];
	int						subMenuCounter;

	float					_landCooldown;

	const wchar_t*			credits;

	bool					_onFlight;

public:
	GameplayScene(Renderer* renderer);
	~GameplayScene();

	void Load();
	void Unload();
	void Update(float dt);
	void Draw();
	void OnMessage(Message* m);
	void OnKeyboard(int key, bool down);

	void LandingOperations();

	void UpdatePlayerBag();
	void UpdateCreditsCount();

	void Fire();
};

