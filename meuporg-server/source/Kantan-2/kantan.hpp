#ifndef KANTAN
#define KANTAN

#include "Platform.hpp"

#include "Utils/StringUtils.hpp"
#include "Utils/MathUtils.hpp"
#include "Utils/GraphicsUtils.hpp"

#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include "System/System.hpp"
#include "Event/Event.hpp"

#include "Component/AnimationComponent.hpp"
#include "Component/AABBHitboxComponent.hpp"
#include "Component/DeletionMarkerComponent.hpp"
#include "Component/MovementComponent.hpp"
#include "Component/ParticleEffectComponent.hpp"
#include "Component/PolygonHitboxComponent.hpp"
#include "Component/RectShapeComponent.hpp"
#include "Component/RotationComponent.hpp"
#include "Component/SpriteComponent.hpp"

#include "System/AABBCollisionSystem.hpp"
#include "System/AnimationSystem.hpp"
#include "System/BatchedSpriteRenderSystem.hpp"
#include "System/ParticleEffectRenderSystem.hpp"
#include "System/ParticleEffectUpdateSystem.hpp"
#include "System/PolygonCollisionSystem.hpp"
#include "System/RectShapeRenderSystem.hpp"
#include "System/SpriteRenderSystem.hpp"
#include "System/SynchronizeBatchedSpriteSystem.hpp"
#include "System/SynchronizeRectShapeSystem.hpp"
#include "System/SynchronizeSpriteSystem.hpp"
#include "System/RotationSystem.hpp"

#include "ResourceHolder/ResourceHolder.hpp"

#include "GUI/GUIGraph.hpp"
#include "GUI/GUIButtonPool.hpp"
#include "GUI/GUITextInputPool.hpp"

#endif // KANTAN
