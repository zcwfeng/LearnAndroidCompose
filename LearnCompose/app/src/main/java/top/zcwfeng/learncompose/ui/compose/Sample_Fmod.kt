import android.annotation.SuppressLint
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.wrapContentSize
import androidx.compose.foundation.lazy.grid.GridCells
import androidx.compose.foundation.lazy.grid.GridItemSpan
import androidx.compose.foundation.lazy.grid.LazyVerticalGrid
import androidx.compose.foundation.lazy.grid.items
import androidx.compose.foundation.lazy.grid.itemsIndexed
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.vector.addPathNodes
import androidx.compose.ui.unit.dp
import top.zcwfeng.learncompose.native.fmod.FmodDemo
import top.zcwfeng.learncompose.ui.compose.SootheBottomNavigation
import top.zcwfeng.learncompose.ui.theme.LearnComposeTheme

@SuppressLint("UnusedMaterial3ScaffoldPaddingParameter")
@Composable
fun FmodDemoApp() {
    var fmodDemo:FmodDemo = FmodDemo()
    LearnComposeTheme() {
        Scaffold() { _ ->
            val itemsList = (0..5).toList()
            val namesList = listOf("正常","萝莉","大叔","惊悚","搞怪","空灵")
//            val itemsIndexedList = listOf("A", "B", "C")

            val itemModifier = Modifier.border(1.dp, Color.Blue).height(80.dp).wrapContentSize()

            LazyVerticalGrid(
                columns = GridCells.Fixed(3)
            ) {


                items(itemsList) {

                    Text(namesList[it], itemModifier.clickable {
                        fmodDemo.voiceChangeNative(it,FmodDemo.path)
                    })
                }
//                item {
//                    Text("Single item", itemModifier)
//                }
//                itemsIndexed(itemsIndexedList) { index, item ->
//                    Text("Item at index $index is $item", itemModifier)
//                }

            }
        }
    }
}