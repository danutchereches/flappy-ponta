package org.cocos2dx.plugin;

public interface InterfaceGameServices {
	public final int PluginType = 7;
	
	public void setDebugMode(boolean debug);
	public String getSDKVersion();
	public String getPluginVersion();
	
	public void startSession();
	public void stopSession();
	public void initiateSignIn();
	public void signOut();
	public void showLeaderboard();
	public void showAchievements();
	public void publishScore(int score);
	public void unlockAchievement(int id);
	
	public boolean isSignedIn();
}
