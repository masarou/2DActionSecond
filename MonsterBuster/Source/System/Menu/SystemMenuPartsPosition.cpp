/* ====================================================================== */
/**
 * @brief  �p�[�c�N���X�̂ЂƂ�(�ʒu�\��)
 *
 * @note
 *		
 */
/* ====================================================================== */
#include "SystemMenuPartsPosition.h"
#include "System/Draw2D/SystemDraw2DResource.h"
#include "System/Sound/SystemSoundManager.h"
#include "Common/Utility/CommonGameUtility.h"

MenuParts *PartsPosition::Create( const std::string &partsStr, const std::string &jsonStr, const Common::PRIORITY &priority, const math::Vector2 &originalPos )
{
	if( partsStr.empty() || jsonStr.empty() ){
		DEBUG_ASSERT( 0, "�p�[�c�쐬���̕����񂪖���");
		return NULL;
	}
	return NEW PartsPosition( partsStr, jsonStr, priority, originalPos );
}

PartsPosition::PartsPosition( const std::string &partsStr, const std::string &jsonStr, const Common::PRIORITY &priority, const math::Vector2 &originalPos )
: MenuParts( partsStr, jsonStr, priority, originalPos )
{
}


PartsPosition::~PartsPosition(void)
{
}

// �ʒu���擾
math::Vector2 PartsPosition::GetPosition() const
{
	return m_relativePos;
}
