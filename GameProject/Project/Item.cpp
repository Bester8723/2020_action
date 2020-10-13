#include	"Item.h"

/**
 * �R���X�g���N�^
 *
 */
CItem::CItem() :
m_pTexture(NULL) ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_MoveX(0.0f) ,
m_MoveY(0.0f) ,
m_bShow(false) ,
m_SrcRect() ,
m_bCollision(false) {
}

/**
 * �f�X�g���N�^
 *
 */
CItem::~CItem(){
	//delete[] �ŉ�������悤��Release���f�X�g���N�^�Ŏ��s����
	Release();
}

/**
 * ������
 * �p�����[�^�[����W������������B
 *
 * ����
 * [in]			px					X���W
 * [in]			py					Y���W
 * [in]			type				�A�C�e���^�C�v
 */
void CItem::Initialize(float px,float py,int type){
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = 0.3f;
	m_MoveY = 0.0f;
	m_bShow = true;
	if (!GetType() == ITEM_GOAL)
	{
		m_bCollision = false;
	}
	else
	{
		m_bCollision = true;
		m_MoveX = 0.0f;
	}
	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[] = {
		{
			"�A�C�e��",
			0,0,
			32,32,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
		{
			"�S�[��",
			0,0,
			32,320,
			TRUE,{{30,0,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
	//�A�j���[�V�����̏����ݒ�
	if (GetType() == ITEM_RECOVER)
	{
		m_Motion.ChangeMotion(MOTION_MOVE);
	}
	else if (GetType() == ITEM_GOAL)
	{
		m_Motion.ChangeMotion(MOTION_GOAL);
	}
}

/**
 * �X�V
 *
 */
void CItem::Update(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�͂Ăȃu���b�N����h���b�v�����瓮��
	if (m_bCollision)
	{
		//�d�͂ɂ�艺�ɏ�����������
		m_MoveY += GRAVITY * 0.7;
		if (m_MoveY >= 20.0f)
		{
			m_MoveY = 20.0f;
		}
		//���ۂɍ��W���ړ�������
		m_PosX += m_MoveX;
		m_PosY += m_MoveY;
	}
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

/**
 * �X�e�[�W�Ƃ̓�����
 *
 * ����
 * [in]			ox					X���܂��
 * [in]			oy					Y���܂��
 */
void CItem::CollisionStage(float ox,float oy){
	//�͂Ăȃu���b�N�ɖ��܂��Ă�Ƃ�
	if (!m_bCollision)
	{
		return;
	}
	m_PosX += ox;
	m_PosY += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if(oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
	}
	else if(oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if(ox < 0 && m_MoveX > 0)
	{
		m_MoveX = 0;
	}
	else if(ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}

/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CItem::Render(float wx,float wy){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_PosX - wx,m_PosY - wy,m_SrcRect);
}

/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CItem::RenderDebug(float wx,float wy){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx,hr.Top - wy,hr.Right - wx,hr.Bottom - wy,MOF_XRGB(255,0,0));
}

/**
 * ���
 *
 */
void CItem::Release(void){
	m_Motion.Release();
}

/**
 * �A�C�e���o��
 *
 */
void CItem::Drop()
{
	m_bCollision = true;
	m_PosY -= m_SrcRect.GetHeight();
}