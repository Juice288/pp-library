#if defined _pp_foreach_included
    #endinput
#endif
#define _pp_foreach_included

#include <open.mp>
#include <PawnPlus>

#if !defined _FOREACH_LOCAL_VERSION
    #define _FOREACH_LOCAL_VERSION 19
#endif

#define ITER_NONE -1

#define Iterator:%1<%2> %1@YSII_Cg, %1@YSII_Ag[(%2)+1]={(%2)*2,(%2)*2-1,...}
#define IteratorArray:%1[%2]<%3> %1@YSII_Cg[%2],%1@YSII_Ag[%2][%3+1]
#define iterator%0<%1> new Iterator:%0<%1>

#define _Y_ITER_ARRAY_SIZE(%1) (sizeof(%1@YSII_Ag)-1)

#define Iter_Init(%1) Iter_InitInternal(%1@YSII_Ag, sizeof(%1@YSII_Ag), sizeof(%1@YSII_Ag[])-1)
#define Iter_Add(%1,%2) Iter_AddInternal(%1@YSII_Cg, %1@YSII_Ag, %2, _Y_ITER_ARRAY_SIZE(%1))
#define Iter_Remove(%1,%2) Iter_RemoveInternal(%1@YSII_Cg, %1@YSII_Ag, %2, _Y_ITER_ARRAY_SIZE(%1))
#define Iter_Contains(%1,%2) Iter_ContainsInternal(%1@YSII_Ag, %2, _Y_ITER_ARRAY_SIZE(%1))
#define Iter_Free(%1) Iter_FreeInternal(%1@YSII_Ag, _Y_ITER_ARRAY_SIZE(%1))
#define Iter_Clear(%1) Iter_ClearInternal(%1@YSII_Cg, %1@YSII_Ag, _Y_ITER_ARRAY_SIZE(%1))
#define Iter_Random(%1) Iter_RandomInternal(%1@YSII_Cg, %1@YSII_Ag, _Y_ITER_ARRAY_SIZE(%1))
#define Iter_Count(%1) (%1@YSII_Cg)
#define Iter_SafeRemove(%1,%2,%3) Iter_SafeRemoveInternal(%1@YSII_Cg, %1@YSII_Ag, %2, %3, _Y_ITER_ARRAY_SIZE(%1))
#define Iter_Index(%1,%2) Iter_IndexInternal(%1@YSII_Cg, %1@YSII_Ag, _Y_ITER_ARRAY_SIZE(%1), _Y_ITER_ARRAY_SIZE(%1), %2)

#define Iter_Begin(%1) _Y_ITER_ARRAY_SIZE(%1)
#define Iter_End(%1) _Y_ITER_ARRAY_SIZE(%1)
#define Iter_Start Iter_Begin
#define Iter_Finish Iter_End
#define Iter_First(%1) (%1@YSII_Ag[_Y_ITER_ARRAY_SIZE(%1)])
#define Iter_Last(%1) Iter_PrevInternal(%1@YSII_Ag, _Y_ITER_ARRAY_SIZE(%1), _Y_ITER_ARRAY_SIZE(%1))
#define Iter_Next(%1,%2) (%1@YSII_Ag[(%2)])
#define Iter_Prev(%1,%2) Iter_PrevInternal(%1@YSII_Ag, _Y_ITER_ARRAY_SIZE(%1), (%2))
#define Iter_Previous Iter_Prev

#define foreach%1(%0) for(new Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||%0|||)
#define new%0|||%9|||%1:%2||| %9|||%0|||%1|||%2|||
#define Y_FOREACH_THIRD|||%0|||%1|||%2||| %1=Y_FOREACH_FIFTH|||Y_FOREACH_FOURTH|||%1:%2|||
#define Y_FOREACH_FOURTH|||%0=Y_FOREACH_FIFTH|||%1|||%2||| new Y_FOREACH_SIXTH;%0|||Y_FOREACH_SEVENTH|||%2|||
#define Y_FOREACH_SEVENTH|||%9Y_FOREACH_SIXTH;%0|||%1|||%2||| new %0:%1=%0:(_Y_ITER_ARRAY_SIZE(%2));_:(%1=%0:%2@YSII_Ag[_:%1])!=_Y_ITER_ARRAY_SIZE(%2);
#define Y_FOREACH_SIXTH;%0|||Y_FOREACH_SEVENTH|||%2||| %0=_Y_ITER_ARRAY_SIZE(%2);_:(%0=%2@YSII_Ag[%0])!=_Y_ITER_ARRAY_SIZE(%2);
#define Y_FOREACH_FIFTH|||Y_FOREACH_FOURTH|||%1:%2||| _Y_ITER_ARRAY_SIZE(%2);_:(%1=%2@YSII_Ag[%1])!=_Y_ITER_ARRAY_SIZE(%2);
#define Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||%1,%2||| %2=_Y_ITER_ARRAY_SIZE(%1);_:(%2=%1@YSII_Ag[%2])!=_Y_ITER_ARRAY_SIZE(%1);

forward Iter_AddInternal(&count, array[], value, size);
forward Iter_RemoveInternal(&count, array[], value, size);
forward Iter_ClearInternal(&count, array[], size);
forward Iter_OPDCInternal(playerid);

stock Iter_RandomInternal(count, const array[], size)
{
    if (count == 0) return ITER_NONE;
    new rnd = random(count), cur = array[size];
    while (cur != size)
    {
        if (rnd-- == 0) return cur;
        cur = array[cur];
    }
    return ITER_NONE;
}

stock Iter_FreeInternal(const array[], size)
{
    for (new i = 0; i != size; ++i)
    {
        if (array[i] > size) return i;
    }
    return ITER_NONE;
}

stock Iter_AddInternal(&count, array[], value, size)
{
    if (0 <= value < size && array[value] > size)
    {
        new last = size, next = array[last];
        while (next < value)
        {
            last = next;
            next = array[last];
        }
        array[last] = value;
        array[value] = next;
        ++count;
        return 1;
    }
    return 0;
}

stock Iter_RemoveInternal(&count, array[], value, size)
{
    new last;
    return Iter_SafeRemoveInternal(count, array, value, last, size);
}

stock Iter_SafeRemoveInternal(&count, array[], value, &last, size)
{
    if (0 <= value < size && array[value] <= size)
    {
        last = size;
        new next = array[last];
        while (next < size)
        {
            if (next == value)
            {
                array[last] = array[value];
                array[value] = size + 1;
                --count;
                return 1;
            }
            last = next;
            next = array[last];
        }
    }
    return 0;
}

stock Iter_ContainsInternal(const array[], value, size)
{
    return 0 <= value < size && array[value] <= size;
}

stock Iter_ClearInternal(&count, array[], size)
{
    for (new i = 0, t = size + 1; i < size; ++i)
    {
        array[i] = t;
    }
    array[size] = size;
    count = 0;
}

stock Iter_IndexInternal(count, const array[], start, size, index)
{
    if (index < 0 || start < size || array[start] >= size) return ITER_NONE;
    if (index >= count) return ITER_NONE;
    start = array[start];
    while (index--)
    {
        start = array[start];
    }
    return start;
}

stock Iter_InitInternal(arr[][], s0, s1)
{
    for (new i = 0, t = s1 + 1; i < s0; ++i)
    {
        for (new j = 0; j < s1; ++j)
        {
            arr[i][j] = t;
        }
        arr[i][s1] = s1;
    }
}

stock Iter_PrevInternal(const array[], size, slot)
{
    if (0 <= slot <= size && array[slot] <= size)
    {
        for (new last = slot; last--; )
        {
            if (array[last] == slot) return last;
        }
    }
    return size;
}

new Iterator:Player<MAX_PLAYERS>;
new Iterator:Vehicle<MAX_VEHICLES>;
new Iterator:Actor<MAX_ACTORS>;

#define NPC@YSII_Cg Player@YSII_Cg
#define NPC@YSII_Ag Player@YSII_Ag
#define Character@YSII_Cg Player@YSII_Cg
#define Character@YSII_Ag Player@YSII_Ag
#define Bot@YSII_Cg Player@YSII_Cg
#define Bot@YSII_Ag Player@YSII_Ag

#if defined _INC_open_mp
    stock Iter_CreateVehicle(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, respawn_delay, bool:addsiren = false)
#else
    stock Iter_CreateVehicle(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, respawn_delay, addsiren = 0)
#endif
{
    new ret = CreateVehicle(modelid, x, y, z, angle, color1, color2, respawn_delay, addsiren);
    if (ret != INVALID_VEHICLE_ID && ret != 0) Iter_Add(Vehicle, ret);
    return ret;
}
#if defined _ALS_CreateVehicle
    #undef CreateVehicle
#else
    #define _ALS_CreateVehicle
#endif
#define CreateVehicle Iter_CreateVehicle

stock Iter_AddStaticVehicle(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2)
{
    new ret = AddStaticVehicle(modelid, x, y, z, angle, color1, color2);
    if (ret != INVALID_VEHICLE_ID) Iter_Add(Vehicle, ret);
    return ret;
}
#if defined _ALS_AddStaticVehicle
    #undef AddStaticVehicle
#else
    #define _ALS_AddStaticVehicle
#endif
#define AddStaticVehicle Iter_AddStaticVehicle

#if defined _INC_open_mp
    stock Iter_AddStaticVehicleEx(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, respawn_delay, bool:addsiren = false)
#else
    stock Iter_AddStaticVehicleEx(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, respawn_delay, addsiren = 0)
#endif
{
    new ret = AddStaticVehicleEx(modelid, x, y, z, angle, color1, color2, respawn_delay, addsiren);
    if (ret != INVALID_VEHICLE_ID) Iter_Add(Vehicle, ret);
    return ret;
}
#if defined _ALS_AddStaticVehicleEx
    #undef AddStaticVehicleEx
#else
    #define _ALS_AddStaticVehicleEx
#endif
#define AddStaticVehicleEx Iter_AddStaticVehicleEx

stock Iter_DestroyVehicle(vehicleid)
{
    Iter_Remove(Vehicle, vehicleid);
    return DestroyVehicle(vehicleid);
}
#if defined _ALS_DestroyVehicle
    #undef DestroyVehicle
#else
    #define _ALS_DestroyVehicle
#endif
#define DestroyVehicle Iter_DestroyVehicle

stock Iter_CreateActor(modelid, Float:X, Float:Y, Float:Z, Float:Rotation)
{
    new ret = CreateActor(modelid, X, Y, Z, Rotation);
    if (ret != INVALID_ACTOR_ID) Iter_Add(Actor, ret);
    return ret;
}
#if defined _ALS_CreateActor
    #undef CreateActor
#else
    #define _ALS_CreateActor
#endif
#define CreateActor Iter_CreateActor

stock Iter_DestroyActor(actorid)
{
    Iter_Remove(Actor, actorid);
    return DestroyActor(actorid);
}
#if defined _ALS_DestroyActor
    #undef DestroyActor
#else
    #define _ALS_DestroyActor
#endif
#define DestroyActor Iter_DestroyActor

forward PPF_OnPlayerConnect(playerid);
public PPF_OnPlayerConnect(playerid)
{
    if (!IsPlayerNPC(playerid)) Iter_Add(Player, playerid);
    return 1;
}

forward PPF_OnPlayerDisconnect(playerid, reason);
public PPF_OnPlayerDisconnect(playerid, reason)
{
    #pragma unused reason
    SetTimerEx("Iter_OPDCInternal", 0, false, "i", playerid);
    return 1;
}

public Iter_OPDCInternal(playerid)
{
    if (IsPlayerConnected(playerid)) return 0;
    if (!IsPlayerNPC(playerid)) Iter_Remove(Player, playerid);
    return 1;
}

stock Iter_ScriptInit()
{
    Iter_Clear(Player);
    Iter_Clear(Vehicle);
    Iter_Clear(Actor);

    for (new playerid; playerid < MAX_PLAYERS; playerid++)
    {
        if (!IsPlayerConnected(playerid)) continue;
        if (!IsPlayerNPC(playerid)) Iter_Add(Player, playerid);
    }
    for (new vehicleid = 1; vehicleid < MAX_VEHICLES; vehicleid++)
    {
        if (!GetVehicleModel(vehicleid)) continue;
        Iter_Add(Vehicle, vehicleid);
    }
    for (new actorid; actorid < MAX_ACTORS; actorid++)
    {
        if (!IsValidActor(actorid)) continue;
        Iter_Add(Actor, actorid);
    }
}

public OnGameModeInit()
{
    Iter_ScriptInit();
    pawn_register_callback("OnPlayerConnect", "PPF_OnPlayerConnect");
    pawn_register_callback("OnPlayerDisconnect", "PPF_OnPlayerDisconnect");

    #if defined PPF_OnGameModeInit
        return PPF_OnGameModeInit();
    #else
        return 1;
    #endif
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit PPF_OnGameModeInit
#if defined PPF_OnGameModeInit
    forward PPF_OnGameModeInit();
#endif

public OnFilterScriptInit()
{
    Iter_ScriptInit();
    pawn_register_callback("OnPlayerConnect", "PPF_OnPlayerConnect");
    pawn_register_callback("OnPlayerDisconnect", "PPF_OnPlayerDisconnect");

    #if defined PPF_OnFilterScriptInit
        return PPF_OnFilterScriptInit();
    #else
        return 1;
    #endif
}
#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit PPF_OnFilterScriptInit
#if defined PPF_OnFilterScriptInit
    forward PPF_OnFilterScriptInit();
#endif

#define foreach_player(%0) for (new %0; %0 < MAX_PLAYERS; %0++) if (IsPlayerConnected(%0))
#define foreach_vehicle(%0) for (new %0; %0 < MAX_VEHICLES; %0++) if (IsValidVehicle(%0))
#define foreach_actor(%0) for (new %0; %0 < MAX_ACTORS; %0++) if (IsValidActor(%0))

#define foreach_list(%0, %1) \
    for (new Iter:_pp_li_%1 = list_iter(%0), %1; \
        iter_inside(_pp_li_%1) \
        && ((%1 = iter_get(_pp_li_%1)) || true) \
        && ((iter_move_next(_pp_li_%1)) || true); )

#define foreach_map(%0, %1, %2) \
    for (new Iter:_pp_ma_%1_%2 = map_iter(%0), %1, %2; \
        iter_inside(_pp_ma_%1_%2) \
        && ((%1 = iter_get_key(_pp_ma_%1_%2)) || true) \
        && ((%2 = iter_get_value(_pp_ma_%1_%2)) || true) \
        && ((iter_move_next(_pp_ma_%1_%2)) || true); )

#define foreach_linked_list(%0, %1) \
    for (new Iter:_pp_ll_%1 = linked_list_iter(%0), %1; \
        iter_inside(_pp_ll_%1) \
        && ((%1 = iter_get(_pp_ll_%1)) || true) \
        && ((iter_move_next(_pp_ll_%1)) || true); )

#define foreach_pool(%0, %1) \
    for (new Iter:_pp_po_%1 = pool_iter(%0), %1; \
        iter_inside(_pp_po_%1) \
        && ((%1 = iter_get(_pp_po_%1)) || true) \
        && ((iter_move_next(_pp_po_%1)) || true); )

#define foreach_arr(%0, %1) \
    for (new %0 = 0, _pp_arr_sz_%0 = sizeof(%1); %0 < _pp_arr_sz_%0; %0++)

#define foreach_arr_value(%0, %1) \
    for (new _pp_arr_i_%0 = 0, _pp_arr_sz_%0 = sizeof(%1), %0; \
        _pp_arr_i_%0 < _pp_arr_sz_%0; _pp_arr_i_%0++) \
        if ((%0 = (%1)[_pp_arr_i_%0]) || true)

#define foreach_count(%0, %1) for (new %0 = 0; %0 < (%1); %0++)
#define foreach_range(%0, %1, %2) for (new %0 = (%1); %0 < (%2); %0++)
#define foreach_down(%0, %1, %2) for (new %0 = (%1); %0 > (%2); %0--)