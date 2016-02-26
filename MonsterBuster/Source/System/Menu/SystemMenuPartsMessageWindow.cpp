/* ====================================================================== */
/**
 * @brief  パーツクラスのひとつ(数値カウンター)
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
		DEBUG_ASSERT( 0, "パーツ作成時の文字列が無効");
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
 * @brief	初期化
 */
/* ================================================ */
void PartsMessageWindow::Read()
{
	for( uint32_t i = 0; i < m_readFile.size() ; ++i ){
		std::string filePath = TEXT_PATH + m_readFile.at(i);
		uint32_t handle = FileRead_open( filePath.c_str() );

		// 一行ずつ読み込み
		for(;;){
			char readLine[256];
			int32_t result = FileRead_gets( readLine, 256, handle );
			if( result != -1 ){
				std::string tmp = readLine;
				m_strArray.push_back( tmp );
			}
			else{
				// ファイル読み込み終了
				break;
			}
		}

		FileRead_close( handle );
	}
}

/* ================================================ */
/**
 * @brief	毎フレーム呼ばれるクラス更新の起点
 */
/* ================================================ */
void PartsMessageWindow::UpdateParts()
{
	if( !m_userCommandWait ){

		if( m_isFinish ){
			// 画面終了

		}

		// 次の文字列を解析するタイミングかどうか
		if( m_waitTimer > 0 ){
			m_waitTimer--;
		}
		else if( m_waitTimer == 0 ){
			// 文字列解析
			AnalysisNextChar();

			// 次の更新タイミング調整
			AdjustAnalysisTiming();
		}
	}

	// 文字列描画
	DrawUpdate();
}

/* ================================================ */
/**
 * @brief	更新タイミング調整
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
			// 毎フレーム更新なので特に何もしない
			break;
		}
	}

}

/* ================================================ */
/**
 * @brief	次に表示する文字列解析
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
				// 表示完了ユーザーの入力待ち
				m_isFinish = true;
				m_userCommandWait = true;
			}
			else{
				// 最後まで表示したので次の文章へ
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
			// 改行マーク
			checkStr.erase( --checkStr.end() );
			checkStr += "\n";
			break;
		}
		else if( (*--checkStr.end()) == '*' ){
			// ユーザー入力待ち
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
 * @brief	文字列描画
 */
/* ================================================ */
void PartsMessageWindow::DrawUpdate()
{
	// 説明文セット
	PartsPosition *pParts = static_cast<PartsPosition*>( GetPartsRecursive( "strPos" ) );
	Draw2DManager::GetInstance()->PushDrawString( m_dispStr, pParts->GetPosition() );
}
