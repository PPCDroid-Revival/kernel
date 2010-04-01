 /*
 * linux/drivers/video/xgi/vb_setmode.c
 *
 * Frame Buffer Device for XGI Z7 Z9 Z9s Z9m Z11 Z11m
 *
 * Copyright (C) 2003-2009, XGI Technology inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the named License,
 * or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
 
#ifndef _VBUTIL_
#define _VBUTIL_
extern   void     NewDelaySeconds( int );
extern   void     XGINew_SetReg1(ULONG, USHORT, USHORT);
extern   void     XGINew_SetReg3(ULONG, USHORT);
extern   UCHAR    XGINew_GetReg1(ULONG, USHORT);
extern   UCHAR    XGINew_GetReg2(ULONG);
extern   void     XGINew_SetReg4(ULONG, ULONG);
extern   ULONG    XGINew_GetReg3(ULONG);
extern   void     XGINew_ClearDAC( PUCHAR ) ;
extern   void     XGINew_SetRegOR(ULONG Port,USHORT Index,USHORT DataOR);
extern   void     XGINew_SetRegAND(ULONG Port,USHORT Index,USHORT DataAND);
extern   void     XGINew_SetRegANDOR(ULONG Port,USHORT Index,USHORT DataAND,USHORT DataOR);
#endif

