#if defined _pp_iterate_included
    #endinput
#endif
#define _pp_iterate_included

#include <PawnPlus>

#if !defined MAX_PLAYERS
    #define MAX_PLAYERS 1000
#endif
#if !defined MAX_VEHICLES
    #define MAX_VEHICLES 2000
#endif
#if !defined MAX_ACTORS
    #define MAX_ACTORS 1000
#endif
#if !defined MAX_OBJECTS
    #define MAX_OBJECTS 2000
#endif

/* Container Iterators */

#define foreach_list(%0:%1) \
    for(new Iter:_pp_it_li_%0 = list_iter(%1); iter_inside(_pp_it_li_%0); iter_move_next(_pp_it_li_%0)) \
        for(new %0 = iter_get(_pp_it_li_%0), bool:_pp_c_li_%0 = false; !_pp_c_li_%0; _pp_c_li_%0 = true)

#define foreach_linked_list(%0:%1) \
    for(new Iter:_pp_it_ll_%0 = linked_list_iter(%1); iter_inside(_pp_it_ll_%0); iter_move_next(_pp_it_ll_%0)) \
        for(new %0 = iter_get(_pp_it_ll_%0), bool:_pp_c_ll_%0 = false; !_pp_c_ll_%0; _pp_c_ll_%0 = true)

#define foreach_pool(%0:%1) \
    for(new Iter:_pp_it_po_%0 = pool_iter(%1); iter_inside(_pp_it_po_%0); iter_move_next(_pp_it_po_%0)) \
        for(new %0 = iter_get(_pp_it_po_%0), bool:_pp_c_po_%0 = false; !_pp_c_po_%0; _pp_c_po_%0 = true)

#define foreach_map(%0:%1, %2:%3) \
    for(new Iter:_pp_it_ma_%0_%2 = map_iter(%1); iter_inside(_pp_it_ma_%0_%2); iter_move_next(_pp_it_ma_%0_%2)) \
        for(new %0 = iter_get_key(_pp_it_ma_%0_%2), %2 = iter_get_value(_pp_it_ma_%0_%2), bool:_pp_c_ma_%0_%2 = false; !_pp_c_ma_%0_%2; _pp_c_ma_%0_%2 = true)

/* Generic Container Iterators */

#if defined PP_SYNTAX_GENERIC

#define foreach_list<%0>(%1:%2) \
    for(new Iter<%0>:_pp_it_li_%1 = list_iter<%0>(%2); iter_inside(Iter:%1); iter_move_next(Iter:%1)) \
        for(new %1 = iter_get<%0>(Iter:%1), bool:_pp_c_li_%1 = false; !_pp_c_li_%1; _pp_c_li_%1 = true)

#define foreach_linked_list<%0>(%1:%2) \
    for(new Iter<%0>:_pp_it_ll_%1 = linked_list_iter<%0>(%2); iter_inside(Iter:%1); iter_move_next(Iter:%1)) \
        for(new %1 = iter_get<%0>(Iter:%1), bool:_pp_c_ll_%1 = false; !_pp_c_ll_%1; _pp_c_ll_%1 = true)

#define foreach_pool<%0>(%1:%2) \
    for(new Iter<%0>:_pp_it_po_%1 = pool_iter<%0>(%2); iter_inside(Iter:%1); iter_move_next(Iter:%1)) \
        for(new %1 = iter_get<%0>(Iter:%1), bool:_pp_c_po_%1 = false; !_pp_c_po_%1; _pp_c_po_%1 = true)

#define foreach_map<%0,%1>(%2:%3, %4:%5) \
    for(new PairIter<%0,%1>:_pp_it_ma_%2_%4 = map_iter<%0,%1>(%3); iter_inside(Iter:%2); iter_move_next(Iter:%2)) \
        for(new %2 = iter_get_key<%0,%1>(Iter:%2), %4 = iter_get_value<%0,%1>(Iter:%2), bool:_pp_c_ma_%2_%4 = false; !_pp_c_ma_%2_%4; _pp_c_ma_%2_%4 = true)

#endif

/* Array Iterators */

#define foreach_arr(%0:%1) \
    for(new %0 = 0, _pp_sz_ar_%0 = sizeof(%1); %0 < _pp_sz_ar_%0; %0++)

#define foreach_arr_value(%0:%1) \
    for(new _pp_iv_av_%0 = 0, _pp_sz_av_%0 = sizeof(%1); _pp_iv_av_%0 < _pp_sz_av_%0; _pp_iv_av_%0++) \
        for(new %0 = (%1)[_pp_iv_av_%0], bool:_pp_o_av_%0 = false; !_pp_o_av_%0; _pp_o_av_%0 = true)

#define foreach_arr2(%0:%1, %2:%3, %4:%5) \
    for(new _pp_i2_%0 = 0, _pp_s2_%0 = sizeof(%5); _pp_i2_%0 < _pp_s2_%0; _pp_i2_%0++) \
        for(new _pp_j2_%2 = 0, _pp_s22_%2 = sizeof(%5[]); _pp_j2_%2 < _pp_s22_%2; _pp_j2_%2++) \
            for(new %0 = _pp_i2_%0, %2 = _pp_j2_%2, %4 = (%5)[_pp_i2_%0][_pp_j2_%2], bool:_pp_o2_%0_%2 = false; !_pp_o2_%0_%2; _pp_o2_%0_%2 = true)

#define foreach_arr3(%0:%1, %2:%3, %4:%5, %6:%7) \
    for(new _pp_i3_%0 = 0, _pp_s3_%0 = sizeof(%7); _pp_i3_%0 < _pp_s3_%0; _pp_i3_%0++) \
        for(new _pp_j3_%2 = 0, _pp_s23_%2 = sizeof(%7[]); _pp_j3_%2 < _pp_s23_%2; _pp_j3_%2++) \
            for(new _pp_k3_%4 = 0, _pp_s33_%4 = sizeof(%7[][]); _pp_k3_%4 < _pp_s33_%4; _pp_k3_%4++) \
                for(new %0 = _pp_i3_%0, %2 = _pp_j3_%2, %4 = _pp_k3_%4, %6 = (%7)[_pp_i3_%0][_pp_j3_%2][_pp_k3_%4], bool:_pp_o3_%0_%2_%4 = false; !_pp_o3_%0_%2_%4; _pp_o3_%0_%2_%4 = true)

/* Range Iterators */

#define foreach_range(%0:%1, %2) \
    for(new %0 = (%1); %0 < (%2); %0++)

#define foreach_range_step(%0:%1, %2, %3) \
    for(new %0 = (%1), _pp_st_rs_%0 = (%3), _pp_en_rs_%0 = (%2); (_pp_st_rs_%0 > 0) ? (%0 < _pp_en_rs_%0) : (%0 > _pp_en_rs_%0); %0 += _pp_st_rs_%0)

#define foreach_count(%0:%1) \
    for(new %0 = 0; %0 < (%1); %0++)

#define foreach_down(%0:%1, %2) \
    for(new %0 = (%1); %0 > (%2); %0--)

/* Entity Iterators */

static List:_pp_PlayerCache = INVALID_LIST;
static List:_pp_VehicleCache = INVALID_LIST;
static List:_pp_ActorCache = INVALID_LIST;

stock _pp_PlayerAdd(playerid)
{
    if(!list_valid(_pp_PlayerCache)) _pp_PlayerCache = list_new();
    if(list_find(_pp_PlayerCache, playerid) == -1) list_add(_pp_PlayerCache, playerid);
}

stock _pp_PlayerRemove(playerid)
{
    if(!list_valid(_pp_PlayerCache)) return;
    new idx = list_find(_pp_PlayerCache, playerid);
    if(idx != -1) list_remove(_pp_PlayerCache, idx);
}

stock _pp_VehicleAdd(vehicleid)
{
    if(!list_valid(_pp_VehicleCache)) _pp_VehicleCache = list_new();
    if(list_find(_pp_VehicleCache, vehicleid) == -1) list_add(_pp_VehicleCache, vehicleid);
}

stock _pp_VehicleRemove(vehicleid)
{
    if(!list_valid(_pp_VehicleCache)) return;
    new idx = list_find(_pp_VehicleCache, vehicleid);
    if(idx != -1) list_remove(_pp_VehicleCache, idx);
}

stock _pp_ActorAdd(actorid)
{
    if(!list_valid(_pp_ActorCache)) _pp_ActorCache = list_new();
    if(list_find(_pp_ActorCache, actorid) == -1) list_add(_pp_ActorCache, actorid);
}

stock _pp_ActorRemove(actorid)
{
    if(!list_valid(_pp_ActorCache)) return;
    new idx = list_find(_pp_ActorCache, actorid);
    if(idx != -1) list_remove(_pp_ActorCache, idx);
}

stock _pp_ScanPlayers()
{
    if(!list_valid(_pp_PlayerCache)) _pp_PlayerCache = list_new();
    else list_clear(_pp_PlayerCache);
    for(new i; i < MAX_PLAYERS; i++)
        if(IsPlayerConnected(i)) list_add(_pp_PlayerCache, i);
}

stock _pp_ScanVehicles()
{
    if(!list_valid(_pp_VehicleCache)) _pp_VehicleCache = list_new();
    else list_clear(_pp_VehicleCache);
    for(new i; i < MAX_VEHICLES; i++)
        if(IsValidVehicle(i)) list_add(_pp_VehicleCache, i);
}

stock _pp_ScanActors()
{
    if(!list_valid(_pp_ActorCache)) _pp_ActorCache = list_new();
    else list_clear(_pp_ActorCache);
    for(new i; i < MAX_ACTORS; i++)
        if(IsValidActor(i)) list_add(_pp_ActorCache, i);
}

stock _pp_ScanAll()
{
    _pp_ScanPlayers();
    _pp_ScanVehicles();
    _pp_ScanActors();
}

stock _pp_EnsurePlayerCache()
{
    if(!list_valid(_pp_PlayerCache)) _pp_ScanPlayers();
}

stock _pp_EnsureVehicleCache()
{
    if(!list_valid(_pp_VehicleCache)) _pp_ScanVehicles();
}

stock _pp_EnsureActorCache()
{
    if(!list_valid(_pp_ActorCache)) _pp_ScanActors();
}

#define foreach_player(%0) \
    for(new Iter:_pp_it_pl_%0 = list_iter(_pp_EnsurePlayerCache(), 0, _pp_PlayerCache); iter_inside(_pp_it_pl_%0); iter_move_next(_pp_it_pl_%0)) \
        for(new %0 = iter_get(_pp_it_pl_%0), bool:_pp_c_pl_%0 = false; !_pp_c_pl_%0; _pp_c_pl_%0 = true)

#define foreach_vehicle(%0) \
    for(new Iter:_pp_it_vh_%0 = list_iter(_pp_EnsureVehicleCache(), 0, _pp_VehicleCache); iter_inside(_pp_it_vh_%0); iter_move_next(_pp_it_vh_%0)) \
        for(new %0 = iter_get(_pp_it_vh_%0), bool:_pp_c_vh_%0 = false; !_pp_c_vh_%0; _pp_c_vh_%0 = true)

#define foreach_actor(%0) \
    for(new Iter:_pp_it_ac_%0 = list_iter(_pp_EnsureActorCache(), 0, _pp_ActorCache); iter_inside(_pp_it_ac_%0); iter_move_next(_pp_it_ac_%0)) \
        for(new %0 = iter_get(_pp_it_ac_%0), bool:_pp_c_ac_%0 = false; !_pp_c_ac_%0; _pp_c_ac_%0 = true)

/* Connection Tracking */

forward _pp@PlayerConnect(playerid);
public _pp@PlayerConnect(playerid)
{
    _pp_PlayerAdd(playerid);
    return 1;
}

forward _pp@PlayerDisconnect(playerid, reason);
public _pp@PlayerDisconnect(playerid, reason)
{
    _pp_PlayerRemove(playerid);
    return 1;
}

forward _pp@VehicleSpawn(vehicleid);
public _pp@VehicleSpawn(vehicleid)
{
    _pp_VehicleAdd(vehicleid);
    return 1;
}

forward _pp@VehicleDeath(vehicleid, killerid);
public _pp@VehicleDeath(vehicleid, killerid)
{
    _pp_VehicleRemove(vehicleid);
    return 1;
}

/* Initialization */

#if defined PP_SYNTAX_ON_INIT

pawn_on_init[PPIterate]()
{
    _pp_ScanAll();

    if(pawn_public_exists("OnPlayerConnect"))
        pawn_register_callback("OnPlayerConnect", "_pp@PlayerConnect");
    if(pawn_public_exists("OnPlayerDisconnect"))
        pawn_register_callback("OnPlayerDisconnect", "_pp@PlayerDisconnect");
    if(pawn_public_exists("OnVehicleSpawn"))
        pawn_register_callback("OnVehicleSpawn", "_pp@VehicleSpawn");
    if(pawn_public_exists("OnVehicleDeath"))
        pawn_register_callback("OnVehicleDeath", "_pp@VehicleDeath");
    return 1;
}

#else

forward _pp@on_init@PPIterate();
public _pp@on_init@PPIterate()
{
    _pp_ScanAll();

    if(pawn_public_exists("OnPlayerConnect"))
        pawn_register_callback("OnPlayerConnect", "_pp@PlayerConnect");
    if(pawn_public_exists("OnPlayerDisconnect"))
        pawn_register_callback("OnPlayerDisconnect", "_pp@PlayerDisconnect");
    if(pawn_public_exists("OnVehicleSpawn"))
        pawn_register_callback("OnVehicleSpawn", "_pp@VehicleSpawn");
    if(pawn_public_exists("OnVehicleDeath"))
        pawn_register_callback("OnVehicleDeath", "_pp@VehicleDeath");
    return 1;
}

#endif