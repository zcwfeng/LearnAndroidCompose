package top.zcwfeng.learncompose.ui.compose.data;

import android.util.Log;

public class Person {

    private static final String TAG = Person.class.getSimpleName();

    public Student student;

    // 已经被C++调用了  call setStudent student:Student{name='李元霸', age=99}
    public void setStudent(Student student) {
        Log.d(TAG, "call setStudent student:" + student.toString());
        this.student = student;
    }

    // 已经被C++调用了  call static putStudent student:Student{name='刘奋', age=99}
    public static void putStudent(Student student) {
        Log.d(TAG, "call static putStudent student:" + student.toString());
    }

}