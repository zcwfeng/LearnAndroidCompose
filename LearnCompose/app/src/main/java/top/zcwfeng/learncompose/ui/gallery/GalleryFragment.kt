package top.zcwfeng.learncompose.ui.gallery

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import top.zcwfeng.learncompose.databinding.FragmentGalleryBinding
import top.zcwfeng.learncompose.native.JNIDemo
import top.zcwfeng.learncompose.ui.compose.ComposeDemoActivity

/**
 * NDK 的Demo
 */
class GalleryFragment : Fragment() {

    private var _binding: FragmentGalleryBinding? = null
    private val binding get() = _binding!!
    val jniDemo: JNIDemo = JNIDemo()

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val galleryViewModel =
            ViewModelProvider(this).get(GalleryViewModel::class.java)

        _binding = FragmentGalleryBinding.inflate(inflater, container, false)
        val root: View = binding.root

        val textView: TextView = binding.textGallery
        galleryViewModel.text.observe(viewLifecycleOwner) {
            textView.text = it
        }
        textView.setOnClickListener {
//          ComposeDemoActivity.launch(this.activity)
            textView.text = jniDemo.stringFromJNI()
        }

        println("name修改前是：${jniDemo.name}")
        jniDemo.changeName()
        println("name修改后是：${jniDemo.name}")


        println("age修改前是：${JNIDemo.age}")
        JNIDemo.changeAge()
        println("age修改后是：${JNIDemo.age}")

        jniDemo.callAddMethod()
        jniDemo.callShowStringMethod()

        return root
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}