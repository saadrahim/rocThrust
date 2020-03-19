/*
 *  Copyright© 2019 Advanced Micro Devices, Inc. All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef ROCTHRUST_VERSION_HPP_
#define ROCTHRUST_VERSION_HPP_

/// \def ROCTHRUST_VERSION
/// \brief ROCTHRUST library version
///
/// Version number may not be visible in the documentation.
///
/// ROCTHRUST_VERSION % 100 is the patch level,
/// ROCTHRUST_VERSION / 100 % 1000 is the minor version,
/// ROCTHRUST_VERSION / 100000 is the major version.
///
/// For example, if ROCTHRUST_VERSION is 100500, then the major version is 1,
/// the minor version is 5, and the patch level is 0.
#define ROCTHRUST_VERSION 2 * 100000 + 10 * 100 + 0

#define ROCTHRUST_VERSION_MAJOR 2
#define ROCTHRUST_VERSION_MINOR 10
#define ROCTHRUST_VERSION_PATCH 0

#endif // ROCTHRUST_VERSION_HPP_
