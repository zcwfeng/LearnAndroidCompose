package top.zcwfeng.learncompose.ui.compose

import FmodDemoApp
import android.content.Intent
import android.os.Bundle
import androidx.activity.compose.setContent
import androidx.appcompat.app.AppCompatActivity
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface

import androidx.compose.ui.Modifier
import androidx.fragment.app.FragmentActivity
import org.fmod.FMOD
import top.zcwfeng.learncompose.native.JNIDemo
import top.zcwfeng.learncompose.ui.theme.BasicsCodelabTheme
import top.zcwfeng.learncompose.ui.theme.LearnComposeTheme
import top.zcwfeng.learncompose.utils.*

class ComposeDetailActivity : AppCompatActivity() {
    val jniDemo: JNIDemo = JNIDemo()

    companion object {
        fun launch(context: FragmentActivity?, value: String) {
            val intent = Intent(context, ComposeDetailActivity::class.java)
            intent.putExtra("demo_key", value)
            context?.startActivity(intent)
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val demoStr = intent.getStringExtra("demo_key")
        FMOD.init(this)
        setContent {
            when (demoStr) {
                DEMO_4 ->
                    BasicsCodelabTheme() {
                        MyApp(Modifier.fillMaxSize())
                    }

                else ->
                    LearnComposeTheme {
                        // A surface container using the 'background' color from the theme
                        Surface(
                            modifier = Modifier.fillMaxSize(),
                            color = MaterialTheme.colorScheme.background
                        ) {
                            when (demoStr) {
                                DEMO_1 ->
                                    demoTextJustify()

                                DEMO_2 ->
                                    BirthdayGreetingWithImage("Hello Message", " - Weimiao")

                                DEMO_3 ->
                                    TipTimeScreen()

                                DEMO_5 ->
                                    MySootheApp()

                                DEMO_6 ->
                                    WellnessScreen()

                                NDK_DEMO_1 -> {
                                    println("name修改前是：${jniDemo.name}")
                                    jniDemo.changeName()
                                    println("name修改后是：${jniDemo.name}")


                                    println("age修改前是：${JNIDemo.age}")
                                    JNIDemo.changeAge()
                                    println("age修改后是：${JNIDemo.age}")

                                    jniDemo.callAddMethod()
                                    jniDemo.callShowStringMethod()
                                }

                                NDK_DEMO_2 -> {
                                    jniDemo.testArray()
                                }

                                NDK_DEMO_3 -> {
                                    jniDemo.testPutObject();
                                }

                                NDK_DEMO_4 -> {
                                    jniDemo.insertObject()
                                }

                                NDK_DEMO_5 -> {
                                    jniDemo.testQuote()
                                }

                                NDK_DEMO_6 -> {
                                    jniDemo.delQuote()
                                }

                                NDK_DEMO_FMOD -> {
                                    FmodDemoApp()
                                }

                            }
                        }
                    }
            }

        }
    }

    override fun onDestroy() {
        super.onDestroy()
        jniDemo.delQuote()
        FMOD.close()

    }
}





