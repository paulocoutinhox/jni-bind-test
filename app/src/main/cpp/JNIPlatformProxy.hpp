#pragma once

#include "jni_bind_release.h"

#include <memory>
#include <string>

namespace xplpc::proxy {
    class JNIPlatformProxy {
    public:
        static std::shared_ptr<JNIPlatformProxy> shared();

        void initialize();

        void initializePlatform();

        bool hasMapping(const std::string &name);

        void setPlatformJavaVM(JavaVM *pjvm);

    private:
        static std::shared_ptr<JNIPlatformProxy> instance;

        static constexpr ::jni::Class kPlatformProxy{
                "com/paulocoutinho/jnibindtest/PlatformProxy",
                ::jni::Static{
                        ::jni::Method{"onInitializePlatform", ::jni::Return<void>{},
                                      ::jni::Params{}},
                        ::jni::Method{"onHasMapping", ::jni::Return<jboolean>{},
                                      ::jni::Params<jstring>{}},
                },
        };

        JavaVM *platformJavaVM;
    };

}
