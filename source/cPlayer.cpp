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
cPlayer::cPlayer()noexcept
: m_vVelocity       (coreVector2(0.0f,0.0f))
, m_fVelocityHeight (0.0f)
, m_bFalling        (false)
, m_bLanding        (true)
{
    this->DefineProgram("object_player_program");
    this->DefineModel  ("object_player.md3");

    this->SetSize  (coreVector3(1.0f,1.0f,1.0f) * PLAYER_SCALE);
    this->SetColor3(coreVector3(0.8f,0.8f,0.8f));

    m_Shadow.DefineModel  ("default_sphere.md3");
    m_Shadow.DefineProgram("shadow_object_program");
    m_Shadow.SetSize      (coreVector3(0.99f,0.99f,3.0f) * 0.95f);
}


// ****************************************************************
cPlayer::~cPlayer()
{
    
}


// ****************************************************************
void cPlayer::Render()
{
    this->coreObject3D::Render();
}


// ****************************************************************
void cPlayer::Move()
{
    coreVector2 vMove = coreVector2(0.0f,0.0f);

         if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(D), CORE_INPUT_HOLD) || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(RIGHT), CORE_INPUT_HOLD)) vMove.x =  1.0f;
    else if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(A), CORE_INPUT_HOLD) || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(LEFT),  CORE_INPUT_HOLD)) vMove.x = -1.0f;
         if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(W), CORE_INPUT_HOLD) || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(UP),    CORE_INPUT_HOLD)) vMove.y =  1.0f;
    else if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(S), CORE_INPUT_HOLD) || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(DOWN),  CORE_INPUT_HOLD)) vMove.y = -1.0f;

    Core::Input->ForwardHatToStick(0u);
    vMove += Core::Input->GetJoystickRelativeL(0u);

    if(!vMove.IsNull()) vMove = vMove.Normalized();

    if(!m_bFalling) m_vVelocity += vMove * (PLAYER_ACCELERATION * TIME);
    if(!m_vVelocity.IsNull()) m_vVelocity *= POW(1.0f - PLAYER_BRAKE * (1.0f/60.0f) * (m_bFalling ? 0.2f : 1.0f), TIME * 60.0f);

    const coreVector2 vNewPos = this->GetPosition().xy() + m_vVelocity * TIME;

    m_fVelocityHeight += -1.0f * (PLAYER_ACCELERATION_HEIGHT * TIME);
    if(m_fVelocityHeight) m_fVelocityHeight *= POW(1.0f - PLAYER_BRAKE_HEIGHT * (1.0f/60.0f), TIME * 60.0f);

    const coreFloat fNewHeight = this->GetPosition().z + m_fVelocityHeight * TIME;

    this->SetPosition(coreVector3(vNewPos, fNewHeight));

    if(m_vVelocity.LengthSq() >= CORE_MATH_PRECISION)
    {
        const coreMatrix3 mRota = coreMatrix4::RotationAxis(m_vVelocity.Length() * TIME * -1.1f, coreVector3(m_vVelocity.Rotated90().Normalized(), 0.0f)).m123();

        this->SetDirection  (this->GetDirection  () * mRota);
        this->SetOrientation(this->GetOrientation() * mRota);
    }

    this->coreObject3D::Move();

    m_Shadow.SetPosition(this->GetPosition());
}


// ****************************************************************
void cPlayer::RenderShadow()
{
    if(this->GetPosition().z > 10.0f) return;   // to prevent shadow flickering on teleportation
    m_Shadow.Render();
}


// ****************************************************************
void cPlayer::Land()
{
    if(!m_bFalling)
    {
        if(this->GetPosition().z <= PLAYER_SCALE && m_fVelocityHeight <= 0.0f)
        {
            m_fVelocityHeight = 0.0f;
            this->SetPosition(coreVector3(this->GetPosition().xy(), PLAYER_SCALE));
        }
    }
}
