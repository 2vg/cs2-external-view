
#include "./main.h"

#include <memory>

#include <commonmacros.h>
#include <vscript/ivscript.h>

#include "./addresses.h"
#include "./gameConfig.h"

#include <lpe/core/sout.h>

#include "./gameSystem.h"

void Message(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);

    char buf[1024] = {};
    V_vsnprintf(buf, sizeof(buf) - 1, msg, args);

    ConColorMsg(Color(255, 0, 255, 255), "[ExternalViewHelper] %s", buf);

    va_end(args);
}

void Panic(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);

    char buf[1024] = {};
    V_vsnprintf(buf, sizeof(buf) - 1, msg, args);

    Warning("[ExternalViewHelper] %s", buf);

    va_end(args);
}

LPE_USE_SOUT(Root);

ExternalViewHelperPlugin g_ExternalViewHelperPlugin;
IExternalViewHelper* g_pExternalViewHelper = static_cast<IExternalViewHelper*>(&g_ExternalViewHelperPlugin);

IVEngineServer2* g_pEngineServer2 = nullptr;
std::shared_ptr<CGameConfig> g_pGameConfig = nullptr;

PLUGIN_EXPOSE(ExternalViewHelperPlugin, g_ExternalViewHelperPlugin);

bool ExternalViewHelperPlugin::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
    PLUGIN_SAVEVARS();

    GET_V_IFACE_CURRENT(GetEngineFactory, g_pEngineServer2, IVEngineServer2, SOURCE2ENGINETOSERVER_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetFileSystemFactory, g_pFullFileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);

    g_SMAPI->AddListener(this, this);

    CBufferStringGrowable<256> gameDir;
    g_pEngineServer2->GetGameDir(gameDir);

    std::string gameDirName = CGameConfig::GetDirectoryName(gameDir.Get());
    lpe::SoutManager::initialize({
        .name = "ExternalViewHelper",
        .logDir = fmt::format("{}/addons/externalviewhelper/logs", gameDir.Get()),
    });

    sout.log("Game dir: {}", gameDir.Get());

    const char* gamedataPath = "addons/externalviewhelper/gamedata/externalviewhelper.games.txt";
    //const char* gamedataPath = "addons/cs2fixes/gamedata/cs2fixes.games.txt"
    sout.log("Loading {} for game: {}", gamedataPath, gameDirName);

    g_pGameConfig = std::make_shared<CGameConfig>(gameDirName, gamedataPath);
    char szConfError[255] = "";
    if (!g_pGameConfig->Init(g_pFullFileSystem, szConfError, sizeof(szConfError))) {
        sout.error("Could not read {}: {}", g_pGameConfig->GetPath(), szConfError);
        return false;
    }

    addresses::Initialize(g_pGameConfig.get());

    GameSystem::setup();

    sout.log("ExternalViewHelper plugin has been loaded");

    return true;
}

bool ExternalViewHelperPlugin::Unload(char* error, size_t maxlen)
{
    GameSystem::teardown();

    g_pGameConfig.reset();

    return true;
}

const char* ExternalViewHelperPlugin::GetAuthor()
{
    return "Spitice";
}

const char* ExternalViewHelperPlugin::GetName()
{
    return "ExternalViewHelper";
}

const char* ExternalViewHelperPlugin::GetDescription()
{
    return "A helper metamod plugin for CS2 ExternelView plugin.";
}

const char* ExternalViewHelperPlugin::GetURL()
{
    return "https://github.com/spitice/cs2-external-view";
}

const char* ExternalViewHelperPlugin::GetLicense()
{
    return "GPL v3 License";
}

const char* ExternalViewHelperPlugin::GetVersion()
{
    return EXTERNALVIEWHELPER_VERSION;
}

const char* ExternalViewHelperPlugin::GetDate()
{
    return __DATE__;
}

const char* ExternalViewHelperPlugin::GetLogTag()
{
    return "ExternalViewHelper";
}

void* ExternalViewHelperPlugin::OnMetamodQuery(const char* iface, int* ret)
{
    if (V_strcmp(iface, EXTERNALVIEWHELPER_INTERFACE_NAME)) {
        if (ret) {
            *ret = META_IFACE_FAILED;

            return nullptr;
        }
    }

    if (ret) {
        *ret = META_IFACE_OK;
    }

    return g_pExternalViewHelper;
}

//
// ALWAYS INCLUDE DEBUG INFORMATION (i.e., build with RelWithDebInfo, not Release)
// otherwise hooked functins on CSSharp side won't be called. (not 100% sure)
//
void ExternalViewHelperPlugin::OnPreEntityThink()
{
    // HOOK this function
}

void ExternalViewHelperPlugin::OnPostEntityThink()
{
    // HOOK this function
}
