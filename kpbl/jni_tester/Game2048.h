#pragma once
#include "gl.h"
#include "BlockMng.h"


namespace kpbl{

	/************ Callback *********/
	typedef void(*FnTestCallback)();
	/******************************/


	class CGame2048
	{
	public:
		CGame2048(void);
		~CGame2048(void);

		bool Initialize(FnTestCallback pFN);  // Initialize

		void RenderReady();
		void Render();
		unsigned int OnTouch(int x, int y);
		

	private:

		CBlockMng m_BlockMng;

		bool _Initialize3D();
		void _SHOthogonal(float left, float bottom, float right, float top, float n, float f, float* pmatrix);
		

		// !!! For call back //
		FnTestCallback m_FnCallback;

	};

}
