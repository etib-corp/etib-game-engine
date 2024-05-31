##
## EPITECH PROJECT, 2024
## etib-game-engine
## File description:
## Makefile
##

CLANG = /home/julithein/Android/Sdk/ndk/27.0.11718014/toolchains/llvm/prebuilt/linux-x86_64/bin/clang

AAPT = /home/julithein/Android/Sdk/build-tools/34.0.0/aapt

JARSIGNER = /usr/bin/jarsigner

ZIPALIGN = /home/julithein/Android/Sdk/build-tools/34.0.0/zipalign

ANDROID_JAR = /home/julithein/Android/Sdk/platforms/android-34/android.jar

ANDROID_LIBS = /home/julithein/Android/Sdk/ndk/27.0.11718014/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include

ANDROID_LIBS_LINK = /home/julithein/Android/Sdk/ndk/27.0.11718014/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/aarch64-linux-android/29

SRC = 	src/main.cpp \
	  	../../src/WindowVR.cpp

all:
	rm temp.apk questxrexample.apk || true
	$(CLANG) --target=aarch64-linux-android29 -ffunction-sections -Os -fdata-sections -fvisibility=hidden -m64 -Os -fPIC -DANDROIDVERSION=29 -DANDROID -I./include -I../../include -I../../include/external/vr/include -I./src -I$(ANDROID_LIBS) -I$(ANDROID_LIBS)/android $(SRC) ../../include/external/vr/src/android_native_app_glue.c ../../include/external/vr/lib/libopenxr_loader.so -L$(ANDROID_LIBS_LINK) -s -lm -lGLESv3 -lEGL -landroid -llog -shared -uANativeActivity_onCreate -L../.. -o build/lib/arm64-v8a/libquestxrexample.so
	$(AAPT) package -f -F temp.apk -I $(ANDROID_JAR) -M src/AndroidManifest.xml -S resources -A build/assets -v --target-sdk-version 29 build
	$(JARSIGNER) -sigalg SHA1withRSA -digestalg SHA1 -verbose -keystore debug.keystore -storepass android temp.apk androiddebugkey
	$(ZIPALIGN) -f -v 4 temp.apk questxrexample.apk