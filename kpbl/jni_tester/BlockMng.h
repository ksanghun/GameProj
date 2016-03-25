#pragma once

#include "NumBlock.h"

namespace kpbl{

	class CBlockMng
	{
		CNumBlock m_testBlock[16];		// How many we need?? static allocation? dynamic allocation??


	public:
		CBlockMng();
		~CBlockMng();

		void initBlock(int screenWidth, int screenHeight);
		void drawBlocks();

	};

}

