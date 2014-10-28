package org.cocos2dx.plugin;

import java.util.Hashtable;
import java.util.Iterator;
import java.util.Map;

import com.google.android.gms.analytics.HitBuilders;
import com.google.android.gms.analytics.HitBuilders.EventBuilder;
import com.google.android.gms.analytics.Tracker;

import android.app.Activity;
import android.util.Log;

public class GoogleAnalytics implements InterfaceAnalytics {
	
	private Activity mContext = null;
	private Tracker mTracker = null;
	protected static String TAG = "GoogleAnalytics";
	
	protected static void LogE(String msg, Exception e) {
		Log.e(TAG, msg, e);
		e.printStackTrace();
	}
	
	private static boolean isDebug = false;
	
	protected static void LogD(String msg) {
		if (isDebug) {
			Log.d(TAG, msg);
		}
	}
	
	public GoogleAnalytics(Activity context) {
		mContext = context;
	}
	
	@Override
	public void startSession(String appKey) {
		LogD("startSession invoked!");
		final String curKey = appKey;
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				com.google.android.gms.analytics.GoogleAnalytics analytics
						= com.google.android.gms.analytics.GoogleAnalytics.getInstance(mContext);
				analytics.setLocalDispatchPeriod(5);
				mTracker = analytics.newTracker(curKey);
				mTracker.enableAdvertisingIdCollection(true);
			}
		});
	}
	
	@Override
	public void stopSession() {
		LogD("stopSession invoked!");
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				com.google.android.gms.analytics.GoogleAnalytics.getInstance(mContext).dispatchLocalHits();
			}
		});
	}
	
	@Override
	public void setSessionContinueMillis(int millis) {
		LogD("setSessionContinueMillis invoked!");
		final int curMillis = millis;
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				mTracker.setSessionTimeout(curMillis);
			}
		});
	}
	
	@Override
	public void setCaptureUncaughtException(boolean isEnabled) {
		LogD("setCaptureUncaughtException invoked!");
		final boolean curEnable = isEnabled;
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				mTracker.enableExceptionReporting(curEnable);
			}
		});
	}

	@Override
	public void setDebugMode(boolean isDebugMode) {
		isDebug = isDebugMode;
	}
	
	@Override
	public void logError(String errorId, String message) {
		Hashtable<String, String> params = new Hashtable<String, String>();
		params.put("message", message);
		
		logEvent(errorId, params);
	}
	
	@Override
	public void logEvent(String eventId) {
		logEvent(eventId, new Hashtable<String, String>());
	}
	
	@Override
	public void logEvent(String eventId, Hashtable<String, String> paramMap) {
		LogD("logEvent(eventId, paramMap) invoked!");
		final String curId = eventId;
		final Hashtable<String, String> curParam = paramMap;
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				EventBuilder builder = new HitBuilders.EventBuilder();
				builder.setCategory("generic");
				builder.setAction(curId);
				
				Iterator<Map.Entry<String, String>> it = curParam.entrySet().iterator();
				while (it.hasNext()) {
					Map.Entry<String, String> entry = it.next();
					builder.set(entry.getKey(), entry.getValue());
				}
				
				mTracker.send(builder.build());
			}
		});
	}
	
	protected void logPageView(String pageName) {
		LogD("logPageView invoked! " + pageName);
		final String currPage = pageName;
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				mTracker.setScreenName(currPage);
				mTracker.send(new HitBuilders.ScreenViewBuilder().build());
			}
		});
	}
	
	@Override
	public void logTimedEventBegin(String eventId) {
		LogD("logTimedEventBegin not implemented!!!");
	}
	
	@Override
	public void logTimedEventEnd(String eventId) {
		LogD("logTimedEventEnd not implemented!!!");
	}
	
	@Override
	public String getSDKVersion() {
		return "0.0.0";
	}
	
	@Override
	public String getPluginVersion() {
		return "0.0.2";
	}
}
