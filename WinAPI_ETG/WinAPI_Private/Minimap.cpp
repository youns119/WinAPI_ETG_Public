#include "pch.h"
#include "Minimap.h"

#include "ResourceManager.h"
#include "Main.h"
#include "Camera.h"
#include "SceneManager.h"

#include "Texture.h"

CMinimap::CMinimap()
	: m_pBack(nullptr)
	, m_pPlayer(nullptr)
	, m_pTexture(nullptr)
{
	SetRenderType(RENDER_TYPE::RENDER_UI);
}

CMinimap::~CMinimap()
{
	Release();
}

void CMinimap::Init()
{
	SetPos({ CMain::Get()->GetResolution().x - 400.f, 0.f});

	m_pBack = CResourceManager::Get()->FindTexture(L"Minimap_Background");
	m_pPlayer = CResourceManager::Get()->FindTexture(L"PlayerPortrait");
	m_pTexture = CResourceManager::Get()->FindTexture(L"Minimap");

	float fWidth = CResourceManager::Get()->FindTexture(L"Minimap")->GetWidth();
	float fHeight = CResourceManager::Get()->FindTexture(L"Minimap")->GetHeight();

	SetScale({ fWidth, fHeight });

	SetUIType(UI_TYPE::MINIMAP);
}

void CMinimap::Update()
{
}

void CMinimap::LateUpdate()
{
	__super::LateUpdate();
}

void CMinimap::Render(HDC _hDC)
{
	if (!GetShow())
		return;

	Vec2 vPos = CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0]->GetPos();

	vPos = vPos * 0.1f;

	//BitBlt
	//(
	//	m_pBack->GetHDC(),
	//	0, 0,
	//	m_pTexture->GetWidth(),
	//	m_pTexture->GetHeight(),
	//	m_pTexture->GetHDC(),
	//	0, 0,
	//	SRCCOPY
	//);

	BitBlt
	(
		m_pBack->GetHDC(),
		0, 0,
		400.f, 200.f,
		m_pTexture->GetHDC(),
		vPos.fX - 200.f, 
		vPos.fY - 100.f,
		SRCCOPY
	);

	BitBlt
	(
		m_pBack->GetHDC(),
		200.f - m_pPlayer->GetWidth() / 2.f, 
		100.f - m_pPlayer->GetHeight() / 2.f,
		m_pPlayer->GetWidth(), 
		m_pPlayer->GetHeight(),
		m_pPlayer->GetHDC(),
		0, 0,
		SRCCOPY
	);

	BitBlt
	(
		_hDC,
		GetPos().fX, GetPos().fY,
		400.f, 200.f,
		m_pBack->GetHDC(),
		0, 0,
		SRCCOPY
	);

	__super::Render(_hDC);
}

void CMinimap::Release()
{
}