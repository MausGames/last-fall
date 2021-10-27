/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Last Fall (https://www.maus-games.at) |//
//*-----------------------------------------------*//
//| Released under the zlib License               |//
//| More information available in the readme file |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////
#pragma once
#ifndef _LAF_GUARD_PLAYER_H_
#define _LAF_GUARD_PLAYER_H_


// ****************************************************************
#define PLAYER_SCALE               (1.0f)
#define PLAYER_ACCELERATION        (220.0f)
#define PLAYER_ACCELERATION_HEIGHT (100.0f)
#define PLAYER_BRAKE               (10.0f)
#define PLAYER_BRAKE_HEIGHT        (0.5f)


// ****************************************************************
class cPlayer final : public coreObject3D
{
private:
    coreVector2 m_vVelocity;
    coreFloat   m_fVelocityHeight;

    coreBool m_bFalling;
    coreBool m_bLanding;

    coreObject3D m_Shadow;


public:
    cPlayer()noexcept;

    DISABLE_COPY(cPlayer)

    void Move()final;

    void RenderShadow();

    void Land();

    inline void AddVelocity      (const coreVector2 vVelocity) {m_vVelocity       += vVelocity;}
    inline void AddVelocityHeight(const coreFloat   fVelocity) {m_fVelocityHeight += fVelocity;}

    void        SetFullPosition  (const coreVector3 vPosition);
    inline void SetVelocity      (const coreVector2 vVelocity) {m_vVelocity       = vVelocity;}
    inline void SetVelocityHeight(const coreFloat   fVelocity) {m_fVelocityHeight = fVelocity;}
    inline void SetFalling       (const coreBool    bFalling)  {m_bFalling        = bFalling;}
    inline void SetLanding       (const coreBool    bLanding)  {m_bLanding        = bLanding;}

    inline const coreVector2& GetVelocity      ()const {return m_vVelocity;}
    inline const coreFloat&   GetVelocityHeight()const {return m_fVelocityHeight;}
    inline const coreBool&    GetFalling       ()const {return m_bFalling;}
    inline const coreBool&    GetLanding       ()const {return m_bLanding;}
};


#endif // _LAF_GUARD_PLAYER_H_