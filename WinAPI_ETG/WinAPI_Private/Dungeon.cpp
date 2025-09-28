#include "pch.h"
#include "Dungeon.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "ColliderManager.h"
#include "Generator.h"
#include "UIManager.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Camera.h"
#include "Main.h"
#include "SoundManager.h"

#include "Texture.h"
#include "Collider.h"
#include "Player.h"
#include "BulletKin.h"
#include "BulletKing.h"
#include "Item_Gun.h"
#include "Table.h"
#include "Chest.h"
#include "Barrel.h"
#include "Func.h"
#include "Item_HP.h"
#include "Item_Fear.h"

CDungeon::CDungeon()
	: m_fChangeTime(0.f)
	, m_fFadeTime(0.f)
	, m_iTick(0)
	, m_iFadeTick(0)
	, m_bSceneChange(false)
	, m_bFade(false)
	, m_bPrePos(false)
	, m_iShopCount(0)
	, m_pChangeTexture(nullptr)
{
	SetSceneType(SCENE_TYPE::DUNGEON);
}

CDungeon::~CDungeon()
{
	CSceneManager::Get()->SetCurrScene(this);

	Release();
}

void CDungeon::Init()
{
	SetName(L"Dungeon");

	SetVolume(0.001);

	CGenerator::Get()->CreateDungeon();

	SetObjects();

	m_fChangeTime = 2.f;
	m_fFadeTime = 1.f;
	m_pChangeTexture = CResourceManager::Get()->FindTexture(L"CutScene");

	__super::Init();
}

void CDungeon::Update()
{
	__super::Update();

	if (GetVolume() < 0.1f)
	{
		SetVolume(GetVolume() + 0.0001f);

		CSoundManager::Get()->SetChannelVolume(CHANNELID::SOUND_BGM, GetVolume());
	}

	if (CKeyboard::Get()->KeyDown('P'))
	{
		m_iTick = GetTickCount64();
		m_bSceneChange = true;

		CUIManager::Get()->DeleteMinimap();

		CSoundManager::Get()->StopSound(CHANNELID::SOUND_BGM);
		CSoundManager::Get()->PlayBGM(L"BossBGM.wav", CSceneManager::Get()->GetScenes()[(UINT)SCENE_TYPE::BOSSROOM]->GetVolume());
		CSoundManager::Get()->PlaySound(L"BossIntro.wav", CHANNELID::SOUND_INTERFACE, CSceneManager::Get()->GetScenes()[(UINT)SCENE_TYPE::BOSSROOM]->GetVolume());
	}

	if (CKeyboard::Get()->KeyDown('T'))
	{
		CCamera::Get()->FadeOut(1.f);
		CSoundManager::Get()->PlaySound(L"Teleportdepart.wav", CHANNELID::SOUND_EFFECT, 0.5f);

		m_iFadeTick = GetTickCount64();

		m_bFade = true;

		if (!m_bPrePos)
		{
			m_bPrePos = true;

			m_vPrePos = CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0]->GetPos();
		}
		else
		{
			m_bPrePos = false;
		}
	}
}

void CDungeon::LateUpdate()
{
	__super::LateUpdate();

	if (m_bSceneChange)
		if (m_fChangeTime * 1000 < GetTickCount64() - m_iTick)
		{
			ChangeScene(SCENE_TYPE::BOSSROOM, CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0]);
		}

	if (m_bFade && m_fFadeTime * 1000.f <= GetTickCount64() - m_iFadeTick)
	{
		if (m_bPrePos)
		{
			CSoundManager::Get()->PlaySound(L"Teleportarrive.wav", CHANNELID::SOUND_EFFECT, 0.5f);

			CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0]->SetPos({ 4130.f, 4600.f });
			CCamera::Get()->SetLookAtPos(CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0]->GetPos());
			CCamera::Get()->SetPrevLookPos(CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0]->GetPos());

			CCamera::Get()->FadeIn(1.f);

			m_bFade = false;
		}
		else
		{
			CSoundManager::Get()->PlaySound(L"Teleportarrive.wav", CHANNELID::SOUND_EFFECT, 0.5f);

			CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0]->SetPos(m_vPrePos);
			CCamera::Get()->SetLookAtPos(CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0]->GetPos());
			CCamera::Get()->SetPrevLookPos(CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0]->GetPos());

			CCamera::Get()->FadeIn(1.f);

			m_bFade = false;
		}

	}
}

void CDungeon::Render(HDC _hDC)
{
	if (m_bSceneChange)
	{
		BitBlt
		(
			_hDC,
			0, 0,
			CMain::Get()->GetResolution().x, 
			CMain::Get()->GetResolution().y,
			m_pChangeTexture->GetHDC(),
			0, 0,
			SRCCOPY
		);

		return;
	}

	CGenerator::Get()->Render(_hDC);

	__super::Render(_hDC);
}

void CDungeon::Release()
{
}

void CDungeon::Enter(CObject* _pPlayer)
{
	CColliderManager::Get()->Reset();

	CCamera::Get()->SetTarget(CMouse::Get()->GetPoint());
	CCamera::Get()->SetPrevLookPos(CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0]->GetPos());

	CGenerator::Get()->SetTexture(CResourceManager::Get()->FindTexture(L"MapTemplate2"));

	CSoundManager::Get()->PlayBGM(L"BGM.wav", GetVolume());

	SetCollision();
}

void CDungeon::Exit(CObject* _pPlayer)
{
}

void CDungeon::SetObjects()
{
	RoomStart();
	RoomShop();
	RoomChest();
	Room1();
	Room2();
	Room3();
	Room4();
}

void CDungeon::RoomStart()
{
	Vec2 vPos{};

	vPos = CGenerator::Get()->GetRoomPos(0);

	// Player
	CObject* pPlayer = new CPlayer;
	CSceneManager::Get()->AddObject(pPlayer, pPlayer->GetObjectType());
	pPlayer->SetPos(vPos);

	// Mouse
	CMouse::Get()->SetTexture(CResourceManager::Get()->FindTexture(L"Crosshair"));
	CMouse::Get()->SetTarget(pPlayer);

	// UI
	CUIManager::Get()->MakeUI(*pPlayer);

	// Chest
	CObject* pChest1 = new CChest(GUN_TYPE::REVOLVER);
	//CObject* pChest2 = new CChest(GUN_TYPE::MACHINEGUN);
	CObject* pChest2 = new CChest(ITEM_TYPE::MEDIKIT);
	CSceneManager::Get()->AddObject(pChest1, pChest1->GetObjectType());
	CSceneManager::Get()->AddObject(pChest2, pChest2->GetObjectType());
	pChest1->SetPos({vPos.fX - 100.f, vPos.fY + 100.f});
	pChest2->SetPos({vPos.fX + 100.f, vPos.fY + 100.f});

	CObject* pTable1 = new CTable;
	CSceneManager::Get()->AddObject(pTable1, pTable1->GetObjectType());
	pTable1->SetPos({ vPos.fX, vPos.fY + 300.f });
}

void CDungeon::RoomShop()
{
	CObject* pItem1 = new CItem_Gun(GUN_TYPE::HOMINGGUN);
	dynamic_cast<CItem_Gun*>(pItem1)->SetPrice(20.f);
	SetShop(pItem1);

	CObject* pItem2 = new CItem_Gun(GUN_TYPE::REFLECTGUN);
	dynamic_cast<CItem_Gun*>(pItem2)->SetPrice(15.f);
	SetShop(pItem2);

	CObject* pItem3 = new CItem_Gun(GUN_TYPE::SHOTGUN);
	dynamic_cast<CItem_Gun*>(pItem3)->SetPrice(10.f);
	SetShop(pItem3);

	CObject* pItem4 = new CItem_Gun(GUN_TYPE::MACHINEGUN);
	dynamic_cast<CItem_Gun*>(pItem4)->SetPrice(15.f);
	SetShop(pItem4);

	//CObject* pItem5 = new CItem_Gun(GUN_TYPE::MACHINEGUN);
	//dynamic_cast<CItem_Gun*>(pItem5)->SetPrice(15.f);
	//SetShop(pItem5);
}

void CDungeon::RoomChest()
{
	Vec2 vPos{};

	vPos = CGenerator::Get()->GetRoomPos(7);

	// Chest
	CObject* pChest = new CChest(GUN_TYPE::MACHINEGUN);
	CSceneManager::Get()->AddObject(pChest, pChest->GetObjectType());
	pChest->SetPos({ vPos.fX, vPos.fY });
}

void CDungeon::Room1()
{
	Vec2 vPos{};

	vPos = CGenerator::Get()->GetRoomPos(1);

	// Table
	CObject* pTable1 = new CTable;
	CSceneManager::Get()->AddObject(pTable1, pTable1->GetObjectType());
	pTable1->SetPos({ vPos.fX - 150.f , vPos.fY - 150.f });

	CObject* pTable2 = new CTable;
	CSceneManager::Get()->AddObject(pTable2, pTable2->GetObjectType());
	pTable2->SetPos({ vPos.fX + 300.f , vPos.fY - 150.f });

	CObject* pTable3 = new CTable;
	CSceneManager::Get()->AddObject(pTable3, pTable3->GetObjectType());
	pTable3->SetPos({ vPos.fX - 150.f , vPos.fY + 250.f });

	CObject* pTable4 = new CTable;
	CSceneManager::Get()->AddObject(pTable4, pTable4->GetObjectType());
	pTable4->SetPos({ vPos.fX + 300.f , vPos.fY + 250.f });

	// Barrel
	CObject* pBarrel1 = new CBarrel;
	CSceneManager::Get()->AddObject(pBarrel1, pBarrel1->GetObjectType());
	pBarrel1->SetPos({ vPos.fX - 100.f , vPos.fY + 20.f });

	CObject* pBarrel2 = new CBarrel;
	CSceneManager::Get()->AddObject(pBarrel2, pBarrel2->GetObjectType());
	pBarrel2->SetPos({ vPos.fX + 250.f , vPos.fY + 20.f});

	CObject* pChest1 = new CChest(GUN_TYPE::SHOTGUN);
	CSceneManager::Get()->AddObject(pChest1, pChest1->GetObjectType());
	pChest1->SetPos({ vPos.fX - 300.f, vPos.fY + 350.f });
}

void CDungeon::Room2()
{
	Vec2 vPos{};

	vPos = CGenerator::Get()->GetRoomPos(2);

	// Table
	CObject* pTable1 = new CTable;
	CSceneManager::Get()->AddObject(pTable1, pTable1->GetObjectType());
	pTable1->SetPos({ vPos.fX - 150.f , vPos.fY - 150.f });

	CObject* pTable2 = new CTable;
	CSceneManager::Get()->AddObject(pTable2, pTable2->GetObjectType());
	pTable2->SetPos({ vPos.fX + 150.f , vPos.fY - 150.f });

	// Barrel
	CObject* pBarrel1 = new CBarrel;
	CSceneManager::Get()->AddObject(pBarrel1, pBarrel1->GetObjectType());
	pBarrel1->SetPos({ vPos.fX - 150.f , vPos.fY + 150.f });

	CObject* pBarrel2 = new CBarrel;
	CSceneManager::Get()->AddObject(pBarrel2, pBarrel2->GetObjectType());
	pBarrel2->SetPos({ vPos.fX + 150.f , vPos.fY + 150.f });
}

void CDungeon::Room3()
{
	Vec2 vPos{};

	vPos = CGenerator::Get()->GetRoomPos(3);

	// Table
	CObject* pTable1 = new CTable;
	CSceneManager::Get()->AddObject(pTable1, pTable1->GetObjectType());
	pTable1->SetPos({ vPos.fX - 150.f , vPos.fY - 100.f });

	CObject* pTable2 = new CTable;
	CSceneManager::Get()->AddObject(pTable2, pTable2->GetObjectType());
	pTable2->SetPos({ vPos.fX + 150.f , vPos.fY - 100.f });

	CObject* pTable3 = new CTable;
	CSceneManager::Get()->AddObject(pTable3, pTable2->GetObjectType());
	pTable3->SetPos({ vPos.fX, vPos.fY + 400.f });

	// Barrel
	CObject* pBarrel1 = new CBarrel;
	CSceneManager::Get()->AddObject(pBarrel1, pBarrel1->GetObjectType());
	pBarrel1->SetPos({ vPos.fX - 200.f , vPos.fY + 250.f });

	CObject* pBarrel2 = new CBarrel;
	CSceneManager::Get()->AddObject(pBarrel2, pBarrel2->GetObjectType());
	pBarrel2->SetPos({ vPos.fX + 200.f , vPos.fY + 250.f });
}

void CDungeon::Room4()
{
	Vec2 vPos{};

	vPos = CGenerator::Get()->GetRoomPos(4);

	// Table
	CObject* pTable1 = new CTable;
	CSceneManager::Get()->AddObject(pTable1, pTable1->GetObjectType());
	pTable1->SetPos({ vPos.fX - 100.f , vPos.fY - 100.f });

	CObject* pTable2 = new CTable;
	CSceneManager::Get()->AddObject(pTable2, pTable2->GetObjectType());
	pTable2->SetPos({ vPos.fX + 100.f , vPos.fY - 100.f });

	CObject* pTable3 = new CTable;
	CSceneManager::Get()->AddObject(pTable3, pTable3->GetObjectType());
	pTable3->SetPos({ vPos.fX - 100.f , vPos.fY + 100.f });

	CObject* pTable4 = new CTable;
	CSceneManager::Get()->AddObject(pTable4, pTable4->GetObjectType());
	pTable4->SetPos({ vPos.fX + 100.f , vPos.fY + 100.f });

	// Barrel
	CObject* pBarrel1 = new CBarrel;
	CSceneManager::Get()->AddObject(pBarrel1, pBarrel1->GetObjectType());
	pBarrel1->SetPos({ vPos.fX - 300.f , vPos.fY - 300.f });

	CObject* pBarrel2 = new CBarrel;
	CSceneManager::Get()->AddObject(pBarrel2, pBarrel2->GetObjectType());
	pBarrel2->SetPos({ vPos.fX + 300.f , vPos.fY - 300.f });

	CObject* pBarrel3 = new CBarrel;
	CSceneManager::Get()->AddObject(pBarrel3, pBarrel3->GetObjectType());
	pBarrel3->SetPos({ vPos.fX - 300.f , vPos.fY + 300.f });

	CObject* pBarrel4 = new CBarrel;
	CSceneManager::Get()->AddObject(pBarrel4, pBarrel4->GetObjectType());
	pBarrel4->SetPos({ vPos.fX + 300.f , vPos.fY + 300.f });
}

void CDungeon::SetShop(CObject* _pObject)
{
	Vec2 vPos = CGenerator::Get()->GetRoomPos(5);

	if (m_iShopCount == 0)
	{
		_pObject->SetPos({ vPos.fX - 180.f, vPos.fY + 150.f });
		dynamic_cast<CItem*>(_pObject)->SetColOffset({ 0.f, 100.f });
		CSceneManager::Get()->AddObject(_pObject, _pObject->GetObjectType());
	}
	else if (m_iShopCount == 1)
	{
		_pObject->SetPos({ vPos.fX - 80.f, vPos.fY + 150.f });
		dynamic_cast<CItem*>(_pObject)->SetColOffset({ 0.f, 100.f });
		CSceneManager::Get()->AddObject(_pObject, _pObject->GetObjectType());
	}
	else if (m_iShopCount == 2)
	{
		_pObject->SetPos({ vPos.fX + 90.f, vPos.fY + 150.f });
		dynamic_cast<CItem*>(_pObject)->SetColOffset({ 0.f, 100.f });
		CSceneManager::Get()->AddObject(_pObject, _pObject->GetObjectType());
	}
	else if (m_iShopCount == 3)
	{
		_pObject->SetPos({ vPos.fX + 190.f, vPos.fY + 150.f });
		dynamic_cast<CItem*>(_pObject)->SetColOffset({ 0.f, 100.f });
		CSceneManager::Get()->AddObject(_pObject, _pObject->GetObjectType());
	}
	else if (m_iShopCount == 4)
	{
		_pObject->SetPos({ vPos.fX + 260.f, vPos.fY });
		dynamic_cast<CItem*>(_pObject)->SetColOffset({ 100.f, 0.f });
		CSceneManager::Get()->AddObject(_pObject, _pObject->GetObjectType());
	}
	else return;

	m_iShopCount++;
}

void CDungeon::SetCollision()
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
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::INTERACT, OBJECT_TYPE::INTERACT);
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::PLAYER, OBJECT_TYPE::EVENT_TRIGGER);
}