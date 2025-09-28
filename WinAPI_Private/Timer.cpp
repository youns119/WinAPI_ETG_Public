#include "pch.h"
#include "Timer.h"

#include "Main.h"

CTimer::CTimer()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_fDelta(0.f)
	, m_fAcc(0.f)
	, m_iCallCount(0)
	, m_iFPS(0)
{
}

CTimer::~CTimer()
{
}

void CTimer::Init()
{
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimer::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_fDelta = (float)((double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart);

	m_llPrevCount = m_llCurCount;

	Render();

#ifdef _DEBUG
	if (m_fDelta > (1.f / 60.f))
	{
		m_fDelta = float(1.f / 60.f);
	}
#endif
}

void CTimer::Render()
{
	++m_iCallCount;
	m_fAcc += m_fDelta;

	if (m_fAcc >= 1.f)
	{
		m_iFPS = m_iCallCount;
		m_fAcc = 0.f;
		m_iCallCount = 0;

		wchar_t szFrame[255] = {};
		swprintf_s(szFrame, L"FPS : %d, Delta: %f", m_iFPS, m_fDelta);
		SetWindowText(CMain::Get()->GetHwnd(), szFrame);
	}
}