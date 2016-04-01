#include "NumBlock.h"

#define Y_SHIFT 200

namespace kpbl{
	CNumBlock::CNumBlock()
	{
		m_pVertex = nullptr;
		m_pTexCoord = nullptr;

		init();
	}

	CNumBlock::~CNumBlock()
	{
		delete[] m_pVertex;
		delete[] m_pTexCoord;
	}

	void CNumBlock::init(float width, float height)
	{
		m_number = 2;
		m_bLive = false;
		m_position_x = 0;
		m_position_y = 0;
		m_width = 0.0f;
		m_height = 0.0f;
		m_texid = 0;

		m_color[0] = 1.0f;
		m_color[1] = 1.0f;
		m_color[2] = 1.0f;

		if (m_pVertex != nullptr){
			delete[] m_pVertex;
		}
		if (m_pTexCoord != nullptr){
			delete[] m_pTexCoord;
		}

		m_pVertex = new float[3 * 6];
		m_pTexCoord = new float[2 * 6];

		makeQuad(width, height);
	}

	void CNumBlock::setColor(float r, float g, float b)
	{
		m_color[0] = r;
		m_color[1] = g;
		m_color[2] = b;
	}

	void CNumBlock::setPosition(float x, float y)
	{
		m_position_x = x + m_width*0.5f;
		m_position_y = y + m_height*0.5f;
	}

	void CNumBlock::setEnable(bool isLive)
	{
		m_bLive = isLive;
	}

	bool CNumBlock::getEnable() {
		return m_bLive;
	}

	void CNumBlock::makeQuad(float width, float height)
	{
		m_width = width;
		m_height = height;

		float halfW = width*0.48f;
		float halfH = height*0.48f;

		// 1. Triangle Geometry ==============================================//
		// upper triangle - CCW //
		m_pVertex[0] = -halfW;	m_pVertex[1] = halfH;		m_pVertex[2] = 0.0f;
		m_pVertex[3] = -halfW;	m_pVertex[4] = -halfH;		m_pVertex[5] = 0.0f;
		m_pVertex[6] = halfW;	m_pVertex[7] = halfH;		m_pVertex[8] = 0.0f;

		// lower triangle - CCW //
		m_pVertex[9] = -halfW;	m_pVertex[10] = -halfH;		m_pVertex[11] = 0.0f;
		m_pVertex[12] = halfW;	m_pVertex[13] = -halfH;		m_pVertex[14] = 0.0f;
		m_pVertex[15] = halfW;	m_pVertex[16] = halfH;		m_pVertex[17] = 0.0f;

		// 2. Texture coordinates =================//
		m_pTexCoord[0] = 0.0f;	m_pTexCoord[1] = 1.0f;
		m_pTexCoord[2] = 0.0f;	m_pTexCoord[3] = 0.0f;
		m_pTexCoord[4] = 1.0f;	m_pTexCoord[5] = 1.0f;

		// lower triangle - CCW //
		m_pTexCoord[6] = 0.0f;	m_pTexCoord[7] = 0.0f;
		m_pTexCoord[8] = 1.0f;	m_pTexCoord[9] = 0.0f;
		m_pTexCoord[10] = 1.0f;	m_pTexCoord[11] = 1.0f;
	}

	void CNumBlock::draw()
	{
		if (m_bLive){
			glColor4f(m_color[0], m_color[1], m_color[2], 1.0f);
		}
		else{
			glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
		}

		glVertexPointer(3, GL_FLOAT, 0, m_pVertex);
		glTexCoordPointer(2, GL_FLOAT, 0, m_pTexCoord);

		glPushMatrix();
		glTranslatef(m_position_x, m_position_y + Y_SHIFT, 0.0f);
		glBindTexture(GL_TEXTURE_2D, m_texid);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glPopMatrix();
	}

	// Jennie's addition
	void CNumBlock::setValueOfBlock(int value) {
		valueOfBlock = value;
		setColor(value * 10, value*0.1, value);
	}
	// Jennie's addition
	int CNumBlock::getValueOfBlock() {
		return valueOfBlock;
	}

}