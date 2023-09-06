#include <jni.h>
#include <string>
#include <codecvt>
#include <locale>

#include "JNIPlatformProxy.hpp"

using Utf8Converter = std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, std::codecvt_mode::little_endian>, char16_t>;

std::string jniUTF8FromString(JNIEnv *env, const jstring jstr) {
    auto length = env->GetStringLength(jstr);
    const jchar *u16 = env->GetStringChars(jstr, nullptr);
    auto *p = reinterpret_cast<const char16_t *>(u16);
    std::string out = Utf8Converter{}.to_bytes(p, p + length);
    env->ReleaseStringChars(jstr, u16);
    return out;
}

jstring jniStringFromUTF8(JNIEnv *env, const std::string &str) {
    std::u16string u16 = Utf8Converter{}.from_bytes(str);
    jstring res = env->NewString(reinterpret_cast<const jchar *>(u16.data()), u16.size());
    return res;
}

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

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_paulocoutinho_jnibindtest_MainActivity_testJNI(JNIEnv *env, jobject thiz, jstring name) {
    return xplpc::proxy::JNIPlatformProxy::shared()->hasMapping(jniUTF8FromString(env, name));
}