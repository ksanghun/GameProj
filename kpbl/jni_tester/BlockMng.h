#pragma once
#include "NumBlock.h"

namespace kpbl{

#define rowNum 4
#define colNum 4
#define totNum rowNum*colNum

	class CBlockMng
	{
		CNumBlock m_testBlock[totNum];		// How many we need?? static allocation? dynamic allocation??

	public:
		CBlockMng();
		~CBlockMng();

		void initBlock(int screenWidth, int screenHeight);

		void newBlock();

		void swipeUp();
		void swipeDown();
		void swipeLeft();
		void swipeRight();

		void drawBlocks();

	};

}

