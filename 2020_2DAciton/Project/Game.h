#pragma once

#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"EffectManager.h"
#include	"Hatena.h"

class CGame
{
private:
	//�v���C���[
	CPlayer			m_Player;
	//�X�e�[�W
	CStage			m_Stage;
	//�G
	CEnemy*			m_EnemyArray;
	//�G�t�F�N�g
	CEffectManager	m_EffectManager;
	//�A�C�e��
	CItem*			m_ItemArray;
	//�͂Ăȃu���b�N
	CHatena*		m_HatenaArray;
	//�g�o
	CTexture		m_Texture;

public:
	CGame();
	~CGame();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};
