#pragma once

#include <kvn_safe_callback.hpp>
#include <map>
#include "android/ScanResult.h"
#include "jni/Common.hpp"

namespace SimpleBLE {
namespace Android {
namespace Bridge {

class ClassHandler;

class ScanCallback {
  public:
    ScanCallback();
    virtual ~ScanCallback();
    jobject get() { return _obj.get(); }  // TODO: Remove once nothing uses this

    void set_callback_onScanResult(std::function<void(Android::ScanResult)> callback);
    void set_callback_onBatchScanResults(std::function<void()> callback);
    void set_callback_onScanFailed(std::function<void()> callback);

    // Not for public use
    static void jni_onScanResultCallback(JNI::Object thiz, jint callback_type, Android::ScanResult scan_result);
    static void jni_onBatchScanResultsCallback(JNI::Object thiz, JNI::Object results);
    static void jni_onScanFailedCallback(JNI::Object thiz, jint error_code);

  private:
    static JNI::Class _cls;
    static kvn::safe_map<JNI::Object, ScanCallback*, JNI::JniObjectComparator> _map;
    static void initialize();

    JNI::Object _obj;

    kvn::safe_callback<void(Android::ScanResult)> _callback_onScanResult;
    kvn::safe_callback<void()> _callback_onBatchScanResults;
    kvn::safe_callback<void()> _callback_onScanFailed;

    friend class ClassHandler;
};

}  // namespace Bridge
}  // namespace Android
}  // namespace SimpleBLE