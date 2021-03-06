/*************************************************************************//*!
					
					@file	DX11RenderTarget.h
					@brief	DirectX11描画ターゲットクラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__DX11RENDERTARGET__H__

#define		__DX11RENDERTARGET__H__

//INCLUDE
#include	"../RenderTarget.h"

namespace Mof {
	
	/*******************************//*!
	@brief	DirectX11描画ターゲットクラス

			DirectX11描画ターゲットクラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CDX11RenderTarget : public IRenderTarget {
	protected:
		/*******************//*!
		作成グラフィックス
		*//********************/
		LPGraphics				m_pGraphics;
		/*******************//*!
		描画ターゲット
		*//********************/
		ID3D11RenderTargetView*	m_pRenderTargetView;
		/*******************//*!
		クリアカラー
		*//********************/
		Vector4					m_ClearColor;
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CDX11RenderTarget();
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CDX11RenderTarget();
		/*************************************************************************//*!
				@brief			描画ターゲットの生成
				@param[in]		pGraphics	グラフィックスインターフェイス
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Create(LPGraphics pGraphics);
		/*************************************************************************//*!
				@brief			描画ターゲットの生成
				@param[in]		pRenderTarget	描画ターゲット
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Create(MofRenderTarget pRenderTarget);
		/*************************************************************************//*!
				@brief			解放
				@param[in]		pData			解放追加データ

				@return			TRUE			正常終了<br>
								それ以外		解放エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool Release(LPMofVoid pData = NULL);
		
		//----------------------------------------------------------------------------
		////Set
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			クリアカラー設定
				@param[in]		Color	クリアカラー

				@return			None
		*//**************************************************************************/
		virtual void SetClearColor(Vector4& Color);
										
		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			描画ターゲット取得
				@param			None

				@return			描画ターゲット
		*//**************************************************************************/
		virtual MofRenderTarget GetTarget(void);
		/*************************************************************************//*!
				@brief			クリアカラー取得
				@param			None

				@return			クリアカラー
		*//**************************************************************************/
		virtual const Vector4& GetClearColor(void)const;

		//クラス基本定義
		MOF_LIBRARYCLASS(CDX11RenderTarget,MOF_DX11RENDERTARGETCLASS_ID);
	};

	#include	"DX11RenderTarget.inl"

	//置き換え
	typedef CDX11RenderTarget		CRenderTarget;
}

#endif

//[EOF]