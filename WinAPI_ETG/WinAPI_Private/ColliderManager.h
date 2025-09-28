#pragma once

class CCollider;

class CColliderManager : public Singleton<CColliderManager>
{
public :
	union COLLIDER_ID
	{
		struct
		{
			UINT iLeft_id;
			UINT iRight_id;
		};

		ULONGLONG ullID;
	};

public :
	CColliderManager();
	virtual ~CColliderManager();

public:
	void Init();
	void Update();

private:
	void CollisionGroupUpdate(const OBJECT_TYPE _eLeft, const OBJECT_TYPE _eRight);
	bool isCollision(CCollider* _pLeftCol, CCollider* _pRightCol);

public :
	void CheckGroup(const OBJECT_TYPE _eLeft, const OBJECT_TYPE _eRight);
	void Reset()
	{
		memset(m_arrCheck, 0, sizeof(UINT) * (UINT)OBJECT_TYPE::END);
	}

private:
	map <ULONGLONG, bool> m_mapColInfo;
	UINT m_arrCheck[(UINT)OBJECT_TYPE::END];
};