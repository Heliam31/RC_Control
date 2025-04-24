#pragma once

#include "jni/Common.hpp"

namespace SimpleBLE {
namespace Android {

class ClassHandler;

class UUID {
  public:
    static void initialize();
    UUID();
    UUID(JNI::Object obj);

    std::string toString();

  private:
    static JNI::Class _cls;
    static jmethodID _method_toString;

    void check_initialized() const;
    JNI::Object _obj;

    friend class ClassHandler;
};

}  // namespace Android
}  // namespace SimpleBLE
