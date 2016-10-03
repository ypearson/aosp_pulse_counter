
package com.nklabs.android.rcnt_library;

import android.content.Context;
import android.os.IPulseCounterService;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.util.Log;

public final class PulseCounter {

    private static final String         LOG_TAG = "PulseCounter";

    private IPulseCounterService    mService = null;

    private synchronized IPulseCounterService getService() {

        if (mService == null) {

            mService = IPulseCounterService.Stub.asInterface(ServiceManager.getService("rcnt"));

            if (mService == null) {
                Log.w(LOG_TAG, "Unable to get service!");
            } else {
                Log.w(LOG_TAG, "Got service!");
            }
        }

        return mService;
    }

    public PulseCounter() {}

    public String getPulseCount() {

        String ret = "should work";

        try {
            IPulseCounterService srv = getService();

            if (srv != null) {
                ret = srv.read();
            }

        } catch (RemoteException e) {
            Log.w(LOG_TAG, "Error in getPulseCount.");
            throw new RuntimeException(e);

        }

        return ret;
    }
}
