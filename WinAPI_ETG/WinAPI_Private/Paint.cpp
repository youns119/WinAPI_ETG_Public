#include "pch.h"
#include "Paint.h"

CPaint::CPaint(const HDC _hDC, const BRUSH_TYPE _eBrushType)
	: m_hDC(_hDC)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HBRUSH hBrush = CPaintManager::Get()->GetBrush(_eBrushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_hDC, hBrush);
}

CPaint::CPaint(const HDC _hDC, const PEN_TYPE _ePenType)
	: m_hDC(_hDC)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HPEN hPen = CPaintManager::Get()->GetPen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_hDC, hPen);
}

CPaint::~CPaint()
{
	SelectObject(m_hDC, m_hDefaultPen);
	SelectObject(m_hDC, m_hDefaultBrush);
}