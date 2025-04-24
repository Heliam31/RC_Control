#pragma once

#include <jni.h>
#include <vector>
#include "Common.hpp"

namespace SimpleBLE {
namespace JNI {
namespace Types {
class Iterator {
  public:
    Iterator(JNI::Object obj);

    bool hasNext();
    JNI::Object next();

  private:
    static JNI::Class _cls;
    static jmethodID _method_hasNext;
    static jmethodID _method_next;

    static void initialize();
    void check_initialized() const;
    JNI::Object _obj;
};
}  // namespace Types
}  // namespace JNI
}  // namespace SimpleBLE