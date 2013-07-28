#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
//====================================================================

//====================== HeightmapParser Class =========================
// Description:
//		Parse heightmaps with this class.
// Last Modification: 28/05/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================


class HeightmapParser 
{
public:
	//read a heightmap
	static bool Read(const tstring & file, UINT width, UINT height, float heightDivider = 1.0f, float scale = 1.0f, float texScale = 1.0f);
	static bool Read(const tstring & file, UINT width, UINT height, vector<vector<D3DXVECTOR3>> & vertex2DVec, D3DXVECTOR2 & depthInfo, float heightDivider = 1.0f, float scale = 1.0f, float texScale = 1.0f);

private:
	static bool LoadHeightMap(const tstring & file, int width, int height, std::vector<char> & heightmapVec);
	// -------------------------
	// Disabling default copy constructor, default 
	// assignment operator, default constructor and destructor
	// -------------------------
	~HeightmapParser(void);
	HeightmapParser(void);
	HeightmapParser(const HeightmapParser& t);
	HeightmapParser& operator=(const HeightmapParser& t);
};

