#pragma once

class CTimer : public Singleton<CTimer>
{
public :
	CTimer();
	virtual ~CTimer();

public :
	void Init();
	void Update();
	void Render();

public:
	float GetDelta() const { return m_fDelta; }
	int GetFrame() const { return m_iFPS; }

private :
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	float m_fDelta;
	float m_fAcc;
	UINT m_iCallCount;
	UINT m_iFPS;
};