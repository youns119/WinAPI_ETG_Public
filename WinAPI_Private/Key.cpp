#include "pch.h"
#include "Key.h"

#include "ResourceManager.h"

#include "Player.h"
#include "Texture.h"

CKey::CKey()
	: m_iKey(0)
{
	SetRenderType(RENDER_TYPE::RENDER_UI);

	m_vecCount.reserve(4);
}

CKey::~CKey()
{
	Release();
}

void CKey::Init()
{
	SetPos({ 50.f, 150.f });

	float fWidth = (float)CResourceManager::Get()->FindTexture(L"Key")->GetWidth();
	float fHeight = (float)CResourceManager::Get()->FindTexture(L"Key")->GetHeight();

	SetScale({ fWidth, fHeight });

	SetUIType(UI_TYPE::KEY);
}

void CKey::Update()
{
	if (m_iKey != dynamic_cast<CPlayer*>(GetTarget())->GetKeyCount()) 
		KeyUpdate();
}

void CKey::LateUpdate()
{
	__super::LateUpdate();
}

void CKey::Render(HDC _hDC)
{
	if (!GetShow()) return;

	CTexture* pTexture = CResourceManager::Get()->FindTexture(L"Key");

	if (dynamic_cast<CPlayer*>(GetTarget())->GetFearCount() == 0)
	{
		SetPos({ 50.f, 100.f });
	}
	else SetPos({ 50.f, 150.f });

	GdiTransparentBlt
	(
		_hDC,
		(int)(GetPos().fX - GetScale().fX / 2.f),
		(int)(GetPos().fY - GetScale().fY / 2.f),
		(int)(GetScale().fX),
		(int)(GetScale().fY),
		pTexture->GetHDC(),
		0, 0,
		(int)(GetScale().fX),
		(int)(GetScale().fY),
		RGB(255, 255, 255)
	);

	pTexture = CResourceManager::Get()->FindTexture(L"Font");

	float fWidth = (float)pTexture->GetWidth();
	float fHeight = (float)pTexture->GetHeight();

	for (int i = 0; i < m_vecCount.size(); i++)
	{
		GdiTransparentBlt
		(
			_hDC,
			(int)(GetPos().fX - fHeight / 2.f + 40.f + 25.f * i),
			(int)(GetPos().fY - fHeight / 2.f),
			(int)fHeight,
			(int)fHeight,
			pTexture->GetHDC(),
			(int)(fHeight * (9 - m_vecCount[i])),
			0,
			(int)fHeight,
			(int)fHeight,
			RGB(0, 0, 0)
		);
	}

	__super::Render(_hDC);
}

void CKey::Release()
{
}

void CKey::KeyUpdate()
{
	m_iKey = dynamic_cast<CPlayer*>(GetTarget())->GetKeyCount();
	int iDigit = 0;

	m_vecCount.clear();

	iDigit = m_iKey / 1000;
	if (iDigit != 0) m_vecCount.push_back(iDigit);

	iDigit = (m_iKey % 1000) / 100;
	if (iDigit != 0 || (iDigit == 0 && !m_vecCount.empty())) m_vecCount.push_back(iDigit);

	iDigit = (m_iKey % 100) / 10;
	if (iDigit != 0 || (iDigit == 0 && !m_vecCount.empty())) m_vecCount.push_back(iDigit);

	iDigit = m_iKey % 10;

	m_vecCount.push_back(iDigit);
}