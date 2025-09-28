#include "pch.h"
#include "PaintManager.h"

CPaintManager::CPaintManager()
	: m_arrBrush{}
	, m_arrPen{}
{
}

CPaintManager::~CPaintManager()
{
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
		DeleteObject(m_arrPen[i]);
}

void CPaintManager::Init()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}