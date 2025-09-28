#pragma once

#include "PaintManager.h"

class CPaint
{
public :
	CPaint(const HDC _hDC, const BRUSH_TYPE _eBrushType);
	CPaint(const HDC _hDC, const PEN_TYPE _ePenType);
	virtual ~CPaint();

private:
	HDC		m_hDC;
	HPEN	m_hDefaultPen;
	HBRUSH	m_hDefaultBrush;
};