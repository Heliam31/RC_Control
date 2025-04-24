#include "ClassHandler.h"

#include "BluetoothGattCallback.h"
#include "ScanCallback.h"

namespace SimpleBLE {
namespace Android {
namespace Bridge {

void ClassHandler::initialize() {
    BluetoothGattCallback::initialize();
    ScanCallback::initialize();
}

}  // namespace Bridge
}  // namespace Android
}  // namespace SimpleBLE