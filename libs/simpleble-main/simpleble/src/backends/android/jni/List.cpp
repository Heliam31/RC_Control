#include "List.h"

namespace SimpleBLE {
namespace JNI {
namespace Types {

JNI::Class List::_cls;
jmethodID List::_method_iterator;

void List::initialize() {
    JNI::Env env;

    if (_cls.get() == nullptr) {
        _cls = env.find_class("java/util/List");
    }

    if (!_method_iterator) {
        _method_iterator = env->GetMethodID(_cls.get(), "iterator", "()Ljava/util/Iterator;");
    }
}

List::List(JNI::Object obj) : _obj(obj) { initialize(); }

void List::check_initialized() const {
    if (!_obj) throw std::runtime_error("List is not initialized");
}

Iterator List::iterator() {
    check_initialized();

    JNI::Object iterator = _obj.call_object_method(_method_iterator);
    return Iterator(iterator);
}

}  // namespace Types
}  // namespace JNI
}  // namespace SimpleBLE