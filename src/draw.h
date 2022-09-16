/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

// draw.h -- these are the only functions outside the refresh allowed
// to touch the vid buffer

#ifndef __DRAW_H__
#define __DRAW_H__

extern	qpic_t		*draw_disc;	// also used on sbar

void Draw_Init (void);
void Draw_Character (int32_t x, int32_t y, int32_t num);
void Draw_DebugChar (char num);
void Draw_Pic (int32_t x, int32_t y, qpic_t *pic);
void Draw_TransPic (int32_t x, int32_t y, qpic_t *pic);
void Draw_TransPicTranslate (int32_t x, int32_t y, qpic_t *pic, byte *translation);
void Draw_ConsoleBackground (int32_t lines);
void Draw_BeginDisc (void);
void Draw_EndDisc (void);
void Draw_TileClear (int32_t x, int32_t y, int32_t w, int32_t h);
void Draw_Fill (int32_t x, int32_t y, int32_t w, int32_t h, int32_t c);
void Draw_FadeScreen (void);
void Draw_String (int32_t x, int32_t y, char *str);
qpic_t *Draw_PicFromWad (char *name);
qpic_t *Draw_CachePic (char *path);

#endif
