#if defined _airbreak_included
    #endinput
#endif
#define _airbreak_included

#include <a_samp>
#include <foreach>

#if !defined _ALS_
    forward public _ALS_();
    _ALS_()<_ALS_:unhooked>{}
    _ALS_()<_ALS_:hooked>{}
    _ALS_()<>{}
#endif

#define MAX_VEHICLE_AIRBREAK  (80.0)
#define MAX_AIRBREAK_DISTANCE (33.0)

enum E_AIRBREAK_DATA
{
    Float:E_PLAYER_X[MAX_PLAYERS],
    Float:E_PLAYER_Y[MAX_PLAYERS],
    Float:E_PLAYER_Z[MAX_PLAYERS],
    E_AIRBREAK_TIMER
};
new E_AIRBREAK_ENUM[E_AIRBREAK_DATA];

new stock airbreakIndexes[] =
{
    1231, 1266, 1234, 1189,
    1235, 1136, 1196, 1197,
    1198, 1159, 1133, 1130,
    1129, 1208, 1156
};

public OnGameModeInit()
{
    E_AIRBREAK_ENUM[E_AIRBREAK_TIMER] = SetTimer("AirbreakCheck", 1000, true);
    state _ALS_:hooked;
    return ab_OnGameModeInit();
}

forward ab_OnGameModeInit();

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif

public ab_OnGameModeInit() <_ALS_:unhooked> return 1;
public ab_OnGameModeInit() <> return 1;

#define OnGameModeInit(%0) ab_OnGameModeInit(%0)<_ALS_:hooked>

stock Float:GetVehicleSpeed(playerid)
{
    if (!IsPlayerInAnyVehicle(playerid)) return 0.0;
    new
        Float:vX,
        Float:vY,
        Float:vZ
    ;
    GetVehicleVelocity(GetPlayerVehicleID(playerid), vX, vY, vZ);
    return floatsqroot(floatpower(vX, 2) + floatpower(vY, 2) + floatpower(vZ, 2)) * 100;
}

forward AirbreakCheck();
public AirbreakCheck()
{
    new Float:x2, Float:y2, Float:z2, index, Float:dist[4];
    foreach(new i : Player) 
    {
        if (!IsPlayerConnected(i)) continue;
        if (GetPVarInt(i, "CheckDelay"))
        {
            SetPVarInt(i, "CheckDelay", GetPVarInt(i, "CheckDelay") - 1);
            continue;
        }
        if (IsPlayerInAnyVehicle(i))
        {
            GetVehiclePos(GetPlayerVehicleID(i), x2, y2, z2);
        }
        else GetPlayerPos(i, x2, y2, z2);
        index = GetPlayerAnimationIndex(i);

        dist[0] = (E_AIRBREAK_ENUM[E_PLAYER_X][i] < x2) ? E_AIRBREAK_ENUM[E_PLAYER_X][i] - x2 : x2 - E_AIRBREAK_ENUM[E_PLAYER_X][i];
        dist[1] = (E_AIRBREAK_ENUM[E_PLAYER_Y][i] < y2) ? E_AIRBREAK_ENUM[E_PLAYER_Y][i] - y2 : y2 - E_AIRBREAK_ENUM[E_PLAYER_Y][i];
        dist[2] = (E_AIRBREAK_ENUM[E_PLAYER_Z][i] < z2) ? E_AIRBREAK_ENUM[E_PLAYER_Z][i] - z2 : z2 - E_AIRBREAK_ENUM[E_PLAYER_Z][i];
        dist[3] = floatsqroot(floatpower(dist[0], 2.0) + floatpower(dist[1], 2.0) + floatpower(dist[2], 2.0));

        if (x2 == E_AIRBREAK_ENUM[E_PLAYER_X][i] && y2 == E_AIRBREAK_ENUM[E_PLAYER_Y][i] && z2 == E_AIRBREAK_ENUM[E_PLAYER_Z][i])
        {
            // Player is most likely AFK, so let's forget about checking that player.
            continue;
        }
        if (dist[3] > MAX_AIRBREAK_DISTANCE && !IsPlayerInAnyVehicle(i))
        {
            if (GetPlayerState(i) == PLAYER_STATE_ONFOOT)
            {
                for (new l = 0; l < sizeof(airbreakIndexes); l ++)
                {
                    if (index == airbreakIndexes[l])
                    {
                        if (!floatcmp(E_AIRBREAK_ENUM[E_PLAYER_Z][i], z2))
                        {
                            if (funcidx("OnPlayerAirbreak") != -1)
                                CallLocalFunction("OnPlayerAirbreak", "d", i);
                        }
                    }
                }
            }
        }
        else if (dist[3] > MAX_VEHICLE_AIRBREAK && IsPlayerInAnyVehicle(i))
        {
            if (GetPlayerState(i) == PLAYER_STATE_DRIVER)
            {
                if (GetVehicleSpeed(i) >= 0.02 && GetVehicleSpeed(i) <= 0.15)
                {
                    if (funcidx("OnPlayerAirbreak") != -1)
                        CallLocalFunction("OnPlayerAirbreak", "d", i);
                }
            }
        }
        E_AIRBREAK_ENUM[E_PLAYER_X][i] = x2;
        E_AIRBREAK_ENUM[E_PLAYER_Y][i] = y2;
        E_AIRBREAK_ENUM[E_PLAYER_Z][i] = z2;
    }
    return 1;
}

public OnEnterExitModShop(playerid, enterexit)
{
    if (enterexit)
    {
        SetPVarInt(playerid, "CheckDelay", 2);
    }
    else DeletePVar(playerid, "CheckDelay");
    return CallLocalFunction("ab_OnEnterExitModShop", "dd", playerid, enterexit);
}
#if defined _ALS_OnEnterExitModShop
    #undef OnEnterExitModShop
#else
    #define _ALS_OnEnterExitModShop
#endif
#define OnEnterExitModShop ab_OnEnterExitModShop

stock ab_SetPlayerPos(playerid, Float:x2, Float:y2, Float:z2)
{
    E_AIRBREAK_ENUM[E_PLAYER_X][playerid] = x2;
    E_AIRBREAK_ENUM[E_PLAYER_Y][playerid] = y2;
    E_AIRBREAK_ENUM[E_PLAYER_Z][playerid] = z2;
    SetPVarInt(playerid, "CheckDelay", 2);
    return SetPlayerPos(playerid, x2, y2, z2);
}

stock ab_SetVehiclePos(vehicleid, Float:x2, Float:y2, Float:z2)
{
    foreach(new i : Player) 
    {
        if (IsPlayerConnected(i) && IsPlayerInVehicle(i, vehicleid))
        {
            E_AIRBREAK_ENUM[E_PLAYER_X][i] = x2;
            E_AIRBREAK_ENUM[E_PLAYER_Y][i] = y2;
            E_AIRBREAK_ENUM[E_PLAYER_Z][i] = z2;
            SetPVarInt(i, "CheckDelay", 2);
        }
    }
    return SetVehiclePos(vehicleid, x2, y2, z2);
}

stock ab_PutPlayerInVehicle(playerid, vehicleid, seatid)
{
    new Float:x2, Float:y2, Float:z2;
    GetVehiclePos(vehicleid, x2, y2, z2);
    E_AIRBREAK_ENUM[E_PLAYER_X][playerid] = x2;
    E_AIRBREAK_ENUM[E_PLAYER_Y][playerid] = y2;
    E_AIRBREAK_ENUM[E_PLAYER_Z][playerid] = z2;
    SetPVarInt(playerid, "CheckDelay", 2);
    return PutPlayerInVehicle(playerid, vehicleid, seatid);
}

#define SetPlayerPos ab_SetPlayerPos
#define SetVehiclePos ab_SetVehiclePos
#define PutPlayerInVehicle ab_PutPlayerInVehicle
forward OnPlayerAirbreak(playerid);
