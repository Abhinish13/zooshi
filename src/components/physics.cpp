// Copyright 2015 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "components/physics.h"
#include "components/transform.h"
#include "event_system/event_manager.h"
#include "events/audio_event.h"
#include "events/event_ids.h"
#include "fplbase/utilities.h"
#include "mathfu/glsl_mappings.h"
#include "mathfu/vector.h"
#include "pindrop/pindrop.h"

using mathfu::vec3;
using mathfu::quat;

namespace fpl {
namespace fpl_project {

static const float kBounceHeight = 0.8f;
static const float kStartingVelocity = 0.5f;
static const float kGroundPlane = 0.0f;

void PhysicsComponent::Initialize(event::EventManager* event_manager,
                                  pindrop::SoundHandle bounce_handle) {
  event_manager_ = event_manager;
  bounce_handle_ = bounce_handle;
}

void PhysicsComponent::AddFromRawData(entity::EntityRef& entity,
                                      const void* raw_data) {
  auto component_data = static_cast<const ComponentDefInstance*>(raw_data);
  assert(component_data->data_type() == ComponentDataUnion_PhysicsDef);
  auto physics_def = static_cast<const PhysicsDef*>(component_data->data());
  PhysicsData* physics_data = AddEntity(entity);

  (void)physics_def;
  (void)physics_data;

  // TODO - populate data here.
}

void PhysicsComponent::UpdateAllEntities(entity::WorldTime /*delta_time*/) {
  for (auto iter = component_data_.begin();
       iter != component_data_.end(); ++iter) {
    PhysicsData* physics_data = Data<PhysicsData>(iter->entity);
    TransformData* transform_data = Data<TransformData>(iter->entity);

    transform_data->position += physics_data->velocity;
    transform_data->orientation =
        physics_data->angular_velocity * transform_data->orientation;

    if (transform_data->position.z() < kGroundPlane) {
      event_manager_->BroadcastEvent(
          kEventIdPlayAudio,
          AudioEventPayload(bounce_handle_, transform_data->position));

      transform_data->position.z() = kGroundPlane;
      float abs_vel = fabs(physics_data->velocity.z());
      physics_data->velocity.z() = kBounceHeight * abs_vel;
    }
    physics_data->velocity += vec3(0.0f, 0.0f, -0.03f);
  }
}

// Physics component requires that you have a transform component:
void PhysicsComponent::InitEntity(entity::EntityRef& entity) {
  entity_manager_->AddEntityToComponent<TransformComponent>(entity);
  GetComponentData(entity)->velocity = vec3(0, 0, kStartingVelocity);
}

}  // fpl_project
}  // fpl