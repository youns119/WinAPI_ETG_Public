#include "pch.h"
#include "ColliderManager.h"

#include "SceneManager.h"

#include "Object.h"
#include "Collider.h"
#include "Scene.h"

CColliderManager::CColliderManager()
	: m_arrCheck{}
{
}

CColliderManager::~CColliderManager()
{
}

void CColliderManager::Init()
{
}

void CColliderManager::Update()
{
	for (UINT iRow = 0; iRow < (UINT)OBJECT_TYPE::END; iRow++)
		for (UINT iCol = iRow; iCol < (UINT)OBJECT_TYPE::END; iCol++)
			if (m_arrCheck[iRow] & (1 << iCol))
				CollisionGroupUpdate((OBJECT_TYPE)iRow, (OBJECT_TYPE)iCol);

}

void CColliderManager::CollisionGroupUpdate(const OBJECT_TYPE _eLeft, const OBJECT_TYPE _eRight)
{
	CScene* pCurScene = CSceneManager::Get()->GetCurrScene();

	const vector<CObject*>& vecLeft = CSceneManager::Get()->GetGroupObjects(_eLeft);
	const vector<CObject*>& vecRight = CSceneManager::Get()->GetGroupObjects(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (vecLeft[i] == nullptr || vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (vecRight[j] == nullptr || vecRight[j]->GetCollider() == nullptr ||  vecLeft[i] == vecRight[j])
				continue;

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			COLLIDER_ID ID;
			ID.iLeft_id = pLeftCol->GetID();
			ID.iRight_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ullID);

			if (iter == m_mapColInfo.end())
			{
				m_mapColInfo.insert(make_pair(ID.ullID, false));
				iter = m_mapColInfo.find(ID.ullID);
			}

			if (isCollision(pLeftCol, pRightCol))
			{
				if (iter->second)
				{
					if (vecLeft[i]->GetDead() || vecRight[j]->GetDead())
					{
						pLeftCol->OnCollisionExit(*pRightCol);
						pRightCol->OnCollisionExit(*pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(*pRightCol);
						pRightCol->OnCollision(*pLeftCol);
					}
				}
				else
				{
					if (!(vecLeft[i]->GetDead()) && !(vecRight[j]->GetDead()))
					{
						pLeftCol->OnCollisionEnter(*pRightCol);
						pRightCol->OnCollisionEnter(*pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				if (iter->second)
				{
					pLeftCol->OnCollisionExit(*pRightCol);
					pRightCol->OnCollisionExit(*pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CColliderManager::isCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.fX - vLeftPos.fX) <= (vRightScale.fX + vLeftScale.fX) / 2.f
		&& abs(vRightPos.fY - vLeftPos.fY) <= (vRightScale.fY + vLeftScale.fY) / 2.f)
		return true;

	return false;
}

void CColliderManager::CheckGroup(const OBJECT_TYPE _eLeft, const OBJECT_TYPE _eRight)
{
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
		m_arrCheck[iRow] &= ~(1 << iCol);
	else
		m_arrCheck[iRow] |= (1 << iCol);
}