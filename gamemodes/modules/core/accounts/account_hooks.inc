#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid) {
    if(IsPlayerRegistred(playerid)) {
        Dialog_Show(playerid, "Login", DIALOG_STYLE_PASSWORD, "Login", "Type the password:", "Ok", "Kick me");
    }
    else {
        Dialog_Show(playerid, "Register", DIALOG_STYLE_PASSWORD, "Register", "Type password you want on this account:", "Ok", "Kick me");
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerRequestSpawn(playerid) {
    if(Player_IsLogined(playerid)) {
        Player_Spawn(playerid);
    }
    return Y_HOOKS_CONTINUE_RETURN_0;
}

hook OnPlayerDisconnect(playerid, reason) {
    ClearVariables(playerid);
    return 1;
}

hook OnPlayerRequestClass(playerid, classid) {
    if(Player_IsLogined(playerid)) {
        Player_Spawn(playerid);
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}