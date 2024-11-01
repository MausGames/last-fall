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
cTile::cTile()noexcept
: coreObject3D    ()
, m_iValue        (0u)
, m_iCheckpoint   (0u)
, m_bPressed      (false)
, m_bPressedOld   (false)
, m_fPressedShift (0.0f)
, m_bDisable      (false)
, m_fDisableTime  (0.0f)
{
    this->DefineModel  ("object_cube.md3z");
    this->DefineTexture(0u, "text.webp");
    this->DefineProgram("object_tile_program");

    this->SetSize       (coreVector3(0.45f * TILE_SCALE, 0.45f * TILE_SCALE, 0.375f));
    this->SetDirection  (coreVector3(0.0f,1.0f,0.0f));
    this->SetOrientation(coreVector3(0.0f,0.0f,1.0f));
    this->SetTexSize    (coreVector2(1.0f,1.0f) * TILE_TEXSIZE);
}


// ****************************************************************
void cTile::Move()
{
    if(!this->IsEnabled(CORE_OBJECT_ENABLE_MOVE)) return;

    if(m_bPressedOld && !m_bPressed)
    {
        if(m_iValue && (m_iValue != TILE_CHECKPOINT))
        {
            m_iValue -= 1u;
            if(!m_iValue) m_bDisable = true;
        }
        else if(m_iCheckpoint == g_pGame->GetField()->GetFinalCheckpoint())
        {
            m_bDisable = true;
        }
    }
    else if(!m_bPressedOld && m_bPressed)
    {
        if(m_iValue == TILE_CHECKPOINT) g_pGame->SetLastCheckpoint(m_iCheckpoint);
    }

    m_bPressedOld = m_bPressed;

    if(m_bDisable)
    {
        m_fDisableTime.Update(3.0f);
        if(m_fDisableTime >= 1.0f) this->SetEnabled(CORE_OBJECT_ENABLE_NOTHING);

        this->SetAlpha(this->GetAlpha() * LERPH3(1.0f, 0.0f, m_fDisableTime));   // # base-value set by field class
    }

    if(m_bPressed) m_fPressedShift.UpdateMin( 6.0f, 1.0f);
              else m_fPressedShift.UpdateMax(-6.0f, 0.0f);

    const coreFloat fHeight = -0.375f + LERPH3(0.0f, 1.5f, m_fDisableTime) + LERPH3(0.0f, -0.05f, m_fPressedShift);

    this->SetPosition(coreVector3(this->GetPosition().xy(), fHeight));

    coreVector3 vColor;
    coreVector2 vTexOffset;
    switch(m_iValue)
    {
    default: UNREACHABLE
    case 0u:
    case 1u:              vColor = coreVector3(1.000f,0.275f,0.275f); /*COLOR_RED;   */ vTexOffset = coreVector2(0.0f,0.0f); break;
    case 2u:              vColor = coreVector3(1.000f,0.543f,0.227f); /*COLOR_ORANGE;*/ vTexOffset = coreVector2(1.0f,0.0f); break;
    case 3u:              vColor = coreVector3(1.000f,0.824f,0.292f); /*COLOR_YELLOW;*/ vTexOffset = coreVector2(2.0f,0.0f); break;
    case 4u:              vColor = coreVector3(0.102f,0.702f,1.000f); /*COLOR_BLUE;  */ vTexOffset = coreVector2(0.0f,1.0f); break;
    case TILE_CHECKPOINT: vColor = coreVector3(1.000f,1.000f,1.000f); /*COLOR_WHITE; */ vTexOffset = coreVector2(2.0f,2.0f); break;
    }

    this->SetColor3   (LERP(vColor, COLOR_WHITE, m_bPressed ? 0.8f : 0.0f));
    this->SetTexOffset(vTexOffset * TILE_TEXSIZE);

    this->coreObject3D::Move();
}