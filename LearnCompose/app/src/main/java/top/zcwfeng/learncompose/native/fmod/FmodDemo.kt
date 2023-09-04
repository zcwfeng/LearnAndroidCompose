package top.zcwfeng.learncompose.native.fmod

import android.util.Log


class FmodDemo {

    external fun voiceChangeNative(mode: Int, path: String)

    companion object {
        const val path = "file:///android_asset/fmodtest.mp3"
        const val MODE_NORMAL = 0 // 正常
        const val MODE_LUOLI = 1 // 萝莉
        const val MODE_DASHU = 2 // 大叔
        const val MODE_JINGSONG = 3 // 惊悚
        const val MODE_GAOGUAI = 4 // 搞怪
        const val MODE_KONGLING = 5 // 空灵
//        init {
//            System.loadLibrary("learncompose")
//        }
    }

    // 给C++调用的函数
    // JNI 调用 Java函数的时候，忽略掉 私有、公开 等
    // (Ljava/lang/String;)V
    private fun playerEnd(msg: String) {
        Log.d("Fmod", msg)
    }
}