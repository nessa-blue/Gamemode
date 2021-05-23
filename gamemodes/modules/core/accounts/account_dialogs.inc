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
    Player_SetScore(playerid, 1);
    Player_SetDateOfRegistration(playerid);
    Player_Spawn(playerid);
    Player_SetSkin(playerid, 60);
    Player_SetCash(playerid, 8000);
    // va_SendClientMessage(playerid, X11_BLUE, "Server: "WHITE"You're registred, and you have $ %i!", Player_GetCash(playerid));
    SendClientMessage(playerid, X11_BLUE, "Server: "WHITE"Select your gender!");
    Dialog_Show(playerid, "Gender", DIALOG_STYLE_MSGBOX, "Gender: ", "Select your gender:", "Male", "Female");
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
    Player_RegisteredStatus(playerid, true);
    Player_SetScore(playerid, Player_GetScore(playerid));
    Player_Spawn(playerid);
    Player_SetSkin(playerid, Player_GetSkin(playerid));
    return 1;
}

Dialog:Gender(playerid, response, listitem, const inputtext[]) {
    
    Player_SetGender(playerid, response); // Male == 1, so if you click male, then variable response will be 0, and if you click female(== 0), then variable response will be 1
    va_SendClientMessage(playerid, X11_BLUE, "Server: "WHITE"You selected gender, now type your ages!");
    Dialog_Show(playerid, "Ages", DIALOG_STYLE_INPUT, "Ages", "Type number of your ages!", "Ok", "Kick me");
    return 1;
}

Dialog:Ages(playerid, response, listitem, const inputtext[]) {
    if(strval(inputtext) <= 0 || strval(inputtext) > 60) {
        Dialog_Show(playerid, "Ages", DIALOG_STYLE_INPUT, "Ages", "Type number of your ages!", "Ok", "Kick me");
        return 1;
    }
    if(!response) {
        Kick(playerid);
    }
    Player_SetAges(playerid, strval(inputtext));
    va_SendClientMessage(playerid, X11_BLUE, "Server: "WHITE"You typed your ages, you're registered!");
    Player_RegisteredStatus(playerid, true);
    Player_LoginedStatus(playerid, true);
    Player_Spawn(playerid);
    return 1;
}
