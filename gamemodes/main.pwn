const
    MAX_PLAYERS = 50;    

#include <a_samp>
#include <easyDialog>

#include <YSI_Storage\y_ini>
#include <YSI_Server\y_colours>
#include <YSI_Server\y_utils>
#include <YSI_Coding\y_timers>

main() {
    SetGameModeText("HS:RP v1.0");
    SendRconCommand("language English");
}

stock DelayedKick(playerid, time) {
    defer kkck[time](playerid);
}

timer kkck[1](playerid) {
    Kick(playerid);
    return 1;
}
#include <account>
