#include <jni.h>
#include <stdio.h>
#include "HelloWorld.h"

JNIEXPORT void JNICALL Java_HelloWorld_print(JNIEnv *env, jobject object){
    printf("hello world \n");
    return;
}
