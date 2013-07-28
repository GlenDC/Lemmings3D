#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "Helpers/DebugRenderer.h"
#include "GlobalParameters.h"
//====================================================================

//====================== Namespace LemmingsHelpers ============================
// Description:
//		namespace, collectint some classes and public functions
// Last Modification: 20/05/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

namespace LemmingsHelpers
{
	//Structure Posiion
	struct Position
	{
		unsigned int X, Y;
		Position() :X(0), Y(0) {}
		Position(unsigned int x, unsigned int y) :X(x), Y(y) {}
	};

	//Generate hashcode from string
	UINT GenerateHash(tstring str);

	void GetTextureDimensions(ID3D10ShaderResourceView * view, UINT & width, UINT & height);

	//void SetTextureDimensions(ID3D10ShaderResourceView * view, UINT width, UINT height);

	D3DXMATRIX MatrixScale(float scaleX, float scaleY, float scaleZ);
	D3DXMATRIX MatrixTranslation(float tranX, float tranY, float tranZ);
	D3DXMATRIX MatrixTranslation(const D3DXVECTOR3 & translation);
	D3DXMATRIX MatrixRotation(float rotX, float rotY, float rotZ);
	D3DXMATRIX MatrixRotation(const D3DXQUATERNION & quaternion);

	void DrawGrid(float width, float height, float minDepth, float maxDepth);

	float ToRad(const float & degrees);

	float GetPitch(const D3DXQUATERNION & quaternion);
	float GetYaw(const D3DXQUATERNION & quaternion);
	float GetRoll(const D3DXQUATERNION & quaternion);

	float fRound(float number, int accuracy = 2);

	void ScreenToWorld(const GameContext & context, const D3DXVECTOR2 & screenPos, D3DXVECTOR3 & worldPos);
	D3DXVECTOR3 Unproject(const GameContext & context, const D3DXVECTOR3 & point);
	
	void SnapPositionX(D3DXVECTOR3 & pos, float snapSize);
	void SnapPositionY(D3DXVECTOR3 & pos, float snapSize);
	void SnapPositionZ(D3DXVECTOR3 & pos, float snapSize);
	void SnapPositionXYZ(D3DXVECTOR3 & pos, float snapSize);
	void SnapPositionXYZInteger(D3DXVECTOR3 & pos, float snapSize);

	void GetNearPosition(const GameContext & context, D3DXVECTOR3 & pos);

	D3DXVECTOR3 GetMouseWorldDirection(const GameContext & context, D3DXVECTOR3 * pOrig = nullptr);

	float CalculateVector3Length(const D3DXVECTOR3 & p1, const D3DXVECTOR3 & p2);

	D3DXVECTOR3 GetCubeClosestPlane(const D3DXVECTOR3 & cubePos, float sizeCube, const D3DXVECTOR3 & checkPos);
}