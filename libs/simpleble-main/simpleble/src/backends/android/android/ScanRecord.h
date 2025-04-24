#pragma once

#include "UUID.h"
#include "jni/Common.hpp"

#include <map>
#include <vector>
#include "kvn/kvn_bytearray.h"

namespace SimpleBLE {
namespace Android {

class ClassHandler;

class ScanRecord {
  public:
    ScanRecord(JNI::Object obj);

    std::vector<std::string> getServiceUuids();
    std::map<uint16_t, kvn::bytearray> getManufacturerData();

    std::string toString();

  private:
    static JNI::Class _cls;
    static jmethodID _method_getServiceUuids;
    static jmethodID _method_getManufacturerData;
    static jmethodID _method_toString;

    static void initialize();
    void check_initialized() const;
    JNI::Object _obj;

    friend class ClassHandler;
};

}  // namespace Android
}  // namespace SimpleBLE