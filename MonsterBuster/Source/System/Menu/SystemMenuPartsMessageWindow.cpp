/* ====================================================================== */
/**
 * @brief  �p�[�c�N���X�̂ЂƂ�(���l�J�E���^�[)
 *
 * @note
 *		
 */
/* ====================================================================== */
#include "SystemMenuPartsMessageWindow.h"
#include "SystemMenuPartsPosition.h"
#include "System/Draw2D/SystemDraw2DResource.h"
#include "System/Sound/SystemSoundManager.h"
#include "Common/Utility/CommonGameUtility.h"

MenuParts *PartsMessageWindow::Create( const std::string &partsStr, const std::string &jsonStr, const Common::PRIORITY &priority, const math::Vector2 &originalPos )
{
	if( partsStr.empty() || jsonStr.empty() ){
		DEBUG_ASSERT( 0, "�p�[�c�쐬���̕����񂪖���");
		return NULL;
	}
	return NEW PartsMessageWindow( partsStr, jsonStr, priority, originalPos );
}

PartsMessageWindow::PartsMessageWindow( const std::string &partsStr, const std::string &jsonStr, const Common::PRIORITY &priority, const math::Vector2 &originalPos )
: MenuParts( partsStr, jsonStr, priority, originalPos )
, m_messageSpeed( MESSAGE_SLOW )
, m_dispStr("")
, m_isFinish( false )
, m_userCommandWait( false )
, m_waitTimer( 0 )
, m_stringIndex( 0 )
, m_writePlace( 0 )
{
	std::string readFile = "sample.txt";
	m_readFile.push_back( readFile );

	Read();
}


PartsMessageWindow::~PartsMessageWindow(void)
{
}

/* ================================================ */
/**
 * @brief	������
 */
/* ================================================ */
void PartsMessageWindow::Read()
{
	for( uint32_t i = 0; i < m_readFile.size() ; ++i ){
		std::string filePath = TEXT_PATH + m_readFile.at(i);
		uint32_t handle = FileRead_open( filePath.c_str() );

		// ��s���ǂݍ���
		for(;;){
			char readLine[256];
			int32_t result = FileRead_gets( readLine, 256, handle );
			if( result != -1 ){
				std::string tmp = readLine;
				m_strArray.push_back( tmp );
			}
			else{
				// �t�@�C���ǂݍ��ݏI��
				break;
			}
		}

		FileRead_close( handle );
	}
}

/* ================================================ */
/**
 * @brief	���t���[���Ă΂��N���X�X�V�̋N�_
 */
/* ================================================ */
void PartsMessageWindow::UpdateParts()
{
	if( !m_userCommandWait ){

		if( m_isFinish ){
			// ��ʏI��

		}

		// ���̕��������͂���^�C�~���O���ǂ���
		if( m_waitTimer > 0 ){
			m_waitTimer--;
		}
		else if( m_waitTimer == 0 ){
			// ��������
			AnalysisNextChar();

			// ���̍X�V�^�C�~���O����
			AdjustAnalysisTiming();
		}
	}

	// ������`��
	DrawUpdate();
}

/* ================================================ */
/**
 * @brief	�X�V�^�C�~���O����
 */
/* ================================================ */
void PartsMessageWindow::AdjustAnalysisTiming()
{
	if( m_waitTimer == 0 ){
		switch( m_messageSpeed ){
		case MESSAGE_VERY_SLOW:
			m_waitTimer = 5;
			break;
			
		case MESSAGE_SLOW:
			m_waitTimer = 2;
			break;
			
		case MESSAGE_NORMAL:
		case MESSAGE_FAST:
		case MESSAGE_VERY_FAST:
			// ���t���[���X�V�Ȃ̂œ��ɉ������Ȃ�
			break;
		}
	}

}

/* ================================================ */
/**
 * @brief	���ɕ\�����镶������
 */
/* ================================================ */
void PartsMessageWindow::AnalysisNextChar()
{
	uint32_t currentPoint = m_writePlace;
	uint32_t nextPoint = m_writePlace;
	uint32_t checkCharNum = 0;
	switch( m_messageSpeed ){
	case MESSAGE_VERY_SLOW:
	case MESSAGE_SLOW:
	case MESSAGE_NORMAL:
		checkCharNum = 1;
		break;

	case MESSAGE_FAST:
		checkCharNum = 2;
		break;

	case MESSAGE_VERY_FAST:
		checkCharNum = 3;
		break;
	}

	std::string checkStr = "";
	for( uint32_t i = 0; i < checkCharNum ; ++i ){

		if( m_strArray.at( m_stringIndex ).length() <= m_writePlace ){
			if( m_strArray.size() <= m_stringIndex + 1 ){
				// �\���������[�U�[�̓��͑҂�
				m_isFinish = true;
				m_userCommandWait = true;
			}
			else{
				// �Ō�܂ŕ\�������̂Ŏ��̕��͂�
				++m_stringIndex;
				m_writePlace = 0;
			}
			break;
		}
		
		uint32_t char_size = 1;
		unsigned char lead;
		lead = m_strArray.at( m_stringIndex )[m_writePlace];
		if (lead < 0x80) {
			char_size = 1;
		} else if (lead < 0xE0) {
			char_size = 2;
		} else if (lead < 0xF0) {
			char_size = 3;
		} else {
			char_size = 4;
		}

		checkStr += m_strArray.at( m_stringIndex ).substr( m_writePlace, char_size ).c_str();
		m_writePlace += char_size;

		if( (*--checkStr.end()) == '@' ){
			// ���s�}�[�N
			checkStr.erase( --checkStr.end() );
			checkStr += "\n";
			break;
		}
		else if( (*--checkStr.end()) == '*' ){
			// ���[�U�[���͑҂�
			checkStr.erase( --checkStr.end() );
			checkStr += "\n";
			m_userCommandWait = true;
			break;
		}
	}

	m_dispStr += checkStr;
}

/* ================================================ */
/**
 * @brief	������`��
 */
/* ================================================ */
void PartsMessageWindow::DrawUpdate()
{
	// �������Z�b�g
	PartsPosition *pParts = static_cast<PartsPosition*>( GetPartsRecursive( "strPos" ) );
	Draw2DManager::GetInstance()->PushDrawString( m_dispStr, pParts->GetPosition() );
}
