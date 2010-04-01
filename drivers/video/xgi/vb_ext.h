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
 
#ifndef  _VBEXT_
#define  _VBEXT_

struct DWORDREGS {
    ULONG    Eax, Ebx, Ecx, Edx, Esi, Edi, Ebp;
};

struct WORDREGS {
    USHORT    ax, hi_ax, bx, hi_bx, cx, hi_cx, dx, hi_dx, si, hi_si, di ,hi_di, bp, hi_bp;
};

struct BYTEREGS {
    UCHAR   al, ah, hi_al, hi_ah, bl, bh, hi_bl, hi_bh, cl, ch, hi_cl, hi_ch, dl, dh, hi_dl, hi_dh;
};

typedef union   _X86_REGS    {
    struct  DWORDREGS e;    
    struct  WORDREGS x;
    struct  BYTEREGS h;
} X86_REGS, *PX86_REGS;

extern   void     XGI_XG21Fun14( PXGI_HW_DEVICE_INFO pXGIHWDE, PX86_REGS pBiosArguments);
extern   void     XGISetDPMS( PXGI_HW_DEVICE_INFO pXGIHWDE , ULONG VESA_POWER_STATE ) ;
extern   void     XGI_GetSenseStatus( PXGI_HW_DEVICE_INFO HwDeviceExtension , PVB_DEVICE_INFO pVBInfo );
extern   void     XGINew_SetModeScratch ( PXGI_HW_DEVICE_INFO HwDeviceExtension , PVB_DEVICE_INFO pVBInfo ) ;
extern   void 	  ReadVBIOSTablData( UCHAR ChipType , PVB_DEVICE_INFO pVBInfo);
extern   USHORT   XGINew_SenseLCD(PXGI_HW_DEVICE_INFO,PVB_DEVICE_INFO pVBInfo);
#ifdef WIN2000
extern   BOOLEAN  XGI_DySense( PHW_DEVICE_EXTENSION pHWDE , PUCHAR ujConnectStatus );
#endif /* WIN2000 */

#endif
