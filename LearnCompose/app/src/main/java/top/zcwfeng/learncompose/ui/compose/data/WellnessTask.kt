package top.zcwfeng.learncompose.ui.compose.data

import androidx.compose.runtime.MutableState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue

/**
 * 创建一个文件WellnessTask.kt，对包含 ID 和标签的任务进行建模。将其定义为数据类。
 */
data class WellnessTask(val id: Int, val label: String, var initialChecked: Boolean = false) {
    var checked by mutableStateOf(initialChecked)
}

