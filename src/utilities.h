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

#ifndef ZOOSHI_UTILITIES_H
#define ZOOSHI_UTILITIES_H

#include <string>

#include "mathfu/utilities.h"

#include "audio_config_generated.h"

namespace fpl {

bool LoadFile(const char* filename, std::string* dest);

bool ChangeToUpstreamDir(const char* const binary_dir,
                         const char* const target_dir);

bool TouchScreenDevice();

bool MipmapGeneration16bppSupported();

}  // namespace fpl

#endif  // ZOOSHI_UTILITIES_H
