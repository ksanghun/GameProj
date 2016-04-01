#include "BlockMng.h"
#include <stdlib.h>

namespace kpbl{

	CBlockMng::CBlockMng()
	{
		initBlock(1, 1);
	}

	CBlockMng::~CBlockMng()
	{
	}

	void CBlockMng::initBlock(int screenWidth, int screenHeight)
	{
		float blockSize = screenWidth*0.25f;

		int x, y;
		for (x = 0; x < rowNum; x++){
			for (y = 0; y < colNum; y++){
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
		int i = rand() % totNum;
		if (m_testBlock[i].getEnable() == false) {
			m_testBlock[i].setEnable(1);
			m_testBlock[i].setValueOfBlock(1);
		}
	}

	// If you swipe up
	void CBlockMng::swipeUp() {
		int a, i;
    for (a = 0; a < rowNum; a++) {
      for (i = colNum; i < totNum; i++) {
        bool a = m_testBlock[i].getEnable();
        bool b = m_testBlock[i - colNum].getEnable();
        int aValue = m_testBlock[i].getValueOfBlock();
        int bValue = m_testBlock[i - colNum].getValueOfBlock();
        if (a == true && b == false) {
          m_testBlock[i].setEnable(0);
          m_testBlock[i - colNum].setEnable(1);
          m_testBlock[i - colNum].setValueOfBlock(aValue);
        }
        else if (a == true && b == true
          && aValue == bValue) {
          m_testBlock[i].setEnable(0);
          m_testBlock[i - colNum].setValueOfBlock(bValue * 2);
        }
      }
    }
	}

	// If you swipe down
	void CBlockMng::swipeDown() {
		int a, i;
    for (a = 0; a < rowNum; a++) {
      for (i = totNum-colNum-1; i >= 0; i--) {
        bool a = m_testBlock[i].getEnable();
        bool b = m_testBlock[i + colNum].getEnable();
        int aValue = m_testBlock[i].getValueOfBlock();
        int bValue = m_testBlock[i + colNum].getValueOfBlock();
        if (a == true && b == false) {
          m_testBlock[i].setEnable(0);
          m_testBlock[i + colNum].setEnable(1);
          m_testBlock[i + colNum].setValueOfBlock(aValue);
        }
        else if (a == true && b == true
          && aValue == bValue) {
          m_testBlock[i].setEnable(0);
          m_testBlock[i + colNum].setValueOfBlock(bValue * 2);
        }
      }
    }
	}

	// If you swipe left
	void CBlockMng::swipeLeft() {
    int a, i;
    for (a = 0; a < colNum; a++) {
      for (i = 0; i < totNum; i++) {
        if (i != 0 && i != colNum && i != colNum*2 && i != colNum*3) { // need to change
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
    for (a = 0; a < colNum; a++) {
      for (i = totNum-1; i >= 0; i--) {
        if (i != colNum*1-1 && i != colNum*2-1 && i != colNum*3-1 && i != colNum*4-1) { // need to change
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
		for (i = 0; i < totNum; i++){
			m_testBlock[i].draw();
		}
	}

}
