#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "Helpers/stdafx.h"
//====================================================================

//====================== HeightmapParser Class =========================
// Description:
//		Parse heightmaps with this class. (Traits class)
// Last Modification: July 2013s
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class HeightmapParser 
{
public:
	//read a heightmap
	static bool Read(const tstring & file, const UINT width, const UINT height, 
		const float heightDivider = 1.0f, const float scale = 1.0f, const float texScale = 1.0f);
	static bool Read(const tstring & file, const UINT width, const UINT height, 
		vector<vector<D3DXVECTOR3>> & vertex2DVec, D3DXVECTOR2 & depthInfo, 
		const float heightDivider = 1.0f, const float scale = 1.0f, const float texScale = 1.0f);

private:
	static bool LoadHeightMap(const tstring & file, const int width, const int height, std::vector<char> & heightmapVec);

	// Disabling default copy constructor, default assignment operator, default constructor and destructor.
	~HeightmapParser(void);
	HeightmapParser(void);
	HeightmapParser(const HeightmapParser& t);
	HeightmapParser& operator=(const HeightmapParser& t);
};