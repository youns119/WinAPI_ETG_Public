#include "pch.h"
#include "ResourceManager.h"

#include "PathManager.h"

#include "Resources.h"
#include "Texture.h"

CResourceManager::CResourceManager()
{
	m_mapTexture.clear();
}

CResourceManager::~CResourceManager()
{
	Safe_Delete_Map(m_mapTexture);
}

CTexture* CResourceManager::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	CTexture* pTexture = FindTexture(_strKey);

	if (pTexture != nullptr)
		return pTexture;

	pTexture = new CTexture;
	pTexture->SetKey(_strKey);

	pTexture->Create(_iWidth, _iHeight);

	m_mapTexture.insert(make_pair(_strKey, pTexture));

	return pTexture;
}

CTexture* CResourceManager::LoadTexture(const wstring& _strKey, const wstring& _strPath)
{
	CTexture* pTexture = FindTexture(_strKey);
	if (nullptr != pTexture)
		return pTexture;

	wstring strFilePath = CPathManager::Get()->GetRelativePath();
	strFilePath += _strPath;

	pTexture = new CTexture;
	pTexture->Load(strFilePath);

	pTexture->SetKey(_strKey);
	pTexture->SetRelativePath(_strPath);

	m_mapTexture.insert(make_pair(_strKey, pTexture));

	return pTexture;
}

CTexture* CResourceManager::FindTexture(const wstring& _strKey)
{
	map<wstring, CResources*>::iterator iter = m_mapTexture.find(_strKey);

	if (iter == m_mapTexture.end())
		return nullptr;

	return (CTexture*)iter->second;
}