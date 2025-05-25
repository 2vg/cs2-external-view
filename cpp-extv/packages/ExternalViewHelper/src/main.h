
#pragma once

#include <ISmmPlugin.h>
#include <iexternalviewhelper.h>
#include <iserver.h>
#include <sh_vector.h>

class ExternalViewHelperPlugin
    : public ISmmPlugin,
      public IMetamodListener,
      public IExternalViewHelper {
public: // Implements ISmmPlugin
    virtual bool Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late) override;
    virtual bool Unload(char* error, size_t maxlen);

public: // Implements ISmmPlugin
    virtual const char* GetAuthor() override;
    virtual const char* GetName() override;
    virtual const char* GetDescription() override;
    virtual const char* GetURL() override;
    virtual const char* GetLicense() override;
    virtual const char* GetVersion() override;
    virtual const char* GetDate() override;
    virtual const char* GetLogTag() override;

public: // Implements IMetamodListener
    virtual void* OnMetamodQuery(const char* iface, int* ret) override;

public: // Implements IExternalViewHelper
    virtual void OnPreEntityThink() override;
    virtual void OnPostEntityThink() override;
};

extern ExternalViewHelperPlugin g_ExternalViewHelperPlugin;
extern IExternalViewHelper* g_pExternalViewHelper;

PLUGIN_GLOBALVARS();
