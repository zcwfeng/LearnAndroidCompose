package top.zcwfeng.learncompose.ui.compose

import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.*
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import top.zcwfeng.learncompose.R
@Preview(showSystemUi = true, showBackground = true)
@Composable
fun prevDemo() {
    demoTextJustify()
}


val text1 = "Jetpack Compose tutorial"
val text2 =
    "Jetpack Compose is a modern toolkit for building native Android UI. Compose simplifies and accelerates UI development on Android with less code, powerful tools, and intuitive Kotlin APIs."
val text3 =
    "In this tutorial, you build a simple UI component with declarative functions. You call Compose functions to say what elements you want and the Compose compiler does the rest. Compose is built around Composable functions. These functions let you define your app\\'s UI programmatically because they let you describe how it should look and provide data dependencies, rather than focus on the process of the UI\\'s construction, such as initializing an element and then attaching it to a parent. To create a Composable function, you add the @Composable annotation to the function name."

@Composable
fun demoTextJustify() {
    val image = painterResource(id = R.drawable.androidparty)
    Column(
    ) {
        Image(painter = image, contentDescription = null, contentScale = ContentScale.FillWidth, modifier = Modifier.fillMaxWidth())
        Text(
            text = text1,
            fontSize = 24.sp, modifier = Modifier.padding(16.dp)
        )
        Text(
            text = text2,
            textAlign = TextAlign.Justify, modifier = Modifier.padding(start = 16.dp, end = 16.dp)
        )
        Text(
            text = text3,
            textAlign = TextAlign.Justify, modifier = Modifier.padding(16.dp)
        )
    }
}