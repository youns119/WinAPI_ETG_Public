#pragma once

#include "ObjectType.h"
#include "SceneType.h"

class CObject;
class CScene;

void CreateObjectEvent(CObject* _pObject, OBJECT_TYPE _eObjectType);

void DeleteObjectEvent(CObject* _pObject);

void ChangeScene(SCENE_TYPE _eSceneType, CObject* _pObject);

void FScanf(char* _pBuffer, FILE* _pFile);