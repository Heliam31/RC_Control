#include "Set.h"

namespace SimpleBLE {
namespace JNI {
namespace Types {

JNI::Class Set::_cls;
jmethodID Set::_method_iterator;

void Set::initialize() {
    JNI::Env env;

    if (_cls.get() == nullptr) {
        _cls = env.find_class("java/util/Set");
    }

    if (!_method_iterator) {
        _method_iterator = env->GetMethodID(_cls.get(), "iterator", "()Ljava/util/Iterator;");
    }
}

Set::Set(JNI::Object obj) : _obj(obj) { initialize(); }

void Set::check_initialized() const {
    if (!_obj) throw std::runtime_error("Set is not initialized");
}

Iterator Set::iterator() {
    check_initialized();

    JNI::Object iterator = _obj.call_object_method(_method_iterator);
    return Iterator(iterator);
}

}  // namespace Types
}  // namespace JNI
}  // namespace SimpleBLE