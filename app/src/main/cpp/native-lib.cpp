#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "native-lib"
// __VA_ARGS__ 代表 ...的可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG,  __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG,  __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG,  __VA_ARGS__);

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myjni_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "hello c";
//    return env->NewStringUTF(hello.c_str());//c++ code
    return (*env).NewStringUTF(hello.c_str());//c code
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_myjni_MainActivity_test1(JNIEnv *env,
        jobject thiz,
        jboolean jboolean1,
        jbyte jbyte1,
        jchar jchar1,
        /*,jshort s,
         * jlong l,
         * jfloat f,
         * jdouble d */
         jstring name_
         /*,jint age*/,
         jintArray i_,
         jobjectArray strs,
         jobject person
         /*jbooleanArray bArray*/) {
    // TODO: implement test1()
    LOGD("test1 print NULL %d", NULL);
    LOGD("test1 print NULL %c", NULL);
    //1. 接收 Java 传递过来的 boolean 值
    unsigned char b_boolean = jboolean1;
    LOGD("boolean-> %d", b_boolean);
    LOGD("sizeof(unsigned char)-> %d", sizeof(unsigned char));

    //2. 接收 Java 传递过来的 boolean 值
    char c_byte = jbyte1;
    LOGD("jbyte-> %d", c_byte);
    LOGD("sizeof(char)-> %d", sizeof(char));

    //3. 接收 Java 传递过来的 char 值
    unsigned short c_char = jchar1;
    LOGD("char-> %d", c_char);
    LOGD("sizeof(c_char)-> %d", sizeof(c_char));

/*
    //4. 接收 Java 传递过来的 short 值
    short s_short = jshort1;
    LOGD("short-> %d", s_short);

    //5. 接收 Java 传递过来的 long 值
    long l_long = jlong1;
    LOGD("long-> %d", l_long);

    //6. 接收 Java 传递过来的 float 值
    float f_float = jfloat1;
    LOGD("float-> %f", f_float);

    //7. 接收 Java 传递过来的 double 值
    double d_double = jdouble1;
    LOGD("double-> %f", d_double);
*/
    //8. 接收 Java 传递过来的 String 值
    const char *name_string = env->GetStringUTFChars(name_, 0);
    LOGD("string-> %s", name_string);
    //如果不再使用就要释放
    env->ReleaseStringUTFChars(name_, name_string);
    const char *name_string2 = env->GetStringUTFChars(name_, 0);
    //验证发现释放后，还是有值?
    LOGD("print string after call release : %s", name_string);
    LOGD("print string after call release name_string2: %s", name_string2);//还是有值的。
/*
    //9. 接收 Java 传递过来的 int 值
    int age_java = age;
    LOGD("int:%d", age_java);
*/
    //10. 打印 Java 传递过来的 int []
    jint *intArray = env->GetIntArrayElements(i_, NULL);
    //拿到数组长度
    jsize intArraySize = env->GetArrayLength(i_);
    for (int i = 0; i < intArraySize; ++i) {
        LOGD("intArray->%d：", intArray[i]);
    }
    //释放数组
    env->ReleaseIntArrayElements(i_, intArray, 0);
    for (int i = 0; i < intArraySize; ++i) {
        LOGD("print after release intArray->%d：", intArray[i]);
    }

    //11. 打印 Java 传递过来的 String[]
    jsize stringArrayLength = env->GetArrayLength(strs);
    for (int i = 0; i < stringArrayLength; ++i) {
        jobject jobject1 = env->GetObjectArrayElement(strs, i);//获取对象数组中的元素
        //强转 JNI String
        jstring stringArrayData = static_cast<jstring >(jobject1);

        //转 C  String
        const char *itemStr = env->GetStringUTFChars(stringArrayData, NULL);
        LOGD("String[%d]: %s", i, itemStr);
        //回收 String[]
        env->ReleaseStringUTFChars(stringArrayData, itemStr);
    }


    //12. 打印 Java 传递过来的 Object 对象
    //12.1 获取字节码
    const char *person_class_str = "com/example/myjni/bean/Person";
    //12.2 转 jni jclass
    jclass person_class = env->FindClass(person_class_str);
    //12.3 拿到方法签名 javap -s
    const char *sig = "()Ljava/lang/String;";
    jmethodID jmethodID1 = env->GetMethodID(person_class, "getName", sig);

    jobject obj_string = env->CallObjectMethod(person, jmethodID1);
    jstring perStr = static_cast<jstring >(obj_string);
    const char *itemStr2 = env->GetStringUTFChars(perStr, NULL);
    LOGD("Person: %s \n", itemStr2);
    //12.4 获取年龄方法签名
    const char * get_age_sig = "()I";
    jmethodID jmethodId_for_get_age = env->GetMethodID(person_class,"getAge",get_age_sig);
    jint  jint_age = env->CallIntMethod(person,jmethodId_for_get_age);
    int  age = jint_age;
    LOGD("Person,age: %d \n", age);

    env->DeleteLocalRef(person_class); // 回收
    env->DeleteLocalRef(person); // 回收

    /*
    //13. 打印 Java 传递过来的 booleanArray
    jsize booArrayLength = env->GetArrayLength(bArray_);
    jboolean *bArray = env->GetBooleanArrayElements(bArray_, NULL);
    for (int i = 0; i < booArrayLength; ++i) {
        bool b =  bArray[i];
        jboolean b2 =  bArray[i];
        LOGD("boolean:%d",b)
        LOGD("jboolean:%d",b2)
    }
    //回收
    env->ReleaseBooleanArrayElements(bArray_, bArray, 0);*/

}
extern "C" //支持 C 语言
JNIEXPORT void JNICALL //告诉虚拟机，这是jni函数
Java_com_example_myjni_MainActivity_nativeCount(JNIEnv *env, jobject instance) {
    jclass cls = env->GetObjectClass(instance);
    jfieldID fieldID = env->GetFieldID(cls, "count", "I");

    /*if (env->MonitorEnter(instance) != JNI_OK) {
        LOGE("%s: MonitorEnter() failed", __FUNCTION__);
    }*/

    /* synchronized block */
    int val = env->GetIntField(instance, fieldID);
    val++;
    LOGI("count=%d", val);
    env->SetIntField(instance, fieldID, val);

    /*if (env->ExceptionOccurred()) {
        LOGE("ExceptionOccurred()...");
        if (env->MonitorExit(instance) != JNI_OK) {
            LOGE("%s: MonitorExit() failed", __FUNCTION__);
        };
    }

    if (env->MonitorExit(instance) != JNI_OK) {
        LOGE("%s: MonitorExit() failed", __FUNCTION__);
    };*/
}
extern "C"//支持 C 语言
JNIEXPORT void JNICALL//告诉虚拟机，这是jni函数
Java_com_example_myjni_MainActivity_syncNativeCount(JNIEnv *env, jobject instance) {
    jclass cls = env->GetObjectClass(instance);
    jfieldID fieldID = env->GetFieldID(cls, "count", "I");

    if (env->MonitorEnter(instance) != JNI_OK){
        LOGE("%s:MonitorEnter() failed",__FUNCTION__);
    }

    /* synchronized block */
    int val = env->GetIntField(instance, fieldID);
    val++;
    LOGI("count=%d", val);
    env->SetIntField(instance, fieldID, val);

    if (env->ExceptionOccurred()) {
        LOGE("ExceptionOccurred()...");
        if (env->MonitorExit(instance) != JNI_OK) {
            LOGE("%s: MonitorExit() failed", __FUNCTION__);
        };
    }

    if (env->MonitorExit(instance) != JNI_OK) {
        LOGE("%s: MonitorExit() failed", __FUNCTION__);
    };
}
// extern int main();  这样写有坑，因为 main 方法是属于 c 的，而当前是 CPP
//extern "C"{
//    int main();
//}
extern "C" JNIEXPORT void JNICALL
Java_com_example_myjni_MainActivity_testCmake(JNIEnv *env, jclass jobject
/*clazz*/
) {
    std::string hello = "Hello from C++";

//    __android_log_print(ANDROID_LOG_DEBUG, "Java_com_example_myjni_MainActivity_testCmake", "main--->:%d", main());
}
