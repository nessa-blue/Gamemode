static 
    password[MAX_PLAYERS],
    score[MAX_PLAYERS],
    respects[MAX_PLAYERS],
    cash[MAX_PLAYERS],
    skin[MAX_PLAYERS],
    ages[MAX_PLAYERS],
    string: dateOfRegistration[MAX_PLAYERS][128],
    bool: isPlayerLogined[MAX_PLAYERS],
    loginAttempts[MAX_PLAYERS],
    bool: isRegistered[MAX_PLAYERS],
    gender[MAX_PLAYERS];

/**
    Get/Set Functions
*/
stock Player_GetPath(playerid) {
    static 
        string[128];

    format(string, sizeof(string), "accounts/%s.ini", ReturnPlayerName(playerid));    
    return string;
}

stock Player_Spawn(playerid) {
    if(Player_IsLogined(playerid)) {
        SetSpawnInfo(playerid, 0, Player_GetSkin(playerid), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        SpawnPlayer(playerid);
    }
    return 1;
}

#define IsPlayerRegistred(%0) fexist(Player_GetPath(%0))

forward Player_Load(playerid, name[], value[]);
public Player_Load(playerid, name[], value[]) {
    INI_Int("Password", password[playerid]);
    INI_Int("Score", score[playerid]);
    INI_Int("Respects", respects[playerid]);
    INI_Int("Cash", cash[playerid]);
    INI_Int("Skin", skin[playerid]);
    INI_Int("Ages", ages[playerid]);
    INI_Int("Gender", gender[playerid]);
    INI_String("DateOfRegistration", dateOfRegistration[playerid]);
    return 1;
}

stock udb_hash(const string: buff[]) {
    new length=strlen(buff);
    new s1 = 1;
    new s2 = 0;
    new n;
    for (n=0; n<length; n++)
    {
        s1 = (s1 + buff[n]) % 65521;
        s2 = (s2 + s1)     % 65521;
    }
    return (s2 << 16) + s1;
}

stock Player_GetPassword(playerid) {
    return password[playerid];
}

stock Player_SetPassword(playerid, const string: pass[]) {
    if(!IsPlayerConnected(playerid) || !strlen(ReturnPlayerName(playerid))) {
        return 0;
    }

    password[playerid] = udb_hash(pass);
    new INI:File = INI_Open(Player_GetPath(playerid));
    INI_WriteInt(File, "Password", Player_GetPassword(playerid));
    INI_Close(File);
    return 1;
}

stock Player_GetScore(playerid) {
    return score[playerid];
}

stock Player_SetScore(playerid, score1) {
    if(!IsPlayerConnected(playerid) || !strlen(ReturnPlayerName(playerid))) {
        return 0;
    }

    score[playerid] = score1;
    SetPlayerScore(playerid, score1);
    new INI:File = INI_Open(Player_GetPath(playerid));
    INI_WriteInt(File, "Score", Player_GetScore(playerid));
    INI_Close(File);
    return 1;
}

stock Player_GetRespects(playerid) {
    return respects[playerid];
}

stock Player_SetRespects(playerid, amount) {
    if(!IsPlayerConnected(playerid) || !strlen(ReturnPlayerName(playerid))) {
        return 0;
    }

    respects[playerid] = amount;
    new INI:File = INI_Open(Player_GetPath(playerid));
    INI_WriteInt(File, "Respects", Player_GetRespects(playerid));
    INI_Close(File);
    return 1;
}

stock Player_GetCash(playerid) {
    return cash[playerid];
}

stock Player_SetCash(playerid, amount) {
    if(!IsPlayerConnected(playerid) || !strlen(ReturnPlayerName(playerid))) {
        return 0;
    }

    cash[playerid] = amount;
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, amount);
    new INI:File = INI_Open(Player_GetPath(playerid));
    INI_WriteInt(File, "Cash", Player_GetCash(playerid));
    INI_Close(File);
    return 1;
}

stock Player_GiveCash(playerid, amount) {
    if(!IsPlayerConnected(playerid) || !strlen(ReturnPlayerName(playerid))) {
        return 0;
    }

    cash[playerid] += amount;
    GivePlayerMoney(playerid, amount);
    new INI:File = INI_Open(Player_GetPath(playerid));
    INI_WriteInt(File, "Cash", Player_GetCash(playerid));
    INI_Close(File);
    return 1;
}

stock Player_GetSkin(playerid) {
    return skin[playerid];
}

stock Player_SetSkin(playerid, id) {
    if(!IsPlayerConnected(playerid) || !strlen(ReturnPlayerName(playerid))) {
        return 0;
    }

    skin[playerid] = id;
    SetPlayerSkin(playerid, id);
    new INI:File = INI_Open(Player_GetPath(playerid));
    INI_WriteInt(File, "Skin", Player_GetSkin(playerid));
    INI_Close(File);
    return 1;
}

stock Player_GetAges(playerid) {
    return ages[playerid];
}

stock Player_SetAges(playerid, amount) {
    if(!IsPlayerConnected(playerid) || !strlen(ReturnPlayerName(playerid))) {
        return 0;
    }

    ages[playerid] = amount;
    new INI:File = INI_Open(Player_GetPath(playerid));
    INI_WriteInt(File, "Ages", Player_GetAges(playerid));
    INI_Close(File);
    return 1;
}

stock Player_GetDateOfRegistration(playerid) {
    return dateOfRegistration[playerid];
}

stock Player_SetDateOfRegistration(playerid, today=1, month = 0, day = 0, year = 0) {
    if(!IsPlayerConnected(playerid) || !strlen(ReturnPlayerName(playerid))) {
        return 0;
    }

    if(today != 1) {
        static
            string[128];
        format(string, sizeof(string), "%02d.%02d.%02d", month, day, year);
        strcopy(dateOfRegistration[playerid], string);
        return 1;
    }

    static 
        month1,
        day1, 
        year1,
        string[128];

    getdate(year1, month1, day1);
    format(string, sizeof(string), "%02d.%02d.%02d", month1, day1, year1);
    strcopy(dateOfRegistration[playerid], string);
    new INI:File = INI_Open(Player_GetPath(playerid));
    INI_WriteString(File, "DateOfRegistration", Player_GetDateOfRegistration(playerid));
    INI_Close(File);
    return 1;
}

stock Player_IsLogined(playerid) {
    return isPlayerLogined[playerid];
}

stock Player_LoginedStatus(playerid, bool: h) {
    if(!IsPlayerConnected(playerid) || !strlen(ReturnPlayerName(playerid))) {
        return 0;
    }

    isPlayerLogined[playerid] = h;
    return 1;
}

stock Player_GetLoginAttempts(playerid) {
    return loginAttempts[playerid];
}

stock Player_SetLoginAttempts(playerid, number) {
    if(!IsPlayerConnected(playerid) || !strlen(ReturnPlayerName(playerid))) {
        return 0;
    }

    loginAttempts[playerid] = number;
    return 1;
}

stock ClearVariables(playerid) {
    isPlayerLogined[playerid] = false;
    loginAttempts[playerid]=0;

    return 1;
}

stock Player_IsRegistered(playerid) {
    return isRegistered[playerid];
}

stock Player_RegisteredStatus(playerid, bool: status) {
    if(!IsPlayerConnected(playerid) || !strlen(ReturnPlayerName(playerid))) {
        return 0;
    }
    isRegistered[playerid] = status;
    return 1;
}

#define Male 1
#define Female 0
stock Player_GetGender(playerid) {
    return gender[playerid];
}

stock Player_SetGender(playerid, Gender) {
    if(!IsPlayerConnected(playerid) || !strlen(ReturnPlayerName(playerid))) {
        return 0;
    }
    gender[playerid] = Gender;
    new INI:File = INI_Open(Player_GetPath(playerid));
    INI_WriteInt(File, "Gender", Player_GetGender(playerid));
    INI_Close(File);
    return 1;
}
