//--------------------------------------------------------------------------------------
//   _____     _______ ____  _     ___  ____  ____    _____ _   _  ____ ___ _   _ _____ 
//  / _ \ \   / / ____|  _ \| |   / _ \|  _ \|  _ \  | ____| \ | |/ ___|_ _| \ | | ____|
// | | | \ \ / /|  _| | |_) | |  | | | | |_) | | | | |  _| |  \| | |  _ | ||  \| |  _|  
// | |_| |\ V / | |___|  _ <| |__| |_| |  _ <| |_| | | |___| |\  | |_| || || |\  | |___ 
//  \___/  \_/  |_____|_| \_\_____\___/|_| \_\____/  |_____|_| \_|\____|___|_| \_|_____|
//
// Overlord Engine v0.44
// Copyright Overlord Brecht Kets & Overlord Thomas Goussaert
// http://www.digitalartsandentertainment.com/
//--------------------------------------------------------------------------------------

#include "Week4.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
#include "Graphics/GraphicsDevice.h"
#include "OverlordComponents.h"
#include "Helpers/GeneralStructs.h"
#include "../../GameObjects/GameEntity.h"
#include "../../GameObjects/ColissionEntity.h"
#include "../../Managers/ScreenManager.h"
#include "Classes/Bone.h"
#include "Components/MeshDrawComponent.h"
#include "helpers/D3DUtil.h"


Week4::Week4(void)
	:BaseScreen(_T("Week4"), _T("Lab Week4: Bones... And their was movement"), true)
	,m_pBone0(nullptr)
	,m_pBone1(nullptr)
	,m_pMeshDrawer(nullptr)
	,m_BoneRotation(0)
	,m_RotationSign(1)
{
}


Week4::~Week4(void)
{
}

void Week4::Initialize()
{
	m_pBone0 = new BoneObject(0,15);
	m_pBone1 = new BoneObject(1,15);

	auto meshObject = new GameObject();
	
	m_pMeshDrawer = new MeshDrawComponent(24);
	meshObject->AddComponent(m_pMeshDrawer);
	

	CreateMesh();


	AddSceneObject(m_pBone0);
	m_pBone0->AddBone(m_pBone1);
	AddSceneObject(meshObject);

	m_pBone0->GetComponent<TransformComponent>()->Rotate(0,90,0);

	m_pBone0->CalculateBindPose();
	BaseScreen::Initialize();
}

void Week4::Update(const GameContext& context)
{

	m_BoneRotation += m_RotationSign * 45 * context.GameTime.ElapsedSeconds();

	if(m_RotationSign < 0 && m_BoneRotation <= -45)
		m_RotationSign = 1;
	if(m_RotationSign > 0 && m_BoneRotation >= 45)
		m_RotationSign = -1;

	auto boneTransform0 = m_pBone0->GetComponent<TransformComponent>();
	auto boneTransform1 = m_pBone1->GetComponent<TransformComponent>();

	boneTransform0->Rotate(m_BoneRotation,0,0);
	boneTransform1->Rotate(-m_BoneRotation*2,0,0);

	D3DXMATRIX boneTransformation0;
	D3DXMATRIX boneTransformation1;
	D3DXMatrixMultiply(&boneTransformation0, &m_pBone0->GetBindPose(), &boneTransform0->GetWorldMatrix());
	D3DXMatrixMultiply(&boneTransformation1, &m_pBone1->GetBindPose(), &boneTransform1->GetWorldMatrix());
	//D3DXMATRIX boneTransformation1 = m_pBone1->GetBindPose() * m_pMeshDrawer->GetTransform()->GetWorldMatrix();

	int counter = 0;
	for(auto & vec : m_SkinnedVertices)
	{
		vec.TransformedVertex.Color = vec.OriginalVertex.Color;
		D3DXVECTOR4 tranVec, tranVec2 , resultVec;
		D3DXVec3Transform(&tranVec, &vec.OriginalVertex.Position, &boneTransformation0);
		D3DXVec3Transform(&tranVec2, &vec.OriginalVertex.Position, &boneTransformation1);
		resultVec = tranVec * vec.BlendWeight0 + tranVec2 * vec.BlendWeight1;
		vec.TransformedVertex.Position = D3DXVECTOR3(resultVec.x, resultVec.y, resultVec.z);
		++counter;
	}

	m_pMeshDrawer->RemoveTriangles();
	for(int i = 0 ; i < (int)m_SkinnedVertices.size() ; i += 4)
	{
		m_pMeshDrawer->AddQuad(MeshDrawVertex(m_SkinnedVertices[i].TransformedVertex.Position, m_SkinnedVertices[i].TransformedVertex.Normal, m_SkinnedVertices[i].TransformedVertex.Color),
								MeshDrawVertex(m_SkinnedVertices[i+1].TransformedVertex.Position, m_SkinnedVertices[i+1].TransformedVertex.Normal, m_SkinnedVertices[i+1].TransformedVertex.Color),
								MeshDrawVertex(m_SkinnedVertices[i+2].TransformedVertex.Position, m_SkinnedVertices[i+2].TransformedVertex.Normal, m_SkinnedVertices[i+2].TransformedVertex.Color),
								MeshDrawVertex(m_SkinnedVertices[i+3].TransformedVertex.Position, m_SkinnedVertices[i+3].TransformedVertex.Normal, m_SkinnedVertices[i+3].TransformedVertex.Color));
	}

	m_pMeshDrawer->UpdateBuffer();

	BaseScreen::Update(context);
}

void Week4::Draw(const GameContext& context)
{
	GraphicsDevice::GetInstance()->Clear(D3DXCOLOR(0.6f,0.81f,0.92f,1.0f));
	BaseScreen::Draw(context);
}

void Week4::CreateMesh()
{
	auto pos = D3DXVECTOR3(7.5f,0,0);
	auto dim = D3DXVECTOR3(15,5,5);
	dim/=2;
	auto col = D3DXCOLOR(1,0,0,0.5f);

	//*****
	//BOX1*
	//*****

	//FRONT
	auto norm = D3DXVECTOR3(0,0,-1);
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,dim.y,-dim.z)+pos,norm,col,1.0f,0));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,dim.y,-dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,-dim.y,-dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,-dim.y,-dim.z)+pos,norm,col,1.0f,0));
	//BACK
	norm = D3DXVECTOR3(0,0,1);
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,dim.y,dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,dim.y,dim.z)+pos,norm,col,1.0f,0));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,-dim.y,dim.z)+pos,norm,col,1.0f,0));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,-dim.y,dim.z)+pos,norm,col,0.5f,0.5f));
	//TOP
	norm = D3DXVECTOR3(0,1,0);
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,dim.y,dim.z)+pos,norm,col,1.0f,0));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,dim.y,dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,dim.y,-dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,dim.y,-dim.z)+pos,norm,col,1.0f,0));
	//BOTTOM
	norm = D3DXVECTOR3(0,-1,0);
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,-dim.y,-dim.z)+pos,norm,col,1.0f,0));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,-dim.y,-dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,-dim.y,dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,-dim.y,dim.z)+pos,norm,col,1.0f,0));
	//LEFT
	norm = D3DXVECTOR3(-1,0,0);
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,dim.y,dim.z)+pos,norm,col,1.0f,0));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,dim.y,-dim.z)+pos,norm,col,1.0f,0));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,-dim.y,-dim.z)+pos,norm,col,1.0f,0));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,-dim.y,dim.z)+pos,norm,col,1.0f,0));
	//RIGHT
	norm = D3DXVECTOR3(1,0,0);
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,dim.y,-dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,dim.y,dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,-dim.y,dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,-dim.y,-dim.z)+pos,norm,col,0.5f,0.5f));

	//*****
	//BOX2*
	//*****

	col = D3DXCOLOR(0,1,0,0.5f);
	pos = D3DXVECTOR3(22.5f,0,0);
	//FRONT
	norm = D3DXVECTOR3(0,0,-1);
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,dim.y,-dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,dim.y,-dim.z)+pos,norm,col,0,1.0f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,-dim.y,-dim.z)+pos,norm,col,0,1.0f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,-dim.y,-dim.z)+pos,norm,col,0.5f,0.5f));
	//BACK
	norm = D3DXVECTOR3(0,0,1);
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,dim.y,dim.z)+pos,norm,col,0,1.0f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,dim.y,dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,-dim.y,dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,-dim.y,dim.z)+pos,norm,col,0,1.0f));
	//TOP
	norm = D3DXVECTOR3(0,1,0);
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,dim.y,dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,dim.y,dim.z)+pos,norm,col,0,1.0f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,dim.y,-dim.z)+pos,norm,col,0,1.0f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,dim.y,-dim.z)+pos,norm,col,0.5f,0.5f));
	//BOTTOM
	norm = D3DXVECTOR3(0,-1,0);

	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,-dim.y,-dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,-dim.y,-dim.z)+pos,norm,col,0,1.0f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,-dim.y,dim.z)+pos,norm,col,0,1.0f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,-dim.y,dim.z)+pos,norm,col,0.5f,0.5f));
	//LEFT
	norm = D3DXVECTOR3(-1,0,0);
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,dim.y,dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,dim.y,-dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,-dim.y,-dim.z)+pos,norm,col,0.5f,0.5f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(-dim.x,-dim.y,dim.z)+pos,norm,col,0.5f,0.5f));
	//RIGHT
	norm = D3DXVECTOR3(1,0,0);
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,dim.y,-dim.z)+pos,norm,col,0,1.0f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,dim.y,dim.z)+pos,norm,col,0,1.0f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,-dim.y,dim.z)+pos,norm,col,0,1.0f));
	m_SkinnedVertices.push_back(SkinnedVertex(D3DXVECTOR3(dim.x,-dim.y,-dim.z)+pos,norm,col,0,1.0f));
}