#include "pch.h"
#include "Medikit.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "Collider.h"
#include "Texture.h"
#include "Player.h"
#include "Func.h"

CMedikit::CMedikit()
	: m_bUsed(false)
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CMedikit::~CMedikit()
{
	Release();
}

void CMedikit::Init()
{
	SetItemType(ITEM_TYPE::MEDIKIT);
	SetVolume(0.2f);

	SetTexture(CResourceManager::Get()->FindTexture(L"Medikit"));

	int iWidth = GetTexture()->GetWidth();
	int iHeight = GetTexture()->GetHeight();

	SetScale({ iWidth, iHeight });

	SetMass(1.f);
	SetFriction(5000.f);
	SetMaxVelocity(1000.f);

	__super::Init();
}

void CMedikit::Update()
{
}

void CMedikit::LateUpdate()
{
	__super::LateUpdate();
}

void CMedikit::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CMedikit::Release()
{
}

void CMedikit::Use()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_pTarget);

	pPlayer->SetCurrHP(pPlayer->GetCurrHP() + 2);

	if (pPlayer->GetCurrHP() > pPlayer->GetMaxHP())
		pPlayer->SetCurrHP(pPlayer->GetMaxHP());

	SetTexture(CResourceManager::Get()->FindTexture(L"Medikit_Used"));
	CSoundManager::Get()->PlaySound(L"Medikit.wav", CHANNELID::SOUND_EFFECT, GetVolume());

	m_bUsed = true;
}

void CMedikit::OnCollision(CCollider& _pOther)
{
	CObject::OnCollision(_pOther);

	CObject* pOwner = _pOther.GetOwner();

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

void CMedikit::OnCollisionEnter(CCollider& _pOther)
{
	CItem::OnCollisionEnter(_pOther);

	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		SetTexture(CResourceManager::Get()->FindTexture(L"Medikit_Alt"));

		int iWidth = GetTexture()->GetWidth();
		int iHeight = GetTexture()->GetHeight();

		SetScale({ iWidth, iHeight });

		GetCollider()->SetScale({ GetScale().fX, GetScale().fY });
	}
}

void CMedikit::OnCollisionExit(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		SetTexture(CResourceManager::Get()->FindTexture(L"Medikit"));

		int iWidth = GetTexture()->GetWidth();
		int iHeight = GetTexture()->GetHeight();

		SetScale({ iWidth, iHeight });

		GetCollider()->SetScale({ GetScale().fX, GetScale().fY });
	}
}