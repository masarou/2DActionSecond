/* ====================================================================== */
/**
 * @brief  パーツクラスのひとつ(メッセージウインドウ)
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
		MESSAGE_VERY_SLOW,	// 5フレーム1文字
		MESSAGE_SLOW,		// 2フレーム1文字
		MESSAGE_NORMAL,		// 1フレーム1文字
		MESSAGE_FAST,		// 1フレーム2文字
		MESSAGE_VERY_FAST,	// 1フレーム3文字
	};

	static MenuParts *Create( const std::string &partsStr, const std::string &jsonStr, const Common::PRIORITY &priority, const math::Vector2 &originalPos );

	PartsMessageWindow( const std::string &partsStr, const std::string &jsonStr, const Common::PRIORITY &priority, const math::Vector2 &originalPos );
	~PartsMessageWindow(void);

	// 初期化
	void Read();

	// パーツタイプ取得
	virtual Common::PARTS_TYPE_MENU GetPartsType() override{ return Common::PARTS_MESSAGE; }

protected:

	// 毎フレーム呼ばれるクラス更新の起点
	virtual void UpdateParts() override;

private:

	// 文字列スピードによって更新タイミングを設定
	void AdjustAnalysisTiming();

	// 次に表示する文字列解析
	void AnalysisNextChar();

	// 文字列描画
	void DrawUpdate();

	MESSAGE_SPEED				m_messageSpeed;	// 文字列表示の速さ
	std::string					m_dispStr;		// 表示している文字列
	std::vector< std::string >	m_readFile;		// 読み込むファイル
	std::vector< std::string >	m_strArray;		// 読み込んだ文字列
	
	bool						m_isFinish;			// すべての文字列を表示し終えたかどうか
	bool						m_userCommandWait;	// ユーザー入力待ちかどうか
	uint32_t					m_waitTimer;		// 待ち時間
	uint32_t					m_stringIndex;		// 現在何行目を表示しようとしているか
	uint32_t					m_writePlace;		// 何文字目まで表示しているか文字数

};
#endif // __SYSTEM_MENU_PARTS_MESSAGE_WINDOW__