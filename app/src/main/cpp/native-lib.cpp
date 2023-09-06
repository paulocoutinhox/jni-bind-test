#include <jni.h>
#include <string>
#include "JNIPlatformProxy.hpp"

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *pjvm, void * /*reserved*/) {
    xplpc::proxy::JNIPlatformProxy::shared()->setPlatformJavaVM(pjvm);
    xplpc::proxy::JNIPlatformProxy::shared()->initialize();
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