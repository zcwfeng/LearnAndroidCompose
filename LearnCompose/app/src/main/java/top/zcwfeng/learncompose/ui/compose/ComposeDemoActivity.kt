package top.zcwfeng.learncompose.ui.compose

import android.annotation.SuppressLint
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.activity.compose.setContent
import androidx.compose.material3.Scaffold
import androidx.compose.runtime.Composable
import androidx.fragment.app.FragmentActivity
import top.zcwfeng.learncompose.ui.theme.LearnComposeTheme
import top.zcwfeng.learncompose.utils.*

class ComposeDemoActivity : AppCompatActivity() {


    companion object {
        fun launch(context: FragmentActivity?) {
            val intent = Intent(context, ComposeDemoActivity::class.java)
            context?.startActivity(intent)
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            LearnComposeApp(this)
        }
    }
}


val demoNames = mutableListOf(
    Pair("基础简单使用入门", DEMO_1),
    Pair("布局简单使用", DEMO_2),
    Pair("Compose中的状态和开关按钮使用:计算汇率Demo", DEMO_3),
    Pair("完整的List带有状态Demo", DEMO_4),
    Pair("完整滑动页面例子", DEMO_5),
    Pair("Jetpack Compose 重组状态详解", DEMO_6),
    Pair("--------------------------", ""),
    Pair("NDK Demo Base", NDK_DEMO_1),
    Pair("NDK Array", NDK_DEMO_2),
    Pair("NDK Class putObject", NDK_DEMO_3),
    Pair("NDK  insertObject", NDK_DEMO_4),
    Pair("NDK test Quote", NDK_DEMO_5),
    Pair("NDK del Quote", NDK_DEMO_6),
    Pair("Fmod 变声库的例子", NDK_DEMO_FMOD)


)

fun onMyItemClick(context: FragmentActivity?, str: String) {
    ComposeDetailActivity.launch(context, str)
}


@SuppressLint("UnusedMaterial3ScaffoldPaddingParameter")
@Composable
fun LearnComposeApp(context: FragmentActivity?) {
    LearnComposeTheme {
        Scaffold {
            MyList(demoNames, onItemClick = {
                onMyItemClick(context, it)
            })
        }

    }
}