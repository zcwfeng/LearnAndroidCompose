package top.zcwfeng.learncompose.native

import android.util.Log
import top.zcwfeng.learncompose.ui.compose.data.Student



class JNIDemo {
    val TAG = JNIDemo.javaClass.name

    val name = "David" // 等下 用 C++代码，修改为Beyond

    external fun changeName() // 改变我们的属性name

    /**
     * A native method that is implemented by the 'temp' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    external fun callAddMethod()//c 调用java
    external fun callShowStringMethod()
    //(II)I
    fun addMethod(num1:Int,num2:Int):Int {
        println("zcwfeng.top C调用kt/java函数：")
        return num1 + num2;
    }
    //(Ljava/lang/String;I)Ljava/lang/String;
    fun  showString(str:String,value:Int):String{
        println("param1:$str,param2:$value")
        return "$str======$value"
    }

    external fun testArrayAction(
        count: Int,
        textInfo: String,
        ints: IntArray,
        strs: Array<String>
    ) // String引用类型，玩数组

    // 只玩Student对象里面的成员
    external fun putObject(student: Student, str: String) // 传递引用类型，传递对象


    // 只玩Person对象里面的成员
    external fun insertObject() // 凭空创建Java对象


    // 只玩Dog对象 构造方法
    external fun testQuote() // 测试引用

    external fun delQuote() // 释放全局引用


    companion object {
        @JvmStatic
        val age = 10
        @JvmStatic
        external fun changeAge() // 改变我们的属性name

        // Used to load the 'temp' library on application startup.
        init {
            System.loadLibrary("learncompose")
        }
    }

    fun testArray() {
        val ints = intArrayOf(1, 2, 3, 4, 5, 6)
        val strs = arrayOf("李小龙", "李连杰", "李元霸")
        testArrayAction(99, "你好", ints, strs)
        for (anInt in ints) {
            Log.d(TAG, "test01: java ints:$anInt")
        }
        for (str in strs) {
            Log.e(TAG, "test01: java strs:$str")
        }
    }

    fun testPutObject(){
        val student = Student()
        student.name = "史泰龙"
        student.age = 88
        putObject(student, "九阳神功")

        println("studnet:$student")
    }

}