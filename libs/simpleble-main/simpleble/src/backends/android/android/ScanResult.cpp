
#include "ScanResult.h"

namespace SimpleBLE {
namespace Android {

JNI::Class ScanResult::_cls;
jmethodID ScanResult::_method_getDevice = nullptr;
jmethodID ScanResult::_method_getRssi = nullptr;
jmethodID ScanResult::_method_getTxPower = nullptr;
jmethodID ScanResult::_method_isConnectable = nullptr;
jmethodID ScanResult::_method_getScanRecord = nullptr;
jmethodID ScanResult::_method_toString = nullptr;

void ScanResult::initialize() {
    JNI::Env env;

    if (_cls.get() == nullptr) {
        _cls = env.find_class("android/bluetooth/le/ScanResult");
    }

    if (!_method_getDevice) {
        _method_getDevice = env->GetMethodID(_cls.get(), "getDevice", "()Landroid/bluetooth/BluetoothDevice;");
    }

    if (!_method_getRssi) {
        _method_getRssi = env->GetMethodID(_cls.get(), "getRssi", "()I");
    }

    if (!_method_getTxPower) {
        _method_getTxPower = env->GetMethodID(_cls.get(), "getTxPower", "()I");
    }

    if (!_method_isConnectable) {
        _method_isConnectable = env->GetMethodID(_cls.get(), "isConnectable", "()Z");
    }

    if (!_method_getScanRecord) {
        _method_getScanRecord = env->GetMethodID(_cls.get(), "getScanRecord", "()Landroid/bluetooth/le/ScanRecord;");
    }

    if (!_method_toString) {
        _method_toString = env->GetMethodID(_cls.get(), "toString", "()Ljava/lang/String;");
    }
}

ScanResult::ScanResult(JNI::Object obj) : _obj(obj) {}

void ScanResult::check_initialized() const {
    if (!_obj) throw std::runtime_error("ScanResult is not initialized");
}

BluetoothDevice ScanResult::getDevice() {
    check_initialized();
    return BluetoothDevice(_obj.call_object_method(_method_getDevice));
}

int16_t ScanResult::getRssi() {
    check_initialized();
    return _obj.call_int_method(_method_getRssi);
}

int16_t ScanResult::getTxPower() {
    check_initialized();
    return _obj.call_int_method(_method_getTxPower);
}

bool ScanResult::isConnectable() {
    check_initialized();
    return _obj.call_boolean_method(_method_isConnectable);
}

ScanRecord ScanResult::getScanRecord() {
    check_initialized();
    return ScanRecord(_obj.call_object_method(_method_getScanRecord));
}

std::string ScanResult::toString() {
    check_initialized();
    return _obj.call_string_method(_method_toString);
}

}  // namespace Android
}  // namespace SimpleBLE