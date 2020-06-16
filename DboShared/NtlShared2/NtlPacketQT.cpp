#include "StdAfx.h"
#include "NtlPacketQT.h"


const char * s_packetName_QT[] =
{
	DECLARE_PACKET_NAME( QT_GUILD_CREATE_RES ),
	DECLARE_PACKET_NAME( QT_GUILD_DATA ),
	DECLARE_PACKET_NAME( QT_GUILD_MEMBER_DATA ),
	DECLARE_PACKET_NAME( QT_GUILD_NOT_EXISTING_NFY ),
	DECLARE_PACKET_NAME( QT_GUILD_DISBAND_RES ),
	DECLARE_PACKET_NAME( QT_GUILD_DISBAND_CANCEL_RES ),

	DECLARE_PACKET_NAME( QT_GUILD_INVITE_RES ),
	DECLARE_PACKET_NAME( QT_GUILD_LEAVE_RES ),
	DECLARE_PACKET_NAME( QT_GUILD_KICK_OUT_RES ),

	DECLARE_PACKET_NAME( QT_GUILD_APPOINT_SECOND_MASTER_RES ),
	DECLARE_PACKET_NAME( QT_GUILD_DISMISS_SECOND_MASTER_RES ),
	DECLARE_PACKET_NAME( QT_GUILD_CHANGE_GUILD_MASTER_RES ),
	
	DECLARE_PACKET_NAME( QT_FRIEND_ADD_RES ),		// 친구 추가
	DECLARE_PACKET_NAME( QT_FRIEND_DEL_RES ),		// 친구 삭제
	DECLARE_PACKET_NAME( QT_FRIEND_MOVE_RES ),		// 친구 -> 블랙리스트로 이동
	DECLARE_PACKET_NAME( QT_FRIEND_LIST_LOAD_RES ),	// 친구 리스트 정보
	DECLARE_PACKET_NAME( QT_FRIEND_BLACK_ADD_RES ),		// 친구 블랙 리스트 추가
	DECLARE_PACKET_NAME( QT_FRIEND_BLACK_DEL_RES ),		// 친구 블랙 리스트 삭제

	DECLARE_PACKET_NAME( QT_RANKBATTLE_RANK_LIST_RES ),
	DECLARE_PACKET_NAME( QT_RANKBATTLE_RANK_FIND_CHARACTER_RES ),
	DECLARE_PACKET_NAME( QT_RANKBATTLE_RANK_DATA_UPDATE_NFY	),
	DECLARE_PACKET_NAME( QT_GUILD_FUNCTION_ADD_RES ),
	DECLARE_PACKET_NAME( QT_GUILD_GIVE_ZENNY_RES ),
	DECLARE_PACKET_NAME( QT_GUILD_CHANGE_NOTICE_RES ),
	DECLARE_PACKET_NAME( QT_GUILD_CREATE_MARK_RES ),
	DECLARE_PACKET_NAME( QT_GUILD_CHANGE_MARK_RES ),
	DECLARE_PACKET_NAME( QT_GUILD_CHANGE_NAME_RES ),
	DECLARE_PACKET_NAME( QT_TMQ_RECORD_LIST_RES ),
	DECLARE_PACKET_NAME( QT_TMQ_MEMBER_LIST_RES ),
	DECLARE_PACKET_NAME( QT_DOJO_DATA_RES ),
	DECLARE_PACKET_NAME( QT_DOJO_CREATE_RES ),
	DECLARE_PACKET_NAME( QT_DOJO_UPDATE_RES ),
	DECLARE_PACKET_NAME( QT_DOJO_DEL_RES ),
	DECLARE_PACKET_NAME( QT_DOJO_FUNCTION_ADD_RES ),
	DECLARE_PACKET_NAME( QT_DOGI_CREATE_RES ),
	DECLARE_PACKET_NAME( QT_DOGI_CHANGE_RES ),
	DECLARE_PACKET_NAME( QT_CONNECT_WAIT_CHECK_REQ ),
	DECLARE_PACKET_NAME( QT_CONNECT_WAIT_CANCEL_REQ ),
	DECLARE_PACKET_NAME( QT_DOJO_SCRAMBLE_RES ),
	DECLARE_PACKET_NAME( QT_DOJO_SCRAMBLE_REJECT_RES ),
	DECLARE_PACKET_NAME( QT_CONNECT_WAIT_CHARACTER_SERVER_DOWN_NFY ),
	DECLARE_PACKET_NAME( QT_DOJO_BUDOKAI_SEED_ADD_RES ),
	DECLARE_PACKET_NAME( QT_DOJO_BUDOKAI_SEED_DEL_RES ),
	DECLARE_PACKET_NAME( QT_DOJO_SCRAMBLE_REWARD_RES ),
	DECLARE_PACKET_NAME( QT_DOJO_CHANGE_NOTICE_RES ),

};


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_QT(WORD wOpCode)
{
	if( wOpCode < QT_OPCODE_BEGIN )
	{
		return "NOT DEFINED PACKET NAME : OPCODE LOW";
	}

	if( wOpCode > QT_OPCODE_END )
	{
		return "NOT DEFINED PACKET NAME : OPCODE HIGH";
	}

	int nIndex = wOpCode - QT_OPCODE_BEGIN;
	if( nIndex >= _countof( s_packetName_QT) )
	{
		return "OPCODE BUFFER OVERFLOW";
	}

	return s_packetName_QT[ nIndex ];
}