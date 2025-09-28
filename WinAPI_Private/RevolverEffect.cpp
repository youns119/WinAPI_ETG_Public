#include "pch.h"
#include "RevolverEffect.h"

#include "ResourceManager.h"

#include "Animator.h"
#include "Animation.h"
#include "Func.h"

CRevolverEffect::CRevolverEffect()
{
}

CRevolverEffect::~CRevolverEffect()
{
	Release();
}

void CRevolverEffect::Init()
{
	SetScale({ 36.f, 36.f });
	SetRenderScale(GetScale());

	SetEffectType(EFFECT_TYPE::BULLET_EFFECT);

	__super::Init();

	CreateAnimation();

	GetAnimator()->PlayAnimation(L"RevolverEffect", false);
}

void CRevolverEffect::Update()
{
	if (GetAnimator()->GetCurrAnim()->GetFinish())
		DeleteObjectEvent(this);
}

void CRevolverEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CRevolverEffect::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CRevolverEffect::Release()
{
}

void CRevolverEffect::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"RevolverEffect", CResourceManager::Get()->FindTexture(L"RevolverEffect"), Vec2(0, 0), Vec2(36, 36), Vec2(36, 0), .1f, 7);
}