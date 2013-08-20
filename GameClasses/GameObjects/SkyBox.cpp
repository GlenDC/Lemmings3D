//================================================== INCLUDES =====================================
#include "SkyBox.h"
//-------------------------------------------------------------------------------------------------
#include "../Materials/SkyBoxMaterial.h"
#include "Graphics/GraphicsDevice.h"
#include "../Entities/Level.h"
//=================================================================================================

SkyBox::SkyBox()
	: GameEntity(MatCustom)
{
	m_VisualResourcePath = _T("./Resources/Lemmings3D/models/Sphere.ovm");

	SkyBoxMaterial * pMaterial = new SkyBoxMaterial();
	pMaterial->SetCubeMap(_T("lemmingsmap.dds"));
	m_pVisualMaterial = pMaterial;	
}

SkyBox::~SkyBox(void)
{

}

void SkyBox::Initialize()
{
	GameEntity::Initialize();
}