#include "pch.h"
#include "Item_Fear.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "Collider.h"
#include "Texture.h"
#include "Player.h"
#include "Func.h"

CItem_Fear::CItem_Fear()
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CItem_Fear::~CItem_Fear()
{
	Release();
}

void CItem_Fear::Init()
{
	SetItemType(ITEM_TYPE::FEAR);
	SetVolume(0.2f);

	SetTexture(CResourceManager::Get()->FindTexture(L"Item_Fear"));

	int iWidth = GetTexture()->GetWidth();
	int iHeight = GetTexture()->GetHeight();

	SetScale({ iWidth, iHeight });

	SetMass(1.f);
	SetFriction(100.f);
	SetMaxVelocity(1000.f);

	__super::Init();
}

void CItem_Fear::Update()
{
}

void CItem_Fear::LateUpdate()
{
	__super::LateUpdate();
}

void CItem_Fear::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CItem_Fear::Release()
{
}

void CItem_Fear::OnCollision(CCollider& _pOther)
{
	CObject::OnCollision(_pOther);

	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOwner);

		pPlayer->SetFearCount(pPlayer->GetFearCount() + 1);

		CSoundManager::Get()->PlaySound(L"Fear_Pickup.wav", CHANNELID::SOUND_INTERACT, GetVolume());

		DeleteObjectEvent(this);
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

void CItem_Fear::OnCollisionEnter(CCollider& _pOther)
{
}

void CItem_Fear::OnCollisionExit(CCollider& _pOther)
{
}