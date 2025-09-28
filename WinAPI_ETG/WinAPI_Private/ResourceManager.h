#pragma once

class CResources;
class CTexture;

class CResourceManager : public Singleton<CResourceManager>
{
public :
	CResourceManager();
	virtual ~CResourceManager();

public :
	CTexture* CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight);

public :
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strPath);

public :
	CTexture* FindTexture(const wstring& _strKey);

private:
	map<wstring, CResources*> m_mapTexture;
};