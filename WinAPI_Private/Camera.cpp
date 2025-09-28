#include "pch.h"
#include "Camera.h"

#include "Keyboard.h"
#include "Timer.h"
#include "ResourceManager.h"
#include "Main.h"

#include "Object.h"
#include "Texture.h"

CCamera::CCamera()
	: m_vLookAtPos{}
	, m_vCurrLookPos{}
	, m_vPrevLookPos{}
	, m_pTarget(nullptr)
	, m_fTargettingSpeed(0.f)
	, m_vDiff{}
	, m_bShake(false)
	, m_iRL(1)
	, m_fDistance(0.f)
	, m_tCameraShake{}
	, m_pVeilTexture(nullptr)
{
	m_listCameraEffect.clear();
}

CCamera::~CCamera()
{
}

void CCamera::Init()
{
	Vec2 vResolution = CMain::Get()->GetResolution();

	m_fTargettingSpeed = 2.f;

	m_pVeilTexture = CResourceManager::Get()->CreateTexture(L"CameraVeil", (UINT)vResolution.fX, (UINT)vResolution.fY);
}

void CCamera::Update()
{
	if (m_pTarget)
	{
		if (m_pTarget->GetDead())
			m_pTarget = nullptr;
		else
			m_vLookAtPos = m_pTarget->GetPos();
	}

	if (m_bShake && m_tCameraShake.fCurrTime >= m_tCameraShake.fDuration)
	{
		m_tCameraShake.fCurrTime = 0.f;
		m_tCameraShake.fDuration = 0.f;

		m_bShake = false;
		m_fDistance = 0.f;
	}

	CalDiff();
}

void CCamera::Render(HDC _hDC)
{
	if (m_listCameraEffect.empty())
		return;

	CameraEffect& tCameraEffect = m_listCameraEffect.front();
	tCameraEffect.fCurrTime += CTimer::Get()->GetDelta();

	float fRatio = 0.f;
	fRatio = tCameraEffect.fCurrTime / tCameraEffect.fDuration;

	if (fRatio < 0.f) fRatio = 0.f;
	else if (fRatio > 1.f) fRatio = 1.f;

	int iAlpha = 0;

	if (CAMERA_EFFECT::FADE_OUT == tCameraEffect.eEffectType)
		iAlpha = (int)(255.f * fRatio);
	else if (CAMERA_EFFECT::FADE_IN == tCameraEffect.eEffectType)
		iAlpha = (int)(255.f * (1.f - fRatio));

	BLENDFUNCTION tBlendFunc = {};

	tBlendFunc.BlendOp = AC_SRC_OVER;
	tBlendFunc.BlendFlags = 0;
	tBlendFunc.AlphaFormat = 0;
	tBlendFunc.SourceConstantAlpha = iAlpha;

	AlphaBlend
	(
		_hDC,
		0, 0,
		(int)m_pVeilTexture->GetWidth(),
		(int)m_pVeilTexture->GetHeight(),
		m_pVeilTexture->GetHDC(),
		0, 0,
		(int)m_pVeilTexture->GetWidth(),
		(int)m_pVeilTexture->GetHeight(),
		tBlendFunc
	);

	if (tCameraEffect.fCurrTime > tCameraEffect.fDuration)
		m_listCameraEffect.pop_front();
}

void CCamera::CalDiff()
{
	Vec2 vLookDir = m_vLookAtPos - m_vPrevLookPos;

	if (!vLookDir.IsZero())
		m_vCurrLookPos = m_vPrevLookPos + vLookDir * CTimer::Get()->GetDelta() * m_fTargettingSpeed;

	if (m_bShake)
	{
		m_tCameraShake.fCurrTime += CTimer::Get()->GetDelta();

		m_vCurrLookPos.fX += m_fDistance;
		m_fDistance = -m_fDistance * 0.95f;
	}

	Vec2 vResolution = CMain::Get()->GetResolution();
	Vec2 vCenterPos = vResolution / 2.f;

	m_vDiff = m_vCurrLookPos - vCenterPos;
	m_vPrevLookPos = m_vCurrLookPos;
}

void CCamera::Shake(float _fDuration, float _fDistance)
{
	m_tCameraShake.eEffectType = CAMERA_EFFECT::SHAKE;
	m_tCameraShake.fDuration = _fDuration;
	m_tCameraShake.fCurrTime = 0.f;

	m_bShake = true;
	m_fDistance = _fDistance * m_iRL;
	m_iRL *= -1;
}

void CCamera::FadeIn(float _fDuration)
{
	CameraEffect tCameraEffect = {};
	tCameraEffect.eEffectType = CAMERA_EFFECT::FADE_IN;
	tCameraEffect.fDuration = _fDuration;
	tCameraEffect.fCurrTime = 0.f;

	m_listCameraEffect.push_back(tCameraEffect);

	if (0.f == _fDuration)
		assert(nullptr);
}

void CCamera::FadeOut(float _fDuration)
{
	CameraEffect tCameraEffect = {};
	tCameraEffect.eEffectType = CAMERA_EFFECT::FADE_OUT;
	tCameraEffect.fDuration = _fDuration;
	tCameraEffect.fCurrTime = 0.f;

	m_listCameraEffect.push_back(tCameraEffect);

	if (0.f == _fDuration)
		assert(nullptr);
}