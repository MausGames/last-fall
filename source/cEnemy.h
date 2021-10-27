/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _LAF_GUARD_ENEMY_H_
#define _LAF_GUARD_ENEMY_H_


// ****************************************************************
#define ENEMY_SCALE (1.2f)


// ****************************************************************
class cEnemy final : public coreObject3D
{
private:
    coreFlow m_fRotation;
    coreFlow m_fBump;

    coreBool m_bDisable;
    coreFlow m_fDisableTime;

    coreUint8   m_iType;
    coreFlow    m_fJobTime;     // time offset
    coreFloat   m_fJobOffset;   // move offset
    coreFloat   m_fJobSpeed;
    coreVector2 m_vJobPosition;
    coreVector2 m_vJobVelocity;


public:
    cEnemy()noexcept;

    DISABLE_COPY(cEnemy)

    void Move()final;

    void Configure(const coreUint8 iType, const coreFloat fTimeOffset, const coreFloat fMoveOffset, const coreFloat fSpeed);
    void Execute();

    inline void Bump() {m_fBump = 1.0f;}

    inline const coreBool& GetDisable()const {return m_bDisable;}
};


#endif // _LAF_GUARD_ENEMY_H_