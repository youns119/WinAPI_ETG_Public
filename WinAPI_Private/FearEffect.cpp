#include "pch.h"
#include "FearEffect.h"

#include "ResourceManager.h"
#include "SoundManager.h"

#include "Animator.h"
#include "Animation.h"
#include "Func.h"

CFearEffect::CFearEffect()
{
}

CFearEffect::~CFearEffect()
{
	Release();
}

void CFearEffect::Init()
{
	SetScale({ 94.f, 94.f });
	SetRenderScale(GetScale());
	SetVolume(0.2f);

	SetEffectType(EFFECT_TYPE::FEAR_EFFECT);

	__super::Init();

	CreateAnimation();

	GetAnimator()->PlayAnimation(L"FearEffect", false);

	CSoundManager::Get()->PlaySound(L"Fear_Effect.wav", CHANNELID::SOUND_EFFECT, GetVolume());
}

void CFearEffect::Update()
{
}

void CFearEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CFearEffect::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CFearEffect::Release()
{
}

void CFearEffect::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"FearEffect", CResourceManager::Get()->FindTexture(L"FearEffect"), Vec2(0, 0), Vec2(300.f, 300.f), Vec2(300.f, 0.f), .05f, 4);
}