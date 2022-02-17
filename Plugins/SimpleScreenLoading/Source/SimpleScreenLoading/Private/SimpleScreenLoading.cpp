// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleScreenLoading.h"
#include <UObject/UObjectGlobals.h>
#include <SScreenLoading.h>
#include <MoviePlayer/Public/MoviePlayer.h>

#define LOCTEXT_NAMESPACE "FSimpleScreenLoadingModule"

void FSimpleScreenLoadingModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module



}

void FSimpleScreenLoadingModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}


void FSimpleScreenLoadingModule::SetupScreenLoading()
{
	//在预加载的时候，添加函数绑定。这个绑定的函数就是创建的BeginLoadingScreen
	FCoreUObjectDelegates::PreLoadMap.AddRaw(this, &FSimpleScreenLoadingModule::BeginLoadingScreen);

	//在加载完成后进行通知，结束当前Loading
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddRaw(this, &FSimpleScreenLoadingModule::EndLoadingScreen);
}

void FSimpleScreenLoadingModule::BeginLoadingScreen(const FString& MapName)
{
	//读取画面属性
	FLoadingScreenAttributes LoadingScreenArg;

	//为假时，当资源加载完成后，就直接跳过，不会等待画面的内容是否播放完成
	//为真时，那么即使加载完成，也要等待播放的东西播放完成，类似过场动画
	LoadingScreenArg.bAutoCompleteWhenLoadingCompletes = false;

	//是否可以跳过当前电影（为真就是按任意键跳过）
	LoadingScreenArg.bMoviesAreSkippable = true;

	//是否进行循环播放（等待手动停止），为false和第一个配合，在加载完成前都一直循环。
	LoadingScreenArg.bWaitForManualStop = false;

	//播放完成后自动循环（一个枚举）
	LoadingScreenArg.PlaybackType = EMoviePlaybackType::MT_LoadingLoop;

	//添加Widget，就是我们的LoadingScreen，这个Widget就是刚才创建的SScreenLoading
	LoadingScreenArg.WidgetLoadingScreen = SNew(SScreenLoading,MapName);

	//最后进行登陆页面的播放(传入读取页面参数)
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenArg);

	//播放UI
	GetMoviePlayer()->PlayMovie();

}

void FSimpleScreenLoadingModule::EndLoadingScreen(UWorld* World)
{

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSimpleScreenLoadingModule, SimpleScreenLoading)