#include "Game2048.h"

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

		GLint viewport[4] = { 0, };
		glGetIntegerv(GL_VIEWPORT, viewport);
		glEnable(GL_TEXTURE_2D);
		
		return ret;
	}

	void CGame2048::RenderReady()
	{
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		
		
		m_FnCallback();
	}
}
