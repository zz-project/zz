/******************************************************************************/
/*                                                                            */
/*  Copyright 2026 The ZZ Project                                             */
/*                                                                            */
/*  Licensed under the Apache License, Version 2.0 (the "License");           */
/*  you may not use this file except in compliance with the License.          */
/*  You may obtain a copy of the License at                                   */
/*                                                                            */
/*      http://www.apache.org/licenses/LICENSE-2.0                            */
/*                                                                            */
/*  Unless required by applicable law or agreed to in writing, software       */
/*  distributed under the License is distributed on an "AS IS" BASIS,         */
/*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  */
/*  See the License for the specific language governing permissions and       */
/*  limitations under the License.                                            */
/*                                                                            */
/******************************************************************************/

#ifndef ZZ_PCI_CLASS_CODE_H__
#define ZZ_PCI_CLASS_CODE_H__

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace zz::pci {

enum class ClassCode : uint8_t {
  kUnclassifiedDevice = 0x00,
  kMassStorageController = 0x01,
  kNetworkController = 0x02,
  kDisplayController = 0x03,
  kMultimediaController = 0x04,
  kMemoryController = 0x05,
  kBridge = 0x06,
  kCommunicationController = 0x07,
  kGenericSystemPeripheral = 0x08,
  kInputDeviceController = 0x09,
  kDockingStation = 0x0A,
  kProcessor = 0x0B,
  kSerialBusController = 0x0C,
  kWirelessController = 0x0D,
  kIntelligentController = 0x0E,
  kSatelliteCommunicationsController = 0x0F,
  kEncryptionController = 0x10,
  kSignalProcessingController = 0x11,
  kProcessingAccelerators = 0x12,
  kNonEssentialInstrumentation = 0x13,
  kCoprocessor = 0x40,
  kUnassignedClass = 0xFF,
};

struct ClassCodeAndDescription {
  ClassCode code;
  const char* description;
};

constexpr ClassCodeAndDescription kClassCodeDescription[] = {
    {ClassCode::kUnclassifiedDevice, "Unclassified Device"},
    {ClassCode::kMassStorageController, "Mass Storage Controller"},
    {ClassCode::kNetworkController, "Network Controller"},
    {ClassCode::kDisplayController, "Display Controller"},
    {ClassCode::kMultimediaController, "Multimedia Controller"},
    {ClassCode::kMemoryController, "Memory Controller"},
    {ClassCode::kBridge, "Bridge"},
    {ClassCode::kCommunicationController, "Communication Controller"},
    {ClassCode::kGenericSystemPeripheral, "Generic System Peripheral"},
    {ClassCode::kInputDeviceController, "Input Device Controller"},
    {ClassCode::kDockingStation, "Docking Station"},
    {ClassCode::kProcessor, "Processor"},
    {ClassCode::kSerialBusController, "Serial Bus Controller"},
    {ClassCode::kWirelessController, "Wireless Controller"},
    {ClassCode::kIntelligentController, "Intelligent Controller"},
    {ClassCode::kSatelliteCommunicationsController,
     "Satellite Communications Controller"},
    {ClassCode::kEncryptionController, "Encryption Controller"},
    {ClassCode::kSignalProcessingController, "Signal Processing Controller"},
    {ClassCode::kProcessingAccelerators, "Processing Accelerators"},
    {ClassCode::kNonEssentialInstrumentation, "Non-essential Instrumentation"},
    {ClassCode::kCoprocessor, "Coprocessor"},
    {ClassCode::kUnassignedClass, "Unassigned Class"},
};

constexpr std::string_view GetClassCodeDescription(ClassCode code) {
  for (auto& code_and_description : kClassCodeDescription) {
    if (code_and_description.code == code) {
      return code_and_description.description;
    }
  }
  return "Unknown Class Code";
}

}  // namespace zz::pci

#endif  // ZZ_PCI_CLASS_CODE_H__
