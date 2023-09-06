#include "JNIPlatformProxy.hpp"
#include <cassert>

namespace xplpc::proxy {
    std::shared_ptr<JNIPlatformProxy> JNIPlatformProxy::instance = nullptr;

    std::shared_ptr<JNIPlatformProxy> JNIPlatformProxy::shared() {
        if (instance == nullptr) {
            instance = std::make_shared<JNIPlatformProxy>();
        }

        return instance;
    }

    void JNIPlatformProxy::initialize() {
        initializePlatform();
    }

    void JNIPlatformProxy::initializePlatform() {
        // set jvm from platform jvm
        static ::jni::JvmRef<::jni::kDefaultJvm> jvm{platformJavaVM};

        // call initialize platform method
        ::jni::StaticRef<kPlatformProxy>{}("onInitializePlatform");

        // another test
        hasMapping("test name");
    }

    bool JNIPlatformProxy::hasMapping(const std::string &name) {
        return ::jni::StaticRef<kPlatformProxy>{}("onHasMapping", name);
    }

    void JNIPlatformProxy::setPlatformJavaVM(JavaVM *pjvm) {
        this->platformJavaVM = pjvm;
    }
}
