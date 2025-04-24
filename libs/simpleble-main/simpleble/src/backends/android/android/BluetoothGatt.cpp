#include "BluetoothGatt.h"
#include <android/log.h>
#include <fmt/core.h>

#include "jni/List.h"

namespace SimpleBLE {
namespace Android {

JNI::Class BluetoothGatt::_cls;
jmethodID BluetoothGatt::_method_close = nullptr;
jmethodID BluetoothGatt::_method_connect = nullptr;
jmethodID BluetoothGatt::_method_disconnect = nullptr;
jmethodID BluetoothGatt::_method_discoverServices = nullptr;
jmethodID BluetoothGatt::_method_getServices = nullptr;
jmethodID BluetoothGatt::_method_readCharacteristic = nullptr;
jmethodID BluetoothGatt::_method_readDescriptor = nullptr;
jmethodID BluetoothGatt::_method_setCharacteristicNotification = nullptr;
jmethodID BluetoothGatt::_method_writeCharacteristic = nullptr;
jmethodID BluetoothGatt::_method_writeDescriptor = nullptr;

void BluetoothGatt::initialize() {
    JNI::Env env;

    if (_cls.get() == nullptr) {
        _cls = env.find_class("android/bluetooth/BluetoothGatt");
    }

    if (!_method_close) {
        _method_close = env->GetMethodID(_cls.get(), "close", "()V");
    }

    if (!_method_connect) {
        _method_connect = env->GetMethodID(_cls.get(), "connect", "()Z");
    }

    if (!_method_disconnect) {
        _method_disconnect = env->GetMethodID(_cls.get(), "disconnect", "()V");
    }

    if (!_method_discoverServices) {
        _method_discoverServices = env->GetMethodID(_cls.get(), "discoverServices", "()Z");
    }

    if (!_method_getServices) {
        _method_getServices = env->GetMethodID(_cls.get(), "getServices", "()Ljava/util/List;");
    }

    if (!_method_readCharacteristic) {
        _method_readCharacteristic = env->GetMethodID(_cls.get(), "readCharacteristic",
                                                      "(Landroid/bluetooth/BluetoothGattCharacteristic;)Z");
    }

    if (!_method_readDescriptor) {
        _method_readDescriptor = env->GetMethodID(_cls.get(), "readDescriptor",
                                                  "(Landroid/bluetooth/BluetoothGattDescriptor;)Z");
    }

    if (!_method_setCharacteristicNotification) {
        _method_setCharacteristicNotification = env->GetMethodID(_cls.get(), "setCharacteristicNotification",
                                                                 "(Landroid/bluetooth/BluetoothGattCharacteristic;Z)Z");
    }

    if (!_method_writeCharacteristic) {
        _method_writeCharacteristic = env->GetMethodID(_cls.get(), "writeCharacteristic",
                                                       "(Landroid/bluetooth/BluetoothGattCharacteristic;)Z");
    }

    if (!_method_writeDescriptor) {
        _method_writeDescriptor = env->GetMethodID(_cls.get(), "writeDescriptor",
                                                   "(Landroid/bluetooth/BluetoothGattDescriptor;)Z");
    }
}

BluetoothGatt::BluetoothGatt() {}

BluetoothGatt::BluetoothGatt(JNI::Object obj) : _obj(obj) {}

void BluetoothGatt::check_initialized() const {
    if (!_obj) throw std::runtime_error("BluetoothGatt is not initialized");
}

void BluetoothGatt::close() {
    check_initialized();

    _obj.call_void_method(_method_close);
}

bool BluetoothGatt::connect() {
    check_initialized();

    return _obj.call_boolean_method(_method_connect);
}

void BluetoothGatt::disconnect() {
    check_initialized();

    _obj.call_void_method(_method_disconnect);
}

bool BluetoothGatt::discoverServices() {
    check_initialized();

    return _obj.call_boolean_method(_method_discoverServices);
}

std::vector<BluetoothGattService> BluetoothGatt::getServices() {
    check_initialized();

    JNI::Object services_obj = _obj.call_object_method(_method_getServices);
    if (!services_obj) return std::vector<BluetoothGattService>();

    std::vector<BluetoothGattService> result;
    JNI::Types::List list(services_obj);
    JNI::Types::Iterator iterator = list.iterator();
    while (iterator.hasNext()) {
        JNI::Object service = iterator.next();

        if (!service) continue;
        result.push_back(BluetoothGattService(service));
    }

    return result;
}

bool BluetoothGatt::readCharacteristic(BluetoothGattCharacteristic characteristic) {
    check_initialized();

    return _obj.call_boolean_method(_method_readCharacteristic, characteristic.getObject().get());
}

bool BluetoothGatt::readDescriptor(BluetoothGattDescriptor descriptor) {
    check_initialized();

    return _obj.call_boolean_method(_method_readDescriptor, descriptor.getObject().get());
}

bool BluetoothGatt::setCharacteristicNotification(BluetoothGattCharacteristic characteristic, bool enable) {
    check_initialized();

    return _obj.call_boolean_method(_method_setCharacteristicNotification, characteristic.getObject().get(), enable);
}

bool BluetoothGatt::writeCharacteristic(BluetoothGattCharacteristic characteristic) {
    check_initialized();

    return _obj.call_boolean_method(_method_writeCharacteristic, characteristic.getObject().get());
}

bool BluetoothGatt::writeDescriptor(BluetoothGattDescriptor descriptor) {
    check_initialized();

    return _obj.call_boolean_method(_method_writeDescriptor, descriptor.getObject().get());
}

}  // namespace Android
}  // namespace SimpleBLE
