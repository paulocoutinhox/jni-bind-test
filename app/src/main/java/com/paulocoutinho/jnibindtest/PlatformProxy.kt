package com.paulocoutinho.jnibindtest

import android.util.Log

class PlatformProxy {
    companion object {
        @JvmStatic
        fun onHasMapping(name: String): Boolean {
            Log.i("JNI-BIND","PlatformProxy::onHasMapping")
            return true
        }

        @JvmStatic
        fun onInitializePlatform() {
            Log.i("JNI-BIND","PlatformProxy::onInitializePlatform")
        }
    }
}
