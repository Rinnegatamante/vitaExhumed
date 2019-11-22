//-------------------------------------------------------------------------
/*
Copyright (C) 2010-2019 EDuke32 developers and contributors
Copyright (C) 2019 sirlemonhead, Nuke.YKT
This file is part of PCExhumed.
PCExhumed is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License version 2
as published by the Free Software Foundation.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
//-------------------------------------------------------------------------

#ifndef __player_h__
#define __player_h__

#include "compat.h"

void PlayerInterruptKeys();
void RestoreSavePoint(int nPlayer, int *x, int *y, int *z, short *nSector, short *nAngle);
void SetSavePoint(int nPlayer, int x, int y, int z, short nSector, short nAngle);
void InitPlayer();
void InitPlayerKeys(short nPlayer);
void DoKenTest();
int GrabPlayer();
void InitPlayerInventory(short nPlayer);
void RestartPlayer(short nPlayer);

void FuncPlayer(int nSector, int nSprite, int nRun);

#define kMaxPlayers			8
#define kDefaultLives		3
#define kMaxPlayerLives		5
#define kMaxHealth			800

extern int nLocalPlayer;

extern int lPlayerXVel;
extern int lPlayerYVel;
extern fix16_t nPlayerDAng;

struct Player
{
    short nHealth;
    short field_2;
    short nAction;
    short nSprite;
    short bIsMummified;
    short someNetVal;
    short invincibility;
    short nAir;
    short nSeq;
    short nMaskAmount;
    uint16_t keys;
    short nMagic;
    char items[8];
    short nAmmo[7]; // TODO - kMaxWeapons?
    short pad[2];

    short nCurrentWeapon;
    short field_3FOUR;
    short bIsFiring;
    short field_38;
    short field_3A;
    short field_3C;
    short nRun;

    fix16_t q16angle, q16oangle;
    fix16_t q16horiz, q16ohoriz;
    vec3_t opos;
};

extern short PlayerCount;

extern short nPlayerTorch[];

extern short nPlayerLives[];
extern short nPlayerItem[];
extern Player PlayerList[];
extern short nPlayerInvisible[];
extern short nPlayerDouble[];
extern short nPlayerViewSect[];
extern short nPlayerFloorSprite[];

extern short nTauntTimer[];

extern short nDoppleSprite[];

extern uint16_t nPlayerWeapons[];

extern short nPlayerOldWeapon[];
extern short nPlayerGrenade[kMaxPlayers];
extern short nGrenadePlayer[50];

extern short nPistolClip[];

extern short nPlayerScore[];

extern short nPlayerClip[];

extern short obobangle, bobangle;

extern int totalvel[];
extern int16_t eyelevel[], oeyelevel[];

extern short nNetStartSprite[kMaxPlayers];
extern short nNetStartSprites;
extern short nCurStartSprite;

extern int nXDamage[kMaxPlayers];
extern int nYDamage[kMaxPlayers];

extern int nPlayerDY[kMaxPlayers];
extern int nPlayerDX[kMaxPlayers];

short GetPlayerFromSprite(short nSprite);
void SetPlayerMummified(int nPlayer, int bIsMummified);
int AddAmmo(int nPlayer, int nWeapon, int nAmmoAmount);
void ShootStaff(int nPlayer);

#endif
