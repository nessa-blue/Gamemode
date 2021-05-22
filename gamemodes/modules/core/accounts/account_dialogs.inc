Dialog:Register(playerid, response, listitem, const inputtext[]) {
    if(!response) {
        Kick(playerid);
    }
    
    if(udb_hash(inputtext) == 131074) {
        SendClientMessage(playerid, X11_RED, "Error: "WHITE"You need to type something!");
        Dialog_Show(playerid, "Register", DIALOG_STYLE_PASSWORD, "Register", "Type password you want on this account:", "Ok", "Kick me");
        return 1;
    }

    Player_SetPassword(playerid, inputtext);
    Player_LoginedStatus(playerid, true);
    Player_SetCash(playerid, 8000);
    Player_SetScore(playerid, 1);
    Player_SetSkin(playerid, 60);
    Player_SetDateOfRegistration(playerid);
    va_SendClientMessage(playerid, X11_BLUE, "Server: "WHITE"You're registred, and you have $ %i!", Player_GetCash(playerid));
    return 1;
}

Dialog:Login(playerid, response, listitem, const inputtext[]) {
    INI_ParseFile(Player_GetPath(playerid), "Player_Load", .bExtra=true, .extra=playerid);
    if(udb_hash(inputtext) == 131074) {
        SendClientMessage(playerid, X11_RED, "Error: "WHITE"You need to type something!");
        Dialog_Show(playerid, "Login", DIALOG_STYLE_PASSWORD, "Login", "Type the password:", "Ok", "Kick me");
        return 1;
    }
    if(!response) {
        Kick(playerid);
    }
    if(udb_hash(inputtext) != Player_GetPassword(playerid)) {
        Player_SetLoginAttempts(playerid, Player_GetLoginAttempts(playerid)+1);
        va_SendClientMessage(playerid, X11_RED, "Error: "WHITE"Incorrect password, you have %i/4 attempts!", Player_GetLoginAttempts(playerid));
        Dialog_Show(playerid, "Login", DIALOG_STYLE_PASSWORD, "Login", "Type the password:", "Ok", "Kick me");
        if(Player_GetLoginAttempts(playerid) >= 4) {
            va_SendClientMessage(playerid, X11_RED, "Error: "WHITE"You were kicked out of the server because you had 4/4 attempts to log in");
            DelayedKick(playerid, 600);
        }
        return 1;
    }

    va_SendClientMessage(playerid, X11_BLUE, "Server: "WHITE"You have logged in to the server, we wish you a great game!", Player_GetCash(playerid));
    Player_LoginedStatus(playerid, true);
    Player_SetCash(playerid, Player_GetCash(playerid));
    Player_SetScore(playerid, Player_GetScore(playerid));
    return 1;
}