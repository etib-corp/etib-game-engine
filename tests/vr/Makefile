##
## EPITECH PROJECT, 2024
## etib-game-engine
## File description:
## Makefile
##

CLANG_JULIEN = /home/julithein/Android/Sdk/ndk/27.0.11718014/toolchains/llvm/prebuilt/linux-x86_64/bin/clang

AAPT_JULIEN = /home/julithein/Android/Sdk/build-tools/34.0.0/aapt

JARSIGNER_JULIEN = /usr/bin/jarsigner

ZIPALIGN_JULIEN = /home/julithein/Android/Sdk/build-tools/34.0.0/zipalign

ANDROID_JAR_JULIEN = /home/julithein/Android/Sdk/platforms/android-34/android.jar

ANDROID_LIBS_JULIEN = /home/julithein/Android/Sdk/ndk/27.0.11718014/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include

ANDROID_LIBS_LINK_JULIEN = /home/julithein/Android/Sdk/ndk/27.0.11718014/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/aarch64-linux-android/29

CLANG_LEO = /home/pepito/Android/Sdk/ndk/27.0.11718014/toolchains/llvm/prebuilt/linux-x86_64/bin/clang

AAPT_LEO = /home/pepito/Android/Sdk/build-tools/34.0.0/aapt

JARSIGNER_LEO = /usr/bin/jarsigner

ZIPALIGN_LEO = /home/pepito/Android/Sdk/build-tools/34.0.0/zipalign

ANDROID_JAR_LEO = /home/pepito/Android/Sdk/platforms/android-34/android.jar

ANDROID_LIBS_LEO = /home/pepito/Android/Sdk/ndk/27.0.11718014/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include

ANDROID_LIBS_LINK_LEO = /home/pepito/Android/Sdk/ndk/27.0.11718014/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/aarch64-linux-android/29

SRC = 	src/main.cpp \
	  	../../src/WindowVR.cpp \
		../../imgui/*.cpp \
		../../imgui/backends/imgui_impl_opengl3.cpp \
		../../src/Mesh.cpp \
		../../src/Shader.cpp \
		../../src/ModelVR.cpp \
		../../src/Texture.cpp \
		../../src/MemoryIOSystem.cpp \
		../../src/MemoryIOStream.cpp \
		../../src/UtilsVR.cpp \

all:
	@echo "Compiling for $(USER)"
	@if [ "$(USER)" = "julithein" ]; then \
		make julien; \
	else \
		make leo; \
	fi

julien:
	rm temp.apk questxrexample.apk || true
	$(CLANG_JULIEN) -DVR --target=aarch64-linux-android29 -ffunction-sections -Os -fdata-sections -fvisibility=hidden -m64 -Os -fPIC -DANDROIDVERSION=29 -DANDROID -I./include -I./../../imgui/ -I./../../imgui/backends/ -I../../include -I../../include/external/vr/include -I./src -I$(ANDROID_LIBS_JULIEN) -I$(ANDROID_LIBS_JULIEN)/android $(SRC) ../../include/external/vr/src/android_native_app_glue.c -L../../include/external/vr/lib -lopenxr_loader -L$(ANDROID_LIBS_LINK_JULIEN) -s -lm -lGLESv3 -lEGL -landroid -llog -lc++_shared -L./build/lib/arm64-v8a -lassimp -shared -uANativeActivity_onCreate -L../.. -o build/lib/arm64-v8a/libquestxrexample.so
	mkdir -p build/lib/arm64-v8a
	cp /home/julithein/Android/Sdk/ndk/27.0.11718014/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/aarch64-linux-android/libc++_shared.so build/lib/arm64-v8a/
	$(AAPT_JULIEN) package -f -F temp.apk -I $(ANDROID_JAR_JULIEN) -M src/AndroidManifest.xml -S resources -v --target-sdk-version 29 build
	$(JARSIGNER_JULIEN) -sigalg SHA1withRSA -digestalg SHA1 -verbose -keystore debug.keystore -storepass android temp.apk androiddebugkey
	$(ZIPALIGN_JULIEN) -f -v 4 temp.apk questxrexample.apk

leo:
	rm temp.apk questxrexample.apk || true
	$(CLANG_LEO) -DVR -flto --target=aarch64-linux-android29 -ffunction-sections -Os -fdata-sections -fvisibility=hidden -m64 -Os -fPIC -DANDROIDVERSION=29 -DANDROID -I./include -I./../../imgui/ -I./../../imgui/backends/ -I../../include -I../../include/external/vr/include -I./src -I$(ANDROID_LIBS_LEO) -I$(ANDROID_LIBS_LEO)/android $(SRC) ../../include/external/vr/src/android_native_app_glue.c -L../../include/external/vr/lib -lopenxr_loader -L$(ANDROID_LIBS_LINK_LEO) -s -lm -lGLESv3 -lEGL -landroid -llog -lc++_shared -L./build/lib/arm64-v8a -lassimp -shared -uANativeActivity_onCreate -o build/lib/arm64-v8a/libquestxrexample.so
	mkdir -p build/lib/arm64-v8a
	cp /home/pepito/Android/Sdk/ndk/27.0.11718014/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/aarch64-linux-android/libc++_shared.so build/lib/arm64-v8a/
	$(AAPT_LEO) package -f -F temp.apk -I $(ANDROID_JAR_LEO) -M src/AndroidManifest.xml -S resources -v --target-sdk-version 29 build
	$(JARSIGNER_LEO) -sigalg SHA1withRSA -digestalg SHA1 -verbose -keystore debug.keystore -storepass android temp.apk androiddebugkey
	$(ZIPALIGN_LEO) -f -v 4 temp.apk questxrexample.apk
