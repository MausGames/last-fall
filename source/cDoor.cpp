/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "main.h"


// ****************************************************************
cDoor::cDoor()noexcept
: m_iCheckStart  (0u)
, m_iCheckEnd    (0u)
, m_bDisable     (false)
, m_bDisableTime (0.0f)
{
    this->DefineProgram("object_door_program");
    this->DefineTexture(0u, "text.png");
    this->DefineModel  ("object_cube.md3");

    constexpr coreFloat fFactor = (1.0f/3.0f);

    this->SetSize     (coreVector3(1.0f,1.0f,1.0f) * DOOR_SCALE);
    this->SetColor3   (coreVector3(0.2f,0.2f,0.2f));
    this->SetTexSize  (coreVector2(1.0f,1.0f) * fFactor);
    this->SetTexOffset(coreVector2(1.0f,1.0f) * fFactor);
}


// ****************************************************************
cDoor::~cDoor()
{
    
}


// ****************************************************************
void cDoor::Render()
{
    this->coreObject3D::Render();
}


// ****************************************************************
void cDoor::Move()
{
    if(!this->IsEnabled(CORE_OBJECT_ENABLE_MOVE)) return;

    coreUint32 iTotal = 0u;

    const coreList<cTile*>* pTileList = g_pGame->GetField()->GetTileList();
    for(coreUintW i = m_iCheckStart, ie = m_iCheckEnd; i < ie; ++i)
    {
        const coreUint8 iValue = (*pTileList)[i]->GetValue();

        if(iValue != TILE_CHECKPOINT) iTotal += iValue;
    }

    if(iTotal <= 1u)
    {
        m_bDisable = true;
    }

    if(m_bDisable)
    {
        m_bDisableTime.Update(3.0f);

        this->SetAlpha(this->GetAlpha() * LERPH3(1.0f, 0.0f, m_bDisableTime));
        if(m_bDisableTime >= 1.0f) this->SetEnabled(CORE_OBJECT_ENABLE_NOTHING);
    }

    this->SetPosition(coreVector3(this->GetPosition().xy(), DOOR_SCALE));
    this->SetSize    (coreVector3(1.0f,1.0f,1.0f) * DOOR_SCALE * LERPH3(1.0f, 1.1f, m_bDisableTime));

    this->coreObject3D::Move();
}