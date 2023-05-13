package top.zcwfeng.learncompose.utils

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp

@Composable
fun MyList(list: List<Pair<String,String>>, onItemClick:(String)->Unit) {
    LazyColumn {
        items(list) {
            Text(
                text = it.first,
                modifier = Modifier
                    .fillMaxWidth()
                    .clickable {
                        onItemClick(it.second)
                    }
                    .padding(16.dp)
            )
        }
    }
}
