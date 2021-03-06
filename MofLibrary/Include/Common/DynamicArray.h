/*************************************************************************//*!
					
					@file	DynamicArray.h
					@brief	動的配列の確保、管理の処理を行うクラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__DYNAMICARRAY__H__

#define		__DYNAMICARRAY__H__

//INCLUDE
#include	"String.h"
#include	"CRC32.h"
#include	"SmartPointer.h"

namespace Mof {
	
	
	/*******************************//*!
	@brief	動的配列管理フラグ列挙

			動的配列の管理フラグ列挙。

	@author	CDW
	*//********************************/
	enum tag_DYNAMICARRAYFLAG {
		DYNAMICARRAY_ARRAYMEMBERDELETE		=		0x00000001,
		DYNAMICARRAY_ARRAYMEMBERCOPY		=		0x00000002,

		DYNAMICARRAY_FLAGALL				=		0xFFFFFFFF,
	};
	
	/*******************************//*!
	@brief	動的配列クラス内部特殊化定義

			動的配列の確保、管理の処理を行うための内部テンプレートを
			定義する内部クラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CDynamicArrayImpl {
	protected:
		/*************************************************************************//*!
				@brief			内部コピー<br>
								内部コピー処理を特殊化で処理<br>
								ポインタ型でIMofCopyObjectを継承しておりDYNAMICARRAY_ARRAYMEMBERCOPYフラグが立っている場合は内部のデータにコピーコンストラクタを実行する。<br>
								ポインタ型でIMofCopyObjectを継承していない状態でDYNAMICARRAY_ARRAYMEMBERCOPYフラグが立っている場合は内部データのコピーでassert発生させる。
		*//**************************************************************************/
		template < typename TX , bool bt = false > struct CopyImpl {
			static MofBool Run(TX* pDest,TX* pSrc,MofU32 Count)
			{
				for(MofU32 i = 0;i < Count;i++)
				{
					pDest[i] = pSrc[i];
				}
				return TRUE;
			}
		};
		/*************************************************************************//*!
				@brief			内部コピー<br>
								内部コピー処理を特殊化で処理<br>
								ポインタ型でIMofCopyObjectを継承しておりDYNAMICARRAY_ARRAYMEMBERCOPYフラグが立っている場合は内部のデータにコピーコンストラクタを実行する。<br>
								ポインタ型でIMofCopyObjectを継承していない状態でDYNAMICARRAY_ARRAYMEMBERCOPYフラグが立っている場合は内部データのコピーでassert発生させる。
		*//**************************************************************************/
		template < typename TX > struct CopyImpl< TX*, false > {
			static MofBool Run(TX** pDest,TX** pSrc,MofU32 Count)
			{
				assert(false);
				return TRUE;
			}
		};
		/*************************************************************************//*!
				@brief			内部コピー<br>
								内部コピー処理を特殊化で処理<br>
								ポインタ型でIMofCopyObjectを継承しておりDYNAMICARRAY_ARRAYMEMBERCOPYフラグが立っている場合は内部のデータにコピーコンストラクタを実行する。<br>
								ポインタ型でIMofCopyObjectを継承していない状態でDYNAMICARRAY_ARRAYMEMBERCOPYフラグが立っている場合は内部データのコピーでassert発生させる。
		*//**************************************************************************/
		template < typename TX > struct CopyImpl< TX*, true > {
			static MofBool Run(TX** pDest,TX** pSrc,MofU32 Count)
			{
				for(MofU32 i = 0;i < Count;i++)
				{
					if (pSrc[i])
					{
						pDest[i] = (TX*)pSrc[i]->CreateCopyObject();
					}
					else
					{
						pDest[i] = NULL;
					}
				}
				return TRUE;
			}
		};
					  
		/*************************************************************************//*!
				@brief			内部名前検索<br>
								内部名前検索処理を特殊化で処理<br>
								ポインタ型でIMofNamedObjectを継承している場合、GetNameで取得できる名前と引数を比較する
		*//**************************************************************************/
		template < typename TX , bool bt = false > struct FindNameImpl {
			static TX* Run(TX* pObj,MofU32 Count,LPCMofChar pName)
			{
				return NULL;
			}
		};
		/*************************************************************************//*!
				@brief			内部名前検索<br>
								内部名前検索処理を特殊化で処理<br>
								ポインタ型でIMofNamedObjectを継承している場合、GetNameで取得できる名前と引数を比較する
		*//**************************************************************************/
		template < typename TX > struct FindNameImpl< TX, true > {
			static TX* Run(TX* pObj,MofU32 Count,LPCMofChar pName)
			{
				for(MofU32 i = 0;i < Count;i++)
				{
					if(pObj[i].GetName()->Compare(pName) == 0)
					{
						return &pObj[i];
					}
				}
				return NULL;
			}
		};
		/*************************************************************************//*!
				@brief			内部名前検索<br>
								内部名前検索処理を特殊化で処理<br>
								ポインタ型でIMofNamedObjectを継承している場合、GetNameで取得できる名前と引数を比較する
		*//**************************************************************************/
		template < typename TX > struct FindNameImpl< TX*, true > {
			static TX** Run(TX** pObj,MofU32 Count,LPCMofChar pName)
			{
				for(MofU32 i = 0;i < Count;i++)
				{
					if(pObj[i]->GetName()->Compare(pName) == 0)
					{
						return &pObj[i];
					}
				}
				return NULL;
			}
		};
		/*************************************************************************//*!
				@brief			内部解放<br>
								内部解放処理を特殊化で処理<br>
								ポインタ型でDYNAMICARRAY_ARRAYMEMBERDELETEフラグが立っている場合は内部のデータにDeleteを実行する。
		*//**************************************************************************/
		template < typename TX > struct ReleaseImpl {
			static MofBool Run(TX& pVal)
			{
				return TRUE;
			}
			static MofBool Run(LPMofVoid pData,TX* pArray,MofU32 Count)
			{
				MOF_SAFE_DELETE_ARRAY(pArray);
				return TRUE;
			}
		};
		/*************************************************************************//*!
				@brief			内部解放<br>
								内部解放処理を特殊化で処理<br>
								ポインタ型でDYNAMICARRAY_ARRAYMEMBERDELETEフラグが立っている場合は内部のデータにDeleteを実行する。
		*//**************************************************************************/
		template < typename TX > struct ReleaseImpl<TX*> {
			static MofBool Run(TX* pVal)
			{
				MOF_SAFE_DELETE(pVal);
				return TRUE;
			}
			static MofBool Run(LPMofVoid pData,TX** pArray,MofU32 Count)
			{
				for(MofU32 i = 0;i < Count;i++)
				{
					MOF_SAFE_DELETE(pArray[i]);
				}
				MOF_SAFE_DELETE_ARRAY(pArray);
				return TRUE;
			}
		};
	public:
	};
	
	/*******************************//*!
	@brief	動的配列クラス

			動的配列の確保、管理の処理を行うクラス。

	@author	CDW
	*//********************************/
	template < typename T >
	class MOFLIBRARY_API CDynamicArray : public IMofObject , public CDynamicArrayImpl {
	protected:
		/*******************//*!
		配列要素
		*//********************/
		T*					m_pArray;
		/*******************//*!
		要素数
		*//********************/
		MofU32				m_Count;
		/*******************//*!
		フラグ
		*//********************/
		MofU32				m_Flag;
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CDynamicArray();
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		Count			要素数

				@return			None
		*//**************************************************************************/
		CDynamicArray(MofU32 Count);
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		List			要素
				@param[in]		Count			要素数

				@return			None
		*//**************************************************************************/
		CDynamicArray(T* List,MofU32 Count);
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param[in]		pObj			コピー配列

				@return			None
		*//**************************************************************************/
		CDynamicArray(const CDynamicArray< T >& pObj);
		
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CDynamicArray();
		
		/*************************************************************************//*!
				@brief			配列最後尾に要素の追加
				@param			None
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool Add(void);
		/*************************************************************************//*!
				@brief			配列最後尾に要素の追加
				@param[in]		Data			追加データ
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool Add(T* Data);
		/*************************************************************************//*!
				@brief			配列最後尾に要素の追加
				@param[in]		Data			追加データ
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool Add(const T& Data);
		/*************************************************************************//*!
				@brief			配列先頭に要素の追加
				@param			None
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool AddFast(void);
		/*************************************************************************//*!
				@brief			配列先頭に要素の追加
				@param[in]		Data			追加データ
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool AddFast(T* Data);
		/*************************************************************************//*!
				@brief			配列先頭に要素の追加
				@param[in]		Data			追加データ
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool AddFast(const T& Data);
		/*************************************************************************//*!
				@brief			配列指定位置に要素の追加
				@param[in]		No				追加位置
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool AddNo(MofU32 No);
		/*************************************************************************//*!
				@brief			配列指定位置に要素の追加
				@param[in]		Data			追加データ
				@param[in]		No				追加位置
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool AddNo(T* Data,MofU32 No);
		/*************************************************************************//*!
				@brief			配列指定位置に要素の追加
				@param[in]		Data			追加データ
				@param[in]		No				追加位置
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool AddNo(const T& Data,MofU32 No);
		/*************************************************************************//*!
				@brief			配列最後尾に要素の追加
				@param			None
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool AddLast(void);
		/*************************************************************************//*!
				@brief			配列最後尾に要素の追加
				@param[in]		Data			追加データ
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool AddLast(T* Data);
		/*************************************************************************//*!
				@brief			配列最後尾に要素の追加
				@param[in]		Data			追加データ
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool AddLast(const T& Data);
		/*************************************************************************//*!
				@brief			配列最後尾に引数の配列要素を追加
				@param[in]		m				追加データ
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool AddList(CDynamicArray< T >* m);
		/*************************************************************************//*!
				@brief			配列指定要素の削除
				@param[in]		Data			削除要素
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Delete(T* Data);
		/*************************************************************************//*!
				@brief			配列指定位置の要素の削除
				@param[in]		No				削除位置
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Delete(MofU32 No);
		/*************************************************************************//*!
				@brief			配列先頭の要素の削除
				@param			None
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool DeleteFast(void);
		/*************************************************************************//*!
				@brief			配列最後尾の要素の削除
				@param			None
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		MofBool DeleteLast(void);
		/*************************************************************************//*!
				@brief			配列の要素位置を入れ替える
				@param[in]		Ind1			配列要素位置
				@param[in]		Ind2			配列要素位置
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Swap(MofU32 Ind1,MofU32 Ind2);

		/*************************************************************************//*!
				@brief			配列のソートを実行する
				@param[in]		pFunc			比較関数
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Sort(int (*pFunc)(const void *, const void *));
		/*************************************************************************//*!
				@brief			配列のソートを実行する
				@param[in]		pFunc			比較関数
				@param[in]		Count			ソート対象数
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Sort(int (*pFunc)(const void *, const void *),MofU32 Count);

		/*************************************************************************//*!
				@brief			配列内で名前で検索を行う。
								ポインタ型でIMofNamedObjectを継承している場合、GetNameで取得できる名前と引数を比較する<br>
								IMofNamedObjectを継承していない場合は検索に失敗する。
				@param[in]		pName			名前
				
				@return			発見した要素のアドレス
								見つからなかった場合NULLを返す
		*//**************************************************************************/
		virtual T* Find(LPCMofChar pName);
		/*************************************************************************//*!
				@brief			配列の件数を設定する
				@param[in]		Count			要素数
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool ReSize(MofU32 Count);
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
				@brief			配列の件数、データを設定する
				@param[in]		pData			要素
				@param[in]		Count			要素数
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetArray(T* pData,MofU32 Count);
		/*************************************************************************//*!
				@brief			配列の指定要素に対してデータを設定する
				@param[in]		Data			要素
				@param[in]		No				要素位置
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetData(const T& Data,MofU32 No);
		/*************************************************************************//*!
				@brief			フラグの設定
				@param[in]		Flag			フラグ
			
				@return			TRUE			正常に設定された<br>
								FALSE			追加の失敗
		*//**************************************************************************/
		MofBool SetFlag(MofU32 Flag);

		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			配列要素数取得
				@param			None

				@return			配列要素数
		*//**************************************************************************/
		MofU32 GetArrayCount(void) const;
		/*************************************************************************//*!
				@brief			配列取得
				@param			None

				@return			配列
		*//**************************************************************************/
		T* GetArray(void) const;
		/*************************************************************************//*!
				@brief			配列要素番号取得
				@param[in]		Data			検索データ

				@return			配列要素番号
		*//**************************************************************************/
		MofU32 GetDataNo(T* Data) const;
		/*************************************************************************//*!
				@brief			配列要素アドレス取得
				@param[in]		n				要素番号

				@return			配列要素アドレス
		*//**************************************************************************/
		T* GetDataAddress(MofU32 n) const;
		/*************************************************************************//*!
				@brief			配列要素取得
				@param[in]		n				要素番号

				@return			配列要素
		*//**************************************************************************/
		T& GetData(MofU32 n);
		/*************************************************************************//*!
				@brief			配列要素取得
				@param[in]		n				要素番号

				@return			配列要素
		*//**************************************************************************/
		T& GetData(MofU32 n) const;
		/*************************************************************************//*!
				@brief			フラグ取得
				@param			None

				@return			フラグ
		*//**************************************************************************/
		MofU32 GetFlag(void) const;

		//----------------------------------------------------------------------------
		////Operator
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			リスト代入<br>
								SetArray関数を内部で実行する。
		*//**************************************************************************/
		CDynamicArray& operator = ( const CDynamicArray& pObj );
		/*************************************************************************//*!
				@brief			配列要素アクセス<br>
								n番目の要素を返す。
		*//**************************************************************************/
		virtual T& operator [] (int n);
		/*************************************************************************//*!
				@brief			配列要素アクセス<br>
								n番目の要素を返す。
		*//**************************************************************************/
		virtual const T& operator [] (int n) const;

		//クラス基本定義
		MOF_LIBRARYCLASS_NOTEQUAL(CDynamicArray,MOF_DYNAMICARRAYCLASS_ID);
	};

	//INCLUDE
	#include	"DynamicArray.inl"

	//基本タイプ配列置き換え
	typedef CDynamicArray< MofU8 >			CByteArray,*LPByteArray;
	typedef CDynamicArray< MofS32 >			CS32Array, *LPS32Array;
	typedef CDynamicArray< MofU32 >			CU32Array,*LPU32Array;
	typedef CDynamicArray< MofFloat >		CFloatArray, *LPFloatArray;
	typedef CDynamicArray< CString >		CStringArray,*LPStringArray;
}

#endif

//[EOF]