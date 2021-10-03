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
cTile::cTile()noexcept
: m_iValue        (0u)
, m_iCheckpoint   (0u)
, m_bPressed      (false)
, m_bPressedOld   (false)
, m_fPressedShift (0.0f)
, m_bDisable      (false)
, m_bDisableTime  (0.0f)
{
    this->DefineProgram("object_tile_program");
    this->DefineTexture(0u, "text.png");
    this->DefineModel  ("object_cube.md3");

    this->SetSize       (coreVector3(0.9f * TILE_SCALE * 0.5f, 0.9f * TILE_SCALE * 0.5f, 0.15f * 2.5f));
    this->SetDirection  (coreVector3(0.0f,1.0f,0.0f));
    this->SetOrientation(coreVector3(0.0f,0.0f,1.0f));
}


// ****************************************************************
cTile::~cTile()
{
    
}


// ****************************************************************
void cTile::Render()
{
    this->coreObject3D::Render();
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
        if(m_iCheckpoint == GAME_CHECKPOINT_FINAL)   // TODO: hack
        {
            m_bDisable = true;
        }
    }
    else if(!m_bPressedOld && m_bPressed)
    {
        if(m_iCheckpoint) g_pGame->SetLastCheckpoint(m_iCheckpoint);
    }
    m_bPressedOld = m_bPressed;

    if(m_bDisable)
    {
        m_bDisableTime.Update(3.0f);

        this->SetAlpha(this->GetAlpha() * LERPH3(1.0f, 0.0f, m_bDisableTime));
        if(m_bDisableTime >= 1.0f) this->SetEnabled(CORE_OBJECT_ENABLE_NOTHING);
    }

    if(m_bPressed) m_fPressedShift.UpdateMin( 6.0f, 1.0f);
              else m_fPressedShift.UpdateMax(-6.0f, 0.0f);

    this->SetPosition(coreVector3(this->GetPosition().xy(), -0.15f * 2.5f + LERPH3(0.0f, 1.5f, m_bDisableTime) + m_fPressedShift * -0.05f));

    constexpr coreFloat fFactor = (1.0f/3.0f);

    coreVector2 vTexOffset;
    switch(m_iValue)
    {
    default: ASSERT(false)
    case TILE_CHECKPOINT: vTexOffset = coreVector2(2.0f,2.0f); break;
    case 4u: vTexOffset = coreVector2(0.0f,1.0f); break;
    case 3u: vTexOffset = coreVector2(2.0f,0.0f); break;
    case 2u: vTexOffset = coreVector2(1.0f,0.0f); break;
    case 0u:
    case 1u: vTexOffset = coreVector2(0.0f,0.0f); break;
    }

    this->SetTexSize  (coreVector2(1.0f,1.0f) * fFactor);
    this->SetTexOffset(vTexOffset * fFactor);

    coreVector3 vColor;
    switch(m_iValue)
    {
    default: ASSERT(false)
    case TILE_CHECKPOINT: vColor = coreVector3(1.0f,1.0f,1.0f); break;
    case 4u: vColor = COLOR_BLUE;                  break;
    case 3u: vColor = COLOR_YELLOW;                break;
    case 2u: vColor = COLOR_ORANGE;                break;
    case 0u:
    case 1u: vColor = COLOR_RED;                   break;
    }
    this->SetColor3(LERP(vColor, coreVector3(1.0f,1.0f,1.0f), m_bPressed ? 0.8f : 0.0f));

    this->coreObject3D::Move();
}