#include "pch.h"
#include "Item_HP.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "Collider.h"
#include "Texture.h"
#include "Player.h"
#include "Func.h"

CItem_HP::CItem_HP()
	: m_iType(0)
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CItem_HP::CItem_HP(int _iType)
	: m_iType(_iType)
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CItem_HP::~CItem_HP()
{
	Release();
}

void CItem_HP::Init()
{
	SetItemType(ITEM_TYPE::HP);
	SetVolume(0.1f);

	if (m_iType == 0)
		SetTexture(CResourceManager::Get()->FindTexture(L"Item_HPFull"));
	else
		SetTexture(CResourceManager::Get()->FindTexture(L"Item_HPHalf"));

	int iWidth = GetTexture()->GetWidth();
	int iHeight = GetTexture()->GetHeight();

	SetScale({ iWidth, iHeight });

	SetMass(1.f);
	SetFriction(100.f);
	SetMaxVelocity(1000.f);

	__super::Init();
}

void CItem_HP::Update()
{
}

void CItem_HP::LateUpdate()
{
	__super::LateUpdate();
}

void CItem_HP::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CItem_HP::Release()
{
}

void CItem_HP::OnCollision(CCollider& _pOther)
{
	CObject::OnCollision(_pOther);

	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOwner);

		if (pPlayer->GetCurrHP() < pPlayer->GetMaxHP())
		{
			if(m_iType == 0)
				pPlayer->SetCurrHP(pPlayer->GetCurrHP() + 2);
			else
				pPlayer->SetCurrHP(pPlayer->GetCurrHP() + 1);

			if (pPlayer->GetCurrHP() > pPlayer->GetMaxHP())
				pPlayer->SetCurrHP(pPlayer->GetMaxHP());

			CSoundManager::Get()->PlaySound(L"HP_Pickup.wav", CHANNELID::SOUND_INTERACT, GetVolume());

			DeleteObjectEvent(this);
		}
		else
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

void CItem_HP::OnCollisionEnter(CCollider& _pOther)
{
}

void CItem_HP::OnCollisionExit(CCollider& _pOther)
{
}