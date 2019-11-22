//-------------------------------------------------------------------------
/*
Copyright (C) 2010-2019 EDuke32 developers and contributors
Copyright (C) 2019 sirlemonhead, Nuke.YKT
This file is part of PCExhumed.
PCExhumed is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License version 2
as published by the Free Software Foundation.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
//-------------------------------------------------------------------------

#ifndef __view_h__
#define __view_h__

#include "build.h"

extern short bSubTitles;
extern short nViewTop;
extern short bClip;
extern short nViewBottom;
extern short nViewRight;
extern short nViewLeft;
extern short besttarget;
extern short bCamera;

void InitView();
void SetView1();
void RefreshBackground();
void DrawView(int smoothRatio);
void MySetView(int x1, int y1, int x2, int y2);
void ResetView();
void NoClip();
void Clip();

int viewSetInterpolation(int32_t *const posptr);
void viewStopInterpolation(const int32_t * const posptr);
void viewDoInterpolations(int smoothRatio);
void viewUpdateInterpolations(void);
void viewRestoreInterpolations(void);

extern fix16_t nDestVertPan[];
extern short dVertPan[];
extern fix16_t nVertPan[];
extern short nQuake[];

extern int nCamerax;
extern int nCameray;
extern int nCameraz;

extern short bTouchFloor;

extern short nChunkTotal;

static inline int angle_interpolate16(int a, int b, int smooth)
{
    return a + mulscale16(((b+1024-a)&2047)-1024, smooth);
}

#endif
