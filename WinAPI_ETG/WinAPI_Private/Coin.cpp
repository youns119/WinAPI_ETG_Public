#include "pch.h"
#include "Coin.h"

#include "ResourceManager.h"

#include "Player.h"
#include "Texture.h"

CCoin::CCoin()
	: m_iCoin(-1)
	, m_iOffset(0)
{
	SetRenderType(RENDER_TYPE::RENDER_UI);

	m_vecCount.reserve(4);
}

CCoin::~CCoin()
{
	Release();
}

void CCoin::Init()
{
	SetPos({ 130.f, 150.f });

	float fWidth = (float)CResourceManager::Get()->FindTexture(L"Coin")->GetWidth();
	float fHeight = (float)CResourceManager::Get()->FindTexture(L"Coin")->GetHeight();

	SetScale({ fWidth, fHeight });

	SetUIType(UI_TYPE::COIN);
}

void CCoin::Update()
{
	if (m_iCoin != dynamic_cast<CPlayer*>(GetTarget())->GetCoinCount()) 
		CoinUpdate();

	CoinOffset();
}

void CCoin::LateUpdate()
{
	__super::LateUpdate();
}

void CCoin::Render(HDC _hDC)
{
	if (!GetShow()) return;

	CTexture* pTexture = CResourceManager::Get()->FindTexture(L"Coin");

	if (dynamic_cast<CPlayer*>(GetTarget())->GetFearCount() == 0)
	{
		SetPos({ 140.f + 25.f * (float)m_iOffset, 100.f});
	}
	else SetPos({ 140.f + 25.f * (float)m_iOffset, 150.f });

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

	float fWidth = (float) pTexture->GetWidth();
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

void CCoin::Release()
{
}

void CCoin::CoinUpdate()
{
	m_iCoin = dynamic_cast<CPlayer*>(GetTarget())->GetCoinCount();
	int iDigit = 0;

	m_vecCount.clear();

	iDigit = m_iCoin / 1000;
	if (iDigit != 0) m_vecCount.push_back(iDigit);

	iDigit = (m_iCoin % 1000) / 100;
	if (iDigit != 0 || (iDigit == 0 && !m_vecCount.empty())) m_vecCount.push_back(iDigit);

	iDigit = (m_iCoin % 100) / 10;
	if (iDigit != 0 || (iDigit == 0 && !m_vecCount.empty())) m_vecCount.push_back(iDigit);

	iDigit = m_iCoin % 10;

	m_vecCount.push_back(iDigit);
}

void CCoin::CoinOffset()
{
	int iDigit = dynamic_cast<CPlayer*>(GetTarget())->GetKeyCount();

	if (iDigit / 1000 != 0) m_iOffset = 3;
	else if (iDigit / 100 != 0) m_iOffset = 2;
	else if (iDigit / 10 != 0) m_iOffset = 1;
	else m_iOffset = 0;
}