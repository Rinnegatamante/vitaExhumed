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

#include "compat.h"
#include "baselayer.h"
#include "renderlayer.h"
#include "typedefs.h"
#include "common.h"
#include "keyboard.h"
#include "control.h"
#include "engine.h"
#include "exhumed.h"
#include "osdcmds.h"
#include "map.h"
#include "sequence.h"
#include "movie.h"
#include "names.h"
#include "menu.h"
#include "player.h"
#include "network.h"
#include "input.h"
#include "sound.h"
#include "cd.h"
#include "view.h"
#include "status.h"
#include "config.h"
#include "init.h"
#include "ra.h"
#include "version.h"
#include "timer.h"
#include "runlist.h"
#include "anubis.h"
#include "spider.h"
#include "mummy.h"
#include "fish.h"
#include "lion.h"
#include "light.h"
#include "move.h"
#include "lavadude.h"
#include "rex.h"
#include "set.h"
#include "queen.h"
#include "roach.h"
#include "wasp.h"
#include "scorp.h"
#include "rat.h"
#include "cdrom.h"
#include "cdaudio.h"
#include "serial.h"
#include "network.h"
#include "random.h"
#include "items.h"
#include "trigdat.h"
#include "record.h"
#include "lighting.h"
#include "grpscan.h"
#include <string.h>
#include <cstdio> // for printf
#include <cstdlib>
#include <stdarg.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

#ifdef _WIN32
# include "winbits.h"
#endif /* _WIN32 */

#ifdef __cplusplus
extern "C" {
#endif
    extern const char* s_buildRev;
    extern const char* s_buildTimestamp;
#ifdef __cplusplus
}
#endif

const char* AppProperName = APPNAME;
const char* AppTechnicalName = APPBASENAME;

void FinishLevel();

int htimer = 0;

/* these are XORed in the original game executable then XORed back to normal when the game first starts. Here they are normally */
const char *gString[] =
{
    "CINEMAS",
    "THE ANCIENT EGYPTIAN CITY",
    "OF KARNAK HAS BEEN SEIZED",
    "BY UNKNOWN POWERS, AND GREAT",
    "TURMOIL IS SPREADING INTO",
    "NEIGHBORING LANDS, POSING",
    "A GRAVE THREAT TO PLANET",
    "EARTH. MILITANT FORCES FROM",
    "ALL PARTS OF THE GLOBE HAVE",
    "ENTERED THE KARNAK VALLEY,",
    "BUT NONE HAVE RETURNED. THE",
    "ONLY KNOWN INFORMATION",
    "REGARDING THIS CRISIS CAME",
    "FROM A DYING KARNAK VILLAGER",
    "WHO MANAGED TO WANDER OUT OF",
    "THE VALLEY TO SAFETY.",
    "'THEY'VE STOLEN THE GREAT",
    "KING'S MUMMY...', MURMURED",
    "THE DYING VILLAGER, BUT THE",
    "VILLAGER DIED BEFORE HE",
    "COULD SAY MORE. WITH NO",
    "OTHER OPTIONS, WORLD",
    "LEADERS HAVE CHOSEN TO DROP",
    "YOU INTO THE VALLEY VIA",
    "HELICOPTER IN AN ATTEMPT",
    "TO FIND AND DESTROY THE",
    "THREATENING FORCES AND",
    "RESOLVE THE MYSTERY THAT",
    "HAS ENGULFED THIS ONCE",
    "PEACEFUL LAND. FLYING AT",
    "HIGH ALTITUDE TO AVOID",
    "BEING SHOT DOWN LIKE OTHERS",
    "BEFORE YOU, YOUR COPTER",
    "MYSTERIOUSLY EXPLODES IN THE",
    "AIR AS YOU BARELY ESCAPE,",
    "WITH NO POSSIBLE CONTACT",
    "WITH THE OUTSIDE WORLD.",
    "SCARED AS HELL, YOU DESCEND",
    "INTO THE HEART OF KARNAK...",
    "HOME TO THE CELEBRATED",
    "BURIAL CRYPT OF THE GREAT",
    "KING RAMSES.",
    "END",
    "AN EVIL FORCE KNOWN AS THE",
    "KILMAAT HAS BESIEGED THE",
    "SANCTITY OF MY PALACE AND",
    "IS PULLING AT THE VERY",
    "TENDRILS OF MY EXISTENCE.",
    "THESE FORCES INTEND TO",
    "ENSLAVE ME BY REANIMATING",
    "MY PRESERVED CORPSE. I HAVE",
    "PROTECTED MY CORPSE WITH A",
    "GENETIC KEY.  IF YOU ARE",
    "UNSUCCESSFUL I CANNOT",
    "PROTECT CIVILIZATION, AND",
    "CHAOS WILL PREVAIL. I AM",
    "BEING TORN BETWEEN WORLDS",
    "AND THIS INSIDIOUS",
    "EXPERIMENT MUST BE STOPPED.",
    "END",
    "I HAVE HIDDEN A MYSTICAL",
    "GAUNTLET AT EL KAB THAT WILL",
    "CHANNEL MY ENERGY THROUGH",
    "YOUR HANDS. FIND THE",
    "GAUNTLET AND CROSS THE ASWAN",
    "HIGH DAM TO DEFEAT THE EVIL",
    "BEAST SET.",
    "END",
    "SET WAS A FORMIDABLE FOE.",
    "NO MORTAL HAS EVEN CONQUERED",
    "THEIR OWN FEAR, MUCH LESS",
    "ENTERED MORTAL BATTLE AND",
    "TAKEN HIS LIFE.",
    "END",
    "YOU'VE MADE IT HALFWAY TOWARD",
    "FULLFILLING YOUR DESTINY.",
    "THE KILMAAT ARE GROWING",
    "RESTLESS WITH YOUR PROGRESS.",
    "SEEK OUT A TEMPLE IN THIS",
    "CITADEL WHERE I WILL PROVIDE",
    "MORE INFORMATION",
    "END",
    "THE KILMAAT RACE HAS",
    "CONTINUED THEIR MONSTEROUS",
    "ANIMAL-HUMAN EXPERIMENTS IN",
    "AN EFFORT TO SOLVE THE KEY OF",
    "ANIMATING MY CORPSE. THE",
    "VICTORY DEFEATING SET DIDN'T",
    "SLOW YOU DOWN AS MUCH AS",
    "THEY HAD PLANNED. THEY ARE",
    "ACTIVELY ROBBING A SLAVE",
    "GIRL OF HER LIFE TO CREATE",
    "ANOTHER MONSTEROUS",
    "ABOMINATION, COMBINING HUMAN",
    "AND INSECT INTENT ON SLAYING",
    "YOU.  PREPARE YOURSELF FOR",
    "BATTLE AS SHE WILL BE WAITING",
    "FOR YOU AT THE LUXOR TEMPLE. ",
    "END",
    "YOU'VE DONE WELL TO DEFEAT",
    "SELKIS. YOU HAVE DISTRACTED",
    "THE KILMAAT WITH YOUR",
    "PRESENCE AND THEY HAVE",
    "TEMPORARILY ABANDONED",
    "ANIMATION OF MY CORPSE.",
    "THE ALIEN QUEEN KILMAATIKHAN",
    "HAS A PERSONAL VENDETTA",
    "AGAINST YOU. ARROGANCE IS",
    "HER WEAKNESS, AND IF YOU CAN",
    "DEFEAT KILMAATIKHAN, THE",
    "BATTLE WILL BE WON.",
    "END",
    "THE KILMAAT HAVE BEEN",
    "DESTROYED. UNFORTUNATELY,",
    "YOUR RECKLESSNESS HAS",
    "DESTROYED THE EARTH AND ALL",
    "OF ITS INHABITANTS.  ALL THAT",
    "REMAINS IS A SMOLDERING HUNK",
    "OF ROCK.",
    "END",
    "THE KILMAAT HAVE BEEN",
    "DEFEATED AND YOU SINGLE",
    "HANDEDLY SAVED THE EARTH",
    "FROM DESTRUCTION.",
    " ",
    " ",
    " ",
    "YOUR BRAVERY AND HEROISM",
    "ARE LEGENDARY.",
    "END",
    "ITEMS",
    "LIFE BLOOD",
    "LIFE",
    "VENOM",
    "YOU'RE LOSING YOUR GRIP",
    "FULL LIFE",
    "INVINCIBILITY",
    "INVISIBILITY",
    "TORCH",
    "SOBEK MASK",
    "INCREASED WEAPON POWER!",
    "THE MAP!",
    "AN EXTRA LIFE!",
    ".357 MAGNUM!",
    "GRENADE",
    "M-60",
    "FLAME THROWER!",
    "COBRA STAFF!",
    "THE EYE OF RAH GAUNTLET!",
    "SPEED LOADER",
    "AMMO",
    "FUEL",
    "COBRA!",
    "RAW ENERGY",
    "POWER KEY",
    "TIME KEY",
    "WAR KEY",
    "EARTH KEY",
    "MAGIC",
    "LOCATION PRESERVED",
    "COPYRIGHT",
    "LOBOTOMY SOFTWARE, INC.",
    "3D ENGINE BY 3D REALMS",
    "",
    "LASTLEVEL",
    "INCOMING MESSAGE",
    "",
    "OUR LATEST SCANS SHOW",
    "THAT THE ALIEN CRAFT IS",
    "POWERING UP, APPARENTLY",
    "IN AN EFFORT TO LEAVE.",
    "THE BAD NEWS IS THAT THEY",
    "SEEM TO HAVE LEFT A DEVICE",
    "BEHIND, AND ALL EVIDENCE",
    "SAYS ITS GOING TO BLOW A",
    "BIG HOLE IN OUR FINE PLANET.",
    "A SQUAD IS TRYING TO DISMANTLE",
    "IT RIGHT NOW, BUT NO LUCK SO",
    "FAR, AND TIME IS RUNNING OUT.",
    "",
    "GET ABOARD THAT CRAFT NOW",
    "BEFORE IT LEAVES, THEN FIND",
    "AND SHOOT ALL THE ENERGY",
    "TOWERS TO GAIN ACCESS TO THE",
    "CONTROL ROOM. THERE YOU NEED TO",
    "TAKE OUT THE CONTROL PANELS AND",
    "THE CENTRAL POWER SOURCE.  THIS",
    "IS THE BIG ONE BUDDY, BEST OF",
    "LUCK... FOR ALL OF US.",
    "",
    "",
    "CREDITS",
    "EXHUMED",
    "",
    "EXECUTIVE PRODUCERS",
    " ",
    "BRIAN MCNEELY",
    "PAUL LANGE",
    "",
    "GAME CONCEPT",
    " ",
    "PAUL LANGE",
    "",
    "GAME DESIGN",
    " ",
    "BRIAN MCNEELY",
    "",
    "ADDITIONAL DESIGN",
    " ",
    "PAUL KNUTZEN",
    "PAUL LANGE",
    "JOHN VAN DEUSEN",
    "KURT PFEIFER",
    "DOMINICK MEISSNER",
    "DANE EMERSON",
    "",
    "GAME PROGRAMMING",
    " ",
    "KURT PFEIFER",
    "JOHN YUILL",
    "",
    "ADDITIONAL PROGRAMMING",
    " ",
    "PAUL HAUGERUD",
    "",
    "ADDITIONAL TECHNICAL SUPPORT",
    " ",
    "JOHN YUILL",
    "PAUL HAUGERUD",
    "JEFF BLAZIER",
    "",
    "LEVEL DESIGN",
    " ",
    "PAUL KNUTZEN",
    "",
    "ADDITIONAL LEVELS",
    " ",
    "BRIAN MCNEELY",
    "",
    "MONSTERS AND WEAPONS ",
    " ",
    "JOHN VAN DEUSEN",
    "",
    "ARTISTS",
    " ",
    "BRIAN MCNEELY",
    "PAUL KNUTZEN",
    "JOHN VAN DEUSEN",
    "TROY JACOBSON",
    "KEVIN CHUNG",
    "ERIC KLOKSTAD",
    "RICHARD NICHOLS",
    "JOE KRESOJA",
    "JASON WIGGIN",
    "",
    "MUSIC AND SOUND EFFECTS",
    " ",
    "SCOTT BRANSTON",
    "",
    "PRODUCT TESTING",
    " ",
    "DOMINICK MEISSNER",
    "TOM KRISTENSEN",
    "JASON WIGGIN",
    "MARK COATES",
    "",
    "INSTRUCTION MANUAL",
    " ",
    "TOM KRISTENSEN",
    "",
    "SPECIAL THANKS",
    " ",
    "JACQUI LYONS",
    "MARJACQ MICRO, LTD.",
    "MIKE BROWN",
    "IAN MATHIAS",
    "CHERYL LUSCHEI",
    "3D REALMS",
    "KENNETH SILVERMAN",
    "GREG MALONE",
    "MILES DESIGN",
    "REDMOND AM/PM MINI MART",
    "7-11 DOUBLE GULP",
    "",
    "THANKS FOR PLAYING",
    "",
    "THE END",
    "",
    "GUESS YOURE STUCK HERE",
    "UNTIL THE SONG ENDS",
    "",
    "MAYBE THIS IS A GOOD",
    "TIME TO THINK ABOUT ALL",
    "THE THINGS YOU CAN DO",
    "AFTER THE MUSIC IS OVER.",
    "",
    "OR YOU COULD JUST STARE",
    "AT THIS SCREEN",
    "",
    "AND WATCH THESE MESSAGES",
    "GO BY...",
    "",
    "...AND WONDER JUST HOW LONG",
    "WE WILL DRAG THIS OUT...",
    "",
    "AND BELIEVE ME, WE CAN DRAG",
    "IT OUT FOR QUITE A WHILE.",
    "",
    "SHOULD BE OVER SOON...",
    "",
    "ANY MOMENT NOW...",
    "",
    " ",
    "",
    "SEE YA",
    "",
    "END",
    "PASSWORDS",
    "HOLLY",
    "KIMBERLY",
    "LOBOCOP",
    "LOBODEITY",
    "LOBOLITE",
    "LOBOPICK",
    "LOBOSLIP",
    "LOBOSNAKE",
    "LOBOSPHERE",
    "LOBOSWAG",
    "LOBOXY",
    "",
    "PASSINFO",
    "",
    "HI SWEETIE, I LOVE YOU",
    "",
    "",
    "SNAKE CAM ENABLED",
    "FLASHES TOGGLED",
    "FULL MAP",
    "",
    "",
    "",
    "",
    "",
    "EOF",
    "",
};

static char g_rootDir[BMAX_PATH];
char g_modDir[BMAX_PATH] = "/";

buildvfs_kfd kopen4loadfrommod(const char *fileName, char searchfirst)
{
    buildvfs_kfd kFile = buildvfs_kfd_invalid;

    if (g_modDir[0] != '/' || g_modDir[1] != 0)
    {
        static char staticFileName[BMAX_PATH];
        Bsnprintf(staticFileName, sizeof(staticFileName), "%s/%s", g_modDir, fileName);
        kFile = kopen4load(staticFileName, searchfirst);
    }

    return (kFile == buildvfs_kfd_invalid) ? kopen4load(fileName, searchfirst) : kFile;
}

struct grpfile_t const *g_selectedGrp;

int32_t g_gameType = GAMEFLAG_POWERSLAVE;

// g_gameNamePtr can point to one of: grpfiles[].name (string literal), string
// literal, malloc'd block (XXX: possible leak)
const char *g_gameNamePtr = NULL;

// grp handling

static const char *defaultgamegrp = "STUFF.DAT";
static const char *defaultdeffilename = "exhumed.def";

// g_grpNamePtr can ONLY point to a malloc'd block (length BMAX_PATH)
char *g_grpNamePtr = NULL;

void clearGrpNamePtr(void)
{
    Xfree(g_grpNamePtr);
    // g_grpNamePtr assumed to be assigned to right after
}

const char *G_DefaultGrpFile(void)
{
    return defaultgamegrp;
}
const char *G_DefaultDefFile(void)
{
    return defaultdeffilename;
}

const char *G_GrpFile(void)
{
    return (g_grpNamePtr == NULL) ? G_DefaultGrpFile() : g_grpNamePtr;
}

const char *G_DefFile(void)
{
    return (g_defNamePtr == NULL) ? G_DefaultDefFile() : g_defNamePtr;
}

int32_t g_commandSetup = 0;
int32_t g_noSetup = 0;
int32_t g_noAutoLoad = 0;
int g_useCwd;
int32_t g_groupFileHandle;

void G_ExtPreInit(int32_t argc,char const * const * argv)
{
    g_useCwd = G_CheckCmdSwitch(argc, argv, "-usecwd");

#ifdef _WIN32
    GetModuleFileName(NULL,g_rootDir,BMAX_PATH);
    Bcorrectfilename(g_rootDir,1);
    //buildvfs_chdir(g_rootDir);
#else
    buildvfs_getcwd(g_rootDir,BMAX_PATH);
    strcat(g_rootDir,"/");
#endif
}

void G_ExtInit(void)
{
    char cwd[BMAX_PATH];

#ifdef EDUKE32_OSX
    char *appdir = Bgetappdir();
    addsearchpath(appdir);
    Xfree(appdir);
#endif

#ifdef USE_PHYSFS
    strncpy(cwd, PHYSFS_getBaseDir(), ARRAY_SIZE(cwd));
    cwd[ARRAY_SIZE(cwd)-1] = '\0';
#else
    if (buildvfs_getcwd(cwd, ARRAY_SIZE(cwd)) && Bstrcmp(cwd, "/") != 0)
#endif
        addsearchpath(cwd);

    if (CommandPaths)
    {
        int32_t i;
        struct strllist *s;
        while (CommandPaths)
        {
            s = CommandPaths->next;
            i = addsearchpath(CommandPaths->str);
            if (i < 0)
            {
                initprintf("Failed adding %s for game data: %s\n", CommandPaths->str,
                           i==-1 ? "not a directory" : "no such directory");
            }

            Xfree(CommandPaths->str);
            Xfree(CommandPaths);
            CommandPaths = s;
        }
    }

#if defined(_WIN32) && !defined(EDUKE32_STANDALONE)
    if (buildvfs_exists("user_profiles_enabled"))
#else
    if (g_useCwd == 0 && !buildvfs_exists("user_profiles_disabled"))
#endif
    {
        char *homedir;
        int32_t asperr;

        if ((homedir = Bgethomedir()))
        {
            Bsnprintf(cwd, ARRAY_SIZE(cwd), "%s/"
#if defined(_WIN32)
                      APPNAME
#elif defined(GEKKO)
                      "apps/" APPBASENAME
#else
                      ".config/" APPBASENAME
#endif
                      ,homedir);
            asperr = addsearchpath(cwd);
            if (asperr == -2)
            {
                if (buildvfs_mkdir(cwd,S_IRWXU) == 0) asperr = addsearchpath(cwd);
                else asperr = -1;
            }
            if (asperr == 0)
                buildvfs_chdir(cwd);
            Xfree(homedir);
        }
    }
}

void G_ScanGroups(void)
{
    ScanGroups();

    g_selectedGrp = NULL;

    char const * const currentGrp = G_GrpFile();

    for (grpfile_t const *fg = foundgrps; fg; fg=fg->next)
    {
        if (!Bstrcasecmp(fg->filename, currentGrp))
        {
            g_selectedGrp = fg;
            break;
        }
    }

    if (g_selectedGrp == NULL)
        g_selectedGrp = foundgrps;
}

static int32_t G_TryLoadingGrp(char const * const grpfile)
{
    int32_t i;

    if ((i = initgroupfile(grpfile)) == -1)
        initprintf("Warning: could not find main data file \"%s\"!\n", grpfile);
    else
        initprintf("Using \"%s\" as main game data file.\n", grpfile);

    return i;
}

static int32_t G_LoadGrpDependencyChain(grpfile_t const * const grp)
{
    if (!grp)
        return -1;

    if (grp->type->dependency && grp->type->dependency != grp->type->crcval)
        G_LoadGrpDependencyChain(FindGroup(grp->type->dependency));

    int32_t const i = G_TryLoadingGrp(grp->filename);

    return i;
}

void G_LoadGroups(int32_t autoload)
{
    if (g_modDir[0] != '/')
    {
        char cwd[BMAX_PATH];

        Bstrcat(g_rootDir, g_modDir);
        addsearchpath(g_rootDir);
        //        addsearchpath(mod_dir);

        char path[BMAX_PATH];

        if (buildvfs_getcwd(cwd, BMAX_PATH))
        {
            Bsnprintf(path, sizeof(path), "%s/%s", cwd, g_modDir);
            if (!Bstrcmp(g_rootDir, path))
            {
                if (addsearchpath(path) == -2)
                    if (buildvfs_mkdir(path, S_IRWXU) == 0)
                        addsearchpath(path);
            }
        }

#ifdef USE_OPENGL
        Bsnprintf(path, sizeof(path), "%s/%s", g_modDir, TEXCACHEFILE);
        Bstrcpy(TEXCACHEFILE, path);
#endif
    }

    const char *grpfile;
    int32_t i;

    if ((i = G_LoadGrpDependencyChain(g_selectedGrp)) != -1)
    {
        grpfile = g_selectedGrp->filename;

        clearGrpNamePtr();
        g_grpNamePtr = dup_filename(grpfile);

        grpinfo_t const * const type = g_selectedGrp->type;

        g_gameType = type->game;
        g_gameNamePtr = type->name;

        if (type->defname && g_defNamePtr == NULL)
            g_defNamePtr = dup_filename(type->defname);
    }
    else
    {
        grpfile = G_GrpFile();
        i = G_TryLoadingGrp(grpfile);
    }

    if (autoload)
    {
        G_LoadGroupsInDir("autoload");

        if (i != -1)
            G_DoAutoload(grpfile);
    }

    if (g_modDir[0] != '/')
        G_LoadGroupsInDir(g_modDir);

    loaddefinitions_game(G_DefFile(), TRUE);

    struct strllist *s;

    int const bakpathsearchmode = pathsearchmode;
    pathsearchmode = 1;

    while (CommandGrps)
    {
        int32_t j;

        s = CommandGrps->next;

        if ((j = initgroupfile(CommandGrps->str)) == -1)
            initprintf("Could not find file \"%s\".\n", CommandGrps->str);
        else
        {
            g_groupFileHandle = j;
            initprintf("Using file \"%s\" as game data.\n", CommandGrps->str);
            if (autoload)
                G_DoAutoload(CommandGrps->str);
        }

        Xfree(CommandGrps->str);
        Xfree(CommandGrps);
        CommandGrps = s;
    }
    pathsearchmode = bakpathsearchmode;
}

//////////

struct strllist *CommandPaths, *CommandGrps;

void G_AddGroup(const char *buffer)
{
    char buf[BMAX_PATH];

    struct strllist *s = (struct strllist *)Xcalloc(1,sizeof(struct strllist));

    Bstrcpy(buf, buffer);

    if (Bstrchr(buf,'.') == 0)
        Bstrcat(buf,".grp");

    s->str = Xstrdup(buf);

    if (CommandGrps)
    {
        struct strllist *t;
        for (t = CommandGrps; t->next; t=t->next) ;
        t->next = s;
        return;
    }
    CommandGrps = s;
}

void G_AddPath(const char *buffer)
{
    struct strllist *s = (struct strllist *)Xcalloc(1,sizeof(struct strllist));
    s->str = Xstrdup(buffer);

    if (CommandPaths)
    {
        struct strllist *t;
        for (t = CommandPaths; t->next; t=t->next) ;
        t->next = s;
        return;
    }
    CommandPaths = s;
}

//////////

// loads all group (grp, zip, pk3/4) files in the given directory
void G_LoadGroupsInDir(const char *dirname)
{
    static const char *extensions[] = { "*.grp", "*.zip", "*.ssi", "*.pk3", "*.pk4" };
    char buf[BMAX_PATH];
    fnlist_t fnlist = FNLIST_INITIALIZER;

    for (auto & extension : extensions)
    {
        CACHE1D_FIND_REC *rec;

        fnlist_getnames(&fnlist, dirname, extension, -1, 0);

        for (rec=fnlist.findfiles; rec; rec=rec->next)
        {
            Bsnprintf(buf, sizeof(buf), "%s/%s", dirname, rec->name);
            initprintf("Using group file \"%s\".\n", buf);
            initgroupfile(buf);
        }

        fnlist_clearnames(&fnlist);
    }
}

void G_DoAutoload(const char *dirname)
{
    char buf[BMAX_PATH];

    Bsnprintf(buf, sizeof(buf), "autoload/%s", dirname);
    G_LoadGroupsInDir(buf);
}

//////////

enum gametokens
{
    T_INCLUDE = 0,
    T_INTERFACE = 0,
    T_LOADGRP = 1,
    T_MODE = 1,
    T_CACHESIZE = 2,
    T_ALLOW = 2,
    T_NOAUTOLOAD,
    T_INCLUDEDEFAULT,
    T_MUSIC,
    T_SOUND,
    T_FILE,
    T_CUTSCENE,
    T_ANIMSOUNDS,
    T_NOFLOORPALRANGE,
    T_ID,
    T_MINPITCH,
    T_MAXPITCH,
    T_PRIORITY,
    T_TYPE,
    T_DISTANCE,
    T_VOLUME,
    T_DELAY,
    T_RENAMEFILE,
    T_GLOBALGAMEFLAGS,
    T_ASPECT,
    T_FORCEFILTER,
    T_FORCENOFILTER,
    T_TEXTUREFILTER,
    T_NEWGAMECHOICES,
    T_CHOICE,
    T_NAME,
    T_LOCKED,
    T_HIDDEN,
    T_USERCONTENT,
};

int exhumed_globalflags;

static int parsedefinitions_game(scriptfile *, int);

static void parsedefinitions_game_include(const char *fileName, scriptfile *pScript, const char *cmdtokptr, int const firstPass)
{
    scriptfile *included = scriptfile_fromfile(fileName);

    if (!included)
    {
        if (!Bstrcasecmp(cmdtokptr,"null") || pScript == NULL) // this is a bit overboard to prevent unused parameter warnings
            {
           // initprintf("Warning: Failed including %s as module\n", fn);
            }
/*
        else
            {
            initprintf("Warning: Failed including %s on line %s:%d\n",
                       fn, script->filename,scriptfile_getlinum(script,cmdtokptr));
            }
*/
    }
    else
    {
        parsedefinitions_game(included, firstPass);
        scriptfile_close(included);
    }
}

static int parsedefinitions_game(scriptfile *pScript, int firstPass)
{
    int   token;
    char *pToken;

    static const tokenlist tokens[] =
    {
        { "include",         T_INCLUDE          },
        { "#include",        T_INCLUDE          },
        { "includedefault",  T_INCLUDEDEFAULT   },
        { "#includedefault", T_INCLUDEDEFAULT   },
        { "loadgrp",         T_LOADGRP          },
        { "cachesize",       T_CACHESIZE        },
        { "noautoload",      T_NOAUTOLOAD       },
        { "renamefile",      T_RENAMEFILE       },
        { "globalgameflags", T_GLOBALGAMEFLAGS  },
    };

    do
    {
        token  = getatoken(pScript, tokens, ARRAY_SIZE(tokens));
        pToken = pScript->ltextptr;

        switch (token)
        {
        case T_LOADGRP:
        {
            char *fileName;

            pathsearchmode = 1;
            if (!scriptfile_getstring(pScript,&fileName) && firstPass)
            {
                if (initgroupfile(fileName) == -1)
                    initprintf("Could not find file \"%s\".\n", fileName);
                else
                {
                    initprintf("Using file \"%s\" as game data.\n", fileName);
                    if (!g_noAutoLoad && !gSetup.noautoload)
                        G_DoAutoload(fileName);
                }
            }

            pathsearchmode = 0;
        }
        break;
        case T_CACHESIZE:
        {
            int32_t cacheSize;

            if (scriptfile_getnumber(pScript, &cacheSize) || !firstPass)
                break;

            if (cacheSize > 0)
                MAXCACHE1DSIZE = cacheSize << 10;
        }
        break;
        case T_INCLUDE:
        {
            char *fileName;

            if (!scriptfile_getstring(pScript, &fileName))
                parsedefinitions_game_include(fileName, pScript, pToken, firstPass);

            break;
        }
        case T_INCLUDEDEFAULT:
        {
            parsedefinitions_game_include(G_DefaultDefFile(), pScript, pToken, firstPass);
            break;
        }
        case T_NOAUTOLOAD:
            if (firstPass)
                g_noAutoLoad = 1;
            break;
        case T_GLOBALGAMEFLAGS: scriptfile_getnumber(pScript, &exhumed_globalflags); break;
        case T_EOF: return 0;
        default: break;
        }
    }
    while (1);

    return 0;
}

int loaddefinitions_game(const char *fileName, int32_t firstPass)
{
    scriptfile *pScript = scriptfile_fromfile(fileName);

    if (pScript)
        parsedefinitions_game(pScript, firstPass);

    for (char const * m : g_defModules)
        parsedefinitions_game_include(m, NULL, "null", firstPass);

    if (pScript)
        scriptfile_close(pScript);

    scriptfile_clearsymbols();

    return 0;
}

////////

#define kSpiritX = 106;
#define kSpiritY = 97;

short cPupData[300];
//int worktile[97 * 106] = { 0 };
uint8_t worktile[(97*2) * (106*2)] = { 0 };
int lHeadStartClock;
short *pPupData;
int lNextStateChange;
int nPixels;
int nHeadTimeStart;
short curx[97 * 106];
short cury[97 * 106];
int8_t destvelx[97 * 106];
int8_t destvely[97 * 106];
uint8_t pixelval[97 * 106];
int8_t origy[97 * 106];
int8_t origx[97 * 106];
int8_t velx[97 * 106];
int8_t vely[97 * 106];
short nMouthTile;

short nPupData = 0;
int headfd = -1;

short word_964E8 = 0;
short word_964EA = 0;
short word_964EC = 10;

short nSpiritRepeatX;
short nSpiritRepeatY;
short nPixelsToShow;

void CopyTileToBitmap(short nSrcTile, short nDestTile, int xPos, int yPos);
void DoTitle();

// void TestSaveLoad();
void EraseScreen(int nVal);
void LoadStatus();
int FindGString(const char *str);
void MySetView(int x1, int y1, int x2, int y2);
void mysetbrightness(char al);
void FadeIn();

char sHollyStr[40];

short nFontFirstChar;
short nBackgroundPic;
short nShadowPic;

short nCreaturesLeft = 0;
short bNoSound = kFalse;

short nFreeze;
short bFullScreen;

short nSnakeCam = -1;

short nBestLevel;
short nSpiritSprite;

short nLocalSpr;
short levelnew = 1;

int nNetPlayerCount = 0;

short nClockVal;
short fps;
short nRedTicks;
short lastlevel;
volatile short bInMove;
short nAlarmTicks;
short nButtonColor;
short nEnergyChan;


short bSerialPlay = kFalse;
short bModemPlay = kFalse;
int lCountDown = 0;
short nEnergyTowers = 0;


short nHeadStage;

short nCfgNetPlayers = 0;
FILE *vcrfp = NULL;
short nTalkTime = 0;

short forcelevel = -1;

int lLocalButtons = 0;
int lLocalCodes = 0;

short bHiRes = kFalse;
short bCoordinates = kFalse;

short bNoCDCheck = kFalse;
int nNetTime = -1;

short nCodeMin = 0;
short nCodeMax = 0;
short nCodeIndex = 0;

short levelnum = -1;
//short nScreenWidth = 320;
//short nScreenHeight = 200;
int moveframes;
int flash;
int localclock;
int totalmoves;

short nCurBodyNum = 0;

short nBodyTotal = 0;


short textpages;

short nCDTrackLength = 0;

short lastfps;

short nCDTracks = 0;

short nMapMode = 0;
short bNoCreatures = kFalse;

short nTotalPlayers = 1;
// TODO: Rename this (or make it static) so it doesn't conflict with library function
//short socket = 0;

short nFirstPassword = 0;
short nFirstPassInfo = 0;
short nPasswordCount = 0;

short word_964B0 = 0;

short word_9AC30 = 0;

short word_96E3C = 0;
short word_96E3E = -1;
short word_96E40 = 0;

short nGamma = 0;

short word_CB326;

short screensize;

short bSnakeCam = kFalse;
short bRecord = kFalse;
short bPlayback = kFalse;
short bPause = kFalse;
short bInDemo = kFalse;
short bSlipMode = kFalse;
short bDoFlashes = kTrue;
short bHolly = kFalse;

short nItemTextIndex;

short scan_char = 0;

int nStartLevel;
int nTimeLimit;

int bVanilla = 0;

char debugBuffer[256];

short wConsoleNode; // TODO - move me into network file

int mouseaiming, aimmode, mouseflip;
int runkey_mode, auto_run;

ClockTicks tclocks, tclocks2;

void DebugOut(const char *fmt, ...)
{
#ifdef _DEBUG
    va_list args;
    va_start(args, fmt);

    debugBuffer[0] = '\0';

    vsprintf(debugBuffer, fmt, args);

    initprintf("%s", debugBuffer);
    fflush(stdout);

    va_end(args);
#endif
}

void ShutDown(void)
{
    CONFIG_WriteSetup(0);
    StopCD();
    if (bSerialPlay)
    {
        if (bModemPlay) {
            HangUp();
        }
        UnInitSerial();
    }

    KB_Shutdown();
    RemoveEngine();
    UnInitNet();
    UnInitFX();
}

void bail2dos(const char *fmt, ...)
{
    char buf[256];

#ifdef __WATCOMC__
    setvmode(3);
#endif

    initprintf("bailed to dos\n");

    va_list args;
    va_start(args, fmt);

    vsprintf(buf, fmt, args);

    va_end(args);

    initprintf(buf);

    if (*buf != 0)
    {
        if (!(buf[0] == ' ' && buf[1] == 0))
        {
            char titlebuf[256];
            Bsprintf(titlebuf,APPNAME " %s",s_buildRev);
            wm_msgbox(titlebuf, "%s", buf);
        }
    }

    exit(0);
}

void faketimerhandler()
{
    if ((totalclock < ototalclock + 1) || bInMove)
        return;
    ototalclock = ototalclock + 1;

    if (!((int)ototalclock&3) && moveframes < 4)
        moveframes++;

    PlayerInterruptKeys();
}

void timerhandler()
{
    scan_char++;
    if (scan_char == kTimerTicks)
    {
        scan_char = 0;
        lastfps = fps;
        fps = 0;

        if (nCDTrackLength > 0) {
            nCDTrackLength--;
        }
    }
}

void HandleAsync()
{
    handleevents();
    if (!bInMove)
        OSD_DispatchQueued();
}

int MyGetStringWidth(const char *str)
{
    int nLen = strlen(str);

    int nWidth = 0;

    for (int i = 0; i < nLen; i++)
    {
        int nPic = seq_GetSeqPicnum(kSeqFont2, 0, str[i] - 32);
        nWidth += tilesiz[nPic].x + 1;
    }

    return nWidth;
}

void UpdateScreenSize()
{
    int xsize = xdim - scale(screensize*16, xdim, 320);
    int ysize = scale(ydim, xsize, xdim);
    int y1 = ((ydim >> 1) - (ysize >> 1));

    MySetView(
        (xdim >> 1) - (xsize >> 1),
        y1,
        (xdim >> 1) - (xsize >> 1) + xsize - 1,
        (y1 + ysize - 1));

    RefreshStatus();
}

void ResetPassword()
{
    nCodeMin = nFirstPassword;
    nCodeIndex = 0;

    nCodeMax = (nFirstPassword + nPasswordCount) - 1;
}

void DoPassword(int nPassword)
{
    if (nNetPlayerCount) {
        return;
    }

    const char *str = gString[nFirstPassInfo + nPassword];

    if (str[0] != '\0') {
        StatusMessage(750, str);
    }

    switch (nPassword)
    {
        case 0:
        {
            if (!nNetPlayerCount) {
                bHolly = kTrue;
            }
            break;
        }

        case 2: // LOBOCOP
        {
            lLocalCodes |= 0x20;
            break;
        }

        case 3: // LOBODEITY
        {
            lLocalCodes |= 0x40;
            break;
        }

        case 4:
        {
            if (bDoFlashes == kFalse) {
                bDoFlashes = kTrue;
            }
            else {
                bDoFlashes = kFalse;
            }
            break;
        }

        case 5:
        {
            lLocalCodes |= 0x80;
            break;
        }

        case 6:
        {
            if (!nNetPlayerCount)
            {
                if (bSlipMode == kFalse)
                {
                    bSlipMode = kTrue;
                    StatusMessage(300, "Slip mode %s", "ON");
                }
                else {
                    bSlipMode = kFalse;
                    StatusMessage(300, "Slip mode %s", "OFF");
                }
            }
            break;
        }

        case 7:
        {
            if (!nNetPlayerCount)
            {
                if (bSnakeCam == kFalse) {
                    bSnakeCam = kTrue;
                }
                else {
                    bSnakeCam = kFalse;
                }
            }
            break;
        }

        case 8:
        {
            GrabMap();
            bShowTowers = kTrue;
            break;
        }

        case 9:
        {
            lLocalCodes |= 0x100; // LOBOSWAG?
            break;
        }

        case 10:
        {
            if (bCoordinates == kFalse) {
                bCoordinates = kTrue;
            }
            else {
                bCoordinates = kFalse;
            }
            break;
        }

        default:
            return;
    }
}

void mysetbrightness(char nBrightness)
{
    g_visibility = 2048 - (nBrightness << 9);
}

void CheckKeys()
{
    int eax;

    if (BUTTON(gamefunc_Enlarge_Screen))
    {
        if (screensize == 0)
        {
            if (!bFullScreen)
            {
                bFullScreen = kTrue;
                UnMaskStatus();
            }
        }
        else
        {
            screensize--;
            if (screensize < 0) {
                screensize = 0;
            }

            UpdateScreenSize();
        }
        CONTROL_ClearButton(gamefunc_Enlarge_Screen);
    }

    // if (BUTTON(gamefunc_Mouse_Sensitivity_Up))
    // {
    //     if (lMouseSens < 64)
    //         lMouseSens++;
    //
    //     CONTROL_ClearButton(gamefunc_Mouse_Sensitivity_Up);
    //     StatusMessage(500, "MOUSE SENSITIVITY SET TO %d", lMouseSens);
    // }
    // else
    // {
    //     if (BUTTON(gamefunc_Mouse_Sensitivity_Down))
    //     {
    //         if (lMouseSens >= 1)
    //             lMouseSens -= 1;
    //
    //         CONTROL_ClearButton(gamefunc_Mouse_Sensitivity_Down);
    //         StatusMessage(500, "MOUSE SENSITIVITY SET TO %d", lMouseSens);
    //     }
    // }

    // F11?
    if (BUTTON(gamefunc_Gamma_Correction))
    {
        nGamma++;

        if (nGamma > 4)
            nGamma = 0;

        mysetbrightness((uint8_t)nGamma);
        CONTROL_ClearButton(gamefunc_Gamma_Correction);
    }

    if (BUTTON(gamefunc_Shrink_Screen))
    {
        if (bFullScreen)
        {
            bFullScreen = kFalse;
        }
        else
        {
            if ((screensize + 1) < 15)
                screensize++;
        }

        UpdateScreenSize();
        CONTROL_ClearButton(gamefunc_Shrink_Screen);
    }

    // print version string?
    if (KB_KeyDown[sc_V] && KB_KeyDown[sc_LeftAlt])
    {
        KB_KeyDown[sc_V] = 0;
        StatusMessage(300, versionstr);
        return;
    }

    // go to 3rd person view?
    if (KB_KeyDown[sc_C] && KB_KeyDown[sc_LeftAlt])
    {
        if (!nFreeze)
        {
            if (bCamera) {
                bCamera = kFalse;
            }
            else {
                bCamera = kTrue;
            }

            if (bCamera)
                GrabPalette();
        }
        KB_KeyDown[sc_C] = 0;
        return;
    }

    if (KB_KeyDown[sc_Pause])
    {
        if (!nNetPlayerCount)
        {
            if (bPause)
            {
                ototalclock = totalclock = tclocks;
                bPause = kFalse;
            }
            else
            {
                bPause = kTrue;
                // NoClip();
                // int nLen = MyGetStringWidth("PAUSED");
                // myprintext((320 - nLen) / 2, 100, "PAUSED", 0);
                // Clip();
                // videoNextPage();
            }
            KB_KeyDown[sc_Pause] = 0;
        }
        return;
    }

    // Handle cheat codes
    if (!bInDemo && KB_KeyWaiting())
    {
        char ch = KB_GetCh();

        if (bHolly)
        {
            if (ch)
            {
                int nStringLen = strlen(sHollyStr);

                if (ch == asc_Enter)
                {
                    char *pToken = strtok(sHollyStr, " ");

                    if (nStringLen == 0) // bjd - added this check. watcom allows passing NULL to strcmp so the below checks will all fail OK on DOS but will cause a crash on Windows
                    {
                        bHolly = kFalse;
                        StatusMessage(1, " ");
                    }
                    else if (!strcmp(pToken, "GOTO"))
                    {
                        // move player to X, Y coordinates
                        int nSprite = PlayerList[0].nSprite;

                        pToken = strtok(NULL, ",");
                        sprite[nSprite].x = atoi(pToken);
                        pToken = strtok(NULL, ",");
                        sprite[nSprite].y = atoi(pToken);

                        setsprite(nSprite, &sprite[nSprite].pos);
                        sprite[nSprite].z = sector[sprite[nSprite].sectnum].floorz;
                    }
                    else if (!strcmp(pToken, "LEVEL"))
                    {
                        pToken = strtok(NULL, " ");
                        levelnew = atoi(pToken);
                    }
                    else if (!strcmp(pToken, "DOORS"))
                    {
                        for (int i = 0; i < kMaxChannels; i++)
                        {
                            // CHECKME - does this toggle?
                            if (sRunChannels[i].c == 0) {
                                runlist_ChangeChannel(i, 1);
                            }
                            else {
                                runlist_ChangeChannel(i, 0);
                            }
                        }
                    }
                    else if (!strcmp(pToken, "EXIT"))
                    {
                        FinishLevel();
                    }
                    else if (!strcmp(pToken, "CREATURE"))
                    {
                        // i = nNetPlayerCount;
                        if (!nNetPlayerCount)
                        {
                            pToken = strtok(NULL, " ");
                            switch (atoi(pToken))
                            {
                                // TODO - enums?
                                case 0:
                                    BuildAnubis(-1, initx, inity, sector[initsect].floorz, initsect, inita, kFalse);
                                    break;
                                case 1:
                                    BuildSpider(-1, initx, inity, sector[initsect].floorz, initsect, inita);
                                    break;
                                case 2:
                                    BuildMummy(-1, initx, inity, sector[initsect].floorz, initsect, inita);
                                    break;
                                case 3:
                                    BuildFish(-1, initx, inity, initz + eyelevel[nLocalPlayer], initsect, inita);
                                    break;
                                case 4:
                                    BuildLion(-1, initx, inity, sector[initsect].floorz, initsect, inita);
                                    break;
                                case 5:
                                    BuildLava(-1, initx, inity, sector[initsect].floorz, initsect, inita, nNetPlayerCount);
                                    break;
                                case 6:
                                    BuildRex(-1, initx, inity, sector[initsect].floorz, initsect, inita, nNetPlayerCount);
                                    break;
                                case 7:
                                    BuildSet(-1, initx, inity, sector[initsect].floorz, initsect, inita, nNetPlayerCount);
                                    break;
                                case 8:
                                    BuildQueen(-1, initx, inity, sector[initsect].floorz, initsect, inita, nNetPlayerCount);
                                    break;
                                case 9:
                                    BuildRoach(0, -1, initx, inity, sector[initsect].floorz, initsect, inita);
                                    break;
                                case 10:
                                    BuildRoach(1, -1, initx, inity, sector[initsect].floorz, initsect, inita);
                                    break;
                                case 11:
                                    BuildWasp(-1, initx, inity, sector[initsect].floorz - 25600, initsect, inita);
                                    break;
                                case 12:
                                    BuildScorp(-1, initx, inity, sector[initsect].floorz, initsect, inita, nNetPlayerCount);
                                    break;
                                case 13:
                                    BuildRat(-1, initx, inity, sector[initsect].floorz, initsect, inita);
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                    else
                    {
                        if (nStringLen == 0)
                        {
                            bHolly = kFalse;
                            StatusMessage(1, " ");
                        }
                        else
                        {
                            for (int i = 0; i < nPasswordCount; ++i)
                            {
                                if (!strcmp(sHollyStr, gString[i + nFirstPassword]))
                                {
                                    DoPassword(i);
                                    break;
                                }
                            }
                        }
                    }
                    sHollyStr[0] = '\0';
                }
                else if (ch == asc_BackSpace)
                {
                    if (nStringLen != 0) {
                        sHollyStr[nStringLen - 1] = '\0';
                    }
                }
                else if (nStringLen < (sizeof(sHollyStr) - 1)) // do we have room to add a char and null terminator?
                {
                    sHollyStr[nStringLen] = toupper(ch);
                    sHollyStr[nStringLen + 1] = '\0';
                }
            }
            else
            {
                KB_GetCh();
            }
        }

        if (isalpha(ch))
        {
            ch = toupper(ch);

            int ecx = nCodeMin;

            int ebx = nCodeMin;
            int edx = nCodeMin - 1;

            while (ebx <= nCodeMax)
            {
                if (ch == gString[ecx][nCodeIndex])
                {
                    nCodeMin = ebx;
                    nCodeIndex++;

                    if (gString[ecx][nCodeIndex] == 0)
                    {
                        ebx -= nFirstPassword;

                        DoPassword(ebx);
                        ResetPassword();
                    }

                    break;
                }
                else if (gString[ecx][nCodeIndex] < ch)
                {
                    nCodeMin = ebx + 1;
                }
                else if (gString[ecx][nCodeIndex] > ch)
                {
                    nCodeMax = edx;
                }

                ecx++;
                edx++;
                ebx++;
            }

            if (nCodeMin > nCodeMax) {
                ResetPassword();
            }
        }
    }
}

void DoCredits()
{
    NoClip();

    playCDtrack(19);

    int var_20 = 0;

    FadeOut(0);

    int nCreditsIndex = FindGString("CREDITS");

    while (strcmp(gString[nCreditsIndex], "END") != 0)
    {
        EraseScreen(overscanindex);

        int nStart = nCreditsIndex;

        // skip blanks
        while (strlen(gString[nCreditsIndex]) != 0) {
            nCreditsIndex++;
        }

        // vars
        int eax = (10 * (nCreditsIndex - nStart - 1)) / 2;

        if (eax < 0) {
            eax++;
        }

        eax >>= 1;

        int y = 100 - eax;

        int edi = nStart;


        for (int i = nStart; i < nCreditsIndex; i++)
        {
            // var 24 ==

            int nWidth = MyGetStringWidth(gString[edi]);
            myprintext((320 - nWidth) / 2, y, gString[edi], 0);

            edi++;
            y += 10;
        }

        videoNextPage();
        FadeIn();

        while ((int)totalclock + 600 > (int)totalclock)
        {
            if (KB_KeyDown[sc_F12])
            {
                var_20++;

                KB_KeyDown[sc_F12] = 0;

                if (var_20 > 5) {
                    return;
                }
            }
        }

        FadeOut(0);
    }

    while (CDplaying())
    {
        if (KB_KeyWaiting()) {
            KB_GetCh();
        }
    }

    Clip();
}

void FinishLevel()
{
    if (levelnum > nBestLevel) {
        nBestLevel = levelnum - 1;
    }

    levelnew = levelnum + 1;

    StopAllSounds();

    bCamera = kFalse;
    nMapMode = 0;

    if (levelnum != kMap20)
    {
        EraseScreen(4);
        SetLocalChan(1);
        PlayLocalSound(StaticSound[59], 0);
        videoNextPage();
        WaitTicks(12);
        WaitVBL();
        RefreshBackground();
        RefreshStatus();
        DrawView(65536);
        videoNextPage();
    }

    FadeOut(1);
    EraseScreen(overscanindex);

    if (levelnum == 0)
    {
        nPlayerLives[0] = 0;
        levelnew = 100;
    }
    else
    {
        DoAfterCinemaScene(levelnum);
        if (levelnum == kMap20)
        {
            DoCredits();
            nPlayerLives[0] = 0;
        }
    }
}

void WritePlaybackInputs()
{
    fwrite(&moveframes, sizeof(moveframes), 1, vcrfp);
    fwrite(&sPlayerInput[nLocalPlayer], sizeof(PlayerInput), 1, vcrfp);
}

uint8_t ReadPlaybackInputs()
{
    assert(sizeof(PlayerInput) == 32);

    if (fread(&moveframes, 1, sizeof(moveframes), vcrfp))
    {
#if 0
        fread(&sPlayerInput[nLocalPlayer], 1, sizeof(PlayerInput), vcrfp);
#else
        /*
        struct PlayerInput
        {
            int xVel;
            int yVel;
            short nAngle;
            short buttons;
            short nTarget;
            char horizon;
            int8_t nItem;
            int h;
            char i;
            char field_15[11];
        };
        */
        fread(&sPlayerInput[nLocalPlayer].xVel,    1, sizeof(sPlayerInput[nLocalPlayer].xVel), vcrfp);
        fread(&sPlayerInput[nLocalPlayer].yVel,    1, sizeof(sPlayerInput[nLocalPlayer].yVel), vcrfp);
        fread(&sPlayerInput[nLocalPlayer].nAngle,  1, sizeof(sPlayerInput[nLocalPlayer].nAngle), vcrfp);
        fread(&sPlayerInput[nLocalPlayer].buttons, 1, sizeof(sPlayerInput[nLocalPlayer].buttons), vcrfp);
        fread(&sPlayerInput[nLocalPlayer].nTarget, 1, sizeof(sPlayerInput[nLocalPlayer].nTarget), vcrfp);
        fread(&sPlayerInput[nLocalPlayer].horizon, 1, sizeof(sPlayerInput[nLocalPlayer].horizon), vcrfp);
        fread(&sPlayerInput[nLocalPlayer].nItem,   1, sizeof(sPlayerInput[nLocalPlayer].nItem), vcrfp);
        fread(&sPlayerInput[nLocalPlayer].h,       1, sizeof(sPlayerInput[nLocalPlayer].h), vcrfp);
        fread(&sPlayerInput[nLocalPlayer].i,       1, sizeof(sPlayerInput[nLocalPlayer].i), vcrfp);

        // skip pad
        fseek(vcrfp, 11, SEEK_CUR);


#endif
        besttarget = sPlayerInput[nLocalPlayer].nTarget;
        Ra[nLocalPlayer].nTarget = besttarget;
        return kTrue;
    }
    else
    {
        fclose(vcrfp);
        vcrfp = NULL;
        bPlayback = kFalse;
        return kFalse;
    }
}

void SetHiRes()
{
    //nScreenWidth  = 640;
    //nScreenHeight = 400;
    bHiRes = kTrue;
}

void DoClockBeep()
{
    for (int i = headspritestat[407]; i != -1; i = nextspritestat[i]) {
        PlayFX2(StaticSound[kSound74], i);
    }
}

void DoRedAlert(int nVal)
{
    if (nVal)
    {
        nAlarmTicks = 69;
        nRedTicks = 30;
    }

    for (int i = headspritestat[405]; i != -1; i = nextspritestat[i])
    {
        if (nVal)
        {
            PlayFXAtXYZ(StaticSound[kSoundAlarm], sprite[i].x, sprite[i].y, sprite[i].z, sprite[i].sectnum);
            AddFlash(sprite[i].sectnum, sprite[i].x, sprite[i].y, sprite[i].z, 192);
        }
    }
}

void LockEnergyTiles()
{
    // old	loadtilelockmode = 1;
    tileLoad(kTile3603);
    tileLoad(kEnergy1);
    tileLoad(kEnergy2);
    // old  loadtilelockmode = 0;
}

void DrawClock()
{
    int ebp = 49;

    tileLoad(kTile3603);

//    nRedTicks = 0;
    memset((void*)waloff[kTile3603], -1, 4096);

    if (lCountDown / 30 != nClockVal)
    {
        nClockVal = lCountDown / 30;
        DoClockBeep();
    }

    int nVal = nClockVal;

    while (nVal)
    {
        int v2 = nVal & 0xF;
        int yPos = 32 - tilesiz[v2 + kTile3606].y / 2;

        CopyTileToBitmap(v2 + kTile3606, kTile3603, ebp - tilesiz[v2 + kTile3606].x / 2, yPos);

        ebp -= 15;

        nVal /= 16;
    }

    DoEnergyTile();
}

void M32RunScript(const char* s) { UNREFERENCED_PARAMETER(s); }
void app_crashhandler(void)
{
    ShutDown();
}

void G_Polymer_UnInit(void) { }

static inline int32_t calc_smoothratio(ClockTicks totalclk, ClockTicks ototalclk)
{
    // if (!((ud.show_help == 0 && (!g_netServer && ud.multimode < 2) && ((g_player[myconnectindex].ps->gm & MODE_MENU) == 0)) ||
    //       (g_netServer || ud.multimode > 1) ||
    //       ud.recstat == 2) ||
    //     ud.pause_on)
    // {
    //     return 65536;
    // }
    if (bRecord || bPlayback || nFreeze != 0 || bCamera || bPause)
        return 65536;
    int32_t rfreq = (refreshfreq != -1 ? refreshfreq : 60);
    uint64_t elapsedFrames = tabledivide64(((uint64_t) (totalclk - ototalclk).toScale16()) * rfreq, 65536*120);
#if 0
    //POGO: additional debug info for testing purposes
    OSD_Printf("Elapsed frames: %" PRIu64 ", smoothratio: %" PRIu64 "\n", elapsedFrames, tabledivide64(65536*elapsedFrames*30, rfreq));
#endif
    return clamp(tabledivide64(65536*elapsedFrames*30, rfreq), 0, 65536);
}

int r_showfps;

#define COLOR_RED redcol
#define COLOR_WHITE whitecol

#define LOW_FPS ((videoGetRenderMode() == REND_CLASSIC) ? 35 : 50)
#define SLOW_FRAME_TIME 20

#if defined GEKKO
# define FPS_YOFFSET 16
#else
# define FPS_YOFFSET 0
#endif

#define FPS_COLOR(x) ((x) ? COLOR_RED : COLOR_WHITE)

static void G_PrintFPS(void)
{
    static char tempbuf[256];
    static int32_t frameCount;
    static double cumulativeFrameDelay;
    static double lastFrameTime;
    static float lastFPS, minFPS = std::numeric_limits<float>::max(), maxFPS;
    static double minGameUpdate = std::numeric_limits<double>::max(), maxGameUpdate;

    double frameTime = timerGetHiTicks();
    double frameDelay = frameTime - lastFrameTime;
    cumulativeFrameDelay += frameDelay;

    if (frameDelay >= 0)
    {
        int32_t x = (xdim <= 640);

        if (r_showfps)
        {
            int32_t chars = Bsprintf(tempbuf, "%.1f ms, %5.1f fps", frameDelay, lastFPS);

            printext256(windowxy2.x-(chars<<(3-x))+1, windowxy1.y+2+FPS_YOFFSET, blackcol, -1, tempbuf, x);
            printext256(windowxy2.x-(chars<<(3-x)), windowxy1.y+1+FPS_YOFFSET,
                FPS_COLOR(lastFPS < LOW_FPS), -1, tempbuf, x);
        }

        if (cumulativeFrameDelay >= 1000.0)
        {
            lastFPS = 1000.f * frameCount / cumulativeFrameDelay;
            // g_frameRate = Blrintf(lastFPS);
            frameCount = 0;
            cumulativeFrameDelay = 0.0;
        }
        frameCount++;
    }
    lastFrameTime = frameTime;
}

static void GameDisplay(void)
{
    // End Section B

    SetView1();

    if (levelnum == kMap20)
    {
        LockEnergyTiles();
        DoEnergyTile();
        DrawClock();
    }

    auto smoothRatio = calc_smoothratio(totalclock, tclocks);

    DrawView(smoothRatio);

    if (bPause)
    {
        int nLen = MyGetStringWidth("PAUSED");
        myprintext((320 - nLen) / 2, 100, "PAUSED", 0);
    }

    G_PrintFPS();

    videoNextPage();
}

static void GameMove(void)
{
    FixPalette();

    if (levelnum == kMap20)
    {
        if (lCountDown <= 0)
        {
            for (int i = 0; i < nTotalPlayers; i++) {
                nPlayerLives[i] = 0;
            }

            DoFailedFinalScene();
            levelnew = 100;

            return;
        }
        // Pink section
        lCountDown--;
        DrawClock();

        if (nRedTicks)
        {
            nRedTicks--;

            if (nRedTicks <= 0) {
                DoRedAlert(0);
            }
        }

        nAlarmTicks--;
        nButtonColor--;

        if (nAlarmTicks <= 0) {
            DoRedAlert(1);
        }
    }

    // YELLOW SECTION
    MoveThings();

    obobangle = bobangle;

    if (totalvel[nLocalPlayer] == 0)
    {
        bobangle = 0;
    }
    else
    {
        bobangle += 56;
        bobangle &= kAngleMask;
    }

    UpdateCreepySounds();

    // loc_120E9:
    totalmoves++;
    moveframes--;
}

#if defined(_WIN32) && defined(DEBUGGINGAIDS)
// See FILENAME_CASE_CHECK in cache1d.c
static int32_t check_filename_casing(void)
{
    return 1;
}
#endif

int32_t r_maxfps = 60;
int32_t r_maxfpsoffset = 0;
double g_frameDelay = 0.0;

int G_FPSLimit(void)
{
    if (!r_maxfps)
        return 1;

    static double   nextPageDelay;
    static uint64_t lastFrameTicks;

    uint64_t const frameTicks   = timerGetTicksU64();
    uint64_t const elapsedTime  = frameTicks - lastFrameTicks;
    double const   dElapsedTime = elapsedTime;

    if (dElapsedTime >= floor(nextPageDelay))
    {
        if (dElapsedTime <= nextPageDelay+g_frameDelay)
            nextPageDelay += g_frameDelay-dElapsedTime;

        lastFrameTicks = frameTicks;

        return 1;
    }

    return 0;
}

static int32_t nonsharedtimer;

int app_main(int argc, char const* const* argv)
{
    char tempbuf[256];
#ifdef _WIN32
#ifndef DEBUGGINGAIDS
    if (!G_CheckCmdSwitch(argc, argv, "-noinstancechecking") && win_checkinstance())
    {
#ifdef EDUKE32_STANDALONE
        if (!wm_ynbox(APPNAME, "It looks like " APPNAME " is already running.\n\n"
#else
        if (!wm_ynbox(APPNAME, "It looks like the game is already running.\n\n"
#endif
                      "Are you sure you want to start another copy?"))
            return 3;
    }
#endif

    backgroundidle = 0;

#ifndef USE_PHYSFS
#ifdef DEBUGGINGAIDS
    extern int32_t (*check_filename_casing_fn)(void);
    check_filename_casing_fn = check_filename_casing;
#endif
#endif
#endif

    G_ExtPreInit(argc, argv);

    OSD_SetLogFile(APPBASENAME ".log");

    OSD_SetFunctions(NULL,
                     NULL,
                     NULL,
                     NULL,
                     NULL,
                     GAME_clearbackground,
                     BGetTime,
                     GAME_onshowosd);

    wm_setapptitle(APPNAME);

    initprintf("Exhumed %s\n", s_buildRev);
    PrintBuildInfo();

    int i;


    //int esi = 1;
    //int edi = esi;
    int doTitle = kTrue; // REVERT kTrue;
    int stopTitle = kFalse;
    levelnew = 1;

    // REVERT - change back to kTrue
//	short bDoTitle = kFalse;

    wConsoleNode = 0;

    int nMenu = 0; // TEMP

    // Check for any command line arguments
    for (i = 1; i < argc; i++)
    {
        const char *pChar = argv[i];

        if (*pChar == '/')
        {
            pChar++;
            //strlwr(pChar);

            if (Bstrcasecmp(pChar, "nocreatures") == 0) {
                bNoCreatures = kTrue;
            }
            else if (Bstrcasecmp(pChar, "nosound") == 0) {
                bNoSound = kTrue;
            }
            else if (Bstrcasecmp(pChar, "record") == 0)
            {
                if (!bPlayback)
                {
                    vcrfp = fopen("data.vcr", "wb+");
                    if (vcrfp != NULL) {
                        bRecord = kTrue;
                    }
                    else {
                        DebugOut("Can't open data file for recording\n");
                    }
                }
            }
            else if (Bstrcasecmp(pChar, "playback") == 0)
            {
                if (!bRecord)
                {
                    vcrfp = fopen("data.vcr", "rb");
                    if (vcrfp != NULL) {
                        bPlayback = kTrue;
                        doTitle = kFalse;
                    }
                    else {
                        DebugOut("Can't open data file 'data.vcr' for reading\n");
                    }
                }
            }
            else if (Bstrncasecmp(pChar, "null", 4) == 0)
            {
                pChar += 4;

                bSerialPlay = kTrue;
                nNetPlayerCount = 1;
                nTotalPlayers = 2;

                doTitle = kFalse;

                char ch = *pChar;

                // bjd - unused/unfished code in original .exe?
                switch (ch - 1)
                {
                    default:
                        break;

                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        break;
                }

                if (forcelevel < 0)
                {
                    forcelevel = levelnew;
                }
            }
            else if (Bstrcasecmp(pChar, "modem") == 0)
            {
                bModemPlay = kTrue;
                bSerialPlay = kTrue;
                nNetPlayerCount = 1;
                nTotalPlayers = 2;

                doTitle = kFalse;

                if (forcelevel < 0) {
                    forcelevel = levelnew;
                }
            }
            else if (Bstrcasecmp(pChar, "network") == 0)
            {
                nNetPlayerCount = -1;
                forcelevel = levelnew;
                bModemPlay = kFalse;
                bSerialPlay = kFalse;

                doTitle = kFalse;
            }
            else if (Bstrcasecmp(pChar, "setup") == 0) {
                g_commandSetup = 1;
            }
            else if (Bstrcasecmp(pChar, "nosetup") == 0) {
                g_noSetup = 1;
                g_commandSetup = 0;
            }
            else
            {
                char c = tolower(*pChar);

                switch (c)
                {
                    case 'h':
                        SetHiRes();
                        break;
#if 0
                    case 's':
                        socket = atoi(pChar + 1);
                        break;
#endif
                    case 't':
                        nNetTime = atoi(pChar + 1);
                        if (nNetTime < 0) {
                            nNetTime = 0;
                        }
                        else {
                            nNetTime = nNetTime * 1800;
                        }
                        break;
                    case 'c':
                    {
                        // CHANGEME? - make this a strcmp. this is how the original does it though...
                        if (pChar[1] == 'd' && pChar[2] == 'o' && pChar[3] == 'f' && pChar[4] == 'f') {
                            bNoCDCheck = kTrue;
                        }

						break;
                    }
                    default:
                    {
                        if (isdigit(c))
                        {
                            levelnew = atoi(pChar);
                            forcelevel = levelnew;

                            doTitle = kFalse;

                            initprintf("Jumping to level %d...\n", levelnew);
                        }
                        break;
                    }
                }
            }
        }
    }

    if (nNetPlayerCount && forcelevel == -1) {
        forcelevel = 1;
    }

    // This needs to happen afterwards, as G_CheckCommandLine() is where we set
    // up the command-line-provided search paths (duh).
    // TODO:
    //G_ExtInit();

#if defined(RENDERTYPEWIN) && defined(USE_OPENGL)
    if (forcegl) initprintf("GL driver blacklist disabled.\n");
#endif

    // used with binds for fast function lookup
    hash_init(&h_gamefuncs);
    for (bssize_t i=kMaxGameFunctions-1; i>=0; i--)
    {
        if (gamefunctions[i][0] == '\0')
            continue;

        hash_add(&h_gamefuncs,gamefunctions[i],i,0);
    }

#ifdef STARTUP_SETUP_WINDOW
    int const readSetup =
#endif
    CONFIG_ReadSetup();

    if (enginePreInit())
    {
        wm_msgbox("Build Engine Initialization Error",
                  "There was a problem initializing the Build engine: %s", engineerrstr);
        ERRprintf("app_main: There was a problem initializing the Build engine: %s\n", engineerrstr);
        Bexit(2);
    }

    if (Bstrcmp(setupfilename, kSetupFilename))
        initprintf("Using config file \"%s\".\n",setupfilename);

    G_ScanGroups();

#ifdef STARTUP_SETUP_WINDOW
    if (readSetup < 0 || (!g_noSetup && gSetup.forcesetup) || g_commandSetup)
    {
        if (quitevent || !startwin_run())
        {
            engineUnInit();
            Bexit(0);
        }
    }
#endif

    G_LoadGroups(!g_noAutoLoad && !gSetup.noautoload);

    // Decrypt strings code would normally be here
#if 0

    for (int i = 0; ; i++)
    {
        int j = i - 1;

        while (j >= 0)
        {
            if (gString_Enc[i] == gString_Enc[j]) {
                break;
            }

            j--;
        }

        if (j < 0)
        {
            int k = 0;

            while (1)
            {
                uint8_t v27 = gString_Enc[i + k];
                if (v27)
                {
                    gString_Enc[i + k] = v27 ^ 0xFF;

                    k++;
                }
                else {
                    break;
                }


            }

//			strupr(gString[j]);

            int blah = 123;
//			if (!strcmp(*(char **)((char *)gString + v29), "EOF", v27, v30))
//				break;
        }
    }
#endif

    // loc_115F5:
    nItemTextIndex = FindGString("ITEMS");
    nFirstPassword = FindGString("PASSWORDS");
    nFirstPassInfo = FindGString("PASSINFO");

    // count the number of passwords available
    for (nPasswordCount = 0; strlen(gString[nFirstPassword+nPasswordCount]) != 0; nPasswordCount++)
    {
    }

    ResetPassword();
    nCDTracks = initcdaudio();

    // GetCurPal(NULL);

    CONFIG_WriteSetup(1);
    CONFIG_ReadSetup();

    initprintf("Initializing OSD...\n");

    Bsprintf(tempbuf, "Exhumed %s", s_buildRev);
    OSD_SetVersion(tempbuf, 10,0);
    OSD_SetParameters(0, 0, 0, 0, 0, 0, OSD_ERROR, OSDTEXT_RED, gamefunctions[gamefunc_Show_Console][0] == '\0' ? OSD_PROTECTED : 0);
    registerosdcommands();

    SetupInput();

    char *const setupFileName = Xstrdup(setupfilename);
    char *const p = strtok(setupFileName, ".");

    if (!p || !Bstrcmp(setupfilename, kSetupFilename))
        Bsprintf(tempbuf, "settings.cfg");
    else
        Bsprintf(tempbuf, "%s_settings.cfg", p);

    Xfree(setupFileName);

    OSD_Exec(tempbuf);
    OSD_Exec("autoexec.cfg");

    CONFIG_SetDefaultKeys(keydefaults, true);

    system_getcvars();

    if (nNetPlayerCount == -1)
    {
        nNetPlayerCount = nCfgNetPlayers - 1;
        nTotalPlayers += nNetPlayerCount;
    }

    // loc_116A5:

#if 0
    if (nNetPlayerCount)
    {
        InitInput();
        forcelevel = nStartLevel;
        nNetTime = 1800 * nTimeLimit;

        if (nNetTime == 0) {
            nNetTime = -1;
        }

        int nWaitTicks = 0;

        if (!bSerialPlay)
        {
            if (InitNet(socket, nTotalPlayers))
            {
                DebugOut("Found network players!\n");
                nWaitTicks = 30;
            }
            else
            {
                AbortNetworkPlay();
                DebugOut("Network play aborted\n");
                initprintf("Network play aborted\n");
                nWaitTicks = 60;
            }

            WaitTicks(nWaitTicks);
        }
    }
#endif

    // temp - moving InstallEngine(); before FadeOut as we use nextpage() in FadeOut
    InstallEngine();

    const char *defsfile = G_DefFile();
    uint32_t stime = timerGetTicks();
    if (!loaddefinitionsfile(defsfile))
    {
        uint32_t etime = timerGetTicks();
        initprintf("Definitions file \"%s\" loaded in %d ms.\n", defsfile, etime-stime);
    }
    loaddefinitions_game(defsfile, FALSE);


    if (enginePostInit())
        ShutDown();

    g_frameDelay = calcFrameDelay(r_maxfps + r_maxfpsoffset);

    // loc_11745:
    FadeOut(0);
//	InstallEngine();
    KB_Startup();
    InitView();
    myloadconfig();
    InitFX();
    LoadFX();
    setCDaudiovolume(gMusicVolume);
    seq_LoadSequences();
    InitStatus();
    InitTimer();

    for (i = 0; i < kMaxPlayers; i++) {
        nPlayerLives[i] = kDefaultLives;
    }

    nBestLevel = 0;

    UpdateScreenSize();

    EraseScreen(overscanindex);
    ResetEngine();
    EraseScreen(overscanindex);

    ResetView();
    GrabPalette();

    if (bSerialPlay && !InitSerial()) {
        bail2dos("Unable to connect");
    }

    if (doTitle)
    {
        while (!stopTitle)
        {
            DoTitle();
            stopTitle = kTrue;
        }
    }
    // loc_11811:
    if (forcelevel > -1)
    {
        levelnew = forcelevel;
        goto STARTGAME1;
    }
    // no forcelevel specified...
    if (!bPlayback)
    {
        goto MENU;
    }
MENU:
    SavePosition = -1;
    nMenu = menu_Menu(0);
    switch (nMenu)
    {
    case -1:
        goto MENU;
    case 0:
        goto EXITGAME;
    case 3:
        forcelevel = 0;
        goto STARTGAME2;
    case 9:
        vcrfp = fopen("demo.vcr", "rb");
        if (vcrfp == NULL) {
            goto MENU;
        }

        InitRandom();
        bInDemo = kTrue;
        bPlayback = kTrue;

        KB_FlushKeyboardQueue();
        KB_ClearKeysDown();
        break;
    }
STARTGAME1:
    levelnew = 1;
    levelnum = 1;
    if (!nNetPlayerCount) {
        FadeOut(0);
    }
STARTGAME2:

    bCamera = kFalse;
    ClearCinemaSeen();
    PlayerCount = 0;
    lastlevel = -1;

    for (i = 0; i < nTotalPlayers; i++)
    {
        int nPlayer = GrabPlayer();
        if (nPlayer < 0) {
            bail2dos("Can't create local player\n");
        }

        InitPlayerInventory(nPlayer);

        if (i == wConsoleNode) {
            PlayerList[nPlayer].someNetVal = -3;
        }
        else {
            PlayerList[nPlayer].someNetVal = -4;
        }
    }

    nNetMoves = 0;

    if (bPlayback)
    {
        menu_GameLoad2(vcrfp);
        levelnew = GameStats.nMap;
        levelnum = GameStats.nMap;
        forcelevel = GameStats.nMap;
    }

    if (forcelevel > -1)
    {
        // YELLOW SECTION
        levelnew = forcelevel;
        UpdateInputs();
        forcelevel = -1;

        if (bRecord && !bInDemo) {
            menu_GameSave2(vcrfp);
        }
        goto LOOP3;
    }

    // PINK SECTION
    UpdateInputs();
    nNetMoves = 1;

    if (nMenu == 2)
    {
        levelnew = 1;
        levelnum = 1;
        levelnew = menu_GameLoad(SavePosition);
        lastlevel = -1;
    }

    if (bRecord && !bInDemo) {
        menu_GameSave2(vcrfp);
    }

    nBestLevel = levelnew - 1;
LOOP1:

    if (nPlayerLives[nLocalPlayer] <= 0) {
        goto MENU;
    }
    if (levelnew > 99) {
        goto EXITGAME;
    }
    if (!bInDemo && levelnew > nBestLevel && levelnew != 0 && levelnew <= kMap20 && SavePosition > -1) {
        menu_GameSave(SavePosition);
    }
LOOP2:
    if (!nNetPlayerCount && !bPlayback && levelnew > 0 && levelnew <= kMap20) {
        levelnew = showmap(levelnum, levelnew, nBestLevel);
    }

    if (levelnew > nBestLevel) {
        nBestLevel = levelnew;
    }
LOOP3:
    while (levelnew != -1)
    {
        // BLUE
        if (CDplaying()) {
            fadecdaudio();
        }

        CheckCD();

#if 0
        if (!bNoCDCheck)
        {
            while (!checkcdrom())
            {
                EraseScreen(overscanindex);
                Query(2, 0, "Insert CD into drive", "(ESC to abort)");
                KB_ClearKeysDown();
                if (KB_GetCh() == asc_Escape) {
                    bail2dos("Aborted\n");
                }
            }
        }
#endif

        if (levelnew == kMap20)
        {
            lCountDown = 81000;
            nAlarmTicks = 30;
            nRedTicks = 0;
            nClockVal = 0;
            nEnergyTowers = 0;
        }

        if (!LoadLevel(levelnew)) {
            // TODO "Can't load level %d...\n", nMap;
            goto EXITGAME;
        }
        levelnew = -1;
    }
    if (nNetPlayerCount == 0 && lastlevel == levelnum)
    {
        RestoreSavePoint(nLocalPlayer, &initx, &inity, &initz, &initsect, &inita);
    }

    lastlevel = levelnum;

    for (i = 0; i < nTotalPlayers; i++)
    {
        SetSavePoint(i, initx, inity, initz, initsect, inita);
        RestartPlayer(i);
        InitPlayerKeys(i);
    }

    UpdateScreenSize();
    fps = 0;
    lastfps = 0;
    InitStatus();
    ResetView();
    ResetEngine();
    totalmoves = 0;
    GrabPalette();
    ResetMoveFifo();
    moveframes = 0;
    bInMove = kFalse;
    tclocks = totalclock;
    nPlayerDAng = 0;
    lPlayerXVel = 0;
    lPlayerYVel = 0;
    movefifopos = movefifoend;
    nCDTrackLength = 0;
    RefreshStatus();

    if (bSerialPlay) {
        ClearSerialInbuf();
    }

    mysetbrightness((uint8_t)nGamma);
    //int edi = totalclock;
    tclocks2 = totalclock;
    CONTROL_BindsEnabled = 1;
    // Game Loop
    while (1)
    {
        if (levelnew >= 0)
        {
            CONTROL_BindsEnabled = 0;
            goto LOOP1;
        }

        HandleAsync();
        OSD_DispatchQueued();
        // Section B
        if (!nCDTrackLength && !nFreeze && !nNetPlayerCount)
        {
            int nTrack = levelnum;
            if (nTrack != 0) {
                nTrack--;
            }

            nCDTrackLength = playCDtrack((nTrack % 8) + 11);

            if (!nCDTrackLength) {
                nCDTrackLength = -1;
            }
        }

// TODO		CONTROL_GetButtonInput();
        CheckKeys();
        UpdateSounds();

        if (bRecord || bPlayback)
        {
            bInMove = kTrue;

            moveframes = ((int)totalclock - (int)tclocks2) / 4;

            if (moveframes > 4)
                moveframes = 4;

            if (moveframes != 0)
                tclocks2 = totalclock;

            if (bPlayback)
            {
                // YELLOW
                if ((bInDemo && KB_KeyWaiting() || !ReadPlaybackInputs()) && KB_GetCh())
                {
                    KB_FlushKeyboardQueue();
                    KB_ClearKeysDown();

                    bPlayback = kFalse;
                    bInDemo = kFalse;

                    if (vcrfp) {
                        fclose(vcrfp);
                    }

                    CONTROL_BindsEnabled = 0;
                    goto MENU;
                }
            }
            else if (bRecord || moveframes)
            {
                GetLocalInput();

                sPlayerInput[nLocalPlayer].xVel = lPlayerXVel;
                sPlayerInput[nLocalPlayer].yVel = lPlayerYVel;
                sPlayerInput[nLocalPlayer].buttons = lLocalButtons | lLocalCodes;
                sPlayerInput[nLocalPlayer].nAngle = nPlayerDAng;
                sPlayerInput[nLocalPlayer].nTarget = besttarget;

                Ra[nLocalPlayer].nTarget = besttarget;

                lLocalCodes = 0;
                nPlayerDAng = 0;

                sPlayerInput[nLocalPlayer].horizon = nVertPan[nLocalPlayer];
            }

            // loc_11F72:
            if (bRecord && !bInDemo) {
                WritePlaybackInputs();
            }

            if (nNetPlayerCount)
            {
                if (moveframes)
                {
                    UpdateInputs();
                    moveframes = nNetMoveFrames;
                }
            }
            else
            {
                // loc_11FBC:
                while (bPause)
                {
                    ClearAllKeys();
                    if (WaitAnyKey(-1) != sc_Pause)
                    {
                        bPause = kFalse;
                    }
                }
            }

            // loc_11FEE:
            tclocks += moveframes * 4;
            while (moveframes && levelnew < 0)
            {
                GameMove();
                // if (nNetTime > 0)
                // {
                //     nNetTime--;
                //
                //     if (!nNetTime) {
                //         nFreeze = 3;
                //     }
                // }
                // else if (nNetTime == 0)
                // {
                //     if (BUTTON(gamefunc_Open))
                //     {
                //         CONTROL_ClearButton(gamefunc_Open);
                //         goto MENU2;
                //     }
                // }
            }

            bInMove = kFalse;

            // END YELLOW SECTION

            // loc_12149:
            if (bInDemo)
            {
                while (tclocks > totalclock) { HandleAsync(); }
                tclocks = totalclock;
            }

            if (G_FPSLimit())
            {
                GameDisplay();
            }
        }
        else
        {
            bInMove = kTrue;
            if (!bPause && totalclock >= tclocks + 4)
            {
                GetLocalInput();

                sPlayerInput[nLocalPlayer].xVel = lPlayerXVel;
                sPlayerInput[nLocalPlayer].yVel = lPlayerYVel;
                sPlayerInput[nLocalPlayer].buttons = lLocalButtons | lLocalCodes;
                sPlayerInput[nLocalPlayer].nAngle = nPlayerDAng;
                sPlayerInput[nLocalPlayer].nTarget = besttarget;

                Ra[nLocalPlayer].nTarget = besttarget;

                lLocalCodes = 0;
                nPlayerDAng = 0;

                sPlayerInput[nLocalPlayer].horizon = nVertPan[nLocalPlayer];

                do
                {
                    timerUpdate();
                    tclocks += 4;
                    GameMove();
                    timerUpdate();
                } while (levelnew < 0 && totalclock >= tclocks + 4);
            }
            bInMove = kFalse;

            faketimerhandler();

            if (G_FPSLimit())
            {
                GameDisplay();
            }
        }
        if (!bInDemo)
        {
            if (BUTTON(gamefunc_Escape))
            {
                CONTROL_ClearButton(gamefunc_Escape);
// MENU2:
                CONTROL_BindsEnabled = 0;
                bInMove = kTrue;
                nMenu = menu_Menu(1);

                switch (nMenu)
                {
                    case 0:
                        goto EXITGAME;

                    case 1:
                        goto STARTGAME1;

                    case 2:
                        levelnum = levelnew = menu_GameLoad(SavePosition);
                        lastlevel = -1;
                        nBestLevel = levelnew - 1;
                        goto LOOP2;

                    case 3: // When selecting 'Training' from ingame menu when already playing a level
                        if (levelnum == 0 || !Query(2, 4, "Quit current game?", "Y/N", 'Y', 13, 'N', 27))
                        {
                            levelnew = 0;
                            levelnum = 0;
                        }
                        goto STARTGAME2;
                }

                totalclock = ototalclock = tclocks;
                bInMove = kFalse;
                CONTROL_BindsEnabled = 1;
                RefreshStatus();
            }
            else if (KB_UnBoundKeyPressed(sc_F12))
            {
                KB_ClearKeyDown(sc_F12);
                videoCaptureScreen("captxxxx.png", 0);
            }
            else if (BUTTON(gamefunc_Map)) // e.g. TAB (to show 2D map)
            {
                CONTROL_ClearButton(gamefunc_Map);

                if (!nFreeze) {
                    nMapMode = (nMapMode+1)%3;
                }
            }

            if (nMapMode != 0)
            {
                int const timerOffset = ((int) totalclock - nonsharedtimer);
                nonsharedtimer += timerOffset;

                if (BUTTON(gamefunc_Zoom_In))
                    lMapZoom += mulscale6(timerOffset, max<int>(lMapZoom, 256));

                if (BUTTON(gamefunc_Zoom_Out))
                    lMapZoom -= mulscale6(timerOffset, max<int>(lMapZoom, 256));

                lMapZoom = clamp(lMapZoom, 48, 2048);
            }

            if (PlayerList[nLocalPlayer].nHealth > 0)
            {
                if (BUTTON(gamefunc_Inventory_Left))
                {
                    SetPrevItem(nLocalPlayer);
                    CONTROL_ClearButton(gamefunc_Inventory_Left);
                }
                if (BUTTON(gamefunc_Inventory_Right))
                {
                    SetNextItem(nLocalPlayer);
                    CONTROL_ClearButton(gamefunc_Inventory_Right);
                }
                if (BUTTON(gamefunc_Inventory))
                {
                    UseCurItem(nLocalPlayer);
                    CONTROL_ClearButton(gamefunc_Inventory);
                }
            }
            else {
                SetAirFrame();
            }
        }
        if (record_mode == 3 && movefifopos == movefifoend) {
            levelnew = 0;
        }
        fps++;
    }
EXITGAME:
    if (bRecord) {
        fclose(vcrfp);
    }

    FadeSong();
    if (CDplaying()) {
        fadecdaudio();
    }

    StopAllSounds();
    StopLocalSound();
    mysaveconfig();

    if (bSerialPlay)
    {
        if (nNetPlayerCount != 0) {
            bSendBye = kTrue;
            UpdateSerialInputs();
        }
    }
    else
    {
        if (nNetPlayerCount != 0) {
            SendGoodbye();
        }
    }

    ShutDown();
    return 0;
}

void mychangespritesect(int nSprite, int nSector)
{
    DoKenTest();
    changespritesect(nSprite, nSector);
    DoKenTest();
}

void mydeletesprite(int nSprite)
{
    if (nSprite < 0 || nSprite > kMaxSprites) {
        bail2dos("bad sprite value %d handed to mydeletesprite", nSprite);
    }

    deletesprite(nSprite);

    if (nSprite == besttarget) {
        besttarget = -1;
    }
}


void KeyFn1()
{
    menu_DoPlasma();
    overwritesprite(160, 100, kSkullHead, 0, 3, kPalNormal);
    overwritesprite(161, 130, kSkullJaw, 0, 3, kPalNormal);
    videoNextPage();
}

void DoGameOverScene()
{
    FadeOut(0);
    ClearAllKeys();

    if (LoadCinemaPalette(16) < 0) {
        return;
    }

    SetOverscan(ANIMPAL);
    NoClip();
    overwritesprite(0, 0, kTile3591, 0, 2, kPalNormal);
    Clip();
    videoNextPage();
    CinemaFadeIn();
    PlayGameOverSound();
    WaitAnyKey(3);
    FadeOut(0);
    SetOverscan(BASEPAL);
}

// TODO - missing some values?
short word_10010[] = {6, 25, 43, 50, 68, 78, 101, 111, 134, 158, 173, 230, 6000};

void DoTitle()
{
    short theArray[13];
    memcpy(theArray, word_10010, sizeof(word_10010));

    videoSetViewableArea(0, 0, xdim - 1, ydim - 1);

    if (videoGetRenderMode() == REND_CLASSIC)
        BlackOut();

    overwritesprite(0, 0, EXHUMED ? kTileBMGLogo : kTilePIELogo, 0, 2, kPalNormal);
    videoNextPage();

    if (videoGetRenderMode() == REND_CLASSIC)
        FadeIn();

    ClearAllKeys();

    WaitAnyKey(2);

    if (videoGetRenderMode() == REND_CLASSIC)
        FadeOut(0);

    SetOverscan(BASEPAL);

    int nScreenTile = seq_GetSeqPicnum(kSeqScreens, 0, 0);

    overwritesprite(0, 0, nScreenTile, 0, 2, kPalNormal);
    videoNextPage();

    if (videoGetRenderMode() == REND_CLASSIC)
        FadeIn();
    PlayLogoSound();

    WaitAnyKey(2);

    if (videoGetRenderMode() == REND_CLASSIC)
        FadeOut(0);
    ClearAllKeys();

    PlayMovie("book.mov");

    if (videoGetRenderMode() == REND_CLASSIC)
        FadeOut(0);

    SetOverscan(BASEPAL);
    GrabPalette();

    SetLocalChan(1);
    PlayLocalSound(StaticSound[59], 0);

    SetLocalChan(0);

    EraseScreen(4);

    playCDtrack(19);

    videoNextPage();
    FadeIn();
    WaitVBL();


    int String_Copyright = FindGString("COPYRIGHT");

    const char *a = gString[String_Copyright];
    const char *b = gString[String_Copyright + 1];

    menu_DoPlasma();

    int nTile = kSkullHead;

    overwritesprite(160, 100, kSkullHead, 0, 3, kPalNormal);
    overwritesprite(161, 130, kSkullJaw, 0, 3, kPalNormal);
    videoNextPage();

    WaitNoKey(2, KeyFn1);

    if (time(0) & 0xF) {
        PlayGameOverSound();
    }
    else {
        PlayLocalSound(StaticSound[61], 0);
    }

    int nStartTime = (int)totalclock;
    int nCount = 0;
    int var_18 = (int)totalclock;
    int var_4 = 0;

    int esi = 130;

    var_18 += theArray[0];

    while (LocalSoundPlaying())
    {
        HandleAsync();

        menu_DoPlasma();
        overwritesprite(160, 100, nTile, 0, 3, kPalNormal);

        int nStringWidth = MyGetStringWidth(a);

        int y = ydim - 24;
        myprintext((xdim / 2 - nStringWidth / 2), y, a, 0);

        nStringWidth = MyGetStringWidth(b);

        y = ydim - 16;
        myprintext((xdim / 2 - nStringWidth / 2), y, b, 0);

        if ((int)totalclock > var_18)
        {
            nCount++;

            assert(nCount <= 12);
            var_18 = nStartTime + theArray[nCount];

            var_4 = var_4 == 0;
        }

        short nTile = kSkullJaw;

        if (var_4)
        {
            if (esi >= 135) {
                nTile = kTile3583;
            }
            else {
                esi += 5;
            }
        }
        else if (esi <= 130)
        {
            esi = 130;
        }
        else
        {
            esi -= 2;
        }

        y = 0;

        if (nTile == kTile3583)
        {
            y = 131;
        }
        else
        {
            y = esi;

            if (y > 135) {
                y = 135;
            }
        }

        overwritesprite(161, y, nTile, 0, 3, kPalNormal);
        videoNextPage();
    }

    WaitNoKey(1, KeyFn1);

    videoSetViewableArea(nViewLeft, nViewTop, nViewRight, nViewBottom);
}

void CopyTileToBitmap(short nSrcTile,  short nDestTile, int xPos, int yPos)
{
    int nOffs = tilesiz[nDestTile].y * xPos;

    uint8_t *pDest = (uint8_t*)waloff[nDestTile] + nOffs + yPos;
    uint8_t *pDestB = pDest;

    tileLoad(nSrcTile);

    int destYSize = tilesiz[nDestTile].y;
    int srcYSize = tilesiz[nSrcTile].y;

    uint8_t *pSrc = (uint8_t*)waloff[nSrcTile];

    for (int x = 0; x < tilesiz[nSrcTile].x; x++)
    {
        pDest += destYSize;

        for (int y = 0; y < srcYSize; y++)
        {
            uint8_t val = *pSrc;
            if (val != 0xFF) {
                *pDestB = val;
            }

            pDestB++;
            pSrc++;
        }

        // reset pDestB
        pDestB = pDest;
    }

    tileInvalidate(nDestTile, -1, -1);
}

int CopyCharToBitmap(char nChar, int nTile, int xPos, int yPos)
{
    if (nChar == ' ') {
        return 4;
    }

    nChar = toupper(nChar);
    int nFontTile = seq_GetSeqPicnum(kSeqFont2, 0, nChar - 32) + 102;
    CopyTileToBitmap(nFontTile, nTile, xPos, yPos);

    return tilesiz[nFontTile].x + 1;
}

// Note: strings passed should be uppercase
int myprintext(int x, int y, const char *str, int shade)
{
    if (y < -15 || y >= 200)
        return x;

    const char *c = str;

    while (*c != '\0')
    {
        int nTile = seq_GetSeqPicnum(kSeqFont2, 0, (*c) - 32);
        overwritesprite(x, y, nTile, shade, 2, kPalNormal);

        int tileWidth = tilesiz[nTile].x;

        x += tileWidth + 1;
        c++;
    }

    return x;
}

void EraseScreen(int nVal)
{
    if (nVal == -1) {
        nVal = overscanindex;
    }

    videoClearScreen(nVal);
#if 0
    for (int i = 0; i < numpages; i++)
    {
        videoClearScreen(nVal);
        videoNextPage();
    }
#endif
}

int Query(short nLines, short nKeys, ...)
{
    short i;

    char strings[20][80];
    char keys[20];

    va_list args;

    short bPrevClip = bClip;
    NoClip();

    short nWidth = 0;

    va_start(args, nKeys);

    for (i = 0; i < nLines; i++)
    {
        char *str = va_arg(args, char*);
        strcpy(strings[i], str);
        Bstrupr(strings[i]);

        int strWidth = MyGetStringWidth(strings[i]);

        if (strWidth > nWidth) {
            nWidth = strWidth;
        }
    }

    for (i = 0; i < nKeys; i++) {
        keys[i] = (char)va_arg(args, int);
    }

    va_end(args);

    int nHeight = (nLines + 1) * 10;
    int y1 = (200 - nHeight) / 2;
    int yB = y1;

    // add some padding to left and right sides of text in the box
    nWidth += 30;

    int x1 = (320 - nWidth) / 2;
    int x2 = x1 + nWidth;

    // if (bHiRes)
    // {
    //     x1 *= 2;
    //     y1 *= 2;
    //     nHeight *= 2;
    //     x2 *= 2;
    // }

    y1 = scale(y1, ydim, 200);
    nHeight = scale(nHeight, ydim, 200);
    x1 = scale(x1-160, ydim*4/3, 320)+xdim/2;
    x2 = scale(x2-160, ydim*4/3, 320)+xdim/2;

    // draw background box that the text sits in
    for (i = 0; i < nHeight; i++) {
        renderDrawLine(x1 << 12, (y1 + i) << 12, x2 << 12, (y1 + i) << 12, overscanindex);
    }

    y1 = yB + 5;

    // draw each line of text
    for (i = 0; i < nLines; i++) {
        myprintext((320 - MyGetStringWidth(strings[i])) / 2, (y1 + i*10) , strings[i], 0);
    }

    videoNextPage();

    if (bPrevClip) {
        Clip();
    }

    i = 0;

    if (nKeys)
    {
        KB_FlushKeyboardQueue();

        while (1)
        {
            HandleAsync();

            char key = toupper(KB_GetCh());

            for (i = 0; i < nKeys; i++)
            {
                if (keys[i] == 0 || key == keys[i])
                {
                    RefreshStatus();
                    ClearAllKeys();
                    return i;
                }
            }
        }
    }

    RefreshStatus();
    ClearAllKeys();

    return i;
}

void InitSpiritHead()
{
    char filename[20];

    nPixels = 0;

    tileLoad(kTileRamsesNormal); // Ramses Normal Head

    for (int i = 0; i < kMaxSprites; i++)
    {
        if (sprite[i].statnum)
        {
            sprite[i].cstat |= 0x8000;
        }
    }

    uint8_t *pTile = (uint8_t*)waloff[kTileRamsesNormal];

    for (int x = 0; x < 97; x++)
    {
        for (int y = 0; y < 106; y++)
        {
            if (*pTile != 255)
            {
                pixelval[nPixels] = *(uint8_t*)(waloff[kTileRamsesGold] + x * 106 + y);
                origx[nPixels] = x - 48;
                origy[nPixels] = y - 53;
                curx[nPixels] = 0;
                cury[nPixels] = 0;
                vely[nPixels] = 0;
                velx[nPixels] = 0;

                destvelx[nPixels] = RandomSize(2) + 1;

                if (curx[nPixels] > 0) {
                    destvelx[nPixels] = -destvelx[nPixels];
                }

                destvely[nPixels] = RandomSize(2) + 1;

                if (cury[nPixels] > 0) {
                    destvely[nPixels] = -destvely[nPixels];
                }

                nPixels++;
            }

            pTile++;
        }
    }

    waloff[kTileRamsesWorkTile] = (intptr_t)worktile;

    sprite[nSpiritSprite].yrepeat = 140;
    sprite[nSpiritSprite].xrepeat = 140;
    sprite[nSpiritSprite].picnum = kTileRamsesWorkTile;

    nHeadStage = 0;

    // work tile is twice as big as the normal head size
    tilesiz[kTileRamsesWorkTile].x = 97  * 2; // 194;
    tilesiz[kTileRamsesWorkTile].y = 106 * 2; // 212;

    sprite[nSpiritSprite].cstat &= 0x7FFF;

    nHeadTimeStart = (int)totalclock;

    memset(worktile, -1, sizeof(worktile));
    tileInvalidate(kTileRamsesWorkTile, -1, -1);

    nPixelsToShow = 0;

    fadecdaudio();

    int nTrack;

    if (levelnum == 1)
    {
        nTrack = 3;
    }
    else
    {
        nTrack = 7;
    }

    nCDTrackLength = playCDtrack(nTrack);

    bSubTitles = nCDTrackLength == 0;

    StartSwirlies();

    sprintf(filename, "LEV%d.PUP", levelnum);
    lNextStateChange = (int)totalclock;
    lHeadStartClock = (int)totalclock;

    headfd = kopen4load(filename, 512); // 512??
    nPupData = kread(headfd, cPupData, sizeof(cPupData));
    pPupData = cPupData;
    kclose(headfd);
    headfd = -1;
    nMouthTile = 0;
    nTalkTime = 1;
}

void DimSector(short nSector)
{
    short startwall = sector[nSector].wallptr;
    short nWalls = sector[nSector].wallnum;

    for (int i = 0; i < nWalls; i++)
    {
        if (wall[startwall+i].shade < 40) {
            wall[startwall+i].shade++;
        }
    }

    if (sector[nSector].floorshade < 40) {
        sector[nSector].floorshade++;
    }

    if (sector[nSector].ceilingshade < 40) {
        sector[nSector].ceilingshade++;
    }
}

void CopyHeadToWorkTile(short nTile)
{
    tileLoad(nTile);

    uint8_t *pSrc = (uint8_t*)waloff[nTile];
    uint8_t *pDest = (uint8_t*)&worktile[212 * 49 + 53];

    for (int i = 0; i < 97; i++)
    {
        memcpy(pDest, pSrc, 106);

        pDest += 212;
        pSrc += 106;
    }
}

#if 1
int DoSpiritHead()
{
    static short word_964E6 = 0;

    nVertPan[0] += (nDestVertPan[0] - nVertPan[0]) / 4;

    tileInvalidate(kTileRamsesWorkTile, -1, -1);

    if (nHeadStage < 2)
    {
        memset(worktile, -1, sizeof(worktile));
    }

    if (nHeadStage < 2 || nHeadStage != 5)
    {
        nPixelsToShow = ((int)totalclock - nHeadTimeStart) * 15;

        if (nPixelsToShow > nPixels) {
            nPixelsToShow = nPixels;
        }

        if (nHeadStage < 3)
        {
            UpdateSwirlies();

            if (sprite[nSpiritSprite].shade > -127) {
                sprite[nSpiritSprite].shade--;
            }

            word_964E6--;
            if (word_964E6 < 0)
            {
                DimSector(sprite[nSpiritSprite].sectnum);
                word_964E6 = 5;
            }

            if (!nHeadStage)
            {
                if (((int)totalclock - nHeadTimeStart) > 480)
                {
                    nHeadStage = 1;
                    nHeadTimeStart = (int)totalclock + 480;
                }

//				int ecx = 0;

                // loc_1362C
                for (int i = 0; i < nPixelsToShow; i++)
                {
                    if (destvely[i] >= 0)
                    {
                        vely[i]++;

                        if (vely[i] >= destvely[i])
                        {
                            destvely[i] = -(RandomSize(2) + 1);
                        }
                    }
                    else
                    {
                        vely[i]--;

                        if (vely[i] <= destvely[i])
                        {
                            destvely[i] = RandomSize(2) + 1;
                        }
                    }

                    // loc_13541
                    if (destvelx[i] >= 0)
                    {
                        velx[i]++;

                        if (velx[i] >= destvelx[i])
                        {
                            destvelx[i] = -(RandomSize(2) + 1);
                        }
                    }
                    else
                    {
                        velx[i]--;

                        if (velx[i] <= destvelx[i])
                        {
                            destvelx[i] = RandomSize(2) + 1;
                        }
                    }

                    // loc_13593
                    int esi = vely[i] + (cury[i] >> 8);

                    if (esi < 106)
                    {
                        if (esi < -105)
                        {
                            vely[i] = 0;
                            esi = 0;
                        }
                    }
                    else
                    {
                        vely[i] = 0;
                        esi = 0;
                    }

                    // loc_135C6
                    int ebx = velx[i] + (curx[i] >> 8);

                    if (ebx < 97)
                    {
                        if (ebx < -96)
                        {
                            velx[i] = 0;
                            ebx = 0;
                        }
                    }
                    else
                    {
                        velx[i] = 0;
                        ebx = 0;
                    }

                    // loc_135F9
                    curx[i] = ebx * 256;
                    cury[i] = esi * 256;

                    //ecx += 2;
//					ecx++;

                    esi += (ebx + 97) * 212;

//					uint8_t *pVal = (uint8_t*)worktile;

                    worktile[106 + esi] = pixelval[i];
                    //pVal += (106 + esi);
                    //*pVal = pixelval[i];
                }

                return 1;
            }
            else
            {
                // loc_13679:
                if (nHeadStage != 1) {
                    return 1;
                }

                uint8_t nXRepeat = sprite[nSpiritSprite].xrepeat;
                if (nXRepeat > nSpiritRepeatX)
                {
                    sprite[nSpiritSprite].xrepeat -= 2;

                    nXRepeat = sprite[nSpiritSprite].xrepeat;
                    if (nXRepeat < nSpiritRepeatX)
                    {
                        sprite[nSpiritSprite].xrepeat = nSpiritRepeatX;
                    }
                }

                uint8_t nYRepeat = sprite[nSpiritSprite].yrepeat;
                if (nYRepeat > nSpiritRepeatY)
                {
                    sprite[nSpiritSprite].yrepeat -= 2;

                    nYRepeat = sprite[nSpiritSprite].yrepeat;
                    if (nYRepeat < nSpiritRepeatY)
                    {
                        sprite[nSpiritSprite].yrepeat = nSpiritRepeatY;
                    }
                }

                // loc_13705
                int esi = 0;
//				int edx = 0;

                // loc_137E7:
                for (int i = 0; i < nPixels; i++)
                {
                    int eax = (origx[i] << 8) - curx[i];
                    int ecx = eax;

                    if (eax)
                    {
                        if (eax < 0) {
                            eax = -eax;
                        }

                        if (eax < 8)
                        {
                            curx[i] = origx[i] << 8;
                            ecx = 0;
                        }
                        else {
                            ecx >>= 3;
                        }
                    }
                    else
                    {
                        ecx >>= 3;
                    }

                    // loc_1374B
                    int var_1C = (origy[i] << 8) - cury[i];
                    int ebp = var_1C;

                    if (var_1C)
                    {
                        eax = ebp;

                        if (eax < 0) {
                            eax = -eax;
                        }

                        if (eax < 8)
                        {
                            cury[i] = origy[i] << 8;
                            var_1C = 0;
                        }
                        else
                        {
                            var_1C >>= 3;
                        }
                    }
                    else
                    {
                        var_1C >>= 3;
                    }

                    if (var_1C || ecx)
                    {
                        curx[i] += ecx;
                        cury[i] += var_1C;

                        esi++;
                    }

                    ecx = (((curx[i] >> 8) + 97) * 212) + (cury[i] >> 8);

//					edx++;

//					uint8_t *pVal = (uint8_t*)worktile;

                    worktile[106 + ecx] = pixelval[i];

                    //pVal += (106 + ecx);
                    //*pVal = pixelval[i];
                }

                if (((int)totalclock - lHeadStartClock) > 600) {
                    CopyHeadToWorkTile(kTileRamsesGold);
                }

                int eax = ((nPixels << 4) - nPixels) / 16;

                if (esi < eax)
                {
                    SoundBigEntrance();
                    AddGlow(sprite[nSpiritSprite].sectnum, 20);
                    AddFlash(
                        sprite[nSpiritSprite].sectnum,
                        sprite[nSpiritSprite].x,
                        sprite[nSpiritSprite].y,
                        sprite[nSpiritSprite].z,
                        128);

                    nHeadStage = 3;
                    TintPalette(255, 255, 255);
                    CopyHeadToWorkTile(kTileRamsesNormal);
                }

                return 1;
            }
        }
        else
        {
            // loc_138A7
            FixPalette();

            if (!nPalDiff)
            {
                nFreeze = 2;
                nHeadStage++;
            }

            return 0;
        }
    }
    else
    {
        if (lNextStateChange <= (int)totalclock)
        {
            if (nPupData)
            {
                short nPupVal = *pPupData;
                pPupData++;
                nPupData -= 2;

                if (nPupData > 0)
                {
                    lNextStateChange = (nPupVal + lHeadStartClock) - 10;
                    nTalkTime = !nTalkTime;
                }
                else
                {
                    nTalkTime = 0;
                    nPupData = 0;
                }
            }
            else if (!bSubTitles)
            {
                if (!CDplaying())
                {
                    levelnew = levelnum + 1;
                    fadecdaudio();
                }
            }
        }

        word_964E8--;
        if (word_964E8 <= 0)
        {
            word_964EA = RandomBit() * 2;
            word_964E8 = RandomSize(5) + 4;
        }

        int ebx = 592;
        word_964EC--;

        if (word_964EC < 3)
        {
            ebx = 593;
            if (word_964EC <= 0) {
                word_964EC = RandomSize(6) + 4;
            }
        }

        ebx += word_964EA;

        tileLoad(ebx);

        // TODO - fixme. How big is worktile?
        uint8_t *pDest = (uint8_t*)&worktile[10441];
        uint8_t *pSrc = (uint8_t*)waloff[ebx];

        for (int i = 0; i < 97; i++)
        {
            memcpy(pDest, pSrc, 106);

            pDest += 212;
            pSrc += 106;
        }

        if (nTalkTime)
        {
            if (nMouthTile < 2) {
                nMouthTile++;
            }
        }
        else if (nMouthTile != 0)
        {
            nMouthTile--;
        }

        if (nMouthTile)
        {
            tileLoad(nMouthTile + 598);

            short nTileSizeX = tilesiz[nMouthTile + 598].x;
            short nTileSizeY = tilesiz[nMouthTile + 598].y;

            // TODO - checkme. near loc_133AA
//			uint8_t *pDest = (uint8_t*)worktile;
//			pDest += (212 * (97 - nTileSizeX / 2)) + (159 - nTileSizeY);

            uint8_t *pDest = (uint8_t*)&worktile[212 * (97 - nTileSizeX / 2)] + (159 - nTileSizeY);
            uint8_t *pSrc = (uint8_t*)waloff[nMouthTile + 598];

            while (nTileSizeX > 0)
            {
                memcpy(pDest, pSrc, nTileSizeY);

                nTileSizeX--;
                pDest += 212;
                pSrc += nTileSizeY;
            }
        }

        return 1;
    }

    // TEMP FIXME - temporary return value. what to return here? 1?

    return 0;
}
#endif

#if 0
int DoSpiritHead()
{
    static short word_964E6 = 0;

    nVertPan[0] += (nDestVertPan[0] - nVertPan[0]) / 4;

    if (nHeadStage < 2)
    {
        memset(worktile, -1, sizeof(worktile));
    }
    else if (nHeadStage == 5)
    {
        if (lNextStateChange <= (int)totalclock)
        {
            if (nPupData)
            {
                short nPupVal = *pPupData;
                pPupData++;
                nPupData -= 2;

                if (nPupData > 0)
                {
                    lNextStateChange = (nPupVal + lHeadStartClock) - 10;
                    nTalkTime = !nTalkTime;
                }
                else
                {
                    nTalkTime = 0;
                    nPupData = 0;
                }
            }
            else if (!bSubTitles)
            {
                if (!CDplaying())
                {
                    levelnew = levelnum + 1;
                    fadecdaudio();
                }
            }
        }

        word_964E8--;
        if (word_964E8 <= 0)
        {
            word_964EA = RandomBit() * 2;
            word_964E8 = RandomSize(5) + 4;
        }

        int ebx = 592;
        word_964EC--;

        if (word_964EC < 3)
        {
            ebx = 593;
            if (word_964EC <= 0) {
                word_964EC = RandomSize(6) + 4;
            }
        }

        ebx += word_964EA;

        loadtile(ebx);

        // TODO - fixme. How big is worktile?
        uint8_t *pDest = (uint8_t*)&worktile[10441];
        uint8_t *pSrc = waloff[ebx];

        for (int i = 0; i < 97; i++)
        {
            memcpy(pDest, pSrc, 106);

            pDest += 212;
            pSrc += 106;
        }

        if (nTalkTime)
        {
            if (nMouthTile < 2) {
                nMouthTile++;
            }
        }
        else if (nMouthTile != 0)
        {
            nMouthTile--;
        }

        if (nMouthTile)
        {
            loadtile(nMouthTile + 598);

            short nTileSizeX = tilesizx[nMouthTile + 598];
            short nTileSizeY = tilesizy[nMouthTile + 598];

            // TODO - checkme. near loc_133AA
            //          uint8_t *pDest = (uint8_t*)worktile;
            //          pDest += (212 * (97 - nTileSizeX / 2)) + (159 - nTileSizeY);

            uint8_t *pDest = (uint8_t*)&worktile[212 * (97 - nTileSizeX / 2)] + (159 - nTileSizeY);
            uint8_t *pSrc = waloff[nMouthTile + 598];

            while (nTileSizeX > 0)
            {
                memcpy(pDest, pSrc, nTileSizeY);

                nTileSizeX--;
                pDest += 212;
                pSrc += nTileSizeY;
            }
        }

        return 1;
    }
    nPixelsToShow = ((int)totalclock - nHeadTimeStart) * 15;

    if (nPixelsToShow > nPixels) {
        nPixelsToShow = nPixels;
    }

    if (nHeadStage < 3)
    {
        UpdateSwirlies();

        if (sprite[nSpiritSprite].shade > -127) {
            sprite[nSpiritSprite].shade--;
        }

        word_964E6--;
        if (word_964E6 < 0)
        {
            DimSector(sprite[nSpiritSprite].sectnum);
            word_964E6 = 5;
        }

        if (!nHeadStage)
        {
            if (((int)totalclock - nHeadTimeStart) > 480)
            {
                nHeadStage = 1;
                nHeadTimeStart = (int)totalclock + 480;
            }

            //              int ecx = 0;

            // loc_1362C
            for (int i = 0; i < nPixelsToShow; i++)
            {
                if (destvely[i] < 0)
                {
                    vely[i]--;

                    if (vely[i] <= destvely[i])
                    {
                        destvely[i] = RandomSize(2) + 1;
                    }
                }
                else
                {
                    vely[i]++;

                    if (vely[i] >= destvely[i])
                    {
                        destvely[i] = -(RandomSize(2) + 1);
                    }
                }

                // loc_13541
                if (destvelx[i] >= 0)
                {
                    velx[i]--;

                    if (velx[i] <= destvelx[i])
                    {
                        destvelx[i] = RandomSize(2) + 1;
                    }
                }
                else
                {
                    velx[i]++;

                    if (velx[i] >= destvelx[i])
                    {
                        destvelx[i] = -(RandomSize(2) + 1);
                    }
                }

                // loc_13593
                int esi = vely[i] + (cury[i] >> 8);

                if (esi >= 106)
                {
                    vely[i] = 0;
                    esi = 0;
                }
                else if (esi < -105)
                {
                    vely[i] = 0;
                    esi = 0;
                }

                // loc_135C6
                int ebx = velx[i] + (curx[i] >> 8);

                if (ebx >= 97)
                {
                    velx[i] = 0;
                    ebx = 0;
                }
                else if (ebx < -96)
                {
                    velx[i] = 0;
                    ebx = 0;
                }

                // loc_135F9
                curx[i] = ebx << 8;
                cury[i] = esi << 8;

                //ecx += 2;
                //                  ecx++;

                //                  uint8_t *pVal = (uint8_t*)worktile;

                worktile[106 + esi + (ebx + 97) * 212] = pixelval[i];
                //pVal += (106 + esi);
                //*pVal = pixelval[i];
            }
        }
        else if (nHeadStage == 1)
        {
            uint8_t nXRepeat = sprite[nSpiritSprite].xrepeat;
            if (nXRepeat > nSpiritRepeatX)
            {
                sprite[nSpiritSprite].xrepeat -= 2;

                nXRepeat = sprite[nSpiritSprite].xrepeat;
                if (nXRepeat < nSpiritRepeatX)
                {
                    sprite[nSpiritSprite].xrepeat = nSpiritRepeatX;
                }
            }

            uint8_t nYRepeat = sprite[nSpiritSprite].yrepeat;
            if (nYRepeat > nSpiritRepeatY)
            {
                sprite[nSpiritSprite].yrepeat -= 2;

                nYRepeat = sprite[nSpiritSprite].yrepeat;
                if (nYRepeat < nSpiritRepeatY)
                {
                    sprite[nSpiritSprite].yrepeat = nSpiritRepeatY;
                }
            }

            // loc_13705
            int esi = 0;
            //              int edx = 0;

            // loc_137E7:
            for (int i = 0; i < nPixels; i++)
            {
                int eax = (origx[i] << 8) - curx[i];
                int ecx = eax;

                if (eax && klabs(eax) < 8)
                {
                    curx[i] = origx[i] << 8;
                    ecx = 0;
                }
                else
                {
                    ecx >>= 3;
                }

                // loc_1374B
                int var_1C = (origy[i] << 8) - cury[i];
                int ebp = var_1C;

                if (ebp && klabs(ebp) < 8)
                {
                    cury[i] = origy[i] << 8;
                    var_1C = 0;
                }
                else
                {
                    var_1C >>= 3;
                }

                if (var_1C | ecx)
                {
                    curx[i] += ecx;
                    cury[i] += var_1C;

                    esi++;
                }

                //                  edx++;

                //                  uint8_t *pVal = (uint8_t*)worktile;

                worktile[106 + (((curx[i] >> 8) + 97) * 212) + (cury[i] >> 8)] = pixelval[i];

                //pVal += (106 + ecx);
                //*pVal = pixelval[i];
            }

            if (((int)totalclock - lHeadStartClock) > 600) {
                CopyHeadToWorkTile(kTileRamsesGold);
            }

            int eax = (nPixels * 15) / 16;

            if (esi < eax)
            {
                // SoundBigEntrance(); // TODO
                AddGlow(sprite[nSpiritSprite].sectnum, 20);
                AddFlash(
                    sprite[nSpiritSprite].sectnum,
                    sprite[nSpiritSprite].x,
                    sprite[nSpiritSprite].y,
                    sprite[nSpiritSprite].z,
                    128);

                nHeadStage = 3;
                TintPalette(255, 255, 255);
                CopyHeadToWorkTile(kTileRamsesNormal);
            }

        }
        return 1;
    }
    // loc_138A7
    FixPalette();

    if (!nPalDiff)
    {
        nFreeze = 2;
        nHeadStage++;
    }

    return 0;
}
#endif
