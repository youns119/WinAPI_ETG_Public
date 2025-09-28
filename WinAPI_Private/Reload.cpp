#include "pch.h"
#include "Reload.h"

#include "ResourceManager.h"

#include "Texture.h"
#include "Player.h"
#include "Animator.h"
#include "Animation.h"
#include "Gun.h"

CReload::CReload()
	: m_fSpeed(0.f)
	, m_pCurrGun(nullptr)
{
	SetRenderType(RENDER_TYPE::RENDER_UI);
}

CReload::~CReload()
{
	Release();
}

void CReload::Init()
{
	SetUIType(UI_TYPE::RELOAD);

	CreateAnimator();
	SetAnimation();
}

void CReload::Update()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetTarget());

	CGun* pGun = dynamic_cast<CGun*>(pPlayer->GetCurrGun());

	if (pGun != m_pCurrGun)
		SetAnimation();

	SetPos({ GetTarget()->GetPos().fX, GetTarget()->GetPos().fY - 45.f });

	if (pPlayer->GetReload())
	{
		SetShow(true);
		GetAnimator()->PlayAnimation(L"Reload", false);
	}
}

void CReload::LateUpdate()
{
	__super::LateUpdate();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetTarget());

	if (GetAnimator()->GetCurrAnim())
	{
		if (GetAnimator()->GetCurrAnim()->GetFinish())
		{
			if (pPlayer->GetReload())
			{
				SetShow(false);
				pPlayer->SetReload(false);

				if (pPlayer->GetCurrGun()->GetCurrMax() < pPlayer->GetCurrGun()->GetMag())
					pPlayer->GetCurrGun()->SetCurrMag(pPlayer->GetCurrGun()->GetCurrMax());
				else
					pPlayer->GetCurrGun()->SetCurrMag(pPlayer->GetCurrGun()->GetMag());
			}
		}
	}
}

void CReload::Render(HDC _hDC)
{
	if (!GetShow()) return;

	__super::Render(_hDC);
}

void CReload::Release()
{
}

void CReload::SetAnimation()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetTarget());

	CGun* pGun = dynamic_cast<CGun*>(pPlayer->GetCurrGun());
	m_pCurrGun = pGun;

	if (m_pCurrGun)
	{
		float fReload = pGun->GetReload();
		float fSpeed = fReload / 27;

		GetAnimator()->CreateAnimation(L"Reload", CResourceManager::Get()->FindTexture(L"Reload"), Vec2(0, 0), Vec2(68, 10), Vec2(0, 10), fSpeed, 27);
	}
	else
		GetAnimator()->CreateAnimation(L"Reload", CResourceManager::Get()->FindTexture(L"Reload"), Vec2(0, 0), Vec2(68, 10), Vec2(0, 10), 0.1f, 27);
}