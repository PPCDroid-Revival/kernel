/*
 * XG20, XG21, XG40, XG42 frame buffer device
 * for Linux kernels  2.5.x, 2.6.x
 * Base on TW's sis fbdev code.
 */

/* frame buffer driver for Linux kernels >= 2.4.14 and >=2.6.3
 *
 * Copyright (C) 2001-2005 Thomas Winischhofer, Vienna, Austria.
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
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Author:	Thomas Winischhofer <thomas@winischhofer.net>
 *
 * Author of (practically wiped) code base:
 *		SiS (www.sis.com)
 *		Copyright (C) 1999 Silicon Integrated Systems, Inc.
 *
 * See http://www.winischhofer.net/ for more information and updates
 *
 * Originally based on the VBE 2.0 compliant graphic boards framebuffer driver,
 * which is (c) 1998 Gerd Knorr <kraxel@goldbach.in-berlin.de>
 *
 */


#ifndef _LINUX_XGIFB
#define _LINUX_XGIFB
#include <linux/spinlock.h>
#include <asm/ioctl.h>
#include <asm/types.h>

#define DISPTYPE_CRT1       0x00000008L
#define DISPTYPE_CRT2       0x00000004L
#define DISPTYPE_LCD        0x00000002L
#define DISPTYPE_TV         0x00000001L
#define DISPTYPE_DISP1      DISPTYPE_CRT1
#define DISPTYPE_DISP2      (DISPTYPE_CRT2 | DISPTYPE_LCD | DISPTYPE_TV)
#define DISPMODE_SINGLE	    0x00000020L
#define DISPMODE_MIRROR	    0x00000010L
#define DISPMODE_DUALVIEW   0x00000040L

#define HASVB_NONE      	0x00
#define HASVB_301       	0x01
#define HASVB_LVDS      	0x02
#define HASVB_TRUMPION  	0x04
#define HASVB_LVDS_CHRONTEL	0x10
#define HASVB_302       	0x20
#define HASVB_303       	0x40
#define HASVB_CHRONTEL  	0x80

#ifndef XGIFB_ID
#define XGIFB_ID          0x53495346    /* Identify myself with 'XGIF' */
#endif

typedef enum _XGI_CHIP_TYPE {
    XGI_VGALegacy = 0,
    XGI_300,
    XGI_630,
    XGI_730,
    XGI_540,
    XGI_315H,   
    XGI_315,
    XGI_315PRO, 
    XGI_550,
    XGI_640,
    XGI_740,
    XGI_650,
    XGI_650M,
    XGI_330 = 16,
    XGI_660,
    XGI_661,
    XGI_760,
    XG40 = 32,
    XG41,
    XG42,
    XG45,
    XG20 = 48,
    XG21,
    XG27,
    MAX_XGI_CHIP
} XGI_CHIP_TYPE;

typedef enum _TVTYPE {
	TVMODE_NTSC = 0,
	TVMODE_PAL,
	TVMODE_HIVISION,
	TVTYPE_PALM,	// vicki@030226
    	TVTYPE_PALN,	// vicki@030226
    	TVTYPE_NTSCJ,	// vicki@030226	
	TVMODE_TOTAL
} XGI_TV_TYPE;


typedef struct _XGIFB_INFO XGIfb_info;
struct _XGIFB_INFO {

unsigned long XGIfb_id;         
 	int    chip_id;			/* PCI ID of detected chip */
	int    memory;			/* video memory in KB which XGIfb manages */
	int    heapstart;               /* heap start (= XGIfb "mem" argument) in KB */
	unsigned char fbvidmode;	/* current XGIfb mode */
	
	unsigned char XGIfb_version;
	unsigned char XGIfb_revision;
	unsigned char XGIfb_patchlevel;

	unsigned char XGIfb_caps;	/* XGIfb capabilities */

	int    XGIfb_tqlen;		/* turbo queue length (in KB) */

	unsigned int XGIfb_pcibus;      /* The card's PCI ID */
	unsigned int XGIfb_pcislot;
	unsigned int XGIfb_pcifunc;

	unsigned char XGIfb_lcdpdc;	/* PanelDelayCompensation */
	
	unsigned char XGIfb_lcda;	/* Detected status of LCDA for low res/text modes */

	char reserved[235]; 		/* for future use */
};




typedef enum _TVPLUGTYPE {	// vicki@030226
//	TVPLUG_Legacy = 0,
//	TVPLUG_COMPOSITE,
//	TVPLUG_SVIDEO,
//	TVPLUG_SCART,
//	TVPLUG_TOTAL
    	TVPLUG_UNKNOWN = 0,
    	TVPLUG_COMPOSITE = 1,
    	TVPLUG_SVIDEO = 2,
    	TVPLUG_COMPOSITE_AND_SVIDEO = 3,
    	TVPLUG_SCART = 4,
    	TVPLUG_YPBPR_525i = 5,
    	TVPLUG_YPBPR_525P = 6,
    	TVPLUG_YPBPR_750P = 7,
    	TVPLUG_YPBPR_1080i = 8,
	TVPLUG_TOTAL
} XGI_TV_PLUG;


struct mode_info {
	int    bpp;
	int    xres;
	int    yres;
	int    v_xres;
	int    v_yres;
	int    org_x;
	int    org_y;
	unsigned int  vrate;
};

struct ap_data {
	struct mode_info minfo;
	unsigned long iobase;
	unsigned int  mem_size;
	unsigned long disp_state;    	
	XGI_CHIP_TYPE chip;
	unsigned char hasVB;
	XGI_TV_TYPE TV_type;
	XGI_TV_PLUG TV_plug;
	unsigned long version;
	char reserved[256];
};



/*     If changing this, vgatypes.h must also be changed (for X driver)    */


/*
 * NOTE! The ioctl types used to be "size_t" by mistake, but were
 * really meant to be __u32. Changed to "__u32" even though that
 * changes the value on 64-bit architectures, because the value
 * (with a 4-byte size) is also hardwired in vgatypes.h for user
 * space exports. So "__u32" is actually more compatible, duh!
 */
#define XGIFB_GET_INFO	  	_IOR('n',0xF8,__u32)
#define XGIFB_GET_VBRSTATUS  	_IOR('n',0xF9,__u32)



struct video_info{
        int           chip_id;
        unsigned int  video_size;
        resource_size_t video_base;
        char  *       video_vbase;
        resource_size_t  mmio_base;
        char  *       mmio_vbase;
        resource_size_t vga_base;
        unsigned long mtrr;
        unsigned long heapstart;
                                                                                
        int    video_bpp;
        int    video_cmap_len;
        int    video_width;
        int    video_height;
        int    video_vwidth;
        int    video_vheight;
        int    org_x;
        int    org_y;
        int    video_linelength;
        unsigned int refresh_rate;
                                                                                
        unsigned long disp_state;
        unsigned char hasVB;
        unsigned char TV_type;
        unsigned char TV_plug;
                                                                                
        XGI_CHIP_TYPE chip;
        unsigned char revision_id;
                                                                                
        unsigned short DstColor;             
        unsigned long  XGI310_AccelDepth;
        unsigned long  CommandReg;
                                                                                
        spinlock_t     lockaccel;
                                                                                
        unsigned int   pcibus;
        unsigned int   pcislot;
        unsigned int   pcifunc;
                                                                                
        int            accel;
        unsigned short subsysvendor;
        unsigned short subsysdevice;
                                                                                
        char reserved[236];
};


extern struct video_info xgi_video_info;
                                                                                
#ifdef __KERNEL__
//extern void xgi_malloc(struct xgi_memreq *req);
extern void xgi_free(unsigned long base);
extern void xgi_dispinfo(struct ap_data *rec);
#endif
#endif
