package top.zcwfeng.learncompose.native

import android.os.Parcel
import android.os.Parcelable

class ParcelDemo():Parcelable {
    constructor(parcel: Parcel) : this() {
        parcel.readInt()
        parcel.readInt()
    }

    override fun writeToParcel(parcel: Parcel, flags: Int) {
        parcel.writeInt(1000000)
        parcel.writeInt(9000000)
    }

    override fun describeContents(): Int {
        return 0
    }

    companion object CREATOR : Parcelable.Creator<ParcelDemo> {
        override fun createFromParcel(parcel: Parcel): ParcelDemo {
            return ParcelDemo(parcel)
        }

        override fun newArray(size: Int): Array<ParcelDemo?> {
            return arrayOfNulls(size)
        }
    }
}