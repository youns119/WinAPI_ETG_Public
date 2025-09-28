#include "pch.h"
#include "Animator.h"

#include "Object.h"
#include "Animation.h"

CAnimator::CAnimator()
	: m_pOwner(nullptr)
	, m_pCurrAnimation(nullptr)
	, m_bAnimRepeat(false)
{
	m_mapAnimation.clear();
}

CAnimator::CAnimator(const CAnimator& _Animator)
	: m_pOwner(_Animator.m_pOwner)
	, m_pCurrAnimation(_Animator.m_pCurrAnimation)
	, m_bAnimRepeat(_Animator.m_bAnimRepeat)
{
	m_mapAnimation.clear();
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnimation);
}

void CAnimator::Update()
{

}

void CAnimator::LateUpdate()
{
	if (m_pCurrAnimation != nullptr)
	{
		m_pCurrAnimation->Update();

		if (m_bAnimRepeat && m_pCurrAnimation->GetFinish())
			m_pCurrAnimation->ResetAnimFrame(0);
		else if (!m_bAnimRepeat && m_pCurrAnimation->GetFinish())
		{
			m_pCurrAnimation->ResetAnimFrame(0);
			m_pCurrAnimation->SetFinish(true);
		}
	}
}

void CAnimator::Render(HDC _hDC)
{
	if (m_pCurrAnimation != nullptr)
		m_pCurrAnimation->Render(_hDC);
}

void CAnimator::CreateAnimation
(
	const wstring& _strName,
	CTexture* _pTexture, 
	Vec2 _vStartPos, Vec2 _vSliceSize, Vec2 _vStep,
	float _fDuration, UINT _iFrameCount
)
{
	CAnimation* pAnimation = FindAnimation(_strName);
	//assert(nullptr == pAnimation);

	if (pAnimation == nullptr)
	{
		pAnimation = new CAnimation();

		pAnimation->SetAnimName(_strName);
		pAnimation->SetAnimator(this);
		pAnimation->Create(_pTexture, _vStartPos, _vSliceSize, _vStep, _fDuration, _iFrameCount);

		m_mapAnimation.insert(make_pair(_strName, pAnimation));
	}
	else
	{
		pAnimation->Create(_pTexture, _vStartPos, _vSliceSize, _vStep, _fDuration, _iFrameCount);
	}
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnimation.find(_strName);

	if (iter == m_mapAnimation.end())
		return nullptr;

	return iter->second;
}

void CAnimator::PlayAnimation(const wstring& _strName, bool _bAnimRepeat)
{
	m_pCurrAnimation = FindAnimation(_strName);
	m_bAnimRepeat = _bAnimRepeat;
	
	m_pCurrAnimation->SetFinish(false);
}