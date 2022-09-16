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
// sound.h -- client sound i/o functions

#ifndef __SOUND_H__
#define __SOUND_H__

#define DEFAULT_SOUND_PACKET_VOLUME 255
#define DEFAULT_SOUND_PACKET_ATTENUATION 1.0

typedef struct
{
	int32_t left;
	int32_t right;
} portable_samplepair_t;

typedef struct sfx_s
{
	char 	name[MAX_QPATH];
	cache_user_t	cache;
} sfx_t;

typedef struct
{
	int32_t 	length;
	int32_t 	loopstart;
	int32_t 	speed;
	int32_t 	width;
	int32_t 	stereo;
	byte	data[1];		// variable sized
} sfxcache_t;

typedef struct
{
	qboolean		gamealive;
	qboolean		soundalive;
	qboolean		splitbuffer;
	int32_t				channels;
	int32_t				samples;				// mono samples in buffer
	int32_t				submission_chunk;		// don't mix less than this #
	int32_t				samplepos;				// in mono samples
	int32_t				samplebits;
	int32_t				speed;
	uint8_t	*buffer;
} dma_t;

typedef struct
{
	sfx_t	*sfx;			// sfx number
	int32_t		leftvol;		// 0-255 volume
	int32_t		rightvol;		// 0-255 volume
	int32_t		end;			// end time in global paintsamples
	int32_t 	pos;			// sample position in sfx
	int32_t		looping;		// where to loop, -1 = no looping
	int32_t		entnum;			// to allow overriding a specific sound
	int32_t		entchannel;		//
	vec3_t	origin;			// origin of sound effect
	vec_t	dist_mult;		// distance multiplier (attenuation/clipK)
	int32_t		master_vol;		// 0-255 master volume
} channel_t;

typedef struct
{
	int32_t		rate;
	int32_t		width;
	int32_t		channels;
	int32_t		loopstart;
	int32_t		samples;
	int32_t		dataofs;		// chunk starts this many bytes from file start
} wavinfo_t;

void S_Init (void);
void S_Startup (void);
void S_Shutdown (void);
void S_StartSound (int32_t entnum, int32_t entchannel, sfx_t *sfx, vec3_t origin, float fvol,  float attenuation);
void S_StaticSound (sfx_t *sfx, vec3_t origin, float vol, float attenuation);
void S_StopSound (int32_t entnum, int32_t entchannel);
void S_StopAllSounds(qboolean clear);
void S_ClearBuffer (void);
void S_Update (vec3_t origin, vec3_t v_forward, vec3_t v_right, vec3_t v_up);
void S_ExtraUpdate (void);

sfx_t *S_PrecacheSound (char *sample);
void S_TouchSound (char *sample);
void S_ClearPrecache (void);
void S_BeginPrecaching (void);
void S_EndPrecaching (void);
void S_PaintChannels(int32_t endtime);
void S_InitPaintChannels (void);

// picks a channel based on priorities, empty slots, number of channels
channel_t *SND_PickChannel(int32_t entnum, int32_t entchannel);

// spatializes a channel
void SND_Spatialize(channel_t *ch);

// initializes cycling through a DMA buffer and returns information on it
qboolean SNDDMA_Init(void);

// gets the current DMA position
int32_t SNDDMA_GetDMAPos(void);

// shutdown the DMA xfer.
void SNDDMA_Shutdown(void);

// ====================================================================
// User-setable variables
// ====================================================================

#define	MAX_CHANNELS			128
#define	MAX_DYNAMIC_CHANNELS	8


extern	channel_t   channels[MAX_CHANNELS];
// 0 to MAX_DYNAMIC_CHANNELS-1	= normal entity sounds
// MAX_DYNAMIC_CHANNELS to MAX_DYNAMIC_CHANNELS + NUM_AMBIENTS -1 = water, etc
// MAX_DYNAMIC_CHANNELS + NUM_AMBIENTS to total_channels = static sounds

extern	int32_t			total_channels;

//
// Fake dma is a synchronous faking of the DMA progress used for
// isolating performance in the renderer.  The fakedma_updates is
// number of times S_Update() is called per second.
//

extern qboolean 		fakedma;
extern int32_t 			fakedma_updates;
extern int32_t		paintedtime;
extern vec3_t listener_origin;
extern vec3_t listener_forward;
extern vec3_t listener_right;
extern vec3_t listener_up;
extern volatile dma_t *shm;
extern volatile dma_t sn;
extern vec_t sound_nominal_clip_dist;

extern	cvar_t loadas8bit;
extern	cvar_t bgmvolume;
extern	cvar_t volume;

extern qboolean	snd_initialized;

extern int32_t		snd_blocked;

void S_LocalSound (char *s);
sfxcache_t *S_LoadSound (sfx_t *s);

wavinfo_t GetWavinfo (char *name, byte *wav, int32_t wavlength);

void SND_InitScaletable (void);
void SNDDMA_Submit(void);

void S_AmbientOff (void);
void S_AmbientOn (void);

#endif
