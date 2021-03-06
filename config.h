/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* moved colors and font stuff here */
#include "themes.h"

/* binary names */
static const char terminal[] = "alacritty";
static const char editor[] = "nvim";
static const char browser[]  = "firefox";

/* tagging */
static const char *tags[] = { "main", "www", "term", "disc", "email", "etc" };
// static const char *tags[] = { "www", "term", "vm", "bt", "irc", "disc", "mail" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    title       tags mask     isfloating   monitor */
	{ "firefox", 		NULL,       NULL,       1 << 1,       0,           -1 }, // "Navigator" applies to Firefox and Firefox-esr
	{ "discord",		NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Virt-manager",	NULL,       NULL,       0,            0,           -1 },
	{ "Gimp",     		NULL,       NULL,       0,            1,           -1 },
	{ "Thunderbird",    	NULL,       NULL,       1 << 4,       0,           -1 },
	{ "Sxiv",           	NULL,       NULL,       0,            1,           -1 },
	{ "mpv",           	NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "j4-dmenu-desktop", "--term=st", "--dmenu=dmenu -i -l 20", NULL };
static const char *killdwmcmd[] = { "killall", "xinit", NULL };
static const char *termcmd[]  = { terminal, NULL };
static const char *browsercmd[]  = { browser, NULL };
static const char *lockcmd[]  = { "i3lock", "-c", col_i3lock, NULL};
static const char *upvol[] = { "pulsemixer", "--change-volume", "+5", NULL };
static const char *downvol[] = { "pulsemixer", "--change-volume", "-5", NULL };
static const char *mute[] = { "pulsemixer", "--toggle-mute", NULL };
static const char *brightupcmd[] = { "light", "-A", "5", NULL };
static const char *brightdowncmd[] = { "light", "-U", "5", NULL };
static const char *scrotcmd[] = { "/home/gpoole/.local/scripts/screenshot_grab.sh", NULL };
static const char *filemancmd[] = { "st", "-e", "vifm", NULL };
static const char *newsboatcmd[] = { terminal, "-e", "newsboat", NULL };
static const char *emailcmd[] = { "thunderbird", NULL };
static const char *editorcmd[] = { "st", "-e", "nvim", NULL };
static const char *passmenucmd[] = { "/home/gpoole/.local/scripts/passmenu", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,				XF86XK_MonBrightnessDown, spawn,  {.v = brightdowncmd} },
	{ 0,				XF86XK_MonBrightnessUp,    spawn, {.v = brightupcmd} },
	{ 0,				XF86XK_AudioRaiseVolume, spawn,          {.v = upvol } },
	{ 0,				XF86XK_AudioLowerVolume, spawn,          {.v = downvol } },
	{ 0,				XF86XK_AudioMute,        spawn,          {.v = mute } },
	{ 0,				XK_Print,  spawn,          {.v = scrotcmd } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = passmenucmd } },
	{ MODKEY,                       XK_n,      spawn,          SHCMD("st -e ~/.config/vifm/scripts/vifmrun") },
	{ MODKEY,                       XK_e,      spawn,          {.v = emailcmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = newsboatcmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = editorcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_o,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      spawn,           {.v = killdwmcmd} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

