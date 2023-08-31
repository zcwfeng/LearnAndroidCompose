package top.zcwfeng.learncompose.ui.compose

import android.annotation.SuppressLint
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.layout.wrapContentSize
import androidx.compose.foundation.lazy.grid.GridCells
import androidx.compose.foundation.lazy.grid.GridItemSpan
import androidx.compose.foundation.lazy.grid.LazyHorizontalGrid
import androidx.compose.foundation.lazy.grid.LazyVerticalGrid
import androidx.compose.foundation.lazy.grid.items
import androidx.compose.foundation.lazy.grid.itemsIndexed
import androidx.compose.foundation.pager.HorizontalPager
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import top.zcwfeng.learncompose.native.fmod.FmodDemo
import top.zcwfeng.learncompose.ui.theme.LearnComposeTheme

@SuppressLint("UnusedMaterial3ScaffoldPaddingParameter")
@Composable
fun GridHorizonDemoApp2() {
    LearnComposeTheme() {
        Scaffold{
            val itemsList = (0..5).toList()
            val itemsIndexedList = listOf("A", "B", "C")

            val itemModifier = Modifier.border(1.dp, Color.Blue).width(80.dp).wrapContentSize()

            LazyHorizontalGrid(
                rows = GridCells.Fixed(3),
                horizontalArrangement = Arrangement.spacedBy(16.dp),
                verticalArrangement = Arrangement.spacedBy(16.dp)
            ) {
                items(itemsList) {
                    Text("Item is $it", itemModifier)
                }

                item {
                    Text("Single item", itemModifier)
                }

                itemsIndexed(itemsIndexedList) { index, item ->
                    Text("Item at index $index is $item", itemModifier)
                }
            }
        }
    }
}

@Preview
@Composable
fun TestHorizonGrid2(){
    GridHorizonDemoApp2();
}