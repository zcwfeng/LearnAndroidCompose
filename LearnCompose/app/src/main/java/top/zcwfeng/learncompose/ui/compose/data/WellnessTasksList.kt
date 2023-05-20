package top.zcwfeng.learncompose.ui.compose.data

import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import top.zcwfeng.learncompose.ui.compose.WellnessTaskItem
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.lazy.rememberLazyListState

/**
 * 4. 对于任务列表本身，请创建一个名为 WellnessTasksList.kt 的新文件，并添加一个方法用于生成一些虚假数据：
 */
private fun getWellnessTasks() = List(30) { i -> WellnessTask(i, "Task # $i") }
@Composable
fun WellnessTasksList(
    modifier: Modifier = Modifier,
    list: List<WellnessTask> = remember { getWellnessTasks() }
) {
    LazyColumn(
        modifier = modifier,
        state = rememberLazyListState()
    ) {
        items(list) { task ->
            WellnessTaskItem(taskName = task.label, onClose = { })
        }
    }
}