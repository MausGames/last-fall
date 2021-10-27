/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "main.h"

// TODO 3: make checkpoint handling more efficient (remove unload, even though it uses memory-pools anyway) (e.g. use current state to prevent creation in Ext functions (and remove lambda wrapper))
// TODO 4: find a cleaner way to align commands (related to X and Y)


// ****************************************************************
void cField::__Setup(const coreUint8 iCheckpoint)
{
    coreInt32 X = 0, Y = 0;

    coreUint8 iCurCheckpoint = 0u;
    const auto nCheckpointFunc = [&](const coreInt32 iX, const coreInt32 iY)
    {
        if(iCurCheckpoint == iCheckpoint) this->Unload();
        this->__CreateTileExt(iX, iY, TILE_CHECKPOINT, iCurCheckpoint++);
    };

    nCheckpointFunc      (X,   Y);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   3u);
    this->__CreateTileExt(++X, Y,   2u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(X,   --Y, 1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateEnemExt(X+1, Y+1, 0u, 0.0f, 0.0f, 1.0f);
    this->__CreateEnemExt(X+3, Y+2, 0u, 0.0f, 0.0f, 1.0f);
    this->__CreateTileExt(X,   ++Y, 1u);
    this->__CreateTileExt(X,   ++Y, 1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(X,   --Y, 1u);
    this->__CreateTileExt(++X, Y,   1u);

    nCheckpointFunc      (++X, Y);
    this->__DoorMarker   ();
    this->__CreateTileExt(X+1, Y+1, 1u);
    this->__CreateTileExt(X+1, Y,   2u);
    this->__CreateTileExt(X+1, Y-1, 1u);
    this->__CreateTileExt(X+2, Y+1, 1u);
    this->__CreateTileExt(X+2, Y,   2u);
    this->__CreateTileExt(X+2, Y-1, 1u);
    nCheckpointFunc      (X+3, Y);
    this->__CreateDoorExt(X+3, Y);
    this->__RetrieveLast (&X,  &Y);

    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X-1, Y-1, 4u);
    this->__CreateTileExt(X,   Y-1, 3u);
    this->__CreateTileExt(X+1, Y-1, 4u);
    this->__CreateTileExt(X-1, Y-2, 4u);
    this->__CreateEnemExt(X,   Y-2, 3u, 0.0f*PI, 1.0f, 1.0f*PI);
    this->__CreateEnemExt(X,   Y-2, 3u, 1.0f*PI, 1.0f, 1.0f*PI);
    this->__CreateTileExt(X+1, Y-2, 4u);
    this->__CreateTileExt(X-1, Y-3, 4u);
    this->__CreateTileExt(X,   Y-3, 3u);
    this->__CreateTileExt(X+1, Y-3, 4u);
    this->__CreateTileExt(X,   Y-4, 4u);
    this->__RetrieveLast (&X,  &Y);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);

    nCheckpointFunc      (++X, Y);
    this->__DoorMarker   ();
    this->__CreateEnemExt(X,   Y-3, 2u, 0.0f, 5.0f, 1.2f, coreVector2(0.5f,0.0f));
    this->__CreateEnemExt(X+1, Y-3, 2u, 1.0f, 5.0f, 1.2f, coreVector2(0.5f,0.0f));
    this->__CreateEnemExt(X+2, Y-3, 2u, 2.0f, 5.0f, 1.2f, coreVector2(0.5f,0.0f));
    this->__CreateEnemExt(X+3, Y-3, 2u, 3.0f, 5.0f, 1.2f, coreVector2(0.5f,0.0f));
    this->__CreateEnemExt(X+4, Y-3, 2u, 4.0f, 5.0f, 1.2f, coreVector2(0.5f,0.0f));
    this->__CreateTileExt(X+1, Y+1, 1u);
    this->__CreateTileExt(X+1, Y,   1u);
    this->__CreateTileExt(X+1, Y-1, 1u);
    this->__CreateTileExt(X+1, Y-2, 1u);
    this->__CreateTileExt(X+2, Y+1, 1u);
    this->__CreateTileExt(X+2, Y,   1u);
    this->__CreateTileExt(X+2, Y-1, 2u);
    this->__CreateTileExt(X+2, Y-2, 1u);
    this->__CreateTileExt(X+3, Y+1, 1u);
    this->__CreateTileExt(X+3, Y,   2u);
    this->__CreateTileExt(X+3, Y-1, 2u);
    this->__CreateTileExt(X+3, Y-2, 1u);
    this->__CreateTileExt(X+4, Y+1, 1u);
    this->__CreateTileExt(X+4, Y,   1u);
    this->__CreateTileExt(X+4, Y-1, 1u);
    this->__CreateTileExt(X+4, Y-2, 1u);
    nCheckpointFunc      (X+5, Y-1);
    this->__CreateDoorExt(X+5, Y-1);
    this->__RetrieveLast (&X,  &Y);

    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateEnemExt(X,   Y+1, 2u, 0.0f*PI, 2.0f, 2.5f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X,   Y+1, 2u, 0.0f*PI, 2.0f, 2.5f, coreVector2( 0.25f,0.0f));
    this->__CreateEnemExt(X,   Y+3, 2u, 0.0f*PI, 2.0f, 2.5f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X,   Y+3, 2u, 0.0f*PI, 2.0f, 2.5f, coreVector2( 0.25f,0.0f));
    this->__CreateEnemExt(X,   Y+5, 2u, 0.0f*PI, 2.0f, 2.5f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X,   Y+5, 2u, 0.0f*PI, 2.0f, 2.5f, coreVector2( 0.25f,0.0f));
    this->__CreateEnemExt(X+1, Y+1, 2u, 1.0f*PI, 2.0f, 2.5f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X+1, Y+1, 2u, 1.0f*PI, 2.0f, 2.5f, coreVector2( 0.25f,0.0f));
    this->__CreateEnemExt(X+1, Y+3, 2u, 1.0f*PI, 2.0f, 2.5f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X+1, Y+3, 2u, 1.0f*PI, 2.0f, 2.5f, coreVector2( 0.25f,0.0f));
    this->__CreateEnemExt(X+1, Y+5, 2u, 1.0f*PI, 2.0f, 2.5f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X+1, Y+5, 2u, 1.0f*PI, 2.0f, 2.5f, coreVector2( 0.25f,0.0f));
    this->__CreateTileExt(X,   Y+1, 1u);
    this->__CreateTileExt(X+1, Y+1, 1u);
    this->__CreateTileExt(X,   Y+2, 1u);
    this->__CreateTileExt(X+1, Y+2, 1u);
    this->__CreateTileExt(X,   Y+3, 1u);
    this->__CreateTileExt(X+1, Y+3, 1u);
    this->__CreateTileExt(X,   Y+4, 1u);
    this->__CreateTileExt(X+1, Y+4, 1u);
    this->__CreateTileExt(X,   Y+5, 1u);
    this->__CreateTileExt(X+1, Y+5, 1u);
    this->__CreateTileExt(X,   Y+6, 1u);
    this->__CreateTileExt(X+1, Y+6, 1u);
    this->__CreateTileExt(X,   Y+7, 1u);
    this->__CreateTileExt(X+1, Y+7, 1u);
    this->__CreateTileExt(X+1, Y+8, 4u);
    this->__CreateTileExt(X+1, Y+9, 4u);
    this->__CreateTileExt(X+1, Y+10,4u);
    this->__RetrieveLast (&X,  &Y);

    nCheckpointFunc      (X,   ++Y);
    this->__DoorMarker   ();
    this->__CreateEnemExt(X-3, Y+1, 1u, 0.0f, 6.0f, 1.0f, coreVector2(0.0f,-0.25f));
    this->__CreateEnemExt(X-3, Y+1, 1u, 0.0f, 6.0f, 1.0f, coreVector2(0.0f, 0.25f));
    this->__CreateEnemExt(X-3, Y+2, 1u, 0.5f, 6.0f, 1.0f, coreVector2(0.0f,-0.25f));
    this->__CreateEnemExt(X-3, Y+2, 1u, 0.5f, 6.0f, 1.0f, coreVector2(0.0f, 0.25f));
    this->__CreateEnemExt(X-3, Y+3, 1u, 1.0f, 6.0f, 1.0f, coreVector2(0.0f,-0.25f));
    this->__CreateEnemExt(X-3, Y+3, 1u, 1.0f, 6.0f, 1.0f, coreVector2(0.0f, 0.25f));
    this->__CreateEnemExt(X-3, Y+4, 1u, 1.5f, 6.0f, 1.0f, coreVector2(0.0f,-0.25f));
    this->__CreateEnemExt(X-3, Y+4, 1u, 1.5f, 6.0f, 1.0f, coreVector2(0.0f, 0.25f));
    this->__CreateEnemExt(X-3, Y+5, 1u, 2.0f, 6.0f, 1.0f, coreVector2(0.0f,-0.25f));
    this->__CreateEnemExt(X-3, Y+5, 1u, 2.0f, 6.0f, 1.0f, coreVector2(0.0f, 0.25f));
    this->__CreateTileExt(X-2, Y+1, 1u);
    this->__CreateTileExt(X-1, Y+1, 1u);
    this->__CreateTileExt(X,   Y+1, 2u);
    this->__CreateTileExt(X+1, Y+1, 1u);
    this->__CreateTileExt(X+2, Y+1, 1u);
    this->__CreateTileExt(X-2, Y+2, 1u);
    this->__CreateTileExt(X,   Y+2, 1u);
    this->__CreateTileExt(X+2, Y+2, 1u);
    this->__CreateTileExt(X-2, Y+3, 2u);
    this->__CreateTileExt(X-1, Y+3, 2u);
    this->__CreateTileExt(X,   Y+3, 3u);
    this->__CreateTileExt(X+1, Y+3, 2u);
    this->__CreateTileExt(X+2, Y+3, 2u);
    this->__CreateTileExt(X-2, Y+4, 1u);
    this->__CreateTileExt(X,   Y+4, 1u);
    this->__CreateTileExt(X+2, Y+4, 1u);
    this->__CreateTileExt(X-2, Y+5, 1u);
    this->__CreateTileExt(X-1, Y+5, 1u);
    this->__CreateTileExt(X,   Y+5, 2u);
    this->__CreateTileExt(X+1, Y+5, 1u);
    this->__CreateTileExt(X+2, Y+5, 1u);
    nCheckpointFunc      (X,   Y+6);
    this->__CreateDoorExt(X,   Y+6);
    this->__RetrieveLast (&X,  &Y);

    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(--X, Y,   4u);
    this->__CreateTileExt(--X, Y,   4u);
    this->__CreateTileExt(--X, Y,   4u);
    this->__CreateTileExt(--X, Y,   4u);
    this->__CreateTileExt(--X, Y,   4u);
    this->__CreateTileExt(--X, Y,   4u);

    nCheckpointFunc      (--X, Y);
    this->__DoorMarker   ();
    this->__CreateEnemExt(X-2, Y+1, 0u, 0.0f,  0.0f, -0.0f*PI);
    this->__CreateEnemExt(X-2, Y+1, 3u, 0.0f,  0.7f, -0.9f*PI);
    this->__CreateEnemExt(X-2, Y+1, 3u, 0.0f,  1.4f, -0.9f*PI);
    this->__CreateEnemExt(X-2, Y+1, 3u, 0.0f, -0.7f, -0.9f*PI);
    this->__CreateEnemExt(X-2, Y+1, 3u, 0.0f, -1.4f, -0.9f*PI);
    this->__CreateTileExt(X-1, Y-1, 1u);
    this->__CreateTileExt(X-1, Y,   3u);
    this->__CreateTileExt(X-1, Y+1, 1u);
    this->__CreateTileExt(X-1, Y+2, 1u);
    this->__CreateTileExt(X-2, Y,   2u);
    this->__CreateTileExt(X-2, Y+2, 1u);
    this->__CreateTileExt(X-3, Y,   2u);
    this->__CreateTileExt(X-3, Y+1, 2u);
    this->__CreateTileExt(X-3, Y+2, 3u);
    this->__CreateTileExt(X-4, Y+2, 1u);
    nCheckpointFunc      (X-3, Y+3);
    this->__CreateDoorExt(X-3, Y+3);
    this->__RetrieveLast (&X,  &Y);

    this->__CreateEnemExt(X,   Y+3, 3u, 0.0f*PI,  1.0f,  0.4f*PI);
    this->__CreateEnemExt(X,   Y+3, 3u, 0.0f*PI, -1.0f,  0.4f*PI);
    this->__CreateEnemExt(X,   Y+4, 3u, 0.5f*PI,  1.0f, -0.4f*PI);
    this->__CreateEnemExt(X,   Y+4, 3u, 0.5f*PI, -1.0f, -0.4f*PI);
    this->__CreateEnemExt(X,   Y+5, 3u, 0.0f*PI,  1.0f,  0.4f*PI);
    this->__CreateEnemExt(X,   Y+5, 3u, 0.0f*PI, -1.0f,  0.4f*PI);
    this->__CreateEnemExt(X,   Y+6, 3u, 0.5f*PI,  1.0f, -0.4f*PI);
    this->__CreateEnemExt(X,   Y+6, 3u, 0.5f*PI, -1.0f, -0.4f*PI);
    this->__CreateEnemExt(X,   Y+7, 3u, 0.0f*PI,  1.0f,  0.4f*PI);
    this->__CreateEnemExt(X,   Y+7, 3u, 0.0f*PI, -1.0f,  0.4f*PI);
    this->__CreateEnemExt(X,   Y+8, 3u, 0.5f*PI,  1.0f, -0.4f*PI);
    this->__CreateEnemExt(X,   Y+8, 3u, 0.5f*PI, -1.0f, -0.4f*PI);
    this->__CreateEnemExt(X,   Y+9, 3u, 0.0f*PI,  1.0f,  0.4f*PI);
    this->__CreateEnemExt(X,   Y+9, 3u, 0.0f*PI, -1.0f,  0.4f*PI);
    this->__CreateEnemExt(X,   Y+10,3u, 0.5f*PI,  1.0f, -0.4f*PI);
    this->__CreateEnemExt(X,   Y+10,3u, 0.5f*PI, -1.0f, -0.4f*PI);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    this->__CreateTileExt(X,   ++Y, 4u);
    nCheckpointFunc      (X,   ++Y);

    this->__CreateEnemExt(X+2, Y-1, 2u, 0.0f*PI, 2.0f, -2.55f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X+2, Y-1, 2u, 0.1f*PI, 2.0f, -2.55f, coreVector2( 0.25f,0.0f));
    this->__CreateEnemExt(X+3, Y-1, 2u, 0.2f*PI, 2.0f, -2.55f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X+3, Y-1, 2u, 0.3f*PI, 2.0f, -2.55f, coreVector2( 0.25f,0.0f));
    this->__CreateEnemExt(X+4, Y-1, 2u, 0.4f*PI, 2.0f, -2.55f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X+4, Y-1, 2u, 0.5f*PI, 2.0f, -2.55f, coreVector2( 0.25f,0.0f));
    this->__CreateEnemExt(X+5, Y-1, 2u, 0.6f*PI, 2.0f, -2.55f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X+5, Y-1, 2u, 0.7f*PI, 2.0f, -2.55f, coreVector2( 0.25f,0.0f));
    this->__CreateEnemExt(X+6, Y-1, 2u, 0.8f*PI, 2.0f, -2.55f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X+6, Y-1, 2u, 0.9f*PI, 2.0f, -2.55f, coreVector2( 0.25f,0.0f));
    this->__CreateEnemExt(X+7, Y-1, 2u, 1.0f*PI, 2.0f, -2.55f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X+7, Y-1, 2u, 1.1f*PI, 2.0f, -2.55f, coreVector2( 0.25f,0.0f));
    this->__CreateEnemExt(X+8, Y-1, 2u, 1.2f*PI, 2.0f, -2.55f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X+8, Y-1, 2u, 1.3f*PI, 2.0f, -2.55f, coreVector2( 0.25f,0.0f));
    this->__CreateEnemExt(X+9, Y-1, 2u, 1.4f*PI, 2.0f, -2.55f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X+9, Y-1, 2u, 1.5f*PI, 2.0f, -2.55f, coreVector2( 0.25f,0.0f));
    this->__CreateEnemExt(X+10,Y-1, 2u, 1.6f*PI, 2.0f, -2.55f, coreVector2(-0.25f,0.0f));
    this->__CreateEnemExt(X+10,Y-1, 2u, 1.7f*PI, 2.0f, -2.55f, coreVector2( 0.25f,0.0f));
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(X,   --Y, 4u);

    nCheckpointFunc      (X,   --Y);
    this->__DoorMarker   ();
    this->__CreateEnemExt(X-1, Y-1, 1u, 0.0f, 6.0f, 1.4f, coreVector2(0.0f, 0.25f));
    this->__CreateEnemExt(X-1, Y-1, 1u, 0.0f, 6.0f, 1.4f, coreVector2(0.0f,-0.25f));
    this->__CreateEnemExt(X-1, Y-2, 1u, 0.0f, 6.0f, 1.4f, coreVector2(0.0f, 0.25f));
    this->__CreateEnemExt(X-1, Y-2, 1u, 0.0f, 6.0f, 1.4f, coreVector2(0.0f,-0.25f));
    this->__CreateTileExt(X,   Y-1, 2u);
    this->__CreateTileExt(X+1, Y-1, 2u);
    this->__CreateTileExt(X+2, Y-1, 2u);
    this->__CreateTileExt(X+3, Y-1, 2u);
    this->__CreateTileExt(X+4, Y-1, 4u);
    this->__CreateTileExt(X,   Y-2, 2u);
    this->__CreateTileExt(X+1, Y-2, 2u);
    this->__CreateTileExt(X+2, Y-2, 2u);
    this->__CreateTileExt(X+3, Y-2, 2u);
    this->__CreateTileExt(X+4, Y-2, 3u);
    this->__CreateTileExt(X+4, Y,   2u);
    this->__CreateTileExt(X+4, Y-3, 1u);
    nCheckpointFunc      (X,   Y-3);
    this->__CreateDoorExt(X,   Y-3);
    this->__RetrieveLast (&X,  &Y);

    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateTileExt(X,   --Y, 4u);
    this->__CreateEnemExt(X-1, Y-1, 0u, 0.0f,  0.0f, 0.0f*PI);
    this->__CreateEnemExt(X-1, Y-1, 3u, 0.0f,  0.7f, 0.9f*PI);
    this->__CreateEnemExt(X-1, Y-1, 3u, 0.0f,  1.4f, 0.9f*PI);
    this->__CreateEnemExt(X-1, Y-1, 3u, 0.0f, -0.7f, 0.9f*PI);
    this->__CreateEnemExt(X-1, Y-1, 3u, 0.0f, -1.4f, 0.9f*PI);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);
    this->__CreateTileExt(++X, Y,   4u);

    this->__CreateTileExt(++X, Y,   3u);
    this->__CreateTileExt(++X, Y,   3u);
    this->__CreateTileExt(++X, Y,   3u);
    this->__CreateTileExt(++X, Y,   2u);
    this->__CreateTileExt(++X, Y,   2u);
    this->__CreateTileExt(++X, Y,   2u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);
    this->__CreateTileExt(++X, Y,   1u);

    nCheckpointFunc      (++X, Y);
    this->__DoorMarker   ();
    this->__CreateEnemExt(X+4, Y+3, 4u, 0.0f, 0.0f, 1.0f);
    this->__CreateTileExt(X+1, Y,   4u);
    this->__CreateTileExt(X+2, Y,   4u);
    this->__CreateTileExt(X+3, Y,   4u);
    this->__CreateTileExt(X+4, Y,   4u);
    this->__CreateTileExt(X+1, Y+1, 4u);
    this->__CreateTileExt(X+2, Y+1, 4u);
    this->__CreateTileExt(X+3, Y+1, 4u);
    this->__CreateTileExt(X+4, Y+1, 4u);
    this->__CreateTileExt(X+1, Y+2, 4u);
    this->__CreateTileExt(X+2, Y+2, 4u);
    this->__CreateTileExt(X+3, Y+2, 4u);
    this->__CreateTileExt(X+4, Y+2, 4u);
    this->__CreateTileExt(X+1, Y+3, 4u);
    this->__CreateTileExt(X+2, Y+3, 4u);
    this->__CreateTileExt(X+3, Y+3, 4u);
    this->__CreateTileExt(X+4, Y+3, 4u);
}