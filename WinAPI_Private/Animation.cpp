#include "pch.h"
#include "Animation.h"

#include "Timer.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "Camera.h"

#include "Func.h"

#include "Texture.h"
#include "Animator.h"

CAnimation::CAnimation()
	: m_strName{}
	, m_pTexture(nullptr)
	, m_pAnimator(nullptr)
	, m_iCurrFrame(0)
	, m_fAccTime(0.f)
	, m_bAnimFinish(false)
{
	m_vecAnimFrame.clear();
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	if (m_bAnimFinish)
		return;

	m_fAccTime += CTimer::Get()->GetDelta();

	if (m_fAccTime > m_vecAnimFrame[m_iCurrFrame].fDuration)
	{
		++m_iCurrFrame;

		if (m_vecAnimFrame.size() <= m_iCurrFrame)
		{
			m_iCurrFrame = -1;
			m_bAnimFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime = m_fAccTime - m_vecAnimFrame[m_iCurrFrame].fDuration;
	}
}

void CAnimation::Render(HDC _hDC)
{
	if (m_bAnimFinish)
		return;

	CObject* pOwner = m_pAnimator->GetOwner();
	Vec2 vPos = pOwner->GetPos();
	vPos += m_vecAnimFrame[m_iCurrFrame].vOffset;

	vPos = CCamera::Get()->GetRenderPos(vPos);

	GdiTransparentBlt
	(
		_hDC,
		(int)(vPos.fX - (m_vecAnimFrame[m_iCurrFrame].vSliceSize.fX / 2.f)),
		(int)(vPos.fY - (m_vecAnimFrame[m_iCurrFrame].vSliceSize.fY / 2.f)),
		(int)(m_vecAnimFrame[m_iCurrFrame].vSliceSize.fX),
		(int)(m_vecAnimFrame[m_iCurrFrame].vSliceSize.fY),
		m_pTexture->GetHDC(),
		(int)(m_vecAnimFrame[m_iCurrFrame].vLeftTop.fX),
		(int)(m_vecAnimFrame[m_iCurrFrame].vLeftTop.fY),
		(int)(m_vecAnimFrame[m_iCurrFrame].vSliceSize.fX),
		(int)(m_vecAnimFrame[m_iCurrFrame].vSliceSize.fY),
		RGB(0, 0, 0)
	);
}

void CAnimation::Create(CTexture* _pTexture, Vec2 _vStartPos, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	if (m_vecAnimFrame.empty())
	{
		m_pTexture = _pTexture;

		AnimFrame tAnimFrame = {};

		for (UINT i = 0; i < _iFrameCount; i++)
		{
			tAnimFrame.fDuration = _fDuration;
			tAnimFrame.vSliceSize = _vSliceSize;
			tAnimFrame.vLeftTop = _vStartPos + _vStep * (float)i;

			m_vecAnimFrame.push_back(tAnimFrame);
		}
	}
	else
	{
		m_pTexture = _pTexture;

		for (UINT i = 0; i < _iFrameCount; i++)
		{
			m_vecAnimFrame[i].fDuration = _fDuration;
			m_vecAnimFrame[i].vSliceSize = _vSliceSize;
			m_vecAnimFrame[i].vLeftTop = _vStartPos + _vStep * (float)i;
		}
	}
}