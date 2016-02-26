/* ====================================================================== */
/**
 * @brief  �p�[�c�N���X�̂ЂƂ�(�ʒu�\��)
 *
 * @note
 *		
 */
/* ====================================================================== */
#ifndef __SYSTEM_MENU_PARTS_POSITION__
#define __SYSTEM_MENU_PARTS_POSITION__

#include "System/SystemDefine.h"
#include "Common/CommonDefine.h"
#include "SystemMenuParts.h"

class PartsPosition : public MenuParts
{

public:

	static MenuParts *Create( const std::string &partsStr, const std::string &jsonStr, const Common::PRIORITY &priority, const math::Vector2 &originalPos );

	PartsPosition( const std::string &partsStr, const std::string &jsonStr, const Common::PRIORITY &priority, const math::Vector2 &originalPos );
	~PartsPosition(void);

	// �p�[�c�^�C�v�擾
	virtual Common::PARTS_TYPE_MENU GetPartsType() override{ return Common::PARTS_POSITION; }

	// �ʒu���擾
	math::Vector2 GetPosition() const;

};
#endif // __SYSTEM_MENU_PARTS_POSITION__