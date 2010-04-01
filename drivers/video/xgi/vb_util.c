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
 
#include "osdef.h"
#include "vb_def.h"
#include "vgatypes.h"
#include "vb_struct.h"

#ifdef LINUX_KERNEL
#include "XGIfb.h"
#include <asm/io.h>
#include <linux/types.h>
#endif

#ifdef TC
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <dos.h>
#endif

#ifdef WIN2000
#include <dderror.h>
#include <devioctl.h>
#include <miniport.h>
#include <ntddvdeo.h>
#include <video.h>

#include "xgiv.h"
#include "dd_i2c.h"
#include "tools.h"
#endif

#ifdef LINUX_XF86
#include "xf86.h"
#include "xf86PciInfo.h"
#include "xgi_regs.h"
#endif




void XGINew_SetReg1( ULONG , USHORT , USHORT ) ;
void XGINew_SetReg2( ULONG , USHORT , USHORT ) ;
void XGINew_SetReg3( ULONG , USHORT ) ;
void XGINew_SetReg4( ULONG , ULONG ) ;
UCHAR XGINew_GetReg1( ULONG , USHORT) ;
UCHAR XGINew_GetReg2( ULONG ) ;
ULONG XGINew_GetReg3( ULONG ) ;
void XGINew_ClearDAC( PUCHAR ) ;
void     XGINew_SetRegANDOR(ULONG Port,USHORT Index,USHORT DataAND,USHORT DataOR);
void     XGINew_SetRegOR(ULONG Port,USHORT Index,USHORT DataOR);
void     XGINew_SetRegAND(ULONG Port,USHORT Index,USHORT DataAND);


/* --------------------------------------------------------------------- */
/* Function : XGINew_SetReg1 */
/* Input : */
/* Output : */
/* Description : SR CRTC GR */
/* --------------------------------------------------------------------- */
void XGINew_SetReg1( ULONG port , USHORT index , USHORT data )
{
#ifdef LINUX_XF86
    OutPortByte( ( PUCHAR )(ULONG)port , index ) ;
    OutPortByte( ( PUCHAR )(ULONG)port + 1 , data ) ;
#else
    OutPortByte( port , index ) ;
    OutPortByte( port + 1 , data ) ;
#endif
}


/* --------------------------------------------------------------------- */
/* Function : XGINew_SetReg2 */
/* Input : */
/* Output : */
/* Description : AR( 3C0 ) */
/* --------------------------------------------------------------------- */
/*void XGINew_SetReg2( ULONG port , USHORT index , USHORT data )
{
    InPortByte( ( PUCHAR )port + 0x3da - 0x3c0 ) ;
    OutPortByte( XGINew_P3c0 , index ) ;
    OutPortByte( XGINew_P3c0 , data ) ;
    OutPortByte( XGINew_P3c0 , 0x20 ) ;
}*/


/* --------------------------------------------------------------------- */
/* Function : */
/* Input : */
/* Output : */
/* Description : */
/* --------------------------------------------------------------------- */
void XGINew_SetReg3( ULONG port , USHORT data )
{
    OutPortByte( port , data ) ;
}


/* --------------------------------------------------------------------- */
/* Function : XGINew_SetReg4 */
/* Input : */
/* Output : */
/* Description : */
/* --------------------------------------------------------------------- */
void XGINew_SetReg4( ULONG port , ULONG data )
{
    OutPortLong( port , data ) ;
}


/* --------------------------------------------------------------------- */
/* Function : XGINew_GetReg1 */
/* Input : */
/* Output : */
/* Description : */
/* --------------------------------------------------------------------- */
UCHAR XGINew_GetReg1( ULONG port , USHORT index )
{
    UCHAR data ;

#ifdef LINUX_XF86
    OutPortByte( ( PUCHAR )(ULONG)port , index ) ;
    data = InPortByte( ( PUCHAR )(ULONG)port + 1 ) ;
#else
    OutPortByte( port , index ) ;
    data = InPortByte( port + 1 ) ;
#endif

    return( data ) ;
}


/* --------------------------------------------------------------------- */
/* Function : XGINew_GetReg2 */
/* Input : */
/* Output : */
/* Description : */
/* --------------------------------------------------------------------- */
UCHAR XGINew_GetReg2( ULONG port )
{
    UCHAR data ;

    data = InPortByte( port ) ;

    return( data ) ;
}


/* --------------------------------------------------------------------- */
/* Function : XGINew_GetReg3 */
/* Input : */
/* Output : */
/* Description : */
/* --------------------------------------------------------------------- */
ULONG XGINew_GetReg3( ULONG port )
{
    ULONG data ;

    data = InPortLong( port ) ;

    return( data ) ;
}



/* --------------------------------------------------------------------- */
/* Function : XGINew_SetRegANDOR */
/* Input : */
/* Output : */
/* Description : */
/* --------------------------------------------------------------------- */
void XGINew_SetRegANDOR( ULONG Port , USHORT Index , USHORT DataAND , USHORT DataOR )
{
    USHORT temp ;

    temp = XGINew_GetReg1( Port , Index ) ;		/* XGINew_Part1Port index 02 */
    temp = ( temp & ( DataAND ) ) | DataOR ;
    XGINew_SetReg1( Port , Index , temp ) ;
}


/* --------------------------------------------------------------------- */
/* Function : XGINew_SetRegAND */
/* Input : */
/* Output : */
/* Description : */
/* --------------------------------------------------------------------- */
void XGINew_SetRegAND(ULONG Port,USHORT Index,USHORT DataAND)
{
    USHORT temp ;

    temp = XGINew_GetReg1( Port , Index ) ;	/* XGINew_Part1Port index 02 */
    temp &= DataAND ;
    XGINew_SetReg1( Port , Index , temp ) ;
}


/* --------------------------------------------------------------------- */
/* Function : XGINew_SetRegOR */
/* Input : */
/* Output : */
/* Description : */
/* --------------------------------------------------------------------- */
void XGINew_SetRegOR( ULONG Port , USHORT Index , USHORT DataOR )
{
    USHORT temp ;

    temp = XGINew_GetReg1( Port , Index ) ;	/* XGINew_Part1Port index 02 */
    temp |= DataOR ;
    XGINew_SetReg1( Port , Index , temp ) ;
}



/* --------------------------------------------------------------------- */
/* Function : */
/* Input : */
/* Output : */
/* Description : */
/* --------------------------------------------------------------------- */
void XGINew_ClearDAC( PUCHAR port )
{
    int i ;

    OutPortByte( port , 0 ) ;
    port++ ;
    for( i = 0 ; i < 256 * 3 ; i++ )
    {
        OutPortByte( port , 0 ) ;
    }
}


/* --------------------------------------------------------------------- */
/* Function : NewDelaySecond */
/* Input : */
/* Output : */
/* Description : */
/* --------------------------------------------------------------------- */
void NewDelaySeconds( int seconds )
{
#ifdef WIN2000
    int j ;
#endif
    int i ;


    for( i = 0 ; i < seconds ; i++ )
    {
#ifdef TC
        delay( 1000 ) ;
#endif

#ifdef WIN2000

        for ( j = 0 ; j < 20000 ; j++ )
            VideoPortStallExecution( 50 ) ;
#endif

#ifdef WINCE_HEADER
#endif

#ifdef LINUX_KERNEL
#endif
    }
}





