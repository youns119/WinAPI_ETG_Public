#include "pch.h"
#include "EnemyGen.h"

#include "SceneManager.h"
#include "ResourceManager.h"

#include "Collider.h"
#include "BulletKin.h"
#include "ShotGunKin.h"
#include "Spawn.h"
#include "SpawnEffect.h"
#include "Func.h"
#include "Item_Coin.h"
#include "Medikit.h"
#include "Player.h"

CEnemyGen::CEnemyGen()
	: m_iCount(0)
	, m_bCollided(false)
	, m_bGenerated(false)
	, m_bSafe(true)
	, m_eEnemyGenType(ENEMY_GEN_TYPE::END)
{
	SetEventTriggerType(EVENT_TRIGGER_TYPE::ENEMY_GEN);
}

CEnemyGen::CEnemyGen(ENEMY_GEN_TYPE _eEnemyGenType)
	: m_iCount(0)
	, m_bCollided(false)
	, m_bGenerated(false)
	, m_bSafe(true)
	, m_eEnemyGenType(_eEnemyGenType)
{
	SetEventTriggerType(EVENT_TRIGGER_TYPE::ENEMY_GEN);
}

CEnemyGen::~CEnemyGen()
{
	Release();
}

void CEnemyGen::Init()
{
	__super::Init();
}

void CEnemyGen::Update()
{
	if (m_bCollided)
	{
		if (EnemyCheck())
		{
			switch (m_eEnemyGenType)
			{
			case ENEMY_GEN_TYPE::ROOM1:
				CreateEnemy1();
				break;
			case ENEMY_GEN_TYPE::ROOM2:
				break;
			case ENEMY_GEN_TYPE::ROOM3:
				break;
			case ENEMY_GEN_TYPE::ROOM4:
				break;
			default:
				break;
			}
		}
	}
}

void CEnemyGen::LateUpdate()
{
	__super::LateUpdate();

	if (m_bCollided && !m_qSpawn.empty())
	{
		while (!m_qSpawn.empty())
		{
			CSpawn* pSpawn = m_qSpawn.front();
			
			CreateObjectEvent(pSpawn, OBJECT_TYPE::SPAWN);
			m_qSpawn.pop();
		}
	}
}

void CEnemyGen::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CEnemyGen::Release()
{
}

void CEnemyGen::CreateEnemy1()
{
	Vec2 vPos = GetPos();

	if (m_iCount == 0)
	{
		CSpawn* pSpawn1 = new CSpawn(ENEMY_TYPE::BULLETKIN, { GetPos().fX - 200.f, GetPos().fY - 200.f });
		pSpawn1->SetTimer(0.f);
		m_qSpawn.push(pSpawn1);

		CSpawn* pSpawn2 = new CSpawn(ENEMY_TYPE::BULLETKIN, { GetPos().fX + 200.f, GetPos().fY - 200.f });
		pSpawn2->SetTimer(0.6f);
		m_qSpawn.push(pSpawn2);

		CSpawn* pSpawn3 = new CSpawn(ENEMY_TYPE::BULLETKIN, { GetPos().fX - 200.f, GetPos().fY + 200.f });
		pSpawn3->SetTimer(0.3f);
		m_qSpawn.push(pSpawn3);

		CSpawn* pSpawn4 = new CSpawn(ENEMY_TYPE::SHOTGUNKIN, { GetPos().fX + 200.f, GetPos().fY + 200.f });
		pSpawn4->SetTimer(0.9f);
		m_qSpawn.push(pSpawn4);
	}
	else if (m_iCount == 1)
	{
		CSpawn* pSpawn1 = new CSpawn(ENEMY_TYPE::SHOTGUNKIN, { GetPos().fX, GetPos().fY });
		pSpawn1->SetTimer(0.f);
		m_qSpawn.push(pSpawn1);

		CSpawn* pSpawn2 = new CSpawn(ENEMY_TYPE::BULLETKIN, { GetPos().fX + 200.f, GetPos().fY - 100.f });
		pSpawn2->SetTimer(0.3f);
		m_qSpawn.push(pSpawn2);

		CSpawn* pSpawn3 = new CSpawn(ENEMY_TYPE::BULLETKIN, { GetPos().fX - 200.f, GetPos().fY + 200.f });
		pSpawn3->SetTimer(0.6f);
		m_qSpawn.push(pSpawn3);

		CSpawn* pSpawn4 = new CSpawn(ENEMY_TYPE::SHOTGUNKIN, { GetPos().fX - 200.f, GetPos().fY - 50.f });
		pSpawn4->SetTimer(0.9f);
		m_qSpawn.push(pSpawn4);
	}
	else if (m_iCount == 2)
	{
		CSpawn* pSpawn1 = new CSpawn(ENEMY_TYPE::BULLETKIN, { GetPos().fX - 50.f, GetPos().fY - 50.f });
		pSpawn1->SetTimer(0.f);
		m_qSpawn.push(pSpawn1);

		CSpawn* pSpawn2 = new CSpawn(ENEMY_TYPE::BULLETKIN, { GetPos().fX + 100.f, GetPos().fY + 50.f });
		pSpawn2->SetTimer(0.3f);
		m_qSpawn.push(pSpawn2);

		CSpawn* pSpawn3 = new CSpawn(ENEMY_TYPE::SHOTGUNKIN, { GetPos().fX - 200.f, GetPos().fY + 200.f });
		pSpawn3->SetTimer(0.6f);
		m_qSpawn.push(pSpawn3);

		CSpawn* pSpawn4 = new CSpawn(ENEMY_TYPE::SHOTGUNKIN, { GetPos().fX, GetPos().fY + 200.f });
		pSpawn4->SetTimer(0.9f);
		m_qSpawn.push(pSpawn4);
	}

	if (m_iCount == 3)
	{
		m_bSafe = true;

		CItem* pItem = dynamic_cast<CPlayer*>(CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0])->GetCurrItem();

		if (pItem)
		{
			switch (pItem->GetItemType())
			{
			case ITEM_TYPE::MEDIKIT:
			{
				CMedikit* pMedikit = dynamic_cast<CMedikit*>(pItem);

				pMedikit->SetUsed(false);
				pMedikit->SetTexture(CResourceManager::Get()->FindTexture(L"Medikit"));

				break;
			}
			}
		}

		DeleteObjectEvent(this);
	}

	m_iCount++;
}

void CEnemyGen::CreateEnemy2()
{
}

void CEnemyGen::CreateEnemy3()
{
}

void CEnemyGen::CreateEnemy4()
{
}

bool CEnemyGen::EnemyCheck()
{
	vector<CObject*> vEnemy = CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::ENEMY);
	vector<CObject*> vSpawn = CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::SPAWN);

	if (!vSpawn.empty()) return false;

	for (int i = 0; i < vEnemy.size(); i++)
		if (dynamic_cast<CEnemy*>(vEnemy[i])->GetCurrHP() > 0)
			return false;

	return true;
}

void CEnemyGen::OnCollision(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER && !m_bGenerated)
	{
		m_bCollided = true;
		m_bGenerated = true;
		m_bSafe = false;
	}
}

void CEnemyGen::OnCollisionEnter(CCollider& _pOther)
{
}

void CEnemyGen::OnCollisionExit(CCollider& _pOther)
{
}