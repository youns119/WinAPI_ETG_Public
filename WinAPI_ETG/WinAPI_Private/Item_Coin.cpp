#include "pch.h"
#include "Item_Coin.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "Timer.h"
#include "SoundManager.h"

#include "Collider.h"
#include "Texture.h"
#include "Player.h"
#include "Func.h"
#include "Physics.h"
#include "EnemyGen.h"

CItem_Coin::CItem_Coin()
	: m_bFollow(false)
	, m_bCollide(true)
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CItem_Coin::~CItem_Coin()
{
	Release();
}

void CItem_Coin::Init()
{
	SetItemType(ITEM_TYPE::COIN);
	SetVolume(0.1f);

	SetTexture(CResourceManager::Get()->FindTexture(L"Item_Coin"));

	int iWidth = GetTexture()->GetWidth();
	int iHeight = GetTexture()->GetHeight();

	SetScale({ iWidth, iHeight });

	SetMass(1.f);
	SetFriction(100.f);
	SetMaxVelocity(1000.f);

	__super::Init();
}

void CItem_Coin::Update()
{
	if (m_bFollow)
	{
		if (!m_bCollide)
		{
			m_bCollide = false;

			CSceneManager::Get()->ChangeRender(this, OBJECT_TYPE::ITEM, RENDER_TYPE::RENDER_EFFECT);
		}

		Follow();
	}
}

void CItem_Coin::LateUpdate()
{
	__super::LateUpdate();

	if(!m_bFollow)
		if (FollowCheck())
		{
			m_bFollow = true;
		}
}

void CItem_Coin::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CItem_Coin::Release()
{
}

bool CItem_Coin::FollowCheck()
{
	vector<CObject*>& vTrigger = CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::EVENT_TRIGGER);

	for (int i = 0; i < vTrigger.size(); i++)
		if (dynamic_cast<CEventTrigger*>(vTrigger[i])->GetEventTriggerType() == EVENT_TRIGGER_TYPE::ENEMY_GEN)
			if (!dynamic_cast<CEnemyGen*>(vTrigger[i])->GetSafe())
				return false;

	return true;
}

void CItem_Coin::Follow()
{
	CObject* pPlayer = CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0];
	
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vNorm = (vPlayerPos - GetPos()).Normalize();

	SetPos(GetPos() + vNorm * 500.f * CTimer::Get()->GetDelta());
}

void CItem_Coin::OnCollision(CCollider& _pOther)
{
	CObject::OnCollision(_pOther);

	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOwner);

		pPlayer->SetCoinCount(pPlayer->GetCoinCount() + 1);

		CSoundManager::Get()->PlaySound(L"Coin_Pickup.wav", CHANNELID::SOUND_INTERACT, GetVolume());

		DeleteObjectEvent(this);
	}

	if (!m_bCollide)
		return;

	if (pOwner->GetObjectType() == OBJECT_TYPE::INTERACT)
	{
		float fWidth = fabsf(GetCollider()->GetFinalPos().fX - _pOther.GetFinalPos().fX);
		float fHeight = fabsf(GetCollider()->GetFinalPos().fY - _pOther.GetFinalPos().fY);

		float fRadiusX = (GetCollider()->GetScale().fX + _pOther.GetScale().fX) * 0.5f;
		float fRadiusY = (GetCollider()->GetScale().fY + _pOther.GetScale().fY) * 0.5f;

		fWidth = fRadiusX - fWidth;
		fHeight = fRadiusY - fHeight;

		if (fWidth > fHeight)
		{
			if (GetCollider()->GetFinalPos().fY < _pOther.GetFinalPos().fY)
				SetPos(Vec2(GetPos().fX, GetPos().fY - fHeight - 1.f));
			else
				SetPos(Vec2(GetPos().fX, GetPos().fY + fHeight + 1.f));
		}
		else
		{
			if (GetCollider()->GetFinalPos().fX < _pOther.GetFinalPos().fX)
				SetPos(Vec2(GetPos().fX - fWidth - 1.f, GetPos().fY));
			else
				SetPos(Vec2(GetPos().fX + fWidth + 1.f, GetPos().fY));
		}
	}
}

void CItem_Coin::OnCollisionEnter(CCollider& _pOther)
{
}

void CItem_Coin::OnCollisionExit(CCollider& _pOther)
{
}