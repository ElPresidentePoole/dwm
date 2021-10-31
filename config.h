/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]     	    = { "UbuntuMono Nerd Font:size=12"};
static const char dmenu_fn[]        = "UbuntuMono Nerd Font:size=12";

static const char col_black[]         = "#282c34";
static const char col_white[]         = "#abb2bf";
static const char col_lred[]          = "#e06c75";
static const char col_dred[]          = "#be5046";
static const char col_green[]         = "#98c379";
static const char col_lyellow[]       = "#e5c07b";
static const char col_dyellow[]       = "#d19a66";
static const char col_blue[]          = "#61afef";
static const char col_magenta[]       = "#c678dd";
static const char col_cyan[]          = "#56b6c2";
static const char col_ggrey[]         = "#4b5263";
static const char col_cgrey[]         = "#5c6370";
static const char col_i3lock[]        = "d19a66";
static const char *colors[][3]      = {
	/*                    fg            bg       border   */
	[SchemeNorm]      = { col_white,   col_black, col_ggrey },
	[SchemeSel]       = { col_magenta, col_black, col_cyan },
	[SchemeStatus]    = { col_green, col_black, NULL }, /* border is unused */
	[SchemeTitleNorm] = { col_white, col_black, NULL }, /* border is unused */
	[SchemeTitleSel]  = { col_lyellow, col_black, NULL }, /* border is unused */
};

/*
static const char col_white[]       = "#cee1ea";
static const char col_cyan[]        = "#1ebbbd";
static const char col_dblue[]       = "#576e6d";
static const char col_lblue[]       = "#697d84";
static const char col_black[]       = "#24222a";
static const char col_i3lock[]      = "274966";
static const char *colors[][3]      = {
	[SchemeNorm] = { col_lblue, col_black, col_black },
	[SchemeSel]  = { col_white, col_dblue, col_cyan },
};*/

/* binary names */
static const char terminal[] = "kitty";
static const char browser[]  = "firefox";
static const char fm[] 	     = "thunar";

/* tagging */
static const char *tags[] = { "www", "2", "3", "irc", "disc", "mail" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       1 << 0,       0,           -1 },
	{ "discord",        NULL,       NULL,       1 << 4,       0,           -1 },
	{ NULL,        	    NULL,       "neomutt",  1 << 5,       0,           -1 },
	{ NULL,        	    NULL,       "WeeChat",  1 << 3,       0,           -1 },
	{ "Gimp",           NULL,       NULL,       0,            1,           -1 },
	{ "Sxiv",           NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

/* commands */
static const char *dmenucmd[] = { "/home/gordon/.local/scripts/vmenu.sh", col_black, col_white, col_black, col_blue, dmenu_fn, NULL };
// static const char *dmenucmd[] = { "j4-dmenu-desktop --term=\"urxvt\" --dmenu=\"dmenu -i -l 20 -sf \'#cee1ea\' -sb \'#576e6d\' -nf \'#6d6662\' -nb \'#24222a\' -fn \'Terminus:size=11\'\"" };
static const char *killdwmcmd[] = { "killall", "xinit", NULL };
static const char *termcmd[]  = { terminal, NULL };
static const char *browsercmd[]  = { browser, NULL };
static const char *lockcmd[]  = { "i3lock", "-c", col_i3lock };
static const char *upvol[] = { "pulsemixer", "--change-volume", "+5", NULL };
static const char *downvol[] = { "pulsemixer", "--change-volume", "-5", NULL };
static const char *mute[] = { "pulsemixer", "--toggle-mute", NULL };
static const char *brightupcmd[] = { "light", "-A", "5" };
static const char *brightdowncmd[] = { "light", "-U", "5" };
static const char *scrotcmd[] = { "/home/gordon/.local/scripts/screenshot_grab", NULL };
static const char *vimcmd[] = { terminal, "-e", "nvim", NULL };
static const char *filemancmd[] = { fm, NULL };
static const char *newsboatcmd[] = { terminal, "-e", "newsboat", NULL };
static const char *irccmd[] = { terminal, "-t", "WeeChat", "-e", "weechat", NULL };
static const char *emailcmd[] = { terminal, "-t", "neomutt", "-e", "neomutt", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,				XF86XK_MonBrightnessDown, spawn,  {.v = brightdowncmd} },
	{ 0,				XF86XK_MonBrightnessUp,    spawn, {.v = brightupcmd} },
	{ 0,				XF86XK_AudioRaiseVolume, spawn,          {.v = upvol } },
	{ 0,				XF86XK_AudioLowerVolume, spawn,          {.v = downvol } },
	{ 0,				XF86XK_AudioMute,        spawn,          {.v = mute } },
	{ 0,				XK_Print,  spawn,          {.v = scrotcmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = filemancmd } },
	// { MODKEY,                       XK_p,      spawn,          {.v = pkgmgrcmd } },
	// { MODKEY,                       XK_s,      spawn,          {.v = sshcmd } },
	// { MODKEY,             		XK_c,      spawn,          {.v = irccmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = emailcmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = newsboatcmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = vimcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = lockcmd } },
	// { MODKEY,                       XK_b,      togglebar,      {0} },
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
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[5]} },
	// { MODKEY,                       XK_o,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_o,  togglefloating, {0} }, // tenative
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = killdwmcmd} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0}}
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

