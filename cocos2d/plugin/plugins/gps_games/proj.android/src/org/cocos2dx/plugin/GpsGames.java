package org.cocos2dx.plugin;

import org.cocos2dx.libgpsgames.R;

import com.google.android.gms.games.Games;
import com.google.games.basegameutils.GameHelper;

import android.app.Activity;
import android.util.Log;

public class GpsGames implements InterfaceGameServices, GameHelper.GameHelperListener {
	protected static final String TAG = "GpsGames";
	protected static final String LEADERBOARD_ID = "CggI2v_CsW8QAhAH";//TODO: add support for all leaderboards
	protected static final String[] ACHIEVEMENT_IDS = {
		"CgkIrJO1yJcMEAIQAg",//  0 -- score 30
		"CgkIrJO1yJcMEAIQAw",//  1 -- score 50
		"CgkIrJO1yJcMEAIQBg",//  3 -- score 70
		"CgkIrJO1yJcMEAIQBA",//  2 -- score 100
		"CgkIrJO1yJcMEAIQBQ",//  4 -- score 150
	};
	private Activity mContext = null;
	public static GameHelper mHelper;
	private boolean mIsDebug = true;
	private boolean mIsSignedIn = false;
	
	public GpsGames(Activity context) {
		mContext = context;
	}
	
	@Override
	public void setDebugMode(boolean isDebugMode) {
		mIsDebug = isDebugMode;
		
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				getGameHelper().enableDebugLog(mIsDebug);
			}
		});
	}
	
	public GameHelper getGameHelper() {
		if (mHelper == null) {
			mHelper = new GameHelper(mContext, GameHelper.CLIENT_GAMES);
			mHelper.enableDebugLog(mIsDebug);
		}
		return mHelper;
	}
	
	@Override
	public void startSession() {
		Log.e(TAG, "start sess");
		
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				if (mHelper == null) {
					getGameHelper();
				}
				mHelper.setup(GpsGames.this);
				mHelper.onStart(mContext);
				PluginWrapper.addOnActivityResultListener(mHelper);
			}
		});
	}
	
	@Override
	public void stopSession() {
		Log.e(TAG, "stop sess");
		
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				PluginWrapper.removeOnActivityResultListener(mHelper);
				mHelper.onStop();
			}
		});
	}
	
	@Override
	public void initiateSignIn() {
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				getGameHelper().beginUserInitiatedSignIn();
			}
		});
	}
	
	@Override
	public void publishScore(final int score) {
		if (!mIsSignedIn)
			return;
		
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				Games.Leaderboards.submitScore(getGameHelper().getApiClient(), LEADERBOARD_ID, score);
			}
		});
	}
	
	@Override
	public void showLeaderboard() {
		if (!mIsSignedIn)
			return;
		
		mContext.startActivityForResult(Games.Leaderboards.getLeaderboardIntent(getGameHelper().getApiClient(), LEADERBOARD_ID), 0);
	}
	
	@Override
	public void unlockAchievement(final int id) {
		if (!mIsSignedIn || id < 0 || id >= ACHIEVEMENT_IDS.length)
			return;
		
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				Games.Achievements.unlock(getGameHelper().getApiClient(), ACHIEVEMENT_IDS[id]);
			}
		});
	}
	
	@Override
	public void showAchievements() {
		if (!mIsSignedIn)
			return;
		
		mContext.startActivityForResult(Games.Achievements.getAchievementsIntent(getGameHelper().getApiClient()), 0);
	}
	
	@Override
	public boolean isSignedIn() {
		return mIsSignedIn;
	}
	
	@Override
	public void signOut() {
		mIsSignedIn = false;
		
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				getGameHelper().signOut();
			}
		});
	}
	
	@Override
	public String getSDKVersion() {
		return mContext.getString(R.integer.google_play_services_version);
	}
	
	@Override
	public String getPluginVersion() {
		return "0.0.1";
	}
	
	@Override
	public void onSignInFailed() {
		Log.e(TAG, "signin failed");
		
		mIsSignedIn = false;
	}
	
	@Override
	public void onSignInSucceeded() {
		Log.e(TAG, "signin succeded");
		
		mIsSignedIn = true;
	}
}
