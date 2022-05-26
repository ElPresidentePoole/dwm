#define GRUVBOX 0
#define COLD 	1
#define BLACK 	2

#define THEME BLACK

#if THEME == GRUVBOX
static const char *fonts[]          = { "UbuntuMono Nerd Font:size=12" };
static const char col_i3lock[]           = "282828";
static const char col_black[]           = "#282828";
static const char col_white[]           = "#ebdbb2";
static const char col_green[]        = "#98971a";
static const char col_red[]        = "#fb4934";
static const char *colors[][3]      = {
	/*                    fg            bg       border   */
	[SchemeNorm]      = { col_white,   col_black, col_black },
	[SchemeSel]       = { col_green, col_black, col_green },
	[SchemeStatus]    = { col_white, col_black, NULL }, /* border is unused */
	[SchemeTitleNorm] = { col_white, col_black, NULL }, /* border is unused */
	[SchemeTitleSel]  = { col_red, col_black, NULL }, /* border is unused */
};
#elif THEME == COLD
static const char *fonts[]          = { "UbuntuMono Nerd Font:size=12" };
static const char col_i3lock[]           = "282828";
static const char col_white[]          	 = "#F6F7DA";
static const char col_black[]            = "#1C2128";
static const char col_blue0[]            = "#28454B";
static const char col_blue1[]            = "#59BACE";
static const char col_blue2[]            = "#4092AC";
static const char col_blue3[]		 = "#B3D7D9";
static const char *colors[][3]      = {
	/*                    fg            bg       border   */
	[SchemeNorm]      = { col_black, col_blue3, col_blue0 },
	[SchemeSel]       = { col_white, col_black, col_blue3 },
	[SchemeStatus]    = { col_black, col_blue3, NULL }, /* border is unused */
	[SchemeTitleNorm] = { col_white, col_black, NULL }, /* border is unused */
	[SchemeTitleSel]  = { col_white, col_black, NULL }, /* border is unused */
};
#elif THEME == BLACK
static const char *fonts[]          = { "Spleen 8x16:pixelsize=16", "UbuntuMono Nerd Font:size=8" };
static const char col_white[]          	 = "#F6F7DA";
static const char col_grey[]          	 = "#777777";
static const char col_black[]            = "#1C2128";
static const char col_i3lock[]            = "#1C2128";
static const char *colors[][3]      = {
	/*                    fg            bg       border   */
	[SchemeNorm]      = { col_grey, col_black, col_black },
	[SchemeSel]       = { col_white, col_black, col_white },
	[SchemeStatus]    = { col_white, col_black, NULL }, /* border is unused */
	[SchemeTitleNorm] = { col_grey, col_black, NULL }, /* border is unused */
	[SchemeTitleSel]  = { col_white, col_black, NULL }, /* border is unused */
};
#endif
