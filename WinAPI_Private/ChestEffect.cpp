#include "pch.h"
#include "ChestEffect.h"

#include "ResourceManager.h"

#include "Animator.h"
#include "Animation.h"
#include "Func.h"

CChestEffect::CChestEffect()
{
}

CChestEffect::~CChestEffect()
{
	Release();
}

void CChestEffect::Init()
{
	SetScale({ 108.f, 108.f });
	SetRenderScale(GetScale());

	SetEffectType(EFFECT_TYPE::INTERACT_EFFECT);

	__super::Init();

	CreateAnimation();

	GetAnimator()->PlayAnimation(L"ChestEffect", false);
}

void CChestEffect::Update()
{
}

void CChestEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CChestEffect::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CChestEffect::Release()
{
}

void CChestEffect::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"ChestEffect", CResourceManager::Get()->FindTexture(L"ChestEffect"), Vec2(0, 0), Vec2(108, 108), Vec2(108, 0), .2f, 3);
}