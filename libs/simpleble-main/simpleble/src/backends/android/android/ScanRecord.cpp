#include "ScanRecord.h"
#include "ParcelUUID.h"
#include "SparseArray.h"
#include "jni/List.h"
#include "jni/Types.h"

namespace SimpleBLE {
namespace Android {

JNI::Class ScanRecord::_cls;
jmethodID ScanRecord::_method_getServiceUuids = nullptr;
jmethodID ScanRecord::_method_getManufacturerData = nullptr;
jmethodID ScanRecord::_method_toString = nullptr;

void ScanRecord::initialize() {
    JNI::Env env;

    if (_cls.get() == nullptr) {
        _cls = env.find_class("android/bluetooth/le/ScanRecord");
    }

    if (!_method_getServiceUuids) {
        _method_getServiceUuids = env->GetMethodID(_cls.get(), "getServiceUuids", "()Ljava/util/List;");
    }

    if (!_method_getManufacturerData) {
        _method_getManufacturerData = env->GetMethodID(_cls.get(), "getManufacturerSpecificData",
                                                       "()Landroid/util/SparseArray;");
    }

    if (!_method_toString) {
        _method_toString = env->GetMethodID(_cls.get(), "toString", "()Ljava/lang/String;");
    }
}

ScanRecord::ScanRecord(JNI::Object obj) : _obj(obj) {}

void ScanRecord::check_initialized() const {
    if (!_obj) throw std::runtime_error("ScanRecord is not initialized");
}

std::vector<std::string> ScanRecord::getServiceUuids() {
    check_initialized();

    JNI::Object service_uuids_obj = _obj.call_object_method(_method_getServiceUuids);
    if (!service_uuids_obj) return {};

    std::vector<std::string> result;
    JNI::Types::List list(service_uuids_obj);
    JNI::Types::Iterator iterator = list.iterator();
    while (iterator.hasNext()) {
        ParcelUUID parcel_uuid = ParcelUUID(iterator.next());
        result.push_back(parcel_uuid.getUuid().toString());
    }

    return result;
}

std::map<uint16_t, kvn::bytearray> ScanRecord::getManufacturerData() {
    check_initialized();

    JNI::Object manufacturer_data_obj = _obj.call_object_method(_method_getManufacturerData);
    if (!manufacturer_data_obj) return {};

    SparseArray<JNI::ByteArray> sparse_array(manufacturer_data_obj);

    std::map<uint16_t, kvn::bytearray> result;
    for (int i = 0; i < sparse_array.size(); i++) {
        uint16_t key = sparse_array.keyAt(i);
        JNI::ByteArray value = sparse_array.valueAt(i);
        result[key] = value.bytes();
    }
    return result;
}

std::string ScanRecord::toString() {
    check_initialized();
    return _obj.call_string_method(_method_toString);
}

}  // namespace Android
}  // namespace SimpleBLE