
#pragma once

#include <common.h>
#include <entitysystem.h>

#define private public
#define protected public
#include "igamesystemfactory.h"
#undef protected
#undef private

template <class T, class U = T>
class CGameSystemStaticCustomFactory : public CGameSystemStaticFactory<T, U> {
public:
    CGameSystemStaticCustomFactory(const char* pName, T* pActualGlobal, U** ppGlobalPointer = nullptr)
        : CGameSystemStaticFactory<T, U>(pName, pActualGlobal, ppGlobalPointer)
    {
    }

    void Destroy()
    {
        CBaseGameSystemFactory* pFactoryCurrent = *CBaseGameSystemFactory::sm_pFirst;
        CBaseGameSystemFactory* pFactoryPrevious = nullptr;
        while (pFactoryCurrent) {
            if (strcmp(pFactoryCurrent->m_pName, this->m_pName) == 0) {
                if (pFactoryPrevious == nullptr)
                    *CBaseGameSystemFactory::sm_pFirst = pFactoryCurrent->m_pNext;
                else
                    pFactoryPrevious->m_pNext = pFactoryCurrent->m_pNext;
                delete pFactoryCurrent;
                return;
            }
            pFactoryPrevious = pFactoryCurrent;
            pFactoryCurrent = pFactoryCurrent->m_pNext;
        }
    }
};

class GameSystem
    : public CBaseGameSystem {
public:
    static CGameSystemStaticCustomFactory<GameSystem>* s_pFactory;

public:
    static bool setup();
    static void teardown();

public: // Implements IGameSystem
    GS_EVENT(ServerPreEntityThink);
    GS_EVENT(ServerPostEntityThink);
};

extern GameSystem g_GameSystem;
