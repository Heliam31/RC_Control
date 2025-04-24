#include "BluetoothDevice.h"

namespace SimpleBLE {
namespace Android {

const int BluetoothDevice::BOND_NONE;
const int BluetoothDevice::BOND_BONDING;
const int BluetoothDevice::BOND_BONDED;

const int BluetoothDevice::ADDRESS_TYPE_ANONYMOUS;
const int BluetoothDevice::ADDRESS_TYPE_PUBLIC;
const int BluetoothDevice::ADDRESS_TYPE_RANDOM;

const int BluetoothDevice::TRANSPORT_AUTO;
const int BluetoothDevice::TRANSPORT_BREDR;
const int BluetoothDevice::TRANSPORT_LE;

JNI::Class BluetoothDevice::_cls;
jmethodID BluetoothDevice::_method_getAddress;
// jmethodID BluetoothDevice::_method_getAddressType;
jmethodID BluetoothDevice::_method_getName;
jmethodID BluetoothDevice::_method_getBondState;
jmethodID BluetoothDevice::_method_removeBond;
jmethodID BluetoothDevice::_method_connectGatt;

void BluetoothDevice::initialize() {
    JNI::Env env;

    if (_cls.get() == nullptr) {
        _cls = env.find_class("android/bluetooth/BluetoothDevice");
    }

    if (!_method_getAddress) {
        _method_getAddress = env->GetMethodID(_cls.get(), "getAddress", "()Ljava/lang/String;");
    }

    // TODO: This is only available on API level 35 and above
    // if (!_method_getAddressType) {
    //     _method_getAddressType = env->GetMethodID(_cls.get(), "getAddressType", "()I");
    // }

    if (!_method_getName) {
        _method_getName = env->GetMethodID(_cls.get(), "getName", "()Ljava/lang/String;");
    }

    if (!_method_getBondState) {
        _method_getBondState = env->GetMethodID(_cls.get(), "getBondState", "()I");
    }

    // if (!_method_removeBond) {
    //     _method_removeBond = env->GetMethodID(_cls.get(), "removeBond", "()V");
    // }

    if (!_method_connectGatt) {
        _method_connectGatt = env->GetMethodID(
            _cls.get(), "connectGatt",
            "(Landroid/content/Context;ZLandroid/bluetooth/BluetoothGattCallback;I)Landroid/bluetooth/BluetoothGatt;");
    }
}

BluetoothDevice::BluetoothDevice(JNI::Object obj) : _obj(obj) {}

void BluetoothDevice::check_initialized() const {
    if (!_obj) throw std::runtime_error("BluetoothDevice is not initialized");
}

std::string BluetoothDevice::getAddress() {
    check_initialized();
    return _obj.call_string_method(_method_getAddress);
}

// int BluetoothDevice::getAddressType() {
//     check_initialized();
//     return _obj.call_int_method(_method_getAddressType);
// }

std::string BluetoothDevice::getName() {
    check_initialized();
    return _obj.call_string_method(_method_getName);
}

int BluetoothDevice::getBondState() {
    check_initialized();
    return _obj.call_int_method(_method_getBondState);
}

// void BluetoothDevice::removeBond() {
//     check_initialized();
//     _obj.call_void_method(_method_removeBond);
// }

BluetoothGatt BluetoothDevice::connectGatt(bool autoConnect, Bridge::BluetoothGattCallback& callback) {
    check_initialized();
    return BluetoothGatt(
        _obj.call_object_method(_method_connectGatt, nullptr, autoConnect, callback.get(), BluetoothDevice::TRANSPORT_LE));
}

}  // namespace Android
}  // namespace SimpleBLE
