/*
 * qaul.net is free software
 * licensed under GPL (version 3)
 */

package net.qaul.qaul;

import android.app.Application;
import android.content.pm.PackageInfo;
import android.util.Log;

public class QaulApplication extends Application {
	public static final String MSG_TAG = "QaulApplication";

	@Override
	public void onCreate() {
		Log.d(MSG_TAG, "Calling onCreate()");
	}

	@Override
	public void onTerminate() {
		Log.d(MSG_TAG, "Calling onTerminate()");
		
		// this will never be called in a production environment (according to documentation)
	}

    public int getVersionNumber() {
    	int version = -1;
        try {
            PackageInfo pi = getPackageManager().getPackageInfo(getPackageName(), 0);
            version = pi.versionCode;
        } catch (Exception e) {
            Log.e(MSG_TAG, "Package name not found", e);
        }
        return version;
    }
    
    public String getVersionName() {
    	String version = "?";
        try {
            PackageInfo pi = getPackageManager().getPackageInfo(getPackageName(), 0);
            version = pi.versionName;
        } catch (Exception e) {
            Log.e(MSG_TAG, "Package name not found", e);
        }
        return version;
    }
}
