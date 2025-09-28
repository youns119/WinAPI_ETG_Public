#include "pch.h"
#include "Effect.h"

#include "Animation.h"
#include "Animator.h"
#include "Func.h"

CEffect::CEffect()
	: m_eEffectType(EFFECT_TYPE::BULLET_EFFECT)
{
	SetObjectType(OBJECT_TYPE::EFFECT);
	SetRenderType(RENDER_TYPE::RENDER_EFFECT);
}

CEffect::~CEffect()
{
	Release();
}

void CEffect::Init()
{
	CreateAnimator();
}

void CEffect::Update()
{
}

void CEffect::LateUpdate()
{
	__super::LateUpdate();

	if (GetAnimator()->GetCurrAnim()->GetFinish())
		DeleteObjectEvent(this);
}

void CEffect::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CEffect::Release()
{
}