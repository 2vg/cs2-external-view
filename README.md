
## CS2 ExternalView Plugin

ExternalView provides external camera modes (third-person, model view, watch other player, and free camera) for alive players that can be accessed via chat command or console command.

## Installation

### Standalone

- PREREQUISITES:
	- [Metamod:Source](https://www.metamodsource.net/)
	- [CounterStrikeSharp](https://docs.cssharp.dev/index.html)
	- [TNCSSPluginFoundation
](https://github.com/fltuna/TNCSSPluginFoundation)
- Download the [latest ExternalView release](https://github.com/spitice/cs2-external-view/releases)
- Copy/move the files to the server's `csgo` directory

> [!WARNING]
> Do not run this standalone version with lupercalia-mg-cs2 plugin!

### With Lupercalia MG Plugin

- Install [Lupercalia MG Plugin](https://github.com/fltuna/lupercalia-mg-cs2)
- Download **HelperOnly** version from the [latest ExternalView release](https://github.com/spitice/cs2-external-view/releases)
- Copy/move the files to the server's `csgo` directory

> [!CAUTION]
> ConVar names are different from the standalone version.

## Camera modes

ExternalView provides the following camera modes:

- Third-person camera
	- `!tp`
	- `!tp <camera dist>`
	- `!camdist` → resets camera distance
	- `!camdist <camera dist>`
- Shoulder camera (third-person camera + offset)
	- `!tpp` (right-hand)
	- `!tpq` (left-hand)
	- `!camdist`
- Model view / mirror view
	- `!mv`
- Watch other player
	- `!g` (or `!watch`)
	- `!g <search name>`
- Free camera a.k.a., noclip
	- `!fc` (or `!freecam`)

You can disable some camera modes that might be unfair in PvP game modes:

| Mode         | Command                   | `extv_observer_enabled 1` | `extv_observer_enabled 0` |
| ------------ | ------------------------- | :-----------------------: | :-----------------------: |
| Third Person | !tp. !tpp, !tpq, !camdist |             ✅             |             ✅             |
| Model View   | !mv                       |             ✅             |             ✅             |
| Watch        | !g, !watch                |             ✅             |             -             |
| Free Cam     | !fc, !freecam             |             ✅             |             -             |

## ConVars

ExternalView will generate a .cfg file to the following path if it is not created.

```
csgo/cfg/extv/extv.cfg
```

```
// ===== External View =====

// External view feature is enabled
extv_enabled 1

// The minimum camera distance for third-person camera.
extv_thirdperson_min_distance 50

// The maximum camera distance for third-person camera.
extv_thirdperson_max_distance 200

// The speed of model view camera movement
extv_modelview_speed 160

// The radius from the player the model view camera can fly around
extv_modelview_radius 120

// The speed of free camera movement
extv_freecam_speed 800

// True if observer views (i.e., freecam and watch) are enabled for non-admin players.
extv_observer_enabled 1

// True if admins can use all features regardless of the flags (e.g., IsObserverViewEnabled)
extv_admin_privileges_enabled 1
```

### Disabling freecam and watch for PvP mode

If you want to disable **freecam** and **watch** camera for PvP game modes (e.g., Zombie Escape), set the following convar:

```
extv_observer_enabled 0
```

Still, admins who are given `@css/root` permission can use freecam and watch. If you want to try to see if the feature is actually disabled without modifying admin settings, you can temporarily disable admin privileges and treat all players as non-admins:

```
extv_admin_privileges_enabled 0
```

## Acknowledgements

I'd like to acknowledge the ideas and inspirations I've drawn from the following awesome CS2 modding projects. Massive thanks to the authors, and CS2 modding community!

- [ThirdPerson-WIP](https://github.com/grrhn/ThirdPerson-WIP) by BoinK & UgurhanK
	- Third-person camera idea via overriding CameraService.ViewEntity
- [CS2-PlayerModelChanger](https://github.com/samyycX/CS2-PlayerModelChanger) by samyyc
	- The logic to inspect player model by using prop_physics_override
- [CS2Fixes](https://github.com/Source2ZE/CS2Fixes) by Source2ZE community
	- Hooking PreEntityThink/PostEntityThink from metamod plugin
- [TNCSSPluginFoundation](https://github.com/fltuna/TNCSSPluginFoundation/tree/main) by tuna
	- Easier development of CSSharp plugin
- [Metamod:Source](https://www.metamodsource.net/)
- [CounterStrikeSharp](https://docs.cssharp.dev/index.html)

## Changelogs

#### v2.0.1 (25-05-25)

- Fix typo on CVar name
  - CORRECTED: `extv_admin_privileges_enabled`
  - OLD: `extv_admin_previleges_enabled`

#### v2.0.0 (25-05-25)

- Initial standalone version

#### v1.0.0 (25-03-15)

- Initial version (only exists in lupercalia-mg-core)
