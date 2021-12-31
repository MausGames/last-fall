/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#include "main.h"


// ****************************************************************
cDoor::cDoor()noexcept
: coreObject3D   ()
, m_iCheckFrom   (0u)
, m_iCheckTo     (0u)
, m_bDisable     (false)
, m_fDisableTime (0.0f)
{
    this->DefineModel  ("object_cube.md3");
    this->DefineProgram("object_door_program");

    this->SetSize  (coreVector3(1.0f,1.0f,1.0f) * DOOR_SCALE);
    this->SetColor3(coreVector3(0.2f,0.2f,0.2f));
}


// ****************************************************************
void cDoor::Move()
{
    if(!this->IsEnabled(CORE_OBJECT_ENABLE_MOVE)) return;

    if(!m_bDisable)
    {
        const coreUint32 iTotal = g_pGame->GetField()->CalculateTileValue(m_iCheckFrom, m_iCheckTo);
        if(iTotal <= 1u) m_bDisable = true;
    }

    if(m_bDisable)
    {
        m_fDisableTime.Update(3.0f);

        this->SetAlpha(this->GetAlpha() * LERPH3(1.0f, 0.0f, m_fDisableTime));   // # base-value set by field class
        if(m_fDisableTime >= 1.0f) this->SetEnabled(CORE_OBJECT_ENABLE_NOTHING);
    }

    const coreFloat fScale = LERPH3(1.0f, 1.1f, m_fDisableTime);

    this->SetPosition(coreVector3(this->GetPosition().xy(), DOOR_SCALE));
    this->SetSize    (coreVector3(1.0f,1.0f,1.0f) * DOOR_SCALE * fScale);

    this->coreObject3D::Move();
}