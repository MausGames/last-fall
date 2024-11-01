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
cPlayer::cPlayer()noexcept
: coreObject3D      ()
, m_vVelocity       (coreVector2(0.0f,0.0f))
, m_fVelocityHeight (0.0f)
, m_bFalling        (false)
, m_bLanding        (true)
{
    this->DefineModel  ("object_player.md3z");
    this->DefineProgram("object_player_program");

    this->SetSize  (coreVector3(1.0f,1.0f,1.0f) * PLAYER_SCALE);
    this->SetColor3(coreVector3(0.8f,0.8f,0.8f));

    m_Shadow.DefineModel  ("default_sphere.md3z");
    m_Shadow.DefineProgram("shadow_object_program");
    m_Shadow.SetSize      (coreVector3(1.0f,1.0f,1.0f) * 0.95f);
}


// ****************************************************************
void cPlayer::Move()
{
    coreVector2 vMove = coreVector2(0.0f,0.0f);

    if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(D), CORE_INPUT_HOLD) || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(RIGHT), CORE_INPUT_HOLD)) vMove.x += 1.0f;
    if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(A), CORE_INPUT_HOLD) || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(LEFT),  CORE_INPUT_HOLD)) vMove.x -= 1.0f;
    if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(W), CORE_INPUT_HOLD) || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(UP),    CORE_INPUT_HOLD)) vMove.y += 1.0f;
    if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(S), CORE_INPUT_HOLD) || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(DOWN),  CORE_INPUT_HOLD)) vMove.y -= 1.0f;

    Core::Input->ForwardHatToStick(CORE_INPUT_JOYSTICK_ANY);

    const coreVector2 vStick = Core::Input->GetJoystickStickL(CORE_INPUT_JOYSTICK_ANY);
    vMove += coreVector2::Direction(ROUND(vStick.Angle() / (0.25f*PI)) * (0.25f*PI)) * vStick.Length();

    if(!vMove.IsNull()) vMove = vMove.Normalized();

    m_vVelocity       += vMove * (PLAYER_ACCELERATION        * TIME) * (m_bFalling ? 0.0f : 1.0f);
    m_fVelocityHeight += -1.0f * (PLAYER_ACCELERATION_HEIGHT * TIME);

    if(!m_vVelocity.IsNull()) m_vVelocity       *= POW(1.0f - PLAYER_BRAKE        * (1.0f/60.0f) * (m_bFalling ? 0.2f : 1.0f), 60.0f * TIME);
    if(m_fVelocityHeight)     m_fVelocityHeight *= POW(1.0f - PLAYER_BRAKE_HEIGHT * (1.0f/60.0f),                              60.0f * TIME);

    const coreVector2 vNewPos    = this->GetPosition().xy() + m_vVelocity       * TIME;
    const coreFloat   fNewHeight = this->GetPosition().z    + m_fVelocityHeight * TIME;

    this->SetFullPosition(coreVector3(vNewPos, fNewHeight));

    if(m_vVelocity.LengthSq() >= CORE_MATH_PRECISION)
    {
        const coreMatrix3 mRota = coreMatrix4::RotationAxis(m_vVelocity.Length() * TIME * -1.1f, coreVector3(m_vVelocity.Rotated90().Normalized(), 0.0f)).m123();

        this->SetDirection  ((this->GetDirection  () * mRota).Normalized());
        this->SetOrientation((this->GetOrientation() * mRota).Normalized());
    }

    this->coreObject3D::Move();

    m_Shadow.Move();
}


// ****************************************************************
void cPlayer::RenderShadow()
{
    m_Shadow.Render();
}


// ****************************************************************
void cPlayer::Land()
{
    if(m_bFalling) return;

    if((m_fVelocityHeight <= 0.0f) && (this->GetPosition().z <= PLAYER_SCALE))
    {
        m_fVelocityHeight = 0.0f;
        this->SetFullPosition(coreVector3(this->GetPosition().xy(), PLAYER_SCALE));
    }
}


// ****************************************************************
void cPlayer::SetFullPosition(const coreVector3 vPosition)
{
    this   ->SetPosition(vPosition);
    m_Shadow.SetPosition(vPosition + coreVector3(0.0f, 0.0f, -PLAYER_SCALE));
}