package top.zcwfeng.learncompose.native

class JNIDemo {

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

}