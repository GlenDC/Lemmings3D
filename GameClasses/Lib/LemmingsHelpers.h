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
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

namespace LemmingsHelpers
{
	//Structure Posiion
	struct Position
	{
		UINT X, Y;
		Position() :X(0), Y(0) {}
		Position(const UINT x, const UINT y) :X(x), Y(y) {}
	};

	//Generate hashcode from string
	const UINT GenerateHash(const tstring & str);

	void GetTextureDimensions(const ID3D10ShaderResourceView * view, UINT & width, UINT & height);

	//void SetTextureDimensions(ID3D10ShaderResourceView * view, UINT width, UINT height);

	D3DXMATRIX MatrixScale(const float scaleX, const float scaleY, const float scaleZ);
	D3DXMATRIX MatrixTranslation(const float tranX, const float tranY, const float tranZ);
	D3DXMATRIX MatrixTranslation(const D3DXVECTOR3 & translation);
	D3DXMATRIX MatrixRotation(const float rotX, const float rotY, const float rotZ);
	D3DXMATRIX MatrixRotation(const D3DXQUATERNION & quaternion);

	void DrawGrid(const float width, const float height, const float minDepth, const float maxDepth);

	float ToRad(const float & degrees);

	float GetPitch(D3DXQUATERNION & quaternion);
	float GetYaw(D3DXQUATERNION & quaternion);
	float GetRoll(D3DXQUATERNION & quaternion);

	float fRound(float number, int accuracy = 2);

	void ScreenToWorld(const GameContext & context, const D3DXVECTOR2 & screenPos, D3DXVECTOR3 & worldPos);
	D3DXVECTOR3 Unproject(const GameContext & context, const D3DXVECTOR3 & point);
	
	void SnapPositionX(D3DXVECTOR3 & pos, const float snapSize);
	void SnapPositionY(D3DXVECTOR3 & pos, const float snapSize);
	void SnapPositionZ(D3DXVECTOR3 & pos, const float snapSize);
	void SnapPositionXYZ(D3DXVECTOR3 & pos, const float snapSize);
	void SnapPositionXYZInteger(D3DXVECTOR3 & pos, const float snapSize);

	void GetNearPosition(const GameContext & context, D3DXVECTOR3 & pos);

	D3DXVECTOR3 GetMouseWorldDirection(const GameContext & context, D3DXVECTOR3 * pOrig = nullptr);

	float CalculateVector3Length(const D3DXVECTOR3 & p1, const D3DXVECTOR3 & p2);

	D3DXVECTOR3 GetCubeClosestPlane(const D3DXVECTOR3 & cubePos, const float sizeCube, const D3DXVECTOR3 & checkPos);

	tstring GetTimeStringFromSecondsValue(UINT seconds);
	tstring GetFullTimeStringFromSecondsValue(UINT seconds);

	tstring GetFullTimeString();
}