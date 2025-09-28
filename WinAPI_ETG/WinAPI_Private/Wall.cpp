#include "pch.h"
#include "Wall.h"

#include "Collider.h"

CWall::CWall()
{
	SetObjectType(OBJECT_TYPE::WALL);
	SetRenderType(RENDER_TYPE::RENDER_TILE_PREV);
}

CWall::~CWall()
{
	Release();
}

void CWall::Init()
{
	SetName(L"Wall");

	CreateCollider();

	GetCollider()->SetScale(GetScale());
	GetCollider()->SetShow(false);
}

void CWall::Update()
{
}

void CWall::LateUpdate()
{
	__super::LateUpdate();
}

void CWall::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CWall::Release()
{
}