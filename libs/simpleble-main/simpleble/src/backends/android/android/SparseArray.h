#pragma once

#include "jni/Common.hpp"

namespace SimpleBLE {
namespace Android {

class ClassHandler;

class SparseArrayBase {
  public:
    static void initialize();

    static JNI::Class _cls;
    static jmethodID _method_size;
    static jmethodID _method_keyAt;
    static jmethodID _method_valueAt;

    friend class ClassHandler;
};

template <typename T>
class SparseArray : public SparseArrayBase {
  public:
    SparseArray();
    SparseArray(JNI::Object obj);

    int size();
    int keyAt(int index);
    T valueAt(int index);

  private:
    void check_initialized() const;
    JNI::Object _obj;
};

}  // namespace Android
}  // namespace SimpleBLE
