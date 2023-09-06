#include <jni.h>
#include <string>
#include "jni_bind_release.h"

static constexpr ::jni::Class kPlatformProxy{
        "com/paulocoutinho/jnibindtest/PlatformProxy",
        ::jni::Static{
                ::jni::Method{"onInitializePlatform", ::jni::Return<void>{}, ::jni::Params{}},
                ::jni::Method{"onHasMapping", ::jni::Return<jboolean>{}, ::jni::Params<jstring>{}},
        },
};

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *pjvm, void * /*reserved*/) {
    static ::jni::JvmRef<::jni::kDefaultJvm> jvm{pjvm};
    ::jni::StaticRef<kPlatformProxy>{}("onInitializePlatform");
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM * /*jvm*/, void * /*reserved*/) {
    // need do something?
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_paulocoutinho_jnibindtest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}