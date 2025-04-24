#include "ParcelUUID.h"

namespace SimpleBLE {
namespace Android {

JNI::Class ParcelUUID::_cls;
jmethodID ParcelUUID::_method_getUuid = nullptr;

void ParcelUUID::initialize() {
    JNI::Env env;

    if (_cls.get() == nullptr) {
        _cls = env.find_class("android/os/ParcelUuid");
    }

    if (!_method_getUuid) {
        _method_getUuid = env->GetMethodID(_cls.get(), "getUuid", "()Ljava/util/UUID;");
    }
}

ParcelUUID::ParcelUUID() {}

ParcelUUID::ParcelUUID(JNI::Object obj) : _obj(obj) {}

void ParcelUUID::check_initialized() const {
    if (!_obj) throw std::runtime_error("ParcelUUID is not initialized");
}

UUID ParcelUUID::getUuid() {
    check_initialized();
    return UUID(_obj.call_object_method(_method_getUuid));
}

}  // namespace Android
}  // namespace SimpleBLE