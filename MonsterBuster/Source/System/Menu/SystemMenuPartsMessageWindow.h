/* ====================================================================== */
/**
 * @brief  �p�[�c�N���X�̂ЂƂ�(���b�Z�[�W�E�C���h�E)
 *
 * @note
 *		
 */
/* ====================================================================== */
#ifndef __SYSTEM_MENU_PARTS_MESSAGE_WINDOW__
#define __SYSTEM_MENU_PARTS_MESSAGE_WINDOW__

#include "System/SystemDefine.h"
#include "Common/CommonDefine.h"
#include "SystemMenuParts.h"

class PartsMessageWindow : public MenuParts
{

public:

	enum MESSAGE_SPEED{
		MESSAGE_VERY_SLOW,	// 5�t���[��1����
		MESSAGE_SLOW,		// 2�t���[��1����
		MESSAGE_NORMAL,		// 1�t���[��1����
		MESSAGE_FAST,		// 1�t���[��2����
		MESSAGE_VERY_FAST,	// 1�t���[��3����
	};

	static MenuParts *Create( const std::string &partsStr, const std::string &jsonStr, const Common::PRIORITY &priority, const math::Vector2 &originalPos );

	PartsMessageWindow( const std::string &partsStr, const std::string &jsonStr, const Common::PRIORITY &priority, const math::Vector2 &originalPos );
	~PartsMessageWindow(void);

	// ������
	void Read();

	// �p�[�c�^�C�v�擾
	virtual Common::PARTS_TYPE_MENU GetPartsType() override{ return Common::PARTS_MESSAGE; }

protected:

	// ���t���[���Ă΂��N���X�X�V�̋N�_
	virtual void UpdateParts() override;

private:

	// ������X�s�[�h�ɂ���čX�V�^�C�~���O��ݒ�
	void AdjustAnalysisTiming();

	// ���ɕ\�����镶������
	void AnalysisNextChar();

	// ������`��
	void DrawUpdate();

	MESSAGE_SPEED				m_messageSpeed;	// ������\���̑���
	std::string					m_dispStr;		// �\�����Ă��镶����
	std::vector< std::string >	m_readFile;		// �ǂݍ��ރt�@�C��
	std::vector< std::string >	m_strArray;		// �ǂݍ��񂾕�����
	
	bool						m_isFinish;			// ���ׂĂ̕������\�����I�������ǂ���
	bool						m_userCommandWait;	// ���[�U�[���͑҂����ǂ���
	uint32_t					m_waitTimer;		// �҂�����
	uint32_t					m_stringIndex;		// ���݉��s�ڂ�\�����悤�Ƃ��Ă��邩
	uint32_t					m_writePlace;		// �������ڂ܂ŕ\�����Ă��邩������

};
#endif // __SYSTEM_MENU_PARTS_MESSAGE_WINDOW__