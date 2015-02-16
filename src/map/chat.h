/****************************************************************************!
*                _           _   _   _                                       *
*               | |__  _ __ / \ | |_| |__   ___ _ __   __ _                  *
*               | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |                 *
*               | |_) | | / ___ \ |_| | | |  __/ | | | (_| |                 *
*               |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|                 *
*                                                                            *
******************************************************************************
*                          www.brathena.org                                  *
*****************************************************************************/

#ifndef MAP_CHAT_H
#define MAP_CHAT_H

#include "map.h" // struct block_list, CHATROOM_TITLE_SIZE
#include "../common/cbasetypes.h"
#include "../common/db.h"

struct chat_data;
struct map_session_data;
struct npc_data;

#define MAX_CHAT_USERS 20

struct chat_data {
	struct block_list bl;            ///< data for this map object
	char title[CHATROOM_TITLE_SIZE]; ///< room title
	char pass[CHATROOM_PASS_SIZE];   ///< password
	bool pub;                        ///< private/public flag
	uint8 users;                     ///< current user count
	uint8 limit;                     ///< join limit
	uint8 trigger;                   ///< number of users needed to trigger event
	uint32 zeny;                     ///< required zeny to join
	uint32 minLvl;                   ///< minimum base level to join
	uint32 maxLvl;                   ///< maximum base level allowed to join
	struct map_session_data* usersd[MAX_CHAT_USERS];
	struct block_list* owner;
	char npc_event[EVENT_NAME_LENGTH];
	/* isn't this a waste? there is a enormous overhead, wouldn't something like skill_blockpc_start be better here? [Ind] */
	DBMap* kick_list;                ///< DBMap of users who were kicked from this chat
};

/**
 * chat.c Interface
 **/
struct chat_interface {
	/* funcs */
	bool (*create_pc_chat) (struct map_session_data* sd, const char* title, const char* pass, int limit, bool pub);
	bool (*join) (struct map_session_data* sd, int chatid, const char* pass);
	int (*leave) (struct map_session_data* sd, bool kicked);
	bool (*change_owner) (struct map_session_data* sd, const char* nextownername);
	bool (*change_status) (struct map_session_data* sd, const char* title, const char* pass, int limit, bool pub);
	bool (*kick) (struct map_session_data* sd, const char* kickusername);
	bool (*create_npc_chat) (struct npc_data* nd, const char* title, int limit, bool pub, int trigger, const char* ev, int zeny, int minLvl, int maxLvl);
	bool (*delete_npc_chat) (struct npc_data* nd);
	bool (*enable_event) (struct chat_data* cd);
	bool (*disable_event) (struct chat_data* cd);
	bool (*npc_kick_all) (struct chat_data* cd);
	bool (*trigger_event) (struct chat_data *cd);
	struct chat_data* (*create) (struct block_list* bl, const char* title, const char* pass, int limit, bool pub, int trigger, const char* ev, int zeny, int minLvl, int maxLvl);
};

struct chat_interface *chat;

#ifdef BRATHENA_CORE
void chat_defaults(void);
#endif // BRATHENA_CORE

#endif /* MAP_CHAT_H */
