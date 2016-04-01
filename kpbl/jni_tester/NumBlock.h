#pragma once

#include "gl.h"

namespace kpbl{

	class CNumBlock
	{
		unsigned short m_number;
		bool m_bLive;

		float m_position_x;
		float m_position_y;
		float m_width;
		float m_height;


		// For drawing data //
		float* m_pVertex;
		float* m_pTexCoord;
		float m_color[3];
		unsigned int m_texid;
		//===================//

		// Jennie's addition
		int valueOfBlock;


	public:
		CNumBlock();
		~CNumBlock();

		void init(float width = 1.0f, float height = 1.0f);
		void makeQuad(float width, float height);
		void draw();

		void setColor(float r, float g, float b);
		void setPosition(float x, float y);
		void setEnable(bool bLive);

		bool getEnable();
		void setValueOfBlock(int value);
		int getValueOfBlock();

	};

}

