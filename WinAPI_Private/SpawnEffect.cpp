#include "pch.h"
#include "SpawnEffect.h"

#include "ResourceManager.h"
#include "SoundManager.h"

#include "Animator.h"
#include "Animation.h"
#include "Func.h"

CSpawnEffect::CSpawnEffect()
{
}

CSpawnEffect::~CSpawnEffect()
{
	Release();
}

void CSpawnEffect::Init()
{
	SetScale({ 80.f, 80.f });
	SetRenderScale(GetScale());
	SetVolume(0.2f);

	SetEffectType(EFFECT_TYPE::SPAWN_EFFECT);

	__super::Init();

	CreateAnimation();

	GetAnimator()->PlayAnimation(L"SpawnEffect", false);

	CSoundManager::Get()->PlaySound(L"Spawn_Effect.wav", CHANNELID::SOUND_EFFECT, GetVolume());
}

void CSpawnEffect::Update()
{
}

void CSpawnEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CSpawnEffect::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CSpawnEffect::Release()
{
}

void CSpawnEffect::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"SpawnEffect", CResourceManager::Get()->FindTexture(L"SpawnEffect"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 10);
}