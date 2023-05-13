package top.zcwfeng.learncompose.ui.compose

import android.annotation.SuppressLint
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.activity.compose.setContent
import androidx.compose.material.Scaffold
import androidx.compose.runtime.Composable
import androidx.fragment.app.FragmentActivity
import top.zcwfeng.learncompose.ui.theme.LearnComposeTheme
import top.zcwfeng.learncompose.utils.DEMO_1
import top.zcwfeng.learncompose.utils.DEMO_2
import top.zcwfeng.learncompose.utils.DEMO_3
import top.zcwfeng.learncompose.utils.MyList

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
    Pair("Compose中的状态和开关按钮使用:计算汇率Demo", DEMO_3)

)

fun onMyItemClick(context: FragmentActivity?, str: String) {
    ComposeDetailActivity.launch(context,str)
}


@SuppressLint("UnusedMaterialScaffoldPaddingParameter")
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