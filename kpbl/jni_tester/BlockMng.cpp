#include "BlockMng.h"
#include <stdlib.h>

namespace kpbl{
	CBlockMng::CBlockMng()
	{
		initBlock(1,1);		// should be change
	}


	CBlockMng::~CBlockMng()
	{
	}


	void CBlockMng::initBlock(int screenWidth, int screenHeight)
	{
		float blockSize = screenWidth*0.25f;

		// This is test code, should be removed !!
		int x = 0;
		int y = 0;
		for (x = 0; x < 4; x++){
			for (y = 0; y < 4; y++){
				m_testBlock[y * 4 + x].init(blockSize, blockSize);
				m_testBlock[y * 4 + x].setColor(1.0f, 1.0f, 0.0f);
				m_testBlock[y * 4 + x].setPosition(x*blockSize, y*blockSize);
				
			}
		}
		


		// This is test code, should be removed !!
	}

	void CBlockMng::drawBlocks()
	{
		int i = 0;
		for (i = 0; i < 16; i++){
			m_testBlock[i].draw();

			// Test code, should be removeed !!!! //
			m_testBlock[i].setEnable(rand() % 2);


		}
	}

}
