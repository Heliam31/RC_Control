#pragma once

#include <atomic>
#include <condition_variable>
#include <kvn_safe_callback.hpp>
#include <kvn_safe_map.hpp>
#include <map>
#include <mutex>
#include "jni/Common.hpp"

namespace SimpleBLE {
namespace Android {
namespace Bridge {

class ClassHandler;

class BluetoothGattCallback {
  public:
    BluetoothGattCallback();
    virtual ~BluetoothGattCallback();
    jobject get() { return _obj.get(); }  // TODO: Remove once nothing uses this

    void set_callback_onConnectionStateChange(std::function<void(bool)> callback);
    void set_callback_onServicesDiscovered(std::function<void(void)> callback);

    void set_callback_onCharacteristicChanged(JNI::Object characteristic,
                                              std::function<void(std::vector<uint8_t> value)> callback);
    void clear_callback_onCharacteristicChanged(JNI::Object characteristic);

    void set_flag_characteristicWritePending(JNI::Object characteristic);
    void clear_flag_characteristicWritePending(JNI::Object characteristic);
    void wait_flag_characteristicWritePending(JNI::Object characteristic);

    void set_flag_characteristicReadPending(JNI::Object characteristic);
    void clear_flag_characteristicReadPending(JNI::Object characteristic, std::vector<uint8_t> value);
    std::vector<uint8_t> wait_flag_characteristicReadPending(JNI::Object characteristic);

    void set_flag_descriptorWritePending(JNI::Object descriptor);
    void clear_flag_descriptorWritePending(JNI::Object descriptor);
    void wait_flag_descriptorWritePending(JNI::Object descriptor);

    void set_flag_descriptorReadPending(JNI::Object descriptor);
    void clear_flag_descriptorReadPending(JNI::Object descriptor, std::vector<uint8_t> value);
    std::vector<uint8_t> wait_flag_descriptorReadPending(JNI::Object descriptor);

    bool connected;
    bool services_discovered;
    uint16_t mtu;

    // Not for public use
    // clang-format off
    static void jni_onConnectionStateChangeCallback(JNI::Object thiz_obj, jint status, jint new_state);
    static void jni_onServicesDiscoveredCallback(JNI::Object thiz_obj, jint status);
    static void jni_onServiceChangedCallback(JNI::Object thiz_obj);

    static void jni_onCharacteristicChangedCallback(JNI::Object thiz_obj, JNI::Object characteristic_obj, JNI::ByteArray value);
    static void jni_onCharacteristicReadCallback(JNI::Object thiz_obj, JNI::Object characteristic_obj, JNI::ByteArray value, jint status);
    static void jni_onCharacteristicWriteCallback(JNI::Object thiz_obj, JNI::Object characteristic_obj, jint status);

    static void jni_onDescriptorReadCallback(JNI::Object thiz_obj, JNI::Object descriptor_obj, JNI::ByteArray value, jint status);
    static void jni_onDescriptorWriteCallback(JNI::Object thiz_obj, JNI::Object descriptor_obj, jint status);

    static void jni_onMtuChangedCallback(JNI::Object thiz_obj, jint mtu, jint status);
    static void jni_onPhyReadCallback(JNI::Object thiz_obj, jint txPhy, jint rxPhy, jint status);
    static void jni_onPhyUpdateCallback(JNI::Object thiz_obj, jint txPhy, jint rxPhy, jint status);
    static void jni_onReadRemoteRssiCallback(JNI::Object thiz_obj, jint rssi, jint status);
    static void jni_onReliableWriteCompletedCallback(JNI::Object thiz_obj, jint status);
    // clang-format on

  private:
    struct FlagData {
        bool flag = false;
        std::condition_variable cv;
        std::mutex mtx;
        std::vector<uint8_t> value;
    };

    static void initialize();

    static JNI::Class _cls;

    static kvn::safe_map<JNI::Object, BluetoothGattCallback*, JNI::JniObjectComparator> _map;

    JNI::Object _obj;

    kvn::safe_callback<void(bool)> _callback_onConnectionStateChange;
    kvn::safe_callback<void()> _callback_onServicesDiscovered;

    kvn::safe_map<JNI::Object, kvn::safe_callback<void(std::vector<uint8_t>)>, JNI::JniObjectComparator>
        _callback_onCharacteristicChanged;

    kvn::safe_map<JNI::Object, FlagData, JNI::JniObjectComparator> _flag_characteristicWritePending;
    kvn::safe_map<JNI::Object, FlagData, JNI::JniObjectComparator> _flag_characteristicReadPending;
    kvn::safe_map<JNI::Object, FlagData, JNI::JniObjectComparator> _flag_descriptorWritePending;
    kvn::safe_map<JNI::Object, FlagData, JNI::JniObjectComparator> _flag_descriptorReadPending;

    friend class ClassHandler;
};

}  // namespace Bridge
}  // namespace Android
}  // namespace SimpleBLE