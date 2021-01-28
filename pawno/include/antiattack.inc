/*

			  Anti-Attack Module
			    BJIADOKC & Co.
	Remove this copyright, if you want to be a superman!
*/





#if defined _aat_included
	#endinput
#endif

#define _aat_included

#define SAMP_CURRENT_VERSION 		"0.3e"

#define ATTACK_TYPE_DIALOG_RESPONSE 	0
#define ATTACK_TYPE_DIALOG_EXPLOIT	1
#define ATTACK_TYPE_RCON_EXPLOIT	2
#define ATTACK_TYPE_BAD_RCON_ATTEMPT	3
#define ATTACK_TYPE_LARGE_RCON		4
#define ATTACK_TYPE_INVALID_CLIENT	5
#define ATTACK_TYPE_PACKET_MODIFIED	6
#define ATTACK_TYPE_REMOTE_PORT_REFUSED	7
#define ATTACK_TYPE_SERVER_FULL		8
#define ATTACK_TYPE_ONESLOT_FLOOD	9
#define ATTACK_TYPE_INVALID_VERSION	10




#pragma tabsize 8





static playerConnected[MAX_PLAYERS char];





forward OnAttackAttempt(attackType, data[]);
forward OnIncomingConnection(ip[]);





public OnAttackAttempt(attackType, data[])
{
	if(data[0] <= '\1')
	{
		printf("Anti-Attack Warning: NULL data passed to callback \"OnAttackAttempt\" %d|\"\"", attackType);

		return 1;
	}

	if(strlen(data) > 15)
	{
		printf("Anti-Attack Warning: Invalid data LEN in callback \"OnAttackAttempt\" %d|\"%s\" (LEN: %d)", attackType, data, strlen(data));

		return 1;
	}

	switch(attackType)
	{
		case ATTACK_TYPE_DIALOG_RESPONSE: // PlayerDialogResponse ... dialog ID doesn't match last sent dialog ID
		{
			BanEx(strval(data), "PlayerDialogResponse attack (Match)");
		}

		case ATTACK_TYPE_DIALOG_EXPLOIT: // PlayerDialogResponse crash exploit from ...
		{
			BanEx(strval(data), "PlayerDialogResponse attack (Crash exploit)");
		}

		case ATTACK_TYPE_RCON_EXPLOIT: // /rcon command exploit from ...
		{
			BanEx(strval(data), "RCON attack (Crash exploit)");
		}

		case ATTACK_TYPE_BAD_RCON_ATTEMPT: // BAD RCON ATTEMPT BY ...
		{
			new dest[24];
			format(dest, sizeof dest, "banip %s", data);
			SendRconCommand(dest);
			printf("Anti-Attack Warning: IP %s was banned (Reason: Bad RCON attempt attack)", data);
		}

		case ATTACK_TYPE_LARGE_RCON: // RCON (In-Game): Player #...
		{
			BanEx(strval(data), "RCON attack (Large RCON)");
		}

		case ATTACK_TYPE_INVALID_CLIENT: // Invalid client connecting from ...
		{
			new dest[24];
			format(dest, sizeof dest, "banip %s", data);
			SendRconCommand(dest);
			printf("Anti-Attack Warning: IP %s was banned (Reason: Invalid client)", data);
		}

		case ATTACK_TYPE_PACKET_MODIFIED: // Packet was modified, sent by ...
		{
			BanEx(strval(data), "Client attack (Packet was modified)");
		}

		case ATTACK_TYPE_REMOTE_PORT_REFUSED: // Remote Port Refused for ...
		{
			BanEx(strval(data), "Client attack (Remote port refused)");
		}

		case ATTACK_TYPE_SERVER_FULL: // Blocking ... due to a 'server full' attack
		{
			new dest[24];
			format(dest, sizeof dest, "banip %s", data);
			SendRconCommand(dest);
			printf("Anti-Attack Warning: IP %s was banned (Reason: 'Server full' attack)", data);
		}

		case ATTACK_TYPE_ONESLOT_FLOOD: // 100 Joins per sec
		{
			return BanEx(strval(data), "Client attack (One-slot flood)");
		}

		case ATTACK_TYPE_INVALID_VERSION: // Version of client is not conform to valid
		{
			return BanEx(strval(data), "Client attack (Invalid client version)");
		}

		default:
		{
			printf("Anti-Attack Warning: Incorrect data passed to callback \"OnAttackAttempt\" %d|\"%s\"", attackType, data);

			return 1;
		}
	}

	return CallLocalFunction("aat_OnAttackAttempt", "is", attackType, data);
}

#if defined _ALS_OnAttackAttempt
    #undef OnAttackAttempt
#else
    #define _ALS_OnAttackAttempt
#endif

#define OnAttackAttempt aat_OnAttackAttempt

forward aat_OnAttackAttempt(attackType, data[]);





public OnPlayerConnect(playerid)
{
	new dest[16];

	playerid &= 65535;

	if(playerConnected{playerid}) 
	{
		valstr(dest, playerid);
		return CallLocalFunction("OnAttackAttempt", "is", ATTACK_TYPE_ONESLOT_FLOOD, dest);
	}

	playerConnected{playerid} = 1;

	GetPlayerVersion(playerid, dest, sizeof dest);
	if(strcmp(dest, SAMP_CURRENT_VERSION, false))
	{
		valstr(dest, playerid);
		return CallLocalFunction("OnAttackAttempt", "is", ATTACK_TYPE_INVALID_VERSION, dest);
	}

	ShowPlayerDialog(playerid, -1, -1, "", "", "", "");

	return CallLocalFunction("aat_OnPlayerConnect", "i", playerid);
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect aat_OnPlayerConnect

forward aat_OnPlayerConnect(playerid);





public OnPlayerDisconnect(playerid, reason)
{
	playerConnected{playerid} = 0;

	return CallLocalFunction("aat_OnPlayerDisconnect", "ii", playerid, reason);
}

#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect aat_OnPlayerDisconnect

forward aat_OnPlayerDisconnect(playerid, reason);





#pragma tabsize 4