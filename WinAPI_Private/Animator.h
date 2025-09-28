#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
public :
	CAnimator();
	CAnimator(const CAnimator& _Animator);
	~CAnimator();

public :
	void Update();
	void LateUpdate();
	void Render(HDC _hDC);

public :
	CObject* GetOwner() const { return m_pOwner; }
	CAnimation* GetCurrAnim() const { return m_pCurrAnimation; }

	void SetOwner(CObject& _pOwner) { m_pOwner = &_pOwner; }

public:
	void CreateAnimation
	(
		const wstring& _strName,
		CTexture* _pTexture,
		Vec2 _vStartPos, Vec2 _vSliceSize, Vec2 _vStep,
		float _fDuration, UINT _iFrameCount
	);
	CAnimation* FindAnimation(const wstring& _strName);
	void PlayAnimation(const wstring& _strName, bool _bAnimRepeat);

private :
	CObject* m_pOwner;
	map<wstring, CAnimation*> m_mapAnimation;
	CAnimation* m_pCurrAnimation;
	bool m_bAnimRepeat;
};