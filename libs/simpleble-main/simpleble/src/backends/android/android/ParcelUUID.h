#pragma once

#include "UUID.h"
#include "jni/Common.hpp"

namespace SimpleBLE {
namespace Android {

class ClassHandler;

class ParcelUUID {
  public:
    ParcelUUID();
    ParcelUUID(JNI::Object obj);

    UUID getUuid();

  private:
    static JNI::Class _cls;
    static jmethodID _method_getUuid;

    static void initialize();
    void check_initialized() const;
    JNI::Object _obj;

    friend class ClassHandler;
};

}  // namespace Android
}  // namespace SimpleBLE
