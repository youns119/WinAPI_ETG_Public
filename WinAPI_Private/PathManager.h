#pragma once

class CPathManager : public Singleton<CPathManager>
{
public :
	CPathManager();
	virtual ~CPathManager();

public :
	void Init();

public :
	const TCHAR* GetRelativePath() { return m_szRelativePath; }

private :
	TCHAR m_szRelativePath[255];
};