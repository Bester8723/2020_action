#include	"Effect.h"
#include	"EffectManager.h"

/**
 * �R���X�g���N�^
 *
 */
CEffect::CEffect() :
m_pTexture(NULL) ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bShow(false) ,
m_SrcRect() {
}

/**
 * �f�X�g���N�^
 *
 */
CEffect::~CEffect(){
}

/**
 * �J�n
 * �p�����[�^�[����W������������B
 *
 * ����
 * [in]			type				�^�C�v
 */
void CEffect::Initialize(int type){
	m_PosX = 0;
	m_PosY = 0;
	m_bShow = false;
	
	switch (type)
	{
	case EFC_DAMAGE:
	{
		SpriteAnimationCreate anim[] = {
			{
				"�G�t�F�N�g",
				0, 0,
				128, 128,
				FALSE, { { 2, 0, 0 }, { 2, 1, 0 }, { 2, 2, 0 }, { 2, 3, 0 }, }
			}
		};
		m_Motion.Create(anim, 1);
		break;
	}
	case EFC_EXPLOSION01:
	{
		SpriteAnimationCreate anim[] = {
			{
				"�G�t�F�N�g",
				0, 0,
				120, 120,
				FALSE, {
					{ 3, 0, 0 }, { 3, 1, 0 }, { 3, 2, 0 }, { 3, 3, 0 }, { 3, 4, 0 },
					{ 3, 5, 0 }, { 3, 6, 0 }, { 3, 7, 0 }, { 3, 8, 0 }, { 3, 9, 0 },
					{ 3, 10, 0 }, { 3, 11, 0 }, { 3, 12, 0 }, { 3, 13, 0 }, { 3, 14, 0 }, { 3, 15, 0 }, }
			}
		};
		m_Motion.Create(anim, 1);
		break;
	}
	case EFC_EXPLOSION02:
	{
		SpriteAnimationCreate anim[] = {
			{
				"�G�t�F�N�g",
				0, 0,
				180, 180,
				FALSE, {
					{ 3, 0, 0 }, { 3, 1, 0 }, { 3, 2, 0 }, { 3, 3, 0 }, { 3, 4, 0 },
					{ 3, 5, 0 }, { 3, 6, 0 }, { 3, 7, 0 }, { 3, 8, 0 }, { 3, 9, 0 }, { 3, 10, 0 },
					{ 3, 0, 1 }, { 3, 1, 1 }, { 3, 2, 1 }, { 3, 3, 1 }, { 3, 4, 1 },
					{ 3, 5, 1 }, { 3, 6, 1 }, { 3, 7, 1 }, { 3, 8, 1 }, { 3, 9, 1 }, { 3, 10, 1 }, }
			}
		};
		m_Motion.Create(anim, 1);
		break;
	}
	}
}

/**
 * �J�n
 * ���W��ݒ肵�ă��[�V�������J�n����B
 *
 * ����
 * [in]			px					X���W
 * [in]			py					Y���W
 */
void CEffect::Start(float px,float py){
  //�\����`���擾
  m_SrcRect = m_Motion.GetSrcRect( );

  //���W��ݒ�B�w�肳�ꂽ���W���㉺���E�����ɂȂ�悤��
  m_PosX = px - m_SrcRect.GetWidth() * 0.5f;
  m_PosY = py - m_SrcRect.GetHeight() * 0.5f;

  //�\����Ԃ�
  m_bShow = true;

  //�ݒ肵���A�j���[�V�������Đ��J�n
  m_Motion.ChangeMotion( 0 );

}

/**
 * �X�V
 *
 */
void CEffect::Update(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//�A�j���[�V�����̏I���Ŕ�\���ɂ���
	if (m_Motion.IsEndMotion())
	{
		m_bShow = false;
	}
}

/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEffect::Render(float wx,float wy){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	m_pTexture->Render(m_PosX - wx, m_PosY - wy, m_SrcRect);
}

/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEffect::RenderDebug(float wx,float wy){
	//��\��
	if(!m_bShow)
	{
		return;
	}
}

/**
 * ���
 *
 */
void CEffect::Release(void){
	m_Motion.Release();
}