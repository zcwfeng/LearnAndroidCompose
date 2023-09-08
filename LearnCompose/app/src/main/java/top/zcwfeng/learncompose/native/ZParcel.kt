package top.zcwfeng.learncompose.native

import top.zcwfeng.learncompose.native.ZParcel.MyObject.ZPARCEL as _
class ZParcel(nativePtr:Long = 0L) {
    var mNativePtr = nativePtr

    object MyObject{val ZPARCEL = ZParcel(0)}


    init {
        println("init......")
        mNativePtr = nativeCreate()
        println("mNativePtr......$mNativePtr")

    }

    companion object {
        fun obtain(): ZParcel = _
    }
    private external fun nativeCreate(): Long
    private external fun  nativeWriteInt(nativePtr:Long,value: Int);
    private external fun nativeSetDataPosition(nativePtr:Long,pos: Int)
    private external fun nativeReadInt(nativePtr:Long):Int

    fun writeInt(i: Int) = nativeWriteInt(mNativePtr,i)

    fun setDataPosition(i: Int) = nativeSetDataPosition(mNativePtr,i)

    fun readInt() = nativeReadInt(mNativePtr)


}