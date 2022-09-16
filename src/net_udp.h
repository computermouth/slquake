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
// net_udp.h

#ifndef __NET_UDP_H__
#define __NET_UDP_H__

int32_t  UDP_Init (void);
void UDP_Shutdown (void);
void UDP_Listen (qboolean state);
int32_t  UDP_OpenSocket (int32_t port);
int32_t  UDP_CloseSocket (int32_t socket);
int32_t  UDP_Connect (int32_t socket, struct qsockaddr *addr);
int32_t  UDP_CheckNewConnections (void);
int32_t  UDP_Read (int32_t socket, byte *buf, int32_t len, struct qsockaddr *addr);
int32_t  UDP_Write (int32_t socket, byte *buf, int32_t len, struct qsockaddr *addr);
int32_t  UDP_Broadcast (int32_t socket, byte *buf, int32_t len);
char *UDP_AddrToString (struct qsockaddr *addr);
int32_t  UDP_StringToAddr (char *string, struct qsockaddr *addr);
int32_t  UDP_GetSocketAddr (int32_t socket, struct qsockaddr *addr);
int32_t  UDP_GetNameFromAddr (struct qsockaddr *addr, char *name);
int32_t  UDP_GetAddrFromName (char *name, struct qsockaddr *addr);
int32_t  UDP_AddrCompare (struct qsockaddr *addr1, struct qsockaddr *addr2);
int32_t  UDP_GetSocketPort (struct qsockaddr *addr);
int32_t  UDP_SetSocketPort (struct qsockaddr *addr, int32_t port);

#endif
