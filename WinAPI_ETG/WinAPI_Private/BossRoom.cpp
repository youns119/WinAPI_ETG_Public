#include "pch.h"
#include "BossRoom.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "ColliderManager.h"
#include "Generator.h"
#include "UIManager.h"
#include "Mouse.h"
#include "Camera.h"
#include "Main.h"
#include "SoundManager.h"

#include "Texture.h"
#include "Player.h"
#include "BulletKin.h"
#include "BulletKing.h"
#include "Item_Gun.h"
#include "Table.h"
#include "Chest.h"
#include "Barrel.h"

CBossRoom::CBossRoom()
	: m_pTexture(nullptr)
{
	SetSceneType(SCENE_TYPE::BOSSROOM);
}

CBossRoom::~CBossRoom()
{
	CSceneManager::Get()->SetCurrScene(this);

	Release();
}

void CBossRoom::Init()
{
	SetName(L"BossRoom");

	CGenerator::Get()->CreateBossRoom();

	SetVolume(0.1);

	CObject* pBulletKing = new CBulletKing;
	CSceneManager::Get()->AddObject(pBulletKing, pBulletKing->GetObjectType());
	pBulletKing->SetPos({ 1500.f, 1000.f });

	CObject* pTable1 = new CTable;
	CSceneManager::Get()->AddObject(pTable1, pTable1->GetObjectType());
	pTable1->SetPos({ 1100.f , 1800.f });

	CObject* pTable4 = new CTable;
	CSceneManager::Get()->AddObject(pTable4, pTable4->GetObjectType());
	pTable4->SetPos({ 2000.f  , 1800.f });

	CUIManager::Get()->MakeBossUI(*pBulletKing);

	__super::Init();
}

void CBossRoom::Update()
{
	__super::Update();
}

void CBossRoom::LateUpdate()
{
	__super::LateUpdate();
}

void CBossRoom::Render(HDC _hDC)
{
	CGenerator::Get()->Render(_hDC);

	__super::Render(_hDC);
}

void CBossRoom::Release()
{
}

void CBossRoom::Enter(CObject* _pPlayer)
{
	CColliderManager::Get()->Reset();

	_pPlayer->SetPos({ 1500.f, 2000.f });

	CMouse::Get()->GetPoint()->SetPos({ _pPlayer->GetPos().fX, _pPlayer->GetPos().fY - 200.f });
	//CMouse::Get()->GetPoint()->SetPos({ (float)CMain::Get()->GetResolution().x / 2, (float)CMain::Get()->GetResolution().y / 2 });
	//CMouse::Get()->GetMouse()->SetPos({ _pPlayer->GetPos().fX, _pPlayer->GetPos().fY - 100.f });
	//CMouse::Get()->GetMouse()->SetPos({ (float)CMain::Get()->GetResolution().x / 2, (float)CMain::Get()->GetResolution().y / 2 });

	CCamera::Get()->SetTarget(CMouse::Get()->GetPoint());
	CCamera::Get()->SetPrevLookPos({ _pPlayer->GetPos().fX, _pPlayer->GetPos().fY - 200.f });

	CBulletKing* pBulletKing = dynamic_cast<CBulletKing*>(CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::ENEMY)[0]);
	pBulletKing->SetTarget(_pPlayer);

	CGenerator::Get()->SetTexture(CResourceManager::Get()->FindTexture(L"BossRoom"));

	SetCollision();
}

void CBossRoom::Exit(CObject* _pPlayer)
{
}

void CBossRoom::SetCollision()
{
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::PLAYER, OBJECT_TYPE::WALL);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::ENEMY, OBJECT_TYPE::WALL);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::INTERACT, OBJECT_TYPE::WALL);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ITEM);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::PROJECTILE_PLAYER, OBJECT_TYPE::WALL);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::PROJECTILE_ENEMY, OBJECT_TYPE::WALL);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ENEMY);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::PLAYER, OBJECT_TYPE::PROJECTILE_ENEMY);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::ENEMY, OBJECT_TYPE::PROJECTILE_PLAYER);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::PLAYER, OBJECT_TYPE::INTERACT);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::ENEMY, OBJECT_TYPE::INTERACT);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::PROJECTILE_PLAYER, OBJECT_TYPE::INTERACT);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::PROJECTILE_ENEMY, OBJECT_TYPE::INTERACT);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::PLAYER, OBJECT_TYPE::BLOW);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::ENEMY, OBJECT_TYPE::BLOW);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::INTERACT, OBJECT_TYPE::BLOW);
}