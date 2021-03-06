/*************************************************************************//*!
					
					@file	Utilities.h
					@brief	汎用処理をまとめたスタティッククラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__UTILITIES__H__

#define		__UTILITIES__H__

//INCLUDE
#include	"../Math/Random.h"
#include	"../Framework/Framework.h"
#include	"../Framework/FrameTimer.h"
#include	"../Network/UdpSocket.h"

#ifdef		MOFLIB_WINDOWS_DESKTOP
#include	"../Framework/Window/Windows/ImeProc.h"
#endif

namespace Mof {

	/*******************************//*!
	@brief	汎用処理をまとめたスタティッククラス

			汎用処理をまとめたスタティッククラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CUtilities {
	private:
		/*******************//*!
		動作フレームワーク
		*//********************/
		static LPFramework			m_pFramework;
		/*******************//*!
		フレームタイム計測
		*//********************/
		static LPFrameTimer			m_pFrameTimer;
		/*******************//*!
		乱数
		*//********************/
		static CRandom				m_Random;
		/*******************//*!
		カレントディレクトリ
		*//********************/
		static CString				m_CurrentDirectory;

#ifdef		MOFLIB_ANDROID
		/*******************//*!
		JNI
		*//********************/
		static JNIEnv*				m_Env;
		/*******************//*!
		呼び出しオブジェクト
		*//********************/
		static jobject				m_Thiz;
#endif

#ifdef		MOFLIB_WINDOWS
		/*******************//*!
		呼び出しオブジェクト
		*//********************/
		static MofBool				m_bNetwork;
#endif
	public:
		/*************************************************************************//*!
				@brief			基礎データを作成する
				@param			None
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		static MofBool CreateUtilities(void);
		/*************************************************************************//*!
				@brief			基礎データを破棄する
				@param			None
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		static MofBool ReleaseUtilities(void);
		
		//----------------------------------------------------------------------------
		////タイマー関連
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			タイマーの更新<br>
								タイマーの更新を行う。<br>
								前回この関数が呼び出されてから、今回実行されるまでの時間を計測しフレーム時間に設定する。<br>
								bWaitがTRUEなら設定されているFPSまでの余剰時間分をsleepにより待機する。<br>
								FPSが設定されていない場合やbWaitがFALSEの場合は待機処理は行われない。
				@param[in]		bWait		FPSウェイトフラグ
			
				@return			None
		*//**************************************************************************/
		static void UpdateTimer(MofBool bWait);

		//----------------------------------------------------------------------------
		////乱数の生成
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			乱数生成
				@param			None

				@return			発生した乱数を返す
		*//**************************************************************************/
		static MofU32 Random(void);
		/*************************************************************************//*!
				@brief			乱数生成<br>
								0〜引数の最大値未満の範囲の乱数が発生する
				@param[in]		h				最大値

				@return			発生した乱数を返す
		*//**************************************************************************/
		static MofU32 Random(MofU32 h);
		/*************************************************************************//*!
				@brief			乱数生成<br>
								引数の最少値〜引数の最大値未満の範囲の乱数が発生する
				@param[in]		l				最少値
				@param[in]		h				最大値

				@return			発生した乱数を返す
		*//**************************************************************************/
		static MofU32 Random(MofU32 l,MofU32 h);
		/*************************************************************************//*!
				@brief			(0.0f〜1.0f)の範囲の乱数生成
				@param			None

				@return			発生した乱数を返す
		*//**************************************************************************/
		static  MofFloat RandomFloat(void);
		
		//----------------------------------------------------------------------------
		////Set
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			フレームワークを設定する
				@param[in]		pfw			フレームワーク
				
				@return			TRUE		正常に設定された<br>
								FALSE		設定の失敗
		*//**************************************************************************/
		static MofBool SetFramework(LPFramework pfw);
		/*************************************************************************//*!
				@brief			FPSの設定<br>
								FPSの固定をする場合に設定を行う。<br>
								引数のFPSに0を設定すると固定なしの時間計測のみの処理になる。
				@param[in]		s			FPS
			
				@return			TRUE		正常に設定された<br>
								FALSE		設定の失敗
		*//**************************************************************************/
		static MofBool SetFPS(MofU32 s);
		/*************************************************************************//*!
				@brief			フレーム時間の設定<br>
								このタイマーで経過したフレーム時間を引数のミリ秒に差し替える。
				@param[in]		s			フレーム時間(msec)
			
				@return			TRUE		正常に設定された<br>
								FALSE		設定の失敗
		*//**************************************************************************/
		static MofBool SetFrameMSecond(MofU32 s);
		/*************************************************************************//*!
				@brief			乱数の種を設定する
				@param[in]		s				種

				@return			None
		*//**************************************************************************/
		static void SetSeed(MofU32 s);
		/*************************************************************************//*!
				@brief			カレントディレクトリを設定する
				@param[in]		pPath		カレントディレクトリパス
				
				@return			TRUE		正常に設定された<br>
								FALSE		設定の失敗
		*//**************************************************************************/
		static MofBool SetCurrentDirectory(LPCMofChar pPath);
		
		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			フレームワークを取得する
				@param			None

				@return			フレームワーク
		*//**************************************************************************/
		static LPFramework GetFramework(void);
		/*************************************************************************//*!
				@brief			インスタンスハンドル取得する
				@param			None

				@return			インスタンスハンドル
		*//**************************************************************************/
		static MofInstanceHandle GetInstanceHandle(void);
		/*************************************************************************//*!
				@brief			制限FPS取得
				@param			None

				@return			FPSの制限値
		*//**************************************************************************/
		static MofU32 GetRestrictFPS(void);
		/*************************************************************************//*!
				@brief			制限フレーム時間取得
				@param			None

				@return			フレーム時間の制限値
		*//**************************************************************************/
		static MofU32 GetRestrictFrameTime(void);
		/*************************************************************************//*!
				@brief			FPS取得
				@param			None

				@return			計測されたFPS
		*//**************************************************************************/
		static MofU32 GetFPS(void);
		/*************************************************************************//*!
				@brief			フレーム時間取得<br>
								取得するフレーム時間の単位はミリ秒
				@param			None

				@return			フレーム時間(msec)
		*//**************************************************************************/
		static MofU32 GetUpdateFrameTime(void);
		/*************************************************************************//*!
				@brief			フレーム時間取得<br>
								取得するフレーム時間の単位はミリ秒
				@param			None

				@return			フレーム時間(msec)
		*//**************************************************************************/
		static MofU32 GetFrameMSecond(void);
		/*************************************************************************//*!
				@brief			フレーム時間取得<br>
								取得するフレーム時間の単位は秒
				@param			None

				@return			フレーム時間(sec)
		*//**************************************************************************/
		static MofFloat GetFrameSecond(void);
		/*************************************************************************//*!
				@brief			カレントディレクトリを取得する
				@param			None
				
				@return			カレントディレクトリのパス
		*//**************************************************************************/
		static LPMofChar GetCurrentDirectory(void);

#ifdef		MOFLIB_ANDROID
		/*************************************************************************//*!
				@brief			JNI呼び出し元設定

								JNI呼び出し情報を設定します

				@param[in]		env				JNI
				@param[in]		obj				JNI呼び出しオブジェクト

				@return			None
		*//**************************************************************************/
		static void SetJNICall(JNIEnv* env,jobject obj);
		/*************************************************************************//*!
				@brief			JNI呼び出し元取得

								JNI呼び出し情報を取得します

				@param			None

				@return			JNI
		*//**************************************************************************/
		static JNIEnv* GetJNIEnv(void);
		/*************************************************************************//*!
				@brief			JNI呼び出し元取得

								JNI呼び出し情報を取得します

				@param			None

				@return			JNI
		*//**************************************************************************/
		static jobject GetJNIObject(void);
#endif
#ifdef		MOFLIB_WINDOWS
		/*************************************************************************//*!
				@brief			WSA初期化
				@param			None

				@return			TRUE			正常終了<br>
								それ以外		初期化エラー、エラーコードを返す。
		*//**************************************************************************/
		static MofBool WSAInitialize();
		/*************************************************************************//*!
				@brief			WSA終了
				@param			None

				@return			TRUE			正常終了<br>
								それ以外		初期化エラー、エラーコードを返す。
		*//**************************************************************************/
		static MofBool WSARelease();
#endif
	private:
		//作成を禁止する
		CUtilities(){};
		CUtilities(const CUtilities& pObj){};
	};

	#include	"Utilities.inl"
}

#endif

//[EOF]
