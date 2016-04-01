#include "Game2048.h"
#include "string.h"

namespace kpbl{

	CGame2048::CGame2048()
	{
	}


	CGame2048::~CGame2048()
	{
	}

	bool CGame2048::_Initialize3D()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glAlphaFunc(GL_ALWAYS, 1.0f);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


		glAlphaFunc(GL_GREATER, 0.5f);
		m_FnCallback();

		return true;
	}

	bool CGame2048::Initialize(FnTestCallback pFN)
	{
		m_FnCallback = pFN;

		// Initialize OpenGL //
		bool ret = _Initialize3D();

		return ret;
	}

	void CGame2048::Render()
	{
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//	glEnableClientState(GL_VERTEX_ARRAY);
		//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


		m_BlockMng.drawBlocks();

		// Jennie is testing from here ...

		//m_BlockMng.swipeDown();
		//m_BlockMng.swipeUp();
		//m_BlockMng.swipeLeft();
		m_BlockMng.swipeRight();

		m_BlockMng.newBlock();

		// ... until here


		//	glDisableClientState(GL_VERTEX_ARRAY);
		//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		m_FnCallback();
	}

	//by Tony
	void CGame2048::checkPosition(float pt_x, float pt_y){
		m_BlockMng.swipeDown();
		m_BlockMng.swipeUp();
		m_BlockMng.swipeLeft();
		m_BlockMng.swipeRight();
	}

	void CGame2048::RenderReady()
	{
		float ProjectionMatrix[16] = { 0, };
		GLint viewport[4] = { 0, };

		glGetIntegerv(GL_VIEWPORT, viewport);

		int width = viewport[2];
		int height = viewport[3];

		_SHOthogonal(0.0f, 0.0f, (float)width, (float)height, 0.0f, 100.0f, ProjectionMatrix);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glEnable(GL_TEXTURE_2D);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMultMatrixf(ProjectionMatrix);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		m_BlockMng.initBlock(width, height);

	}


	void CGame2048::_SHOthogonal(float left, float bottom, float right, float top, float n, float f, float* pmatrix)
	{
		if (!pmatrix)
			return;

		memset(pmatrix, 0, sizeof(16));
		pmatrix[0] = pmatrix[5] = pmatrix[10] = pmatrix[15] = 1.0f;

		float l = -(right - left) / 2.0f;
		float r = (right - left) / 2.0f;
		float b = -(top - bottom) / 2.0f;
		float t = (top - bottom) / 2.0f;

		pmatrix[0] = 2.0f / (r - l);
		pmatrix[5] = -2.0f / (t - b);
		pmatrix[10] = -2.0f / (f - n);

		pmatrix[12] = -1.0f;//-(r+l)/(r-l);
		pmatrix[13] = 1.0f;//-(t+b)/(t-b);
		pmatrix[14] = -1.0f*(f + n) / (f - n);

		return;
	}

}
