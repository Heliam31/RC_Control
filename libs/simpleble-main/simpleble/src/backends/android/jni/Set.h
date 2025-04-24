#pragma once

#include <jni.h>
#include <vector>
#include "Common.hpp"
#include "Iterator.h"

namespace SimpleBLE {
namespace JNI {
namespace Types {
class Set {
  public:
    Set(JNI::Object obj);

    Iterator iterator();

  private:
    static JNI::Class _cls;
    static jmethodID _method_iterator;

    static void initialize();
    void check_initialized() const;
    JNI::Object _obj;
};
}  // namespace Types
}  // namespace JNI
}  // namespace SimpleBLE