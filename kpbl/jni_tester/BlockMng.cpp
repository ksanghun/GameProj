#include "BlockMng.h"
#include <stdlib.h>

namespace kpbl{
	CBlockMng::CBlockMng()
	{
		initBlock(1, 1);		// should be change
	}


	CBlockMng::~CBlockMng()
	{
	}


	void CBlockMng::initBlock(int screenWidth, int screenHeight)
	{
		float blockSize = screenWidth*0.25f;

		int x = 0;
		int y = 0;
		for (x = 0; x < 4; x++){
			for (y = 0; y < 4; y++){
				m_testBlock[y * 4 + x].init(blockSize, blockSize);
				m_testBlock[y * 4 + x].setColor(1.0f, 1.0f, 0.0f);
				m_testBlock[y * 4 + x].setPosition(x*blockSize, y*blockSize);
			}
		}
		m_testBlock[0].setEnable(1);
		m_testBlock[0].setValueOfBlock(1);
	}


	// Create a new block?
	void CBlockMng::newBlock() {
		int i = rand() % 16;
		if (m_testBlock[i].getEnable() == false) {
			m_testBlock[i].setEnable(1);
			m_testBlock[i].setValueOfBlock(1);
		}
	}

	// If you swipe up
	void CBlockMng::swipeUp() {
		int a, i;
    for (a = 0; a < 4; a++) {
      for (i = 4; i < 16; i++) {
        bool a = m_testBlock[i].getEnable();
        bool b = m_testBlock[i - 4].getEnable();
        int aValue = m_testBlock[i].getValueOfBlock();
        int bValue = m_testBlock[i - 4].getValueOfBlock();
        if (a == true && b == false) {
          m_testBlock[i].setEnable(0);
          m_testBlock[i - 4].setEnable(1);
          m_testBlock[i - 4].setValueOfBlock(aValue);
        }
        else if (a == true && b == true
          && aValue == bValue) {
          m_testBlock[i].setEnable(0);
          m_testBlock[i - 4].setValueOfBlock(bValue * 2);
        }
      }
    }
	}

	// If you swipe down
	void CBlockMng::swipeDown() {
		int a, i;
    for (a = 0; a < 4; a++) {
      for (i = 11; i >= 0; i--) {
        bool a = m_testBlock[i].getEnable();
        bool b = m_testBlock[i + 4].getEnable();
        int aValue = m_testBlock[i].getValueOfBlock();
        int bValue = m_testBlock[i + 4].getValueOfBlock();
        if (a == true && b == false) {
          m_testBlock[i].setEnable(0);
          m_testBlock[i + 4].setEnable(1);
          m_testBlock[i + 4].setValueOfBlock(aValue);
        }
        else if (a == true && b == true
          && aValue == bValue) {
          m_testBlock[i].setEnable(0);
          m_testBlock[i + 4].setValueOfBlock(bValue * 2);
        }
      }
    }
	}

	// If you swipe left
	void CBlockMng::swipeLeft() {
    int a, i;
    for (a = 0; a < 4; a++) {
      for (i = 0; i < 16; i++) {
        if (i != 0 && i != 4 && i != 8 && i != 12) {
          bool a = m_testBlock[i].getEnable();
          bool b = m_testBlock[i - 1].getEnable();
          int aValue = m_testBlock[i].getValueOfBlock();
          int bValue = m_testBlock[i - 1].getValueOfBlock();
          if (a == true && b == false) {
            m_testBlock[i].setEnable(0);
            m_testBlock[i - 1].setEnable(1);
            m_testBlock[i - 1].setValueOfBlock(aValue);
          }
          if (a == true && b == true
            && aValue == bValue) {
            m_testBlock[i].setEnable(0);
            m_testBlock[i - 1].setValueOfBlock(bValue * 2);
          }
        }
      }
    }
	}

	// If you swipe right
	void CBlockMng::swipeRight() {
    int a, i;
    for (a = 0; a < 4; a++) {
      for (i = 15; i >= 0; i--) {
        if (i != 3 && i != 7 && i != 11 && i != 15) {
          bool a = m_testBlock[i].getEnable();
          bool b = m_testBlock[i + 1].getEnable();
          int aValue = m_testBlock[i].getValueOfBlock();
          int bValue = m_testBlock[i + 1].getValueOfBlock();
          if (a == true && b == false) {
            m_testBlock[i].setEnable(0);
            m_testBlock[i + 1].setEnable(1);
            m_testBlock[i + 1].setValueOfBlock(aValue);
          }
          if (a == true && b == true
            && aValue == bValue) {
            m_testBlock[i].setEnable(0);
            m_testBlock[i + 1].setValueOfBlock(bValue * 2);
          }
        }
      }
    }
	}


	void CBlockMng::drawBlocks()
	{
		int i = 0;
		for (i = 0; i < 16; i++){
			m_testBlock[i].draw();
		}
	}


}
