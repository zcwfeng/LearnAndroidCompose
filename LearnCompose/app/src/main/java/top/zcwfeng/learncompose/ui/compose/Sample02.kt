package top.zcwfeng.learncompose.ui.compose
import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import top.zcwfeng.learncompose.R

@Composable
fun BirthdayGreetingWithImage(message: String, from: String, modifier: Modifier = Modifier) {
    val image = painterResource(R.drawable.androidparty)
    Image(painter = image, contentDescription = null, contentScale = ContentScale.Crop)
    BirthdayGreetingWithText(message = message, from = from)

}

@Composable
fun BirthdayGreetingWithText(message: String, from: String, modifier: Modifier = Modifier) {
    Column(
        modifier = Modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Top,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(text = message, fontSize = 36.sp, modifier = Modifier.padding(top = 16.dp))
        Text(
            text = from,
            fontSize = 24.sp,
            modifier = Modifier
                .padding(top = 16.dp)
                .align(alignment = Alignment.End)
        )
    }
}