package top.zcwfeng.learncompose.ui.compose

import android.content.Intent
import android.os.Bundle
import androidx.activity.compose.setContent
import androidx.appcompat.app.AppCompatActivity
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface

import androidx.compose.ui.Modifier
import androidx.fragment.app.FragmentActivity
import top.zcwfeng.learncompose.ui.theme.LearnComposeTheme
import top.zcwfeng.learncompose.utils.DEMO_1
import top.zcwfeng.learncompose.utils.DEMO_2
import top.zcwfeng.learncompose.utils.DEMO_3
import top.zcwfeng.learncompose.utils.DEMO_4

class ComposeDetailActivity : AppCompatActivity() {


    companion object {
        fun launch(context: FragmentActivity?,value:String) {
            val intent = Intent(context, ComposeDetailActivity::class.java)
            intent.putExtra("demo_key",value)
            context?.startActivity(intent)
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val demoStr = intent.getStringExtra("demo_key")
        setContent {
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
                            BirthdayGreetingWithImage("Hello Message"," - Weimiao")
                        DEMO_3 ->
                            TipTimeScreen()
                        DEMO_4 ->
                            MyApp(Modifier.fillMaxSize())
                    }
                }
            }
        }
    }
}





