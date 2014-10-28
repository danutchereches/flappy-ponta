#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"

#define LOG_TAG "main"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

void cocos_android_app_init(JNIEnv* env, jobject thiz) {
	LOGD("cocos_android_app_init");
	AppDelegate *pAppDelegate = new AppDelegate();
	
	JavaVM* vm;
	env->GetJavaVM(&vm);
	PluginJniHelper::setJavaVM(vm);
}

/*
static pthread_key_t current_jni_env;
static JavaVM *java_vm;

static JNIEnv *attach_current_thread (void) {
	JNIEnv *env;
	JavaVMAttachArgs args;
	
	LOGD("attaching thread");//GST_DEBUG ("Attaching thread %p", g_thread_self ());
	args.version = JNI_VERSION_1_4;
	args.name = NULL;
	args.group = NULL;
	
	if ((*java_vm)->AttachCurrentThread (java_vm, &env, &args) < 0) {
		LOGD("Failed to attach current thread");
		return NULL;
	}
	
	return env;
}

static JNIEnv *get_jni_env (void) {
	JNIEnv *env;
	
	if ((env = pthread_getspecific (current_jni_env)) == NULL) {
		env = attach_current_thread ();
		pthread_setspecific (current_jni_env, env);
	}
	
	return env;
}

static void detach_current_thread (void *env) {
	LOGD("detaching current thread");
	(*java_vm)->DetachCurrentThread (java_vm);
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	JNIEnv *env = NULL;
	java_vm = vm;
	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		return 0;
	} 
	pthread_key_create(&current_jni_env, detach_current_thread);
	return JNI_VERSION_1_4;
}
*/
