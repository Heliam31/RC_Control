plugins {
    id("com.android.library") version "8.7.1"
}

android {
    namespace = "org.simpleble.android.bridge"
    compileSdk = 31

    defaultConfig {
        minSdk = 31
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    buildTypes {
        getByName("debug") {
            isJniDebuggable = true
        }
    }
}
