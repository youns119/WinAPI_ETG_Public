#include "pch.h"
#include "Mouse.h"

#include "ResourceManager.h"
#include "Camera.h"
#include "Main.h"

#include "Object.h"
#include "Texture.h"
#include "Collider.h"
#include "Func.h"

CMouse::CMouse()
	: m_pMouse(nullptr)
	, m_pPoint(nullptr)
	, m_pTarget(nullptr)
	, m_fDistance(0.f)
	, m_pTexture(nullptr)
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Init()
{
	m_pMouse = new CObject;
	m_pPoint = new CObject;

	m_pTexture = CResourceManager::Get()->FindTexture(L"Crosshair");

	m_pMouse->SetName(L"Mouse");
	m_pMouse->SetObjectType(OBJECT_TYPE::MOUSE);
	m_pMouse->SetRenderType(RENDER_TYPE::RENDER_UI);
	m_pMouse->SetScale(Vec2((float)m_pTexture->GetWidth(), (float)m_pTexture->GetHeight()));

	m_pMouse->CreateCollider();
	m_pMouse->GetCollider()->SetScale(m_pMouse->GetScale());
	m_pMouse->GetCollider()->SetShow(false);

	m_fDistance = 200.f;
}

void CMouse::Update()
{
	POINT ptMouse{};
	Vec2 vPos;

	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);

	vPos.fX = CCamera::Get()->GetLookPos().fX - CMain::Get()->GetResolution().x / 2.f + ptMouse.x;
	vPos.fY = CCamera::Get()->GetLookPos().fY - CMain::Get()->GetResolution().y / 2.f + ptMouse.y;

	m_pMouse->SetPos(vPos);
	if(m_pTarget) SetPointPos();

	m_pMouse->LateUpdate();

	ShowCursor(FALSE);
}

void CMouse::Render(HDC _hDC)
{
	Vec2 vRenderPos = CCamera::Get()->GetRenderPos(m_pMouse->GetPos());

	GdiTransparentBlt
	(
		_hDC,
		(int)(vRenderPos.fX - m_pMouse->GetScale().fX / 2.f),
		(int)(vRenderPos.fY - m_pMouse->GetScale().fY / 2.f),
		(int)(m_pMouse->GetScale().fX),
		(int)(m_pMouse->GetScale().fY),
		m_pTexture->GetHDC(),
		0, 0,
		(int)(m_pMouse->GetScale().fX),
		(int)(m_pMouse->GetScale().fY),
		RGB(0, 0, 0)
	);

	m_pMouse->Render(_hDC);
}

void CMouse::Release()
{
	//Safe_Delete(m_pMouse);
	Safe_Delete(m_pPoint);
}

void CMouse::SetPointPos()
{
	Vec2 vCursorPoint;
	Vec2 vDir;
	float vDistance;

	vCursorPoint = m_pMouse->GetPos() - m_pTarget->GetPos();
	vDir = vCursorPoint.Normalize();
	vDistance = vCursorPoint.Length();

	if (vDistance >= m_fDistance)
		m_pPoint->SetPos(m_pTarget->GetPos() + vDir * m_fDistance);
	else
		m_pPoint->SetPos(m_pMouse->GetPos());
}