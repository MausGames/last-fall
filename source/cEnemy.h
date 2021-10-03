/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _000_GUARD_ENEMY_H_
#define _000_GUARD_ENEMY_H_


// ****************************************************************
#define ENEMY_SCALE (1.2f)


// ****************************************************************
class cEnemy final : public coreObject3D
{
private:
    coreFlow m_fRotation;
    coreFlow m_fBump;

    coreBool m_bDisable;
    coreFlow m_bDisableTime;

    coreFlow m_fAttackDelay;

    coreUint8   m_iType;
    coreFlow    m_fTime;     // time offset with init
    coreFloat   m_fOffset;   // spatial offset
    coreFloat   m_fSpeed;
    coreVector2 m_vStart;

    coreVector2 m_vVelocity;


public:
    cEnemy()noexcept;
    ~cEnemy()final;

    DISABLE_COPY(cEnemy)

    void Render()final;
    void Move  ()final;

    void Configure(const coreUint8 iType, const coreFloat fTimeOffset, const coreFloat fMoveOffset, const coreFloat fSpeed);
    void Execute();

    inline void Bump() {m_fBump = 1.0f;}

    inline void SetDisable    (const coreBool  bDisable)     {m_bDisable     = bDisable;}
    inline void SetAttackDelay(const coreFloat fAttackDelay) {m_fAttackDelay = fAttackDelay;}

    inline const coreBool&  GetDisable    ()const {return m_bDisable;}
    inline const coreFloat& GetAttackDelay()const {return m_fAttackDelay;}
};


#endif // _000_GUARD_ENEMY_H_