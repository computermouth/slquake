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
// vid.h -- video driver defs

#ifndef __VID_H__
#define __VID_H__

#define VID_CBITS	6
#define VID_GRADES	(1 << VID_CBITS)

// a pixel can be one, two, or four bytes
typedef byte pixel_t;

typedef struct vrect_s
{
	int32_t				x,y,width,height;
	struct vrect_s	*pnext;
} vrect_t;

typedef struct
{
	pixel_t			*buffer;		// invisible buffer
	pixel_t			*colormap;		// 256 * VID_GRADES size
	uint16_t	*colormap16;	// 256 * VID_GRADES size
	int32_t				fullbright;		// index of first fullbright color
	uint32_t		rowbytes;	// may be > width if displayed in a window
	uint32_t		width;		
	uint32_t		height;
	float			aspect;		// width / height -- < 0 is taller than wide
	int32_t				numpages;
	int32_t				recalc_refdef;	// if true, recalc vid-based stuff
	pixel_t			*conbuffer;
	int32_t				conrowbytes;
	uint32_t		conwidth;
	uint32_t		conheight;
	pixel_t			*direct;		// direct drawing to framebuffer, if not
									//  NULL
} viddef_t;

extern	viddef_t	vid;				// global video state
extern	uint16_t	d_8to16table[256];
extern	uint32_t	d_8to24table[256];

void	VID_SetPalette (uint8_t *palette);
// called at startup and after any gamma correction

void	VID_ShiftPalette (uint8_t *palette);
// called for bonus and pain flashes, and for underwater color changes

void	VID_Init (uint8_t *palette);
// Called at startup to set up translation tables, takes 256 8 bit RGB values
// the palette data will go away after the call, so it must be copied off if
// the video driver will need it again

void	VID_Shutdown (void);
// Called at shutdown

void	VID_Update (vrect_t *rects);
// flushes the given rectangles from the view buffer to the screen

int32_t VID_SetMode (int32_t modenum, uint8_t *palette);
// sets the mode; only used by the Quake engine for resetting to mode 0 (the
// base mode) on memory allocation failures

void VID_HandlePause (qboolean pause);
// called only on Win32, when pause happens, so the mouse can be released

#endif
