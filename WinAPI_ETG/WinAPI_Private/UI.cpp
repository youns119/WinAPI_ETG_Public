#include "pch.h"
#include "UI.h"

CUI::CUI()
	: m_pTarget(nullptr)
	, m_bShow(false)
	, m_eUIType(UI_TYPE::END)
{
	SetObjectType(OBJECT_TYPE::UI);
}

CUI::~CUI()
{
	Release();
}

void CUI::Init()
{
	__super::Init();
}

void CUI::Update()
{
	__super::Update();
}

void CUI::LateUpdate()
{
	__super::LateUpdate();
}

void CUI::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CUI::Release()
{
}