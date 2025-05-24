
#include <gameconfig.h>

#include "./gameSystem.h"
#include "./main.h"

extern std::shared_ptr<CGameConfig> g_pGameConfig;

CBaseGameSystemFactory** CBaseGameSystemFactory::sm_pFirst = nullptr;
CGameSystemStaticCustomFactory<GameSystem>* GameSystem::s_pFactory = nullptr;
GameSystem g_GameSystem;

namespace {
abstract_class IGameSystemEventDispatcher {
    public :
        virtual ~IGameSystemEventDispatcher() {}
};

class CGameSystemEventDispatcher : public IGameSystemEventDispatcher {
public:
    CUtlVector<CUtlVector<IGameSystem*>>* m_funcListeners;
};

struct AddedGameSystem_t {
    IGameSystem* m_pGameSystem;
    int m_nPriority;
    int m_nInsertionOrder;
};
}

bool GameSystem::setup()
{
    // See CS2Fixes gamesystem.cpp
    uint8* ptr = (uint8*)g_pGameConfig->ResolveSignature("IGameSystem_InitAllSystems_pFirst") + 3;

    if (!ptr) {
        Panic("Failed to setup GameSystem, see warnings above.\n");
        return false;
    }

    uint32 offset = *(uint32*)ptr;
    ptr += 4;

    CBaseGameSystemFactory::sm_pFirst = (CBaseGameSystemFactory**)(ptr + offset);

    GameSystem::s_pFactory = new CGameSystemStaticCustomFactory<GameSystem>("ExternalViewHelper_GameSystem", &g_GameSystem);

    return true;
}

void GameSystem::teardown()
{
    // See CS2Fixes gamesystem.cpp
    uint8* ptr = (uint8*)g_pGameConfig->ResolveSignature("IGameSystem_LoopPostInitAllSystems_pEventDispatcher") + 3;

    if (!ptr) {
        Panic("Failed to teardown GameSystem, see warings above\n");
        return;
    }

    uint32 offset = *(uint32*)ptr;
    ptr += 4;

    CGameSystemEventDispatcher** ppDispatchers = (CGameSystemEventDispatcher**)(ptr + offset);

    ptr = (uint8*)g_pGameConfig->ResolveSignature("IGameSystem_LoopDestroyAllSystems_s_GameSystems") + 2;

    if (!ptr) {
        Panic("Failed to teardown GameSystem, see warings above\n");
        return;
    }

    offset = *(uint32*)ptr;

    ptr += 4;

    CUtlVector<AddedGameSystem_t>* pGameSystems = (CUtlVector<AddedGameSystem_t>*)(ptr + offset);

    auto* pDispatcher = *ppDispatchers;

    if (!pDispatcher || !pGameSystems) {
        Panic("GameSystems and/or dispatchers is null, server is probably shutting down\n");
        return;
    }

    auto& funcListeners = *pDispatcher->m_funcListeners;
    auto& gameSystems = *pGameSystems;

    FOR_EACH_VEC_BACK(gameSystems, i)
    {
        if (&g_GameSystem == gameSystems[i].m_pGameSystem) {
            gameSystems.FastRemove(i);
            break;
        }
    }

    FOR_EACH_VEC_BACK(funcListeners, i)
    {
        auto& vecListeners = funcListeners[i];

        FOR_EACH_VEC_BACK(vecListeners, j)
        {
            if (&g_GameSystem == vecListeners[j]) {
                vecListeners.FastRemove(j);
                break;
            }
        }

        if (!vecListeners.Count()) {
            funcListeners.FastRemove(i);
        }
    }

    GameSystem::s_pFactory->DestroyGameSystem(&g_GameSystem);
    GameSystem::s_pFactory->Destroy();
}

GS_EVENT_MEMBER(GameSystem, ServerPreEntityThink)
{
    g_pExternalViewHelper->OnPreEntityThink();
}

GS_EVENT_MEMBER(GameSystem, ServerPostEntityThink)
{
    g_pExternalViewHelper->OnPostEntityThink();
}
