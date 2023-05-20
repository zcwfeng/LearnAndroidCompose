package top.zcwfeng.learncompose.ui.compose

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Close
import androidx.compose.material3.Button
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import top.zcwfeng.learncompose.ui.theme.LearnComposeTheme

@Composable
fun WaterCounter(modifier: Modifier = Modifier) {
    Column(modifier = modifier.padding(16.dp)) {
        var count by rememberSaveable {
            mutableStateOf(0)
        }
        if (count > 0) {
            var showTask by remember { mutableStateOf(true) }
            if (showTask) {
                WellnessTaskItem(
                    onClose = { showTask = false },
                    taskName = "Have you taken your 15 minute walk today?"
                )
            }
            Text(
                text = "You've had $count glasses.",
                modifier = modifier.padding(16.dp)
            )
        }
        Row(Modifier.padding(top = 8.dp)) {
            Button(onClick = { count++ }, enabled = count < 10) {
                Text("Add one")
            }
            Button(onClick = { count = 0 }, Modifier.padding(start = 8.dp)) {
                Text("Clear water count")
            }
        }
    }
}

@Composable
fun WellnessScreen(modifier: Modifier = Modifier) {
//    WaterCounter(modifier)
    StatefulCounter(modifier)
}

@Composable
fun WellnessTaskItem(
    taskName: String,
    onClose: () -> Unit,
    modifier: Modifier = Modifier
) {
    Row(
        modifier = modifier, verticalAlignment = Alignment.CenterVertically
    ) {
        Text(
            modifier = Modifier
                .weight(1f)
                .padding(start = 16.dp),
            text = taskName
        )
        IconButton(onClick = onClose) {
            Icon(Icons.Filled.Close, contentDescription = "Close")
        }
    }
}


@Preview(showBackground = true)
@Composable
private fun WellnessTaskItemPreview() {
    WellnessTaskItem(taskName = "Demo", onClose = { /*TODO*/ })
}

/**
 * StatelessCounter 的作用是显示 count，并在您递增 count 时调用函数。为此，请遵循上述模式并传递状态 count（作为可组合函数的参数）和 lambda (onIncrement)（在需要递增状态时会调用此函数）
 */
@Composable
fun StatelessCounter(count: Int, onIncrement: () -> Unit, modifier: Modifier = Modifier) {
    Column(modifier = modifier.padding(16.dp)) {
        if (count > 0) {
            Text("You've had $count glasses.")
        }
        Button(onClick = onIncrement, Modifier.padding(top = 8.dp), enabled = count < 10) {
            Text("Add one")
        }
    }
}

/**
 * StatefulCounter 拥有状态。这意味着，它会存储 count 状态，并在调用 StatelessCounter 函数时对其进行修改。
 */
@Composable
fun StatefulCounter(modifier:Modifier) {
    var count by rememberSaveable { mutableStateOf(0) }
//    var juiceCount by remember { mutableStateOf(0) }

    StatelessCounter(count, { count++ })
//    StatelessCounter(juiceCount, { juiceCount++ })

}

/**
 * count 和 showTask 是记住的值。
 * 按下 Add one 按钮。此操作会递增 count（这会导致重组），并同时显示 WellnessTaskItem 和计数器 Text
 * 按下 WellnessTaskItem 组件的 X（这会导致另一项重组）。showTask 现在为 false，这意味着不再显示 WellnessTaskItem。
 * 按下 Add one 按钮（另一项重组）。如果您继续增加杯数，showTask 会记住您在下一次重组时关闭了 WellnessTaskItem。
 * 按下 Clear water count 按钮可将 count 重置为 0 并导致重组。系统不会调用显示 count 的 Text 以及与 WellnessTaskItem 相关的所有代码，并且会退出组合。
 * 由于系统未调用之前调用 showTask 的代码位置，因此会忘记 showTask。
 * 按下 Add one 按钮，使 count 大于 0（重组）。
 * 系统再次显示 WellnessTaskItem 可组合项，因为在退出上述组合时，之前的 showTask 值已被忘记
 */
@Preview(showBackground = true)
@Composable
private fun WellnessScreenPreview() {
    LearnComposeTheme {
        Surface(
            modifier = Modifier.fillMaxSize(),
            color = MaterialTheme.colorScheme.background
        ) {
            WellnessScreen()
        }
    }
}
