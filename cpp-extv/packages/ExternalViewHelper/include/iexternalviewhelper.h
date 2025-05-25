
#pragma once

#define EXTERNALVIEWHELPER_INTERFACE_NAME "ExternalViewHelper v1.0"

class IExternalViewHelper {
public:
    virtual void OnPreEntityThink() = 0;
    virtual void OnPostEntityThink() = 0;
};
