//////////////////////////////////////////////////////////////////////////////////
//*----------------------------------------------------------------------------*//
//| Last Fall v1.2.0 (https://www.maus-games.at)                               |//
//*----------------------------------------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics                                        |//
//|                                                                            |//
//| This software is provided 'as-is', without any express or implied          |//
//| warranty. In no event will the authors be held liable for any damages      |//
//| arising from the use of this software.                                     |//
//|                                                                            |//
//| Permission is granted to anyone to use this software for any purpose,      |//
//| including commercial applications, and to alter it and redistribute it     |//
//| freely, subject to the following restrictions:                             |//
//|                                                                            |//
//| 1. The origin of this software must not be misrepresented; you must not    |//
//|    claim that you wrote the original software. If you use this software    |//
//|    in a product, an acknowledgment in the product documentation would be   |//
//|    appreciated but is not required.                                        |//
//|                                                                            |//
//| 2. Altered source versions must be plainly marked as such, and must not be |//
//|    misrepresented as being the original software.                          |//
//|                                                                            |//
//| 3. This notice may not be removed or altered from any source distribution. |//
//*----------------------------------------------------------------------------*//
//////////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef _LAF_GUARD_MAIN_H_
#define _LAF_GUARD_MAIN_H_


// ****************************************************************
// engine headers
#include "Core.h"


// ****************************************************************
// general definitions
#define CAMERA_POSITION    (coreVector3(0.0f,-1.0f, 1.0f).Normalized() * 50.0f)
#define CAMERA_DIRECTION   (coreVector3(0.0f, 1.0f,-1.0f).Normalized())
#define CAMERA_ORIENTATION (coreVector3(0.0f, 0.0f, 1.0f))


// ****************************************************************
// game headers
#include "cPlayer.h"
#include "cEnemy.h"
#include "cTile.h"
#include "cDoor.h"
#include "cField.h"
#include "cInterface.h"
#include "cGame.h"
#include "cShadow.h"


// ****************************************************************
// global variables
extern cInterface* const g_pInterface;
extern cGame*      const g_pGame;
extern cShadow*    const g_pShadow;


#endif // _LAF_GUARD_MAIN_H_