package top.zcwfeng.learncompose.native

import android.util.Log
import top.zcwfeng.learncompose.ui.compose.ComposeDetailActivity
import top.zcwfeng.learncompose.ui.compose.data.Student


class JNIDemo(_composeDetailActivity: ComposeDetailActivity) {
    val TAG = JNIDemo.javaClass.name

    val composeDetailActivity = _composeDetailActivity

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
    fun addMethod(num1: Int, num2: Int): Int {
        println("zcwfeng.top C调用kt/java函数：")
        return num1 + num2;
    }

    //(Ljava/lang/String;I)Ljava/lang/String;
    fun showString(str: String, value: Int): String {
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

    external fun dynamicJavaMethod()
    external fun dynamicJavaMethodParam(value: String): Int

    external fun nativeThread();
    external fun nativeClose();
    external fun sort(arr: IntArray);

    companion object {
        @JvmStatic
        val age = 10

        // 假设这里定义了一大堆变量
        @JvmStatic
        var name1 = "T1"
        @JvmStatic
        var name2 = "T2"
        @JvmStatic
        var name3 = "T3"

        @JvmStatic
        external fun changeAge() // 改变我们的属性name
        @JvmStatic
        external fun localCache(name:String)
        @JvmStatic
        external fun initialCache()
        @JvmStatic
        external fun staticCache(name:String)
        @JvmStatic
        external fun clearStaticCache()
        @JvmStatic
        external fun exception()// C++ 处理异常
        @JvmStatic
        @Throws(NoSuchFieldException::class)
        external fun exception2() // C++异常抛出给java

        @JvmStatic
        external fun exception3()// java抛出异常给C++

        // 此函数是 让 C++调用的native层 来 调用的函数
        @Throws(Exception::class)
        @JvmStatic
        fun show() {
            Log.d("top.zcwfeng", "show: 111")
            Log.d("top.zcwfeng", "show: 222")
            Log.d("top.zcwfeng", "show: 333")
            Log.d("top.zcwfeng", "show: 444")
            Log.d("top.zcwfeng", "show: 555")
            throw NullPointerException("我是java中的抛出的异常，我的show方法里面发送了Java语法错误")
        }

        // Used to load the 'temp' library on application startup.
        init {
            System.loadLibrary("learncompose")
        }
    }



    fun  exceptionAction() {
        exception();

        try {
            exception2()
        } catch (e: Exception) {
            Log.d("top.zcwfeng", "Java层的 exception2 异常被我捕获到了...");
        }

        exception3();
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

    fun testPutObject() {
        val student = Student()
        student.name = "史泰龙"
        student.age = 88
        putObject(student, "九阳神功")

        println("studnet:$student")
    }

    fun sortAction(){
        println("sortAction")

        var arr = intArrayOf(11,22,-3,2,4,6,-15)
        sort(arr)
        for (element in arr) {
            print("${element.toString()} \t")
        }
    }


    /**
     * 静态缓存策略
     */
    fun staticCacheAction() {
        // 下面是局部缓存 的演示
        localCache("李元霸")
        localCache("李元霸")
        localCache("李元霸")

        // ...
        Log.e("Derry", "name1:$name1")


        // TODO 下面是静态缓存区域==============================
        // 模拟在 构造函数里面初始化
        initialCache() // 先初始化静态缓存(注意：如果是一个类去调用，就需要在构造函数中初始化)
        staticCache("李白") // 再执行...
        Log.e("top.zcwfeng", "静态缓存区域name1:$name1")
        Log.e("top.zcwfeng", "静态缓存区域name2:$name2")
        Log.e("top.zcwfeng", "静态缓存区域name3:$name3")

        staticCache("李小龙")
        Log.e("top.zcwfeng", "静态缓存区域name1:$name1")
        Log.e("top.zcwfeng", "静态缓存区域name2:$name2")
        Log.e("top.zcwfeng", "静态缓存区域name3:$name3")

        staticCache("李连杰")
        Log.e("top.zcwfeng", "静态缓存区域name1:$name1")
        Log.e("top.zcwfeng", "静态缓存区域name2:$name2")
        Log.e("top.zcwfeng", "静态缓存区域name3:$name3")

        staticCache("李贵")
        Log.e("top.zcwfeng", "静态缓存区域name1:$name1")
        Log.e("top.zcwfeng", "静态缓存区域name2:$name2")
        Log.e("top.zcwfeng", "静态缓存区域name3:$name3")

        staticCache("李逵")
        Log.e("top.zcwfeng", "静态缓存区域name1:$name1")
        Log.e("top.zcwfeng", "静态缓存区域name2:$name2")
        Log.e("top.zcwfeng", "静态缓存区域name3:$name3")
        staticCache("李鬼")
        Log.e("top.zcwfeng", "静态缓存区域name1:$name1")
        Log.e("top.zcwfeng", "静态缓存区域name2:$name2")
        Log.e("top.zcwfeng", "静态缓存区域name3:$name3")

    }




}
