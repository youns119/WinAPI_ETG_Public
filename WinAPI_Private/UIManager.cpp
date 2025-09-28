#include "pch.h"
#include "UIManager.h"

#include "ResourceManager.h"
#include "SceneManager.h"

#include "Texture.h"
#include "HP.h"
#include "Fear.h"
#include "Key.h"
#include "Coin.h"
#include "GunBox.h"
#include "Bullet.h"
#include "Magazine.h"
#include "Reload.h"
#include "BossHP.h"
#include "ItemBox.h"
#include "Minimap.h"

CUIManager::CUIManager()
{
}

CUIManager::~CUIManager()
{
	Release();
}

void CUIManager::Init()
{
}

void CUIManager::Update()
{
}

void CUIManager::LateUpdate()
{
}

void CUIManager::Render(HDC _hDC)
{
}

void CUIManager::Release()
{
}

void CUIManager::MakeUI(CObject& _pTarget)
{
	CObject* pHP = new CHP;
	CHP* pTempHP = dynamic_cast<CHP*>(pHP);
	pTempHP->SetTarget(_pTarget);
	pTempHP->SetShow(true);

	CObject* pFear = new CFear;
	CFear* pTempFear = dynamic_cast<CFear*>(pFear);
	pTempFear->SetTarget(_pTarget);
	pTempFear->SetShow(true);

	CObject* pKey = new CKey;
	CKey* pTempKey = dynamic_cast<CKey*>(pKey);
	pTempKey->SetTarget(_pTarget);
	pTempKey->SetShow(true);

	CObject* pCoin = new CCoin;
	CCoin* pTempCoin = dynamic_cast<CCoin*>(pCoin);
	pTempCoin->SetTarget(_pTarget);
	pTempCoin->SetShow(true);

	CObject* pGunBox = new CGunBox;
	CGunBox* pTempGunBox = dynamic_cast<CGunBox*>(pGunBox);
	pTempGunBox->SetTarget(_pTarget);
	pTempGunBox->SetShow(true);
	
	CObject* pBullet = new CBullet;
	CBullet* pTempBullet = dynamic_cast<CBullet*>(pBullet);
	pTempBullet->SetTarget(_pTarget);
	pTempBullet->SetShow(true);

	CObject* pMagazine = new CMagazine;
	CMagazine* pTempMagazine = dynamic_cast<CMagazine*>(pMagazine);
	pTempMagazine->SetTarget(_pTarget);
	pTempMagazine->SetShow(true);

	CObject* pReload = new CReload;
	CReload* pTempReload = dynamic_cast<CReload*>(pReload);
	pTempReload->SetTarget(_pTarget);
	pTempReload->SetShow(false);

	CObject* pItemBox = new CItemBox;
	CItemBox* pTempItemBox = dynamic_cast<CItemBox*>(pItemBox);
	pTempItemBox->SetTarget(_pTarget);
	pTempItemBox->SetShow(true);

	CObject* pMinimap = new CMinimap;
	CMinimap* pTempMinimap = dynamic_cast<CMinimap*>(pMinimap);
	pTempMinimap->SetShow(true);

	CSceneManager::Get()->AddObject(pHP, OBJECT_TYPE::UI);
	CSceneManager::Get()->AddObject(pFear, OBJECT_TYPE::UI);
	CSceneManager::Get()->AddObject(pKey, OBJECT_TYPE::UI);
	CSceneManager::Get()->AddObject(pCoin, OBJECT_TYPE::UI);
	CSceneManager::Get()->AddObject(pGunBox, OBJECT_TYPE::UI);
	CSceneManager::Get()->AddObject(pBullet, OBJECT_TYPE::UI);
	CSceneManager::Get()->AddObject(pMagazine, OBJECT_TYPE::UI);
	CSceneManager::Get()->AddObject(pReload, OBJECT_TYPE::UI);
	CSceneManager::Get()->AddObject(pItemBox, OBJECT_TYPE::UI);
	CSceneManager::Get()->AddObject(pMinimap, OBJECT_TYPE::UI);
}

void CUIManager::MakeBossUI(CObject& _pTarget)
{
	CObject* pBossHP = new CBossHP;
	CBossHP* pTempBossHP = dynamic_cast<CBossHP*>(pBossHP);
	pTempBossHP->SetTarget(_pTarget);
	pTempBossHP->SetShow(true);

	CSceneManager::Get()->AddObject(pBossHP, OBJECT_TYPE::UI);
}

void CUIManager::DeleteBossUI()
{
	vector<CObject*>& vUI = CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::UI);

	for (int i = 0; i < vUI.size(); i++)
	{
		if (dynamic_cast<CUI*>(vUI[i])->GetUIType() == UI_TYPE::BOSSHP)
		{
			dynamic_cast<CUI*>(vUI[i])->SetShow(false);
			break;
		}
	}
}

void CUIManager::DeleteMinimap()
{
	vector<CObject*>& vUI = CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::UI);

	for (int i = 0; i < vUI.size(); i++)
	{
		if (dynamic_cast<CUI*>(vUI[i])->GetUIType() == UI_TYPE::MINIMAP)
		{
			dynamic_cast<CUI*>(vUI[i])->SetShow(false);
			break;
		}
	}
}