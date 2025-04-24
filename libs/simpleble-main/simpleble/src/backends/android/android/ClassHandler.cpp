#include "ClassHandler.h"

#include "BluetoothAdapter.h"
#include "BluetoothDevice.h"
#include "BluetoothGatt.h"
#include "BluetoothGattCharacteristic.h"
#include "BluetoothGattDescriptor.h"
#include "BluetoothGattService.h"
#include "BluetoothScanner.h"
#include "ParcelUUID.h"
#include "ScanRecord.h"
#include "ScanResult.h"
#include "SparseArray.h"
#include "UUID.h"

namespace SimpleBLE {
namespace Android {

void ClassHandler::initialize() {
    BluetoothAdapter::initialize();
    BluetoothDevice::initialize();
    BluetoothGatt::initialize();
    BluetoothGattCharacteristic::initialize();
    BluetoothGattDescriptor::initialize();
    BluetoothGattService::initialize();
    BluetoothScanner::initialize();
    ParcelUUID::initialize();
    ScanResult::initialize();
    ScanRecord::initialize();
    SparseArrayBase::initialize();
    UUID::initialize();
}

}  // namespace Android
}  // namespace SimpleBLE