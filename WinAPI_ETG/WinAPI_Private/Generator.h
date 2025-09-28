#pragma once

class CTexture;

class CGenerator : public Singleton<CGenerator>
{
public :
	CGenerator();
	virtual ~CGenerator();

public:	 
	void Init();
	void Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();

public :
	Vec2 GetRoomPos(const int _iIndex) { return m_vRoomPos[_iIndex]; }

	void SetTexture(CTexture* _pTexture) { m_pTexture = _pTexture; }

public :
	void CreateDungeon();
	void CreateBossRoom();

public :
	void CreateDungeonTrigger();

	void CreateBossWall();
	void CreateDungeonWall();

private :
	CTexture* m_pTexture;

	vector<Vec2> m_vRoomPos;

	vector<CObject*> m_vWall;
};