/*************************************************************************//*!
					
					@file	GLMesh.h
					@brief	OpenGLメッシュクラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__GLMESH__H__

#define		__GLMESH__H__

//INCLUDE
#include	"../MeshBase.h"
#include	"GLGeometry.h"

namespace Mof {
	
	/*******************************//*!
	@brief	メッシュ基底クラス

			メッシュ基底クラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CGLMesh : public CMeshBase {
	private:
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CGLMesh();
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param			pObj		コピージオメトリ

				@return			None
		*//**************************************************************************/
		CGLMesh(const CGLMesh& pObj);
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CGLMesh();
		
		/*************************************************************************//*!
				@brief			メッシュのコピー生成
				@param			None
				
				@return			作成されたコピーメッシュ<br>
								作成に失敗した場合NULLを返す
		*//**************************************************************************/
		virtual IMesh* CreateCopyObject(void) const;
				
		//クラス基本定義
		MOF_LIBRARYCLASS(CGLMesh,MOF_GLMESHCLASS_ID);
	};

	#include	"GLMesh.inl"
	
	//置き換え
	typedef CGLMesh		CMesh;
}

#endif	//__GLMESH__H__

//[EOF]
