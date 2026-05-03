# HoiChoTet (HCT26)

A multi-featured Unreal Engine 5 game project built with C++, featuring an open-world exploration environment and an integrated arcade-style airplane shooter mini-game.

---

## Overview

**HoiChoTet** is a course project developed in Unreal Engine 5.7 (C++). The game features:

- An open exploration world with interactive NPCs and environmental triggers
- An arcade airplane shooter mini-game accessible from the main world
- A modular, tag-based pawn-possession system
- Animation learning sandbox using the Animal Variety Pack

---

# Features

## Main World
- Player-controlled pawn with floating movement
- Multiple NPC pawns with distinct interaction behaviors
- Trigger button system that fires delegates and activates Niagara effects
- Pawn switching via Gameplay Tags (`CanPossess`)
- NPC dialogue interaction through the `IReactToTriggerInterface`

## Airplane Shooter Mini-Game
- Player aircraft with health, shooting, and movement
- Enemy aircraft with AI movement, collision, and self-destruct logic
- Projectile system with gameplay tag filtering (`Bullet`, `Enemy`)
- Wave-based enemy spawning managed by `AHCT26AirPlaneShooterController`
- Full UI flow: Main Menu → Gameplay → Game Over / Win screen

## Animal Variety Pack (`/Game/AnimalVarietyPack`)

A third-party asset pack used as a hands-on sandbox for learning Unreal Engine animation fundamentals.

- Explore skeletal meshes, animation sequences, and blend spaces provided by the pack
- Practice wiring Animation Blueprints (state machines, transitions, blending)
- Used for experimentation only — not part of core gameplay

## Vehicle Configurator

A standalone Blueprint-based vehicle showcase and configuration system built on top of Unreal Engine's **Chaos Vehicles** plugin.

### Architecture

```
Content/VehicleConfigurator/
├── Core/
│   ├── Blueprints/           # BP_Vehicle_Base — parent class for all vehicles
│   ├── ActorComponents/      # BP_MovementComponent — custom vehicle physics/control
│   ├── GamePlayFrameWork/    # BP_VehicleConfigGameMode, BP_VehicleConfigPlayerController
│   ├── Inputs/               # Enhanced Input actions (Throttle, Brake, Steer, LookAround) + IMC_Vehicle
│   └── Tools/                # EUW_Vehicle_Tools — Editor Utility Widget for in-editor configuration
├── Vehicles/
│   ├── Car_1/                # Simple vehicle — Blueprint, wheel classes, skeletal mesh, physics asset
│   └── Mercedes_Benz/        # High-fidelity vehicle — Blueprint + animation blueprint
└── VehicleConfigLevel.umap   # Dedicated playable level for vehicle testing
```

### Vehicles

Each vehicle has dedicated **front** and **rear wheel** Blueprints inheriting from a shared base wheel class, allowing per-axle physics tuning (friction, radius, suspension).

### Input Setup (Enhanced Input)

| Action | Asset |
|---|---|
| Throttle | `IA_Vehicle_Throttle` |
| Brake | `IA_Vehicle_Brake` |
| Steer | `IA_Vehicle_Steer` |
| Look Around | `IA_Vehicle_LookAround` |
| Mapping Context | `IMC_Vehicle` |

### VehicleLiverySwapper Plugin

A **GameFeature plugin** (`Plugins/GameFeatures/VehicleLiverySwapper/`) that provides a modular livery (paint/skin) swapping system.

- Module type: Runtime C++ (`VehicleLiverySwapperRuntime`)
- Loaded explicitly; disabled by default in shipping builds
- C++ module shell is in place — livery swap logic is intended for Blueprint or future C++ extension
- Module dependencies: `Core`, `CoreUObject`, `Engine`, `Slate`, `SlateCore`

---

## Plugins Used

| Plugin | Purpose |
|---|---|
| `ChaosVehiclesPlugin` | Vehicle physics system |
| `GameFeatures` | Dynamic feature loading |
| `VehicleLiverySwapper` | Vehicle appearance customization |
| `ModelingToolsEditorMode` | Editor mesh modeling tools |

---

## Requirements

- Unreal Engine 5.7
- Visual Studio 2022 (with C++ game development workload)
- Windows 10/11

---

## How to Run

1. Clone or download this repository.
2. Right-click `HCT26.uproject` and select **Generate Visual Studio project files**.
3. Open `HCT26.sln` in Visual Studio 2022 and build in **Development Editor** configuration.
4. Launch the project from the Unreal Editor and open `WelcomeLevel` or `Level1`.

---

## Author

**Khoi Van** — UE C++ Course 2026
