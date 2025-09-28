#pragma once

class CResources
{
public :
	CResources();
	virtual ~CResources();

public :
	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

private :
	wstring m_strKey;
	wstring m_strRelativePath;
};