#include "pch.h"
#include "MachineGunEffect.h"

#include "ResourceManager.h"

#include "Animator.h"
#include "Animation.h"
#include "Func.h"

CMachineGunEffect::CMachineGunEffect()
{
}

CMachineGunEffect::~CMachineGunEffect()
{
	Release();
}

void CMachineGunEffect::Init()
{
	SetScale({ 48.f, 48.f });
	SetRenderScale(GetScale());

	SetEffectType(EFFECT_TYPE::BULLET_EFFECT);

	__super::Init();

	CreateAnimation();

	GetAnimator()->PlayAnimation(L"MachineGunEffect", false);
}

void CMachineGunEffect::Update()
{
	if (GetAnimator()->GetCurrAnim()->GetFinish())
		DeleteObjectEvent(this);
}

void CMachineGunEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CMachineGunEffect::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CMachineGunEffect::Release()
{
}

void CMachineGunEffect::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"MachineGunEffect", CResourceManager::Get()->FindTexture(L"MachineGunEffect"), Vec2(0, 0), Vec2(48, 48), Vec2(48, 0), .1f, 7);
}