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
	//��Ԥ���ص�ʱ����Ӻ����󶨡�����󶨵ĺ������Ǵ�����BeginLoadingScreen
	FCoreUObjectDelegates::PreLoadMap.AddRaw(this, &FSimpleScreenLoadingModule::BeginLoadingScreen);

	//�ڼ�����ɺ����֪ͨ��������ǰLoading
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddRaw(this, &FSimpleScreenLoadingModule::EndLoadingScreen);
}

void FSimpleScreenLoadingModule::BeginLoadingScreen(const FString& MapName)
{
	//��ȡ��������
	FLoadingScreenAttributes LoadingScreenArg;

	//Ϊ��ʱ������Դ������ɺ󣬾�ֱ������������ȴ�����������Ƿ񲥷����
	//Ϊ��ʱ����ô��ʹ������ɣ�ҲҪ�ȴ����ŵĶ���������ɣ����ƹ�������
	LoadingScreenArg.bAutoCompleteWhenLoadingCompletes = false;

	//�Ƿ����������ǰ��Ӱ��Ϊ����ǰ������������
	LoadingScreenArg.bMoviesAreSkippable = true;

	//�Ƿ����ѭ�����ţ��ȴ��ֶ�ֹͣ����Ϊfalse�͵�һ����ϣ��ڼ������ǰ��һֱѭ����
	LoadingScreenArg.bWaitForManualStop = false;

	//������ɺ��Զ�ѭ����һ��ö�٣�
	LoadingScreenArg.PlaybackType = EMoviePlaybackType::MT_LoadingLoop;

	//���Widget���������ǵ�LoadingScreen�����Widget���ǸղŴ�����SScreenLoading
	LoadingScreenArg.WidgetLoadingScreen = SNew(SScreenLoading,MapName);

	//�����е�½ҳ��Ĳ���(�����ȡҳ�����)
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenArg);

	//����UI
	GetMoviePlayer()->PlayMovie();

}

void FSimpleScreenLoadingModule::EndLoadingScreen(UWorld* World)
{

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSimpleScreenLoadingModule, SimpleScreenLoading)