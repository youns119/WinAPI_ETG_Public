#include "pch.h"
#include "Main.h"

#include "PathManager.h"
#include "Timer.h"
#include "Keyboard.h"
#include "ResourceManager.h"
#include "PaintManager.h"
#include "SceneManager.h"
#include "Mouse.h"
#include "Camera.h"
#include "ColliderManager.h"
#include "EventManager.h"
#include "Generator.h"
#include "UIManager.h"
#include "SoundManager.h"

#include "Texture.h"
#include "Paint.h"

CMain::CMain()
	: m_hWnd(nullptr)
	, m_tResolution{}
	, m_hDC(nullptr)
	, m_pBackBuffer(nullptr)
{
}

CMain::~CMain()
{
	Release();
}

int CMain::Init(HWND _hWnd, POINT _tResolution)
{
	m_hWnd = _hWnd;
	m_tResolution = _tResolution;

	RECT tRect = { 0, 0, m_tResolution.x, m_tResolution.y };
	AdjustWindowRect(&tRect, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(m_hWnd, nullptr, 0, 0, tRect.right - tRect.left, tRect.bottom - tRect.top, 0);

	m_hDC = GetDC(m_hWnd);

	m_pBackBuffer = CResourceManager::Get()->CreateTexture(L"BackBuffer", (UINT)m_tResolution.x, (UINT)m_tResolution.y);

	srand(unsigned int(time(NULL)));

	CPathManager::Get()->Init();
	CTimer::Get()->Init();
	CKeyboard::Get()->Init();
	CCamera::Get()->Init();
	CPaintManager::Get()->Init();

	TextureSetting();

	/*CGenerator::Get()->Init();*/
	CMouse::Get()->Init();
	CUIManager::Get()->Init();
	CSoundManager::Get()->Init();
	CSceneManager::Get()->Init();

	return S_OK;
}

void CMain::Update()
{
	CTimer::Get()->Update();
	CKeyboard::Get()->Update();
	CMouse::Get()->Update();
	CSceneManager::Get()->Update();
	CCamera::Get()->Update();

	if (CKeyboard::Get()->KeyDown(VK_ESCAPE))
		DestroyWindow(g_hWnd);
}

void CMain::LateUpdate()
{
	CColliderManager::Get()->Update();
}

void CMain::Render()
{
	Clear();

	CSceneManager::Get()->Render(m_pBackBuffer->GetHDC());
	CMouse::Get()->Render(m_pBackBuffer->GetHDC());
	CCamera::Get()->Render(m_pBackBuffer->GetHDC());

	BitBlt
	(
		m_hDC,
		0, 0,
		m_tResolution.x, m_tResolution.y,
		m_pBackBuffer->GetHDC(),
		0, 0,
		SRCCOPY
	);
}

void CMain::Release()
{
	CTimer::Get()->Destroy();
	CKeyboard::Get()->Destroy();
	CPathManager::Get()->Destroy();
	CResourceManager::Get()->Destroy();
	CPaintManager::Get()->Destroy();
	CCamera::Get()->Destroy();
	CGenerator::Get()->Destroy();
	CUIManager::Get()->Destroy();
	CSceneManager::Get()->Destroy();
	CSoundManager::Get()->Destroy();
	CColliderManager::Get()->Destroy();
	CMouse::Get()->Destroy();
	CEventManager::Get()->Destroy();

	ReleaseDC(m_hWnd, m_hDC);
}

void CMain::Run()
{
	Update();
	LateUpdate();
	Render();

	CEventManager::Get()->Update();
}

void CMain::Clear()
{
	CPaint Paint(m_pBackBuffer->GetHDC(), BRUSH_TYPE::BLACK);
	Rectangle(m_pBackBuffer->GetHDC(), -1, -1, m_tResolution.x + 1, m_tResolution.y + 1);
}

void CMain::TextureSetting()
{
	// Mouse
	CResourceManager::Get()->LoadTexture(L"Crosshair", L"texture\\UI\\Crosshair\\Crosshair1.bmp");

	// Player
	CResourceManager::Get()->LoadTexture(L"Player_Idle_D", L"texture\\Character\\Player\\Idle\\Idle_D\\Idle_D.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Idle_DR", L"texture\\Character\\Player\\Idle\\Idle_DR\\Idle_DR.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Idle_DL", L"texture\\Character\\Player\\Idle\\Idle_DL\\Idle_DL.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Idle_U", L"texture\\Character\\Player\\Idle\\Idle_U\\Idle_U.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Idle_UR", L"texture\\Character\\Player\\Idle\\Idle_UR\\Idle_UR.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Idle_UL", L"texture\\Character\\Player\\Idle\\Idle_UL\\Idle_UL.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Walk_D", L"texture\\Character\\Player\\Walk\\Walk_D\\Walk_D.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Walk_DR", L"texture\\Character\\Player\\Walk\\Walk_DR\\Walk_DR.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Walk_DL", L"texture\\Character\\Player\\Walk\\Walk_DL\\Walk_DL.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Walk_U", L"texture\\Character\\Player\\Walk\\Walk_U\\Walk_U.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Walk_UR", L"texture\\Character\\Player\\Walk\\Walk_UR\\Walk_UR.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Walk_UL", L"texture\\Character\\Player\\Walk\\Walk_UL\\Walk_UL.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Dodge_D", L"texture\\Character\\Player\\Dodge\\Dodge_D\\Dodge_D.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Dodge_DR", L"texture\\Character\\Player\\Dodge\\Dodge_DR\\Dodge_DR.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Dodge_DL", L"texture\\Character\\Player\\Dodge\\Dodge_DL\\Dodge_DL.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Dodge_U", L"texture\\Character\\Player\\Dodge\\Dodge_U\\Dodge_U.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Dodge_UR", L"texture\\Character\\Player\\Dodge\\Dodge_UR\\Dodge_UR.bmp");
	CResourceManager::Get()->LoadTexture(L"Player_Dodge_UL", L"texture\\Character\\Player\\Dodge\\Dodge_UL\\Dodge_UL.bmp");

	// Enemy
	CResourceManager::Get()->LoadTexture(L"BulletKin_Idle_DR", L"texture\\Character\\Enemy\\BulletKin\\Idle\\Idle_DR\\Idle_DR.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKin_Idle_DL", L"texture\\Character\\Enemy\\BulletKin\\Idle\\Idle_DL\\Idle_DL.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKin_Idle_U", L"texture\\Character\\Enemy\\BulletKin\\Idle\\Idle_U\\Idle_U.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKin_Walk_DR", L"texture\\Character\\Enemy\\BulletKin\\Walk\\Walk_DR\\Walk_DR.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKin_Walk_DL", L"texture\\Character\\Enemy\\BulletKin\\Walk\\Walk_DL\\Walk_DL.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKin_Walk_U", L"texture\\Character\\Enemy\\BulletKin\\Walk\\Walk_U\\Walk_U.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKin_Hit_R", L"texture\\Character\\Enemy\\BulletKin\\Hit\\Hit_R\\Hit_R.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKin_Hit_L", L"texture\\Character\\Enemy\\BulletKin\\Hit\\Hit_L\\Hit_L.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKin_Death_R", L"texture\\Character\\Enemy\\BulletKin\\Death\\Death_R\\Death_R.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKin_Death_L", L"texture\\Character\\Enemy\\BulletKin\\Death\\Death_L\\Death_L.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKin_Dead_R", L"texture\\Character\\Enemy\\BulletKin\\Dead\\Dead_R\\Dead_R.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKin_Dead_L", L"texture\\Character\\Enemy\\BulletKin\\Dead\\Dead_L\\Dead_L.bmp");

	CResourceManager::Get()->LoadTexture(L"ShotGunKin_Idle_D", L"texture\\Character\\Enemy\\ShotGunKin\\Idle\\Idle_D\\ShotGunKin_Idle_D.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGunKin_Idle_U", L"texture\\Character\\Enemy\\ShotGunKin\\Idle\\Idle_U\\ShotGunKin_Idle_U.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGunKin_Walk_DR", L"texture\\Character\\Enemy\\ShotGunKin\\Walk\\Walk_DR\\ShotGunKin_Walk_DR.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGunKin_Walk_DL", L"texture\\Character\\Enemy\\ShotGunKin\\Walk\\Walk_DL\\ShotGunKin_Walk_DL.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGunKin_Walk_U", L"texture\\Character\\Enemy\\ShotGunKin\\Walk\\Walk_U\\ShotGunKin_Walk_U.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGunKin_Hit_R", L"texture\\Character\\Enemy\\ShotGunKin\\Hit\\Hit_R\\ShotGunKin_Hit_R.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGunKin_Hit_L", L"texture\\Character\\Enemy\\ShotGunKin\\Hit\\Hit_L\\ShotGunKin_Hit_L.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGunKin_Death", L"texture\\Character\\Enemy\\ShotGunKin\\Death\\ShotGunKin_Death.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGunKin_Dead_R", L"texture\\Character\\Enemy\\ShotGunKin\\Dead\\Dead_R\\ShotGunKin_Dead_R.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGunKin_Dead_L", L"texture\\Character\\Enemy\\ShotGunKin\\Dead\\Dead_L\\ShotGunKin_Dead_L.bmp");

	CResourceManager::Get()->LoadTexture(L"BulletKing_Idle", L"texture\\Character\\Enemy\\BulletKing\\Idle\\BulletKing_Idle.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKing_Attack", L"texture\\Character\\Enemy\\BulletKing\\Attack\\BulletKing_Attack.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKing_Hit", L"texture\\Character\\Enemy\\BulletKing\\Hit\\BulletKing_Hit.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKing_Die", L"texture\\Character\\Enemy\\BulletKing\\Die\\BulletKing_Die.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKing_Chair_Idle", L"texture\\Character\\Enemy\\BulletKing\\Idle\\BulletKing_Chair_Idle.bmp");
	CResourceManager::Get()->LoadTexture(L"BulletKing_Chair_Rotate", L"texture\\Character\\Enemy\\BulletKing\\Rotate\\BulletKing_Chair_Rotate.bmp");
	CResourceManager::Get()->LoadTexture(L"Chair", L"texture\\Character\\Enemy\\BulletKing\\Chair.bmp");

	// UI
	CResourceManager::Get()->LoadTexture(L"HP_Full", L"texture\\UI\\Item\\HP_Full.bmp");
	CResourceManager::Get()->LoadTexture(L"HP_Half", L"texture\\UI\\Item\\HP_Half.bmp");
	CResourceManager::Get()->LoadTexture(L"HP_Empty", L"texture\\UI\\Item\\HP_Empty.bmp");

	CResourceManager::Get()->LoadTexture(L"Fear", L"texture\\UI\\Item\\Fear.bmp");

	CResourceManager::Get()->LoadTexture(L"Key", L"texture\\UI\\Item\\Key.bmp");
	CResourceManager::Get()->LoadTexture(L"Coin", L"texture\\UI\\Item\\Coin.bmp");

	CResourceManager::Get()->LoadTexture(L"GunBox", L"texture\\UI\\Gun\\GunBox.bmp");

	CResourceManager::Get()->LoadTexture(L"Bullet_Shell", L"texture\\UI\\Bullet\\Bullet_Shell.bmp");
	CResourceManager::Get()->LoadTexture(L"Revolver_Bullet", L"texture\\UI\\Bullet\\Revolver_Bullet\\Revolver_Bullet.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGun_Bullet", L"texture\\UI\\Bullet\\ShotGun_Bullet\\ShotGun_Bullet.bmp");
	CResourceManager::Get()->LoadTexture(L"MachineGun_Bullet", L"texture\\UI\\Bullet\\MachineGun_Bullet\\MachineGun_Bullet.bmp");
	CResourceManager::Get()->LoadTexture(L"ReflectGun_Bullet", L"texture\\UI\\Bullet\\ReflectGun_Bullet\\ReflectGun_Bullet.bmp");
	CResourceManager::Get()->LoadTexture(L"HomingGun_Bullet", L"texture\\UI\\Bullet\\HomingGun_Bullet\\HomingGun_Bullet.bmp");

	CResourceManager::Get()->LoadTexture(L"Reload", L"texture\\UI\\Reload\\ReloadBar.bmp");

	CResourceManager::Get()->LoadTexture(L"Font", L"texture\\UI\\Font\\Font.bmp");
	CResourceManager::Get()->LoadTexture(L"Font_Smaller", L"texture\\UI\\Font\\Font_Smaller.bmp");
	CResourceManager::Get()->LoadTexture(L"Font_Infinite", L"texture\\UI\\Font\\Font_Infinite.bmp");
	CResourceManager::Get()->LoadTexture(L"Font_Slash", L"texture\\UI\\Font\\Font_Slash.bmp");

	CResourceManager::Get()->LoadTexture(L"BossHP", L"texture\\UI\\BossHP\\BossHP.bmp");
	CResourceManager::Get()->LoadTexture(L"BossHPBar", L"texture\\UI\\BossHP\\BossHPBar.bmp");

	CResourceManager::Get()->LoadTexture(L"Minimap", L"texture\\Map\\Minimap.bmp");
	CResourceManager::Get()->LoadTexture(L"Minimap_Background", L"texture\\Map\\Minimap_Background.bmp");
	CResourceManager::Get()->LoadTexture(L"PlayerPortrait", L"texture\\Map\\PlayerPortrait.bmp");

	// Gun
	CResourceManager::Get()->LoadTexture(L"Revolver_R", L"texture\\Gun\\Revolver\\Revolver_R.bmp");
	CResourceManager::Get()->LoadTexture(L"Revolver_L", L"texture\\Gun\\Revolver\\Revolver_L.bmp");
	CResourceManager::Get()->LoadTexture(L"Revolver_Plg", L"texture\\Gun\\Revolver\\Revolver_Plg.bmp");
	CResourceManager::Get()->LoadTexture(L"Revolver_Reset", L"texture\\Gun\\Revolver\\Revolver_Reset.bmp");

	CResourceManager::Get()->LoadTexture(L"ShotGun_R", L"texture\\Gun\\ShotGun\\ShotGun_R.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGun_L", L"texture\\Gun\\ShotGun\\ShotGun_L.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGun_Plg", L"texture\\Gun\\ShotGun\\ShotGun_Plg.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGun_Reset", L"texture\\Gun\\ShotGun\\ShotGun_Reset.bmp");

	CResourceManager::Get()->LoadTexture(L"MachineGun_R", L"texture\\Gun\\MachineGun\\MachineGun_R.bmp");
	CResourceManager::Get()->LoadTexture(L"MachineGun_L", L"texture\\Gun\\MachineGun\\MachineGun_L.bmp");
	CResourceManager::Get()->LoadTexture(L"MachineGun_Plg", L"texture\\Gun\\MachineGun\\MachineGun_Plg.bmp");
	CResourceManager::Get()->LoadTexture(L"MachineGun_Reset", L"texture\\Gun\\MachineGun\\MachineGun_Reset.bmp");

	CResourceManager::Get()->LoadTexture(L"ReflectGun_R", L"texture\\Gun\\ReflectGun\\ReflectGun_R.bmp");
	CResourceManager::Get()->LoadTexture(L"ReflectGun_L", L"texture\\Gun\\ReflectGun\\ReflectGun_L.bmp");
	CResourceManager::Get()->LoadTexture(L"ReflectGun_Plg", L"texture\\Gun\\ReflectGun\\ReflectGun_Plg.bmp");
	CResourceManager::Get()->LoadTexture(L"ReflectGun_Reset", L"texture\\Gun\\ReflectGun\\ReflectGun_Reset.bmp");

	CResourceManager::Get()->LoadTexture(L"HomingGun_R", L"texture\\Gun\\HomingGun\\HomingGun_R.bmp");
	CResourceManager::Get()->LoadTexture(L"HomingGun_L", L"texture\\Gun\\HomingGun\\HomingGun_L.bmp");
	CResourceManager::Get()->LoadTexture(L"HomingGun_Plg", L"texture\\Gun\\HomingGun\\HomingGun_Plg.bmp");
	CResourceManager::Get()->LoadTexture(L"HomingGun_Reset", L"texture\\Gun\\HomingGun\\HomingGun_Reset.bmp");

	// Item
	CResourceManager::Get()->LoadTexture(L"Revolver_R_Alt", L"texture\\Gun\\Revolver\\Revolver_R_Alt.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGun_R_Alt", L"texture\\Gun\\ShotGun\\ShotGun_R_Alt.bmp");
	CResourceManager::Get()->LoadTexture(L"MachineGun_R_Alt", L"texture\\Gun\\MachineGun\\MachineGun_R_Alt.bmp");
	CResourceManager::Get()->LoadTexture(L"ReflectGun_R_Alt", L"texture\\Gun\\ReflectGun\\ReflectGun_R_Alt.bmp");
	CResourceManager::Get()->LoadTexture(L"HomingGun_R_Alt", L"texture\\Gun\\HomingGun\\HomingGun_R_Alt.bmp");
	CResourceManager::Get()->LoadTexture(L"Item_Coin", L"texture\\Item\\Coin\\Item_Coin.bmp");
	CResourceManager::Get()->LoadTexture(L"Item_Fear", L"texture\\Item\\Fear\\Item_Fear.bmp");
	CResourceManager::Get()->LoadTexture(L"Item_HPHalf", L"texture\\Item\\HP\\Item_HPHalf.bmp");
	CResourceManager::Get()->LoadTexture(L"Item_HPFull", L"texture\\Item\\HP\\Item_HPFull.bmp");
	CResourceManager::Get()->LoadTexture(L"Item_Key", L"texture\\Item\\Key\\Item_Key.bmp");
	CResourceManager::Get()->LoadTexture(L"Medikit", L"texture\\Item\\Medikit\\Medikit.bmp");
	CResourceManager::Get()->LoadTexture(L"Medikit_Alt", L"texture\\Item\\Medikit\\Medikit_Alt.bmp");
	CResourceManager::Get()->LoadTexture(L"Medikit_Used", L"texture\\Item\\Medikit\\Medikit_Used.bmp");

	// Projectile
	CResourceManager::Get()->LoadTexture(L"Projectile_Revolver", L"texture\\Projectile\\Projectile_Revolver\\Projectile_Revolver.bmp");

	CResourceManager::Get()->LoadTexture(L"Projectile_ShotGun", L"texture\\Projectile\\Projectile_ShotGun\\Projectile_ShotGun.bmp");

	CResourceManager::Get()->LoadTexture(L"Projectile_MachineGun", L"texture\\Projectile\\Projectile_MachineGun\\Projectile_MachineGun.bmp");
	CResourceManager::Get()->LoadTexture(L"Projectile_MachineGun_Plg", L"texture\\Projectile\\Projectile_MachineGun\\Projectile_MachineGun_Plg.bmp");
	CResourceManager::Get()->LoadTexture(L"Projectile_MachineGun_Reset", L"texture\\Projectile\\Projectile_MachineGun\\Projectile_MachineGun_Reset.bmp");

	CResourceManager::Get()->LoadTexture(L"Projectile_ReflectGun", L"texture\\Projectile\\Projectile_ReflectGun\\Projectile_ReflectGun.bmp");

	CResourceManager::Get()->LoadTexture(L"Projectile_HomingGun", L"texture\\Projectile\\Projectile_HomingGun\\Projectile_HomingGun.bmp");
	CResourceManager::Get()->LoadTexture(L"Projectile_HomingGun_Plg", L"texture\\Projectile\\Projectile_HomingGun\\Projectile_HomingGun_Plg.bmp");
	CResourceManager::Get()->LoadTexture(L"Projectile_HomingGun_Reset", L"texture\\Projectile\\Projectile_HomingGun\\Projectile_HomingGun_Reset.bmp");

	CResourceManager::Get()->LoadTexture(L"Projectile_Enemy", L"texture\\Projectile\\Projectile_Enemy\\Projectile_Enemy.bmp");

	// Interact
	CResourceManager::Get()->LoadTexture(L"Table", L"texture\\Interact\\Table\\Table.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_Alt_D", L"texture\\Interact\\Table\\Table_Alt_D.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_Alt_U", L"texture\\Interact\\Table\\Table_Alt_U.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_Alt_R", L"texture\\Interact\\Table\\Table_Alt_R.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_Alt_L", L"texture\\Interact\\Table\\Table_Alt_L.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_D", L"texture\\Interact\\Table\\Table_D.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_U", L"texture\\Interact\\Table\\Table_U.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_R", L"texture\\Interact\\Table\\Table_R.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_L", L"texture\\Interact\\Table\\Table_L.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_Flip_D", L"texture\\Interact\\Table\\Flip_D\\Table_Flip_D.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_Flip_U", L"texture\\Interact\\Table\\Flip_U\\Table_Flip_U.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_Flip_R", L"texture\\Interact\\Table\\Flip_R\\Table_Flip_R.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_Flip_L", L"texture\\Interact\\Table\\Flip_L\\Table_Flip_L.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_Break", L"texture\\Interact\\Table\\Break\\Table_Break.bmp");
	CResourceManager::Get()->LoadTexture(L"Table_Broken", L"texture\\Interact\\Table\\Table_Broken.bmp");

	CResourceManager::Get()->LoadTexture(L"Chest", L"texture\\Interact\\Chest\\Chest.bmp");
	CResourceManager::Get()->LoadTexture(L"Chest_Alt", L"texture\\Interact\\Chest\\Chest_Alt.bmp");
	CResourceManager::Get()->LoadTexture(L"Chest_Opened", L"texture\\Interact\\Chest\\Chest_Opened.bmp");
	CResourceManager::Get()->LoadTexture(L"Chest_Broken", L"texture\\Interact\\Chest\\Chest_Broken.bmp");
	CResourceManager::Get()->LoadTexture(L"Chest_Open", L"texture\\Interact\\Chest\\Open\\Chest_Open.bmp");
	CResourceManager::Get()->LoadTexture(L"Chest_Break", L"texture\\Interact\\Chest\\Break\\Chest_Break.bmp");

	CResourceManager::Get()->LoadTexture(L"Barrel", L"texture\\Interact\\Barrel\\Barrel.bmp");
	CResourceManager::Get()->LoadTexture(L"Barrel_Blow", L"texture\\Interact\\Barrel\\Blow\\Barrel_Blow.bmp");

	// Effect
	CResourceManager::Get()->LoadTexture(L"RevolverEffect", L"texture\\Effect\\Revolver\\RevolverEffect.bmp");
	CResourceManager::Get()->LoadTexture(L"ShotGunEffect", L"texture\\Effect\\ShotGun\\ShotGunEffect.bmp");
	CResourceManager::Get()->LoadTexture(L"MachineGunEffect", L"texture\\Effect\\MachineGun\\MachineGunEffect.bmp");
	CResourceManager::Get()->LoadTexture(L"ReflectGunEffect", L"texture\\Effect\\ReflectGun\\ReflectGunEffect.bmp");
	CResourceManager::Get()->LoadTexture(L"HomingGunEffect", L"texture\\Effect\\HomingGun\\HomingGunEffect.bmp");
	CResourceManager::Get()->LoadTexture(L"TableEffect", L"texture\\Effect\\Interact\\Table\\TableEffect.bmp");
	CResourceManager::Get()->LoadTexture(L"ChestEffect", L"texture\\Effect\\Interact\\Chest\\ChestEffect.bmp");
	CResourceManager::Get()->LoadTexture(L"BlowEffect", L"texture\\Effect\\Interact\\Barrel\\Blow\\BlowEffect.bmp");
	CResourceManager::Get()->LoadTexture(L"SmokeEffect", L"texture\\Effect\\Interact\\Barrel\\Smoke\\SmokeEffect.bmp");
	CResourceManager::Get()->LoadTexture(L"SpawnEffect", L"texture\\Effect\\Spawn\\Spawn.bmp");
	CResourceManager::Get()->LoadTexture(L"FearEffect", L"texture\\Effect\\Fear\\FearEffect.bmp");
	CResourceManager::Get()->LoadTexture(L"HomingEffect", L"texture\\Effect\\HomingGun\\HomingEffect.bmp");

	// Map
	CResourceManager::Get()->LoadTexture(L"MapTemplate2", L"texture\\Map\\MapTemplate2.bmp");
	CResourceManager::Get()->LoadTexture(L"BossRoom", L"texture\\Map\\Room\\Boss\\Boss1.bmp");

	// Scene
	CResourceManager::Get()->LoadTexture(L"CutScene", L"texture\\Scene\\CutScene.bmp");
	CResourceManager::Get()->LoadTexture(L"Intro", L"texture\\Scene\\Intro.bmp");
}