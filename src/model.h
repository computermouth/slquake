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

#ifndef __MODEL_H__
#define __MODEL_H__

#include "modelgen.h"
#include "spritegn.h"

/*

d*_t structures are on-disk representations
m*_t structures are in-memory

*/

/*
==============================================================================

BRUSH MODELS

==============================================================================
*/


//
// in memory representation
//

typedef struct
{
	vec3_t		position;
} mvertex_t;

#define	SIDE_FRONT	0
#define	SIDE_BACK	1
#define	SIDE_ON		2


// plane_t structure

typedef struct mplane_s
{
	vec3_t	normal;
	float	dist;
	byte	type;			// for texture axis selection and fast side tests
	byte	signbits;		// signx + signy<<1 + signz<<1
	byte	pad[2];
} mplane_t;

typedef struct texture_s
{
	char		name[16];
	uint32_t	width, height;
	int32_t			anim_total;				// total tenths in sequence ( 0 = no)
	int32_t			anim_min, anim_max;		// time for this frame min <=time< max
	struct texture_s *anim_next;		// in the animation sequence
	struct texture_s *alternate_anims;	// bmodels in frmae 1 use these
	uint32_t	offsets[MIPLEVELS];		// four mip maps stored
} texture_t;


#define	SURF_PLANEBACK		2
#define	SURF_DRAWSKY		4
#define SURF_DRAWSPRITE		8
#define SURF_DRAWTURB		0x10
#define SURF_DRAWTILED		0x20
#define SURF_DRAWBACKGROUND	0x40


typedef struct
{
	uint16_t	v[2];
	uint32_t	cachededgeoffset;
} medge_t;

typedef struct
{
	float		vecs[2][4];
	float		mipadjust;
	texture_t	*texture;
	int32_t			flags;
} mtexinfo_t;

typedef struct msurface_s
{
	int32_t			visframe;		// should be drawn when node is crossed

	int32_t			dlightframe;
	int32_t			dlightbits;

	mplane_t	*plane;
	int32_t			flags;

	int32_t			firstedge;	// look up in model->surfedges[], negative numbers
	int32_t			numedges;	// are backwards edges
	
// surface generation data
	struct surfcache_s	*cachespots[MIPLEVELS];

	int16_t		texturemins[2];
	int16_t		extents[2];

	mtexinfo_t	*texinfo;
	
// lighting info
	byte		styles[MAXLIGHTMAPS];
	byte		*samples;		// [numstyles*surfsize]
} msurface_t;

typedef struct mnode_s
{
// common with leaf
	int32_t			contents;		// 0, to differentiate from leafs
	int32_t			visframe;		// node needs to be traversed if current
	
	int16_t		minmaxs[6];		// for bounding box culling

	struct mnode_s	*parent;

// node specific
	mplane_t	*plane;
	struct mnode_s	*children[2];	

	uint16_t		firstsurface;
	uint16_t		numsurfaces;
} mnode_t;



typedef struct mleaf_s
{
// common with node
	int32_t			contents;		// wil be a negative contents number
	int32_t			visframe;		// node needs to be traversed if current

	int16_t		minmaxs[6];		// for bounding box culling

	struct mnode_s	*parent;

// leaf specific
	byte		*compressed_vis;
	efrag_t		*efrags;

	msurface_t	**firstmarksurface;
	int32_t			nummarksurfaces;
	int32_t			key;			// BSP sequence number for leaf's contents
	byte		ambient_sound_level[NUM_AMBIENTS];
} mleaf_t;


typedef struct
{
	dclipnode_t	*clipnodes;
	mplane_t	*planes;
	int32_t			firstclipnode;
	int32_t			lastclipnode;
	vec3_t		clip_mins;
	vec3_t		clip_maxs;
} hull_t;

/*
==============================================================================

SPRITE MODELS

==============================================================================
*/


// FIXME: shorten these?
typedef struct mspriteframe_s
{
	int32_t		width;
	int32_t		height;
	void	*pcachespot;			// remove?
	float	up, down, left, right;
	byte	pixels[4];
} mspriteframe_t;

typedef struct
{
	int32_t				numframes;
	float			*intervals;
	mspriteframe_t	*frames[1];
} mspritegroup_t;

typedef struct
{
	spriteframetype_t	type;
	mspriteframe_t		*frameptr;
} mspriteframedesc_t;

typedef struct
{
	int32_t					type;
	int32_t					maxwidth;
	int32_t					maxheight;
	int32_t					numframes;
	float				beamlength;		// remove?
	void				*cachespot;		// remove?
	mspriteframedesc_t	frames[1];
} msprite_t;


/*
==============================================================================

ALIAS MODELS

Alias models are position independent, so the cache manager can move them.
==============================================================================
*/

typedef struct
{
	aliasframetype_t	type;
	trivertx_t			bboxmin;
	trivertx_t			bboxmax;
	int32_t					frame;
	char				name[16];
} maliasframedesc_t;

typedef struct
{
	aliasskintype_t		type;
	void				*pcachespot;
	int32_t					skin;
} maliasskindesc_t;

typedef struct
{
	trivertx_t			bboxmin;
	trivertx_t			bboxmax;
	int32_t					frame;
} maliasgroupframedesc_t;

typedef struct
{
	int32_t						numframes;
	int32_t						intervals;
	maliasgroupframedesc_t	frames[1];
} maliasgroup_t;

typedef struct
{
	int32_t					numskins;
	int32_t					intervals;
	maliasskindesc_t	skindescs[1];
} maliasskingroup_t;


typedef struct mtriangle_s {
	int32_t					facesfront;
	int32_t					vertindex[3];
} mtriangle_t;

typedef struct {
	int32_t					model;
	int32_t					stverts;
	int32_t					skindesc;
	int32_t					triangles;
	maliasframedesc_t	frames[1];
} aliashdr_t;

//===================================================================

//
// Whole model
//

typedef enum {mod_brush, mod_sprite, mod_alias} modtype_t;

#define	EF_ROCKET	1			// leave a trail
#define	EF_GRENADE	2			// leave a trail
#define	EF_GIB		4			// leave a trail
#define	EF_ROTATE	8			// rotate (bonus items)
#define	EF_TRACER	16			// green split trail
#define	EF_ZOMGIB	32			// small blood trail
#define	EF_TRACER2	64			// orange split trail + rotate
#define	EF_TRACER3	128			// purple trail

typedef struct model_s
{
	char		name[MAX_QPATH];
	qboolean	needload;		// bmodels and sprites don't cache normally

	modtype_t	type;
	int32_t			numframes;
	synctype_t	synctype;
	
	int32_t			flags;

//
// volume occupied by the model
//		
	vec3_t		mins, maxs;
	float		radius;

//
// brush model
//
	int32_t			firstmodelsurface, nummodelsurfaces;

	int32_t			numsubmodels;
	dmodel_t	*submodels;

	int32_t			numplanes;
	mplane_t	*planes;

	int32_t			numleafs;		// number of visible leafs, not counting 0
	mleaf_t		*leafs;

	int32_t			numvertexes;
	mvertex_t	*vertexes;

	int32_t			numedges;
	medge_t		*edges;

	int32_t			numnodes;
	mnode_t		*nodes;

	int32_t			numtexinfo;
	mtexinfo_t	*texinfo;

	int32_t			numsurfaces;
	msurface_t	*surfaces;

	int32_t			numsurfedges;
	int32_t			*surfedges;

	int32_t			numclipnodes;
	dclipnode_t	*clipnodes;

	int32_t			nummarksurfaces;
	msurface_t	**marksurfaces;

	hull_t		hulls[MAX_MAP_HULLS];

	int32_t			numtextures;
	texture_t	**textures;

	byte		*visdata;
	byte		*lightdata;
	char		*entities;

//
// additional model data
//
	cache_user_t	cache;		// only access through Mod_Extradata

} model_t;

//============================================================================

void	Mod_Init (void);
void	Mod_ClearAll (void);
model_t *Mod_ForName (char *name, qboolean crash);
void	*Mod_Extradata (model_t *mod);	// handles caching
void	Mod_TouchModel (char *name);

mleaf_t *Mod_PointInLeaf (float *p, model_t *model);
byte	*Mod_LeafPVS (mleaf_t *leaf, model_t *model);

#endif	// __MODEL__
