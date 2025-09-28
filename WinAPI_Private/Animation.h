#pragma once

class CAnimator;
class CTexture;

struct AnimFrame
{
	Vec2 vLeftTop;
	Vec2 vSliceSize;
	Vec2 vOffset;
	float fDuration;
};

class CAnimation
{
public :
	CAnimation();
	~CAnimation();

public :
	void Update();
	void Render(HDC _hDC);

public :
	bool GetFinish() const { return m_bAnimFinish; }
	const wstring& GetName() const { return m_strName; }
	CAnimator* GetAnimator() const { return m_pAnimator; }
	AnimFrame& GetAnimFrame(const int _iIndex) { return m_vecAnimFrame[_iIndex]; }
	UINT GetMaxFrame() const { return (UINT)m_vecAnimFrame.size(); }
	int GetCurrFrame() const { return m_iCurrFrame; }

	void SetAnimName(const wstring& _strName) { m_strName = _strName; }
	void SetAnimator(CAnimator* _pAnimator) { m_pAnimator = _pAnimator; }
	void SetFinish(const bool _bAnimFinish) { m_bAnimFinish = _bAnimFinish; }

public :
	void Create
	(
		CTexture* _pTexture,
		Vec2 _vStartPos, Vec2 _vSliceSize, Vec2 _vStep,
		float _fDuration, UINT _iFrameCount
	);
	void ResetAnimFrame(const int _iCurrFrame)
	{
		m_bAnimFinish = false;
		m_iCurrFrame = _iCurrFrame;
		m_fAccTime = 0.f;
	}

private:
	wstring	m_strName;

	CTexture* m_pTexture;
	CAnimator* m_pAnimator;
	vector<AnimFrame> m_vecAnimFrame;

	int	m_iCurrFrame;
	float m_fAccTime;
	bool m_bAnimFinish;
};