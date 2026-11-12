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

#ifndef ZZ_PCI_CAP_ID_H__
#define ZZ_PCI_CAP_ID_H__

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace zz::pci {

enum class CapId : uint8_t {
  /// Null
  kNull = 0x00,

  /// Power Management
  kPowerManagement = 0x01,

  /// AGP (Accelerated Graphics Port)
  kAgp = 0x02,

  /// Vital Product Data
  kVpd = 0x03,

  /// Slot ID
  kSlotId = 0x04,

  /// Message Signalled Interrupts
  kMsi = 0x05,

  /// Compact Host Swap
  kCompactHostSwap = 0x06,

  /// PCI-X
  kPciX = 0x07,

  /// Hyper Transport
  kHyperTransport = 0x08,

  /// Vendor specific
  kVendor = 0x09,

  /// Debug port
  kDebug = 0x0A,

  /// Compact Central Resource Control
  kCompactCentralResourceControl = 0x0B,

  /// PCI Hot-Plug
  kHotPlug = 0x0C,

  /// Subsystem Vendor ID
  kSubsystemVendorId = 0x0D,

  /// AGP 8x
  kAgp3 = 0x0E,

  /// Secure
  kSecure = 0x0F,

  /// PCI Express
  kPciExpress = 0x10,

  /// MSI-X
  kMsiX = 0x11,

  /// SATA
  kSata = 0x12,

  /// Advanced Root Complex Features
  kAdvancedRootComplexFeatures = 0x13,

  /// Enhanced Allocation
  kEnhancedAllocation = 0x14,

  /// Flattening Portal Bridge
  kFlatteningPortalBridge = 0x15,

  /// Used to catch unknown capability IDs.
  kCapIdMax = 0x16
};

constexpr const char* kCapIdDescription[] = {
    "Null",
    "Power Management",
    "AGP (Accelerated Graphics Port)",
    "Vital Product Data",
    "Slot ID",
    "Message Signaled Interrupts",
    "Compact Host Swap",
    "PCI-X",
    "Hyper Transport",
    "Vendor specific",
    "Debug port",
    "Compact Central Resource Control",
    "PCI Hot-Plug",
    "Subsystem Vendor ID",
    "AGP 8x",
    "Secure",
    "PCI Express",
    "MSI-X",
    "SATA",
    "Advanced Root Complex Features",
    "Enhanced Allocation",
    "Flattening Portal Bridge",
};

constexpr std::string_view GetCapIdDescription(CapId cap_id) {
  if (cap_id >= CapId::kCapIdMax) {
    return "Unknown Capability ID";
  }
  return kCapIdDescription[static_cast<size_t>(cap_id)];
}

enum class ECapId : uint16_t {
  kNull = 0x00,
  kAdvancedErrorReporting = 0x01,
  kVirtualChannel = 0x02,
  kDeviceSerialNumber = 0x03,
  kPowerBudgeting = 0x04,
  kRootComplexLinkDeclaration = 0x05,
  kRootComplexInternalLinkDeclaration = 0x06,
  kRootComplexEventCollector = 0x07,
  kMultiFunctionVirtualChannel = 0x08,
  kVirtualChannel2 = 0x09,
  kRootComplexRegisterBlock = 0x0a,
  kVendor = 0x0b,
  kAccessControls = 0x0d,
  kAlternativeRoutingIdInterpretation = 0x0e,
  kAddressTranslationService = 0x0f,
  kSingleRootIoVirtualization = 0x10,
  kMultiRootIoVirtualization = 0x11,
  kMulticast = 0x12,
  kPageRequestInterface = 0x13,
  kResizableBar = 0x15,
  kDynamicPowerAllocation = 0x16,
  kTransactionProcessingHints = 0x17,
  kLatencyToleranceReporting = 0x18,
  kSecondaryPciExpress = 0x19,
  kProtocolMultiplexing = 0x1a,
  kProcessAddressSpaceId = 0x1b,
  kLnRequester = 0x1c,
  kDownstreamPortContainment = 0x1d,
  kL1PmSubstates = 0x1e,
  kPrecisionTimeMeasurement = 0x1f,
  kPcieOverMPhy = 0x20,
  kFrsQueuing = 0x21,
  kReadinessTimeReporting = 0x22,
  kDesignatedVendorSpecific = 0x23,
  kVfResizableBar = 0x24,
  kDataLinkFeature = 0x25,
  kPhysicalLayer16Gt = 0x26,
  kLaneMarginingAtReceiver = 0x27,
  kHierarchyId = 0x28,
  kNativePcieEnclosureManagement = 0x29,
  kPhysicalLayer32Gt = 0x2a,
  kAlternateProtocol = 0x2b,
  kSystemFirmwareIntermediary = 0x2c,
  kDataObjectExchange = 0x2e,
  kDevice3 = 0x2f,
  kIntegrityAndDataEncryption = 0x30,
  kPhysicalLayer64Gt = 0x31,
  kFlitLogging = 0x32,
  kFlitPerformanceMeasurement = 0x33,
  kFlitErrorInjection = 0x34,
  kStreamlinedVirtualChannel = 0x35,
  kMmioRegisterBlockLocator = 0x36,
  kNopFlit = 0x37,
  kScalableIoVirtualization = 0x38,
  kPhysicalLayer128Gt = 0x39,
  kCapturedData = 0x3a,
  kEcapIdMax = 0x3b,
};

constexpr const char* kExtCapIdDescription[] = {
    "Null Capability",
    "Advanced Error Reporting",
    "Virtual Channel",
    "Device Serial Number",
    "Power Budgeting",
    "Root Complex Link Declaration",
    "Root Complex Internal Link Declaration",
    "Root Complex Event Collector",
    "Multi-Function Virtual Channel",
    "Virtual Channel (2nd ID)",
    "Root Complex Register Block",
    "Vendor Specific",
    "Access Controls",
    "Alternative Routing-ID Interpretation",
    "Address Translation Service",
    "Single Root I/O Virtualization",
    "Multi-Root I/O Virtualization",
    "Multicast",
    "Page Request Interface",
    "Unknown Extended Capability",  // 0x14
    "Resizable BAR",
    "Dynamic Power Allocation",
    "Transaction Processing Hints",
    "Latency Tolerance Reporting",
    "Secondary PCI Express",
    "Protocol Multiplexing",
    "Process Address Space ID",
    "LN Requester",
    "Downstream Port Containment",
    "L1 PM Substates",
    "Precision Time Measurement",
    "PCIe Over M-PHY",
    "FRS Queuing",
    "Readiness Time Reporting",
    "Designated Vendor-Specific",
    "VF Resizable BAR",
    "Data Link Feature",
    "Physical Layer 16.0 GT/s",
    "Lane Margining at Receiver",
    "Hierarchy ID",
    "Native PCIe Enclosure Management",
    "Physical Layer 32.0 GT/s",
    "Alternate Protocol",
    "System Firmware Intermediary",
    "Unknown Extended Capability",  // 0x2d
    "Data Object Exchange",
    "Device 3",
    "Integrity and Data Encryption",
    "Physical Layer 64.0 GT/s",
    "Flit Logging",
    "Flit Performance Measurement",
    "Flit Error Injection",
    "Streamlined Virtual Channel",
    "MMIO Register Block Locator",
    "NOP Flit Extended Capability",
    "Scalable I/O Virtualization",
    "Physical Layer 128.0 GT/s",
    "Captured Data",
};

constexpr std::string_view GetECapIdDescription(ECapId ecap_id) {
  if (ecap_id >= ECapId::kEcapIdMax) {
    return "Unknown Capability ID";
  }
  return kExtCapIdDescription[static_cast<size_t>(ecap_id)];
}

}  // namespace zz::pci

#endif  // ZZ_PCI_CAP_ID_H__
