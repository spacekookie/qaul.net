# Android Instructions

## Qaul variants

### flavors
each flover can be installed at the same time on the same device

#### legacy
This is the version before all this everything breaking rewrite started.
Web user interface frontend.

##### Requirements

```diff
- This version of qaul.net requires the android device to be rooted!
```

* qaul.net needs the IBSS/Ad-hoc wifi mode. This wifi standard mode was
  removed in Android 4
  * On Android < 4.x IBSS mode can be activated via the wext (wireless
    extensions).
    Some vendors ship also their 4.x devices with wext.
  * On Android >= 4 IBSS mode can be activated on some devices via
    wpa_supplicant.
* qaul.net needs ARM and Android > 2.3 Gingerbread
  (due to before unsupported pthread functions in pjsip).
* The Android device needs to be rooted.

#### nativeui
This is a native ui version of qaul.

Supports a lot of transports (adhoc/olsr, bluetoof, WifiDirect, LAN, Tor, I2P, ... send patches!!1!)

  * adhoc
    Same requirements as legacy

#### noroot
This version of qaul does not require root access, also comes without any code for it.
 * no captive portal/access point
 * no adhoc/olsr network
 * blootoof/WifiDirect depends on your android version and settings
 * LAN should allways work if you are connected to such a network
 * Tor/I2P, requires internet connection

### variants
each flavor comes in three variants

 * release
    some logging (error, warn)
 * debug
    full logging, can spit out a lot of data ;)
 * testnet
    testnet is seperated from the main network, devs can read the logs remotely.
    So it is not anonymous, but helpful to see what part of routing is gone SNAFU. :)

## Prerequisites

### Java Development Kit (JDK)

Install openjdk-8 (recommended) or any compatible version

### Android NDK
Currently the NDK 13b is required to build

https://developer.android.com/ndk/downloads/older_releases.html
https://dl.google.com/android/repository/android-ndk-r13b-linux-x86_64.zip

### Android SDK
Either command line tools or AndroidStudio is required.
https://developer.android.com/studio/index.html#downloads
command line tools are at the bottom

## Get the source

Create a new directory and cd into it

        mkdir <name>
        cd <name>

Download the source from [https://github.com/qaul/qaul.net](github)

    git clone --recursive -b cmake-android-rewrite --single-branch https://github.com/qaul/qaul.net.git .

Prepare the build:

        cd android

Create a file ```local.properties``` to tell the build tools where the SDK and NDK are located

    ndk.dir=/home/user/android/android-ndk-r13b
    sdk.dir=/home/user/android/android-sdk-linux

For the lagacy build additional files from the target device are required:

    # change to the project root folder
    cd ..

    # The compiler needs some libraries in the build directory
    # Connect your Android device to your computer and pull the libraries
    # from your device to the directory android_extra_lib:
    adb pull /system/lib/libcutils.so android_extra_lib/
    adb pull /system/lib/libwpa_client.so android_extra_lib/
    adb pull /system/bin/ifconfig android_extra_lib/
    adb pull /system/bin/iptables android_extra_lib/

    # back to the android folder
    cd android

## Build

Legacy: ./gradlew assembleLegacyDebug


noroot: ./gradlew assempleNorootDebug

You will find the newly built apk in `android/app/build/outputs/apk`.

    # install your app from the command line
    # make sure your phone is connected and debugging mode is activated
    adb install -r android/app/build/outputs/apk/qaul-debug.apk

    # uninstall app from your phone
    adb uninstall net.qaul.qaul


### Build with Android Studio

Open the android folder of the qaul.net source and let Android Studio run
the gradle scripts. Everything should be in place and you should be
able to build.

Before the qaul.net app can be built via Android Studio, one needs to
build it at least once from CLI.



Testing
-------

Start qaul.net app from CLI

    # login to your android device
    adb shell
    # become super user
    su
    # start bash
    bash
    # install location of the app is: /data/data/net.qaul.qaul
    cd /data/data/net.qaul.qaul

    # start the qaul app
    am start -n net.qaul.qaul/net.qaul.qaul.QaulActivity

