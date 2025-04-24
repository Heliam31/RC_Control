#pragma once

#include "jni/Common.hpp"

#include "BluetoothDevice.h"
#include "ScanRecord.h"

namespace SimpleBLE {
namespace Android {

class ClassHandler;

class ScanResult {
  public:
    ScanResult(JNI::Object obj);

    BluetoothDevice getDevice();
    int16_t getRssi();
    int16_t getTxPower();
    bool isConnectable();
    ScanRecord getScanRecord();
    std::string toString();

  private:
    static JNI::Class _cls;
    static jmethodID _method_getDevice;
    static jmethodID _method_getRssi;
    static jmethodID _method_getTxPower;
    static jmethodID _method_isConnectable;
    static jmethodID _method_getScanRecord;
    static jmethodID _method_toString;

    static void initialize();
    void check_initialized() const;
    JNI::Object _obj;

    friend class ClassHandler;
};

}  // namespace Android
}  // namespace SimpleBLE
