/* See LICENSE file for copyright and license details. */
#define TERMINAL "st"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 0;       /* snap pixel */
static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;       /* vert inner gap between windows */
static const unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:pixelsize=19:antialias=true:autohint=true" };

static const char dmenufont[]       = "JetBrainsMono Nerd Font:pixelsize=19:antialias=true:autohint=true";
//background color
static const char col_gray1[]       = "#1D2021"; 
//inactive window border color
static const char col_gray2[]       = "#282828"; 
//font color
static const char col_gray3[]       = "#aaaaaa"; 
//current tag font color
static const char col_gray4[]       = "#ffffff"; 
//top bar color
static const char col_cyan_bg[]     = "#1D2021"; 
//selelected border color
static const char col_cyan[]      = "#30b27a"; 
static const char *colors[][3]      = {
  /*               fg         bg         border   */
  [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
  [SchemeSel]  = { col_gray4, col_cyan_bg,  col_cyan  },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "flameshot",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "qemu-system-x86_64",    NULL,     NULL,           1,         0,          1,           1,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },         //t  
	{ "[M]",      monocle },      
	{ "[@]",      spiral },       //n
	{ "[\\]",     dwindle },      //
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid }, //shift g
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             XK_Return, spawn,          {.v = termcmd } },
  { MODKEY|ShiftMask,             XK_r,      spawn,      SHCMD(TERMINAL " -e htop") },
  { MODKEY|ShiftMask,             XK_b,      spawn,      SHCMD(TERMINAL " -e pulsemixer") },
  { MODKEY,                       XK_y,      spawn,      SHCMD(TERMINAL " -e ncmpcpp") },
  { MODKEY,                       XK_r,      spawn,      SHCMD(TERMINAL " -e lf") },
  { MODKEY|ShiftMask,             XK_e,      spawn,      SHCMD("flameshot gui") },
  { MODKEY|ShiftMask,             XK_d,      spawn,      SHCMD("discord") },
  { MODKEY,                       XK_w,      spawn,      SHCMD("firefox") },

  { MODKEY,     XK_period,       spawn,       SHCMD("mpc next") },
  { MODKEY,     XK_comma,        spawn,               SHCMD("mpc prev") },
  { MODKEY,     XK_p,        spawn,   SHCMD("mpc toggle")},
  { MODKEY,     XK_bracketleft,      spawn,   SHCMD("mpc seek -10") },
  { MODKEY,     XK_bracketright,     spawn,   SHCMD("mpc seek +10") },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,			                  XK_z,		incrgaps,	{.i = +3 } },
	{ MODKEY,			                  XK_x,		incrgaps,	{.i = -3 } },
	{ MODKEY|Mod4Mask,              XK_a,      togglegaps,     {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[13]} },
	{ MODKEY,                       XK_n,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[11]} },
	{ MODKEY|ShiftMask,             XK_g,      setlayout,      {.v = &layouts[7]} },
  { MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating,      {0} },
  { MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 80y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -80y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "80x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-80x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 80h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -80h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 80w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -80w 0h" } },
	{ MODKEY,                       XK_m,      focusmon,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_m, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
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

