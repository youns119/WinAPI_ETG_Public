#pragma once

#include "BrushType.h"
#include "PenType.h"

class CPaintManager : public Singleton<CPaintManager>
{
public :
	CPaintManager();
	virtual ~CPaintManager();

public :
	void Init();

public :
	HBRUSH GetBrush(const BRUSH_TYPE _eBrushType) { return m_arrBrush[(UINT)_eBrushType]; }
	HPEN GetPen(const PEN_TYPE _ePenType) { return m_arrPen[(UINT)_ePenType]; }

private:
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];
};