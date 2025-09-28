#include "pch.h"
#include "Item_Key.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "Collider.h"
#include "Texture.h"
#include "Player.h"
#include "Func.h"

CItem_Key::CItem_Key()
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CItem_Key::~CItem_Key()
{
	Release();
}

void CItem_Key::Init()
{
	SetItemType(ITEM_TYPE::KEY);
	SetVolume(0.1f);

	SetTexture(CResourceManager::Get()->FindTexture(L"Item_Key"));

	int iWidth = GetTexture()->GetWidth();
	int iHeight = GetTexture()->GetHeight();

	SetScale({ iWidth, iHeight });

	SetMass(1.f);
	SetFriction(100.f);
	SetMaxVelocity(1000.f);

	__super::Init();
}

void CItem_Key::Update()
{
}

void CItem_Key::LateUpdate()
{
	__super::LateUpdate();
}

void CItem_Key::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CItem_Key::Release()
{
}

void CItem_Key::OnCollision(CCollider& _pOther)
{
	CObject::OnCollision(_pOther);

	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pOwner);

		pPlayer->SetKeyCount(pPlayer->GetKeyCount() + 1);

		CSoundManager::Get()->PlaySound(L"Key_Pickup.wav", CHANNELID::SOUND_INTERACT, GetVolume());

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

void CItem_Key::OnCollisionEnter(CCollider& _pOther)
{
}

void CItem_Key::OnCollisionExit(CCollider& _pOther)
{
}
