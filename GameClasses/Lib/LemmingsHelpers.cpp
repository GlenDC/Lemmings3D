#include "LemmingsHelpers.h"
#include <cmath>
#include "../Managers/ScreenManager.h"

namespace LemmingsHelpers
{
	UINT GenerateHash(tstring str) 
	{
		UINT hash(0);
		for(size_t i = 0; i < str.size(); ++i) 
			hash = 65599 * hash + str[i];
		return hash ^ (hash >> 16);
	}

	void GetTextureDimensions(ID3D10ShaderResourceView * view, UINT & width, UINT & height)
	{
		ID3D10Resource* resource;
		D3D10_SHADER_RESOURCE_VIEW_DESC viewDesc;
		view->GetResource(&resource);
		view->GetDesc(&viewDesc);
		ASSERT(viewDesc.ViewDimension == D3D10_SRV_DIMENSION_TEXTURE2D,
			_T("This function only works with a 2D Texture!"));
		D3D10_TEXTURE2D_DESC desc2D;
		((ID3D10Texture2D*)resource)->GetDesc(&desc2D);
		width = desc2D.Width;
		height = desc2D.Height;
		resource->Release();
	}

	//Function removed due to null memory access!
	/*void SetTextureDimensions(ID3D10ShaderResourceView * view, UINT width, UINT height)
	{
		ID3D10Resource* resource;
		D3D10_SHADER_RESOURCE_VIEW_DESC viewDesc;
		view->GetResource(&resource);
		view->GetDesc(&viewDesc);
		ASSERT(viewDesc.ViewDimension == D3D10_SRV_DIMENSION_TEXTURE2D,
			_T("This function only works with a 2D Texture!"));
		D3D10_TEXTURE2D_DESC * desc2D(nullptr);
		((ID3D10Texture2D*)resource)->GetDesc(desc2D);
		desc2D->Width = width;
		desc2D->Height = height;
		resource->Release();
	}*/

	D3DXMATRIX MatrixScale(float scaleX, float scaleY, float scaleZ)
	{
		D3DXMATRIX matrix;
		D3DXMatrixScaling(&matrix, scaleX, scaleY, scaleZ);
		return matrix;
	}

	D3DXMATRIX MatrixTranslation(float tranX, float tranY, float tranZ)
	{
		D3DXMATRIX matrix;
		D3DXMatrixTranslation(&matrix, tranX, tranY, tranZ);
		return matrix;
	}

	
	D3DXMATRIX MatrixTranslation(const D3DXVECTOR3 & translation)
	{
		return MatrixTranslation(translation.x, translation.y, translation.z);
	}

	D3DXMATRIX MatrixRotation(float rotX, float rotY, float rotZ)
	{
		D3DXMATRIX matrix;
		D3DXMatrixRotationYawPitchRoll(&matrix, rotX, rotY, rotZ);
		return matrix;
	}
	
	D3DXMATRIX MatrixRotation(const D3DXQUATERNION & quaternion)
	{
		D3DXMATRIX matrix;
		D3DXMatrixRotationQuaternion(&matrix, &quaternion);
		return matrix;
	}

	
	void DrawGrid(float width, float height, float minDepth, float maxDepth)
	{
		if(ScreenManager::GetInstance()->CanDrawPhysics())
		{
			D3DXVECTOR3 start(GlobalParameters::GetParameters()->GetParameter<D3DXVECTOR3>(_T("LEVEL_OFFSET")));
			float gridSize(GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE")));
			int cols((int)width/(int)gridSize), rows((int)height/(int)gridSize);

			start -= D3DXVECTOR3(gridSize, gridSize, gridSize) * 0.5f;
			//draw lines on the x axis
			for(int c = 0; c < cols * 2 + 1; ++c)
			{
				DebugRenderer::DrawLine(start + D3DXVECTOR3((float)(c * gridSize), 0, 0), start + D3DXVECTOR3((float)(c * gridSize), 0, height * gridSize), D3DXCOLOR(1,1,1,1));
				DebugRenderer::DrawLine(start + D3DXVECTOR3((float)(c * gridSize), minDepth, 0), start + D3DXVECTOR3((float)(c * gridSize), maxDepth, 0), D3DXCOLOR(1,1,1,0.2f));
			}
			//draw lines on z axis
			for(int r = 0; r < rows * 2 + 1 ; ++r)
			{
				DebugRenderer::DrawLine(start + D3DXVECTOR3(0, 0, (float)(r * gridSize)), start + D3DXVECTOR3(width * gridSize, 0, (float)(r * gridSize)), D3DXCOLOR(1,1,1,1));
				DebugRenderer::DrawLine(start + D3DXVECTOR3(0, minDepth, (float)(r * gridSize)), start + D3DXVECTOR3(0, maxDepth, (float)(r * gridSize)), D3DXCOLOR(1,1,1,0.2f));
			}
		}
	}

	float ToRad(const float & degrees)
	{
		//360 deg = 2pi rad // 180 = pi // 1 = pi/180
		float radians = (degrees * 3.14f) / 180.0f;
		return radians;
	}

	float GetPitch(const D3DXQUATERNION & quaternion)
    {
		return (float)atan2f(2 * (quaternion.y * quaternion.z + quaternion.w * quaternion.x),
            quaternion.w * quaternion.w - quaternion.x * quaternion.x - quaternion.y * quaternion.y + quaternion.z * quaternion.z);
    }

    float GetYaw(const D3DXQUATERNION & quaternion)
    {
		return (float)asinf(-2 * (quaternion.x * quaternion.z - quaternion.w * quaternion.y));
    }

    float GetRoll(const D3DXQUATERNION & quaternion)
    {
		return (float)atan2f(2 * (quaternion.x * quaternion.y + quaternion.w * quaternion.z),
            quaternion.w * quaternion.w + quaternion.x * quaternion.x - quaternion.y * quaternion.y - quaternion.z * quaternion.z);
    }

	float fRound(float number, int accuracy)
	{
		accuracy = (int)pow(10, accuracy);
		number *= (float)accuracy;
		float rest = number - (int)number;
		number = (float)(rest > 0.5f ? ceill(number) : floor(number));
		number /= (float)accuracy;
		return number;
	}

	void ScreenToWorld(const GameContext & context, const D3DXVECTOR2 & screenPos, D3DXVECTOR3 & worldPos)
	{
		D3D10_VIEWPORT viewPort = context.Window->GetRenderTarget()->GetViewport();
		// Find near and far plane intersections
		D3DXVECTOR3 point3f(screenPos.x, (float)viewPort.Width * 0.5f - screenPos.y, 0.0f);
		D3DXVECTOR3 nearPlane = Unproject(context, point3f);
		D3DXVECTOR3 farPlane = Unproject(context, D3DXVECTOR3(point3f.x, point3f.y, 1.0f));

		// Calculate X, Y and return point
		float theta = (0.0f - nearPlane.z) / (farPlane.z - nearPlane.z);
		worldPos = D3DXVECTOR3(
			nearPlane.x + theta * (farPlane.x - nearPlane.x), 
			nearPlane.y + theta * (farPlane.y - nearPlane.y), 
			0.0f );
	}
	
	D3DXVECTOR3 Unproject(const GameContext & context, const D3DXVECTOR3 & point)
	{
		D3D10_VIEWPORT viewPort = context.Window->GetRenderTarget()->GetViewport();
		// Find the inverse Modelview-Projection-Matrix
		D3DXMATRIX mInvMVP = context.Camera->GetProjection() * context.Camera->GetView();
		D3DXMatrixInverse(&mInvMVP, NULL, &mInvMVP);

		// Transform to normalized coordinates in the range [-1, 1]
		D3DXVECTOR4 pointNormal;
		pointNormal.x = (point.x - viewPort.TopLeftX) / viewPort.Width * 2.0f - 1.0f;
		pointNormal.y = (point.y - viewPort.TopLeftY) / viewPort.Height * 2.0f;
		pointNormal.z = 2.0f * point.z - 1.0f;
		pointNormal.w = 1.0f;

		// Find the object's coordinates
		D3DXVECTOR4 pointCoord;
		D3DXVec4Transform(&pointCoord, &pointNormal, &mInvMVP);
		if (pointCoord.w != 0.0f)
			pointCoord.w = 1.0f / pointCoord.w;

		// Return coordinate
		return D3DXVECTOR3(
			pointCoord.x * pointCoord.w, 
			pointCoord.y * pointCoord.w, 
			pointCoord.z * pointCoord.w
			);
	}
	void SnapPositionX(D3DXVECTOR3 & pos, float snapSize)
	{
		float mod = fmod(pos.x, snapSize);
		if(mod < snapSize/2)
			pos.x -= mod;
		else
			pos.x += snapSize - mod;
	}

	void SnapPositionY(D3DXVECTOR3 & pos, float snapSize)
	{
		float mod = fmod(pos.y, snapSize);
		if(mod < snapSize/2)
			pos.y -= mod;
		else
			pos.y += snapSize - mod;
	}

	void SnapPositionZ(D3DXVECTOR3 & pos, float snapSize)
	{
		float mod = fmod(pos.z, snapSize);
		if(mod < snapSize/2)
			pos.z -= mod;
		else
			pos.z += snapSize - mod;
	}

	void SnapPositionXYZ(D3DXVECTOR3 & pos, float snapSize)
	{
		SnapPositionX(pos, snapSize);
		SnapPositionY(pos, snapSize);
		SnapPositionZ(pos, snapSize);
	}
	
	void SnapPositionXYZInteger(D3DXVECTOR3 & pos, float snapSize)
	{
		int mod = (int)pos.x % (int) snapSize;
		if(mod < (int)snapSize/2.0f)
			pos.x -= mod;
		else
			pos.x += snapSize - mod;
		mod = (int)pos.y % (int) snapSize;
		if(mod < (int)snapSize/2.0f)
			pos.y -= mod;
		else
			pos.y += snapSize - mod;
		mod = (int)pos.z % (int) snapSize;
		if(mod < (int)snapSize/2.0f)
			pos.z -= mod;
		else
			pos.z += snapSize - mod;
	}

	void GetNearPosition(const GameContext & context, D3DXVECTOR3 & pos)
	{
		POINT mousePos = context.Input->GetMousePosition();
		D3D10_VIEWPORT viewPort = context.Window->GetRenderTarget()->GetViewport();
		float nX(0), nY(0);
		nX = (float)(((double)mousePos.x - (double)mousePos.x/2) / ((double)viewPort.Width/2));
		nY = (float)(((double)viewPort.Height/2 - (double)mousePos.y) / ((double)viewPort.Height/2));

		//Transform the near and far point with the ViewProjectionInverse
		D3DXVECTOR3 nearPoint(nX,nY,0);

		D3DXMATRIX view = context.Camera->GetView();
		D3DXMATRIX proj  = context.Camera->GetProjection();
		D3DXMATRIX viewProjInv;
		D3DXMatrixInverse(&viewProjInv, NULL, &(view*proj));

		D3DXVec3TransformCoord(&nearPoint, &nearPoint, &viewProjInv);

		//Use GetClosestShape (PhysicsManager) to retrieve a physics shape
		pos = D3DXVECTOR3(nearPoint.x, nearPoint.y, nearPoint.z);
	}

	D3DXVECTOR3 GetMouseWorldDirection(const GameContext & context, D3DXVECTOR3 * pOrig)
	{
		POINT mousePos = context.Input->GetMousePosition();
		//Direction
		//===================
		float nX(0), nY(0);
		nX = (float)(((double)mousePos.x - (double)1280/2) / ((double)1280/2));
		nY = (float)(((double)720/2 - (double)mousePos.y) / ((double)720/2));

		//Transform the near and far point with the ViewProjectionInverse
		D3DXVECTOR3 nearPoint(nX,nY,0), farPoint(nX,nY,1.0f);

		D3DXMATRIX view = context.Camera->GetView();
		D3DXMATRIX proj  = context.Camera->GetProjection();
		D3DXMATRIX viewProjInv;
		D3DXMatrixInverse(&viewProjInv, NULL, &(view*proj));

		D3DXVec3TransformCoord(&nearPoint, &nearPoint, &viewProjInv);
		D3DXVec3TransformCoord(&farPoint, &farPoint, &viewProjInv);

		//Use GetClosestShape (PhysicsManager) to retrieve a physics shape
		D3DXVECTOR3 orig(nearPoint.x, nearPoint.y, nearPoint.z);
		if(pOrig != nullptr)
			*pOrig = orig;
		D3DXVECTOR3 direction(D3DXVECTOR3(farPoint.x, farPoint.y, farPoint.z) - orig);
		D3DXVec3Normalize(&direction, &direction);
		return direction;
	}
	
	float CalculateVector3Length(const D3DXVECTOR3 & p1, const D3DXVECTOR3 & p2)
	{
		D3DXVECTOR3 length = p1 - p2;
		return D3DXVec3Length(&length);
	}

	D3DXVECTOR3 GetCubeClosestPlane(const D3DXVECTOR3 & cubePos, float sizeCube, const D3DXVECTOR3 & checkPos)
	{
		D3DXVECTOR3 closPlanePos(0,0,0);
		D3DXVECTOR3 checkPositions[] = { D3DXVECTOR3(sizeCube,0,0), 
								   D3DXVECTOR3(-sizeCube,0,0),
								   D3DXVECTOR3(0,sizeCube,0), 
								   D3DXVECTOR3(0,-sizeCube,0), 
								   D3DXVECTOR3(0,0,sizeCube),
								   D3DXVECTOR3(0,0,-sizeCube) };
		UINT cpID(0);
		float dis(9999);
		for(UINT i = 0 ; i < 6 ; ++i)
		{
			D3DXVECTOR3 v = cubePos + checkPositions[i] - checkPos;
			float distance = D3DXVec3Length(&v);
			if(distance < dis) 
			{
				dis = distance;
				cpID = i;
			}
		}
		return checkPositions[cpID];
	}
}