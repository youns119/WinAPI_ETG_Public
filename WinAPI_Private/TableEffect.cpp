#include "pch.h"
#include "TableEffect.h"

#include "ResourceManager.h"

#include "Animator.h"
#include "Animation.h"
#include "Func.h"

CTableEffect::CTableEffect()
{
}

CTableEffect::~CTableEffect()
{
	Release();
}

void CTableEffect::Init()
{
	SetScale({ 144.f, 144.f });
	SetRenderScale(GetScale());

	SetEffectType(EFFECT_TYPE::INTERACT_EFFECT);

	__super::Init();

	CreateAnimation();

	GetAnimator()->PlayAnimation(L"TableEffect", false);
}

void CTableEffect::Update()
{
	if (GetAnimator()->GetCurrAnim()->GetFinish())
		DeleteObjectEvent(this);
}

void CTableEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CTableEffect::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CTableEffect::Release()
{
}

void CTableEffect::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"TableEffect", CResourceManager::Get()->FindTexture(L"TableEffect"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .2f, 3);
}