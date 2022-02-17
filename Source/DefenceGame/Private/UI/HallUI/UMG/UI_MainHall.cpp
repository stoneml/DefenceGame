// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HallUI/UMG/UI_MainHall.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include "UI/HallUI/UMG/UI_HallMenuSystem.h"
#include <UI_TutorialsWebsite.h>
#include <UI_GameSettingsSystem.h>
#include <UI_ArchivesSystem.h>
#include <Components/SizeBox.h>
#include <Components/Border.h>

//使用模板函数来进行内容的添加
template<class T, class UserObject >
UserObject *CreateAssistWidget(T* ThisClass, UClass* AssistClass, USizeBox* WidgetArray)
{
	//创建一个自定义类
	UserObject* UserObjectElement = nullptr;

	//播放UI动画的判断
	if (0)
	{
		//播放淡入
	}

	//判断sizebox中是否有东西
	if (WidgetArray->GetChildAt(0))  //判断子类第0位是否有效
	{
		if (WidgetArray->GetChildAt(0)->IsA(AssistClass))  //判断当前这个类是不是我们指定的class（使用 IsA）
		{
			//播放 Borad 淡出动画

			//如果是当前的Class，那么就直接进行返回
			return UserObjectElement;
		}
		else
		{
			//如果不是当前传入的assistClass那么就要添加新的元素到SizeBox
			//因此先执行清楚当前SizeBox的所有ChildActor  SizeBox中只能放置一个Child，也就是当有新的东西进入的时候，移除旧的
			WidgetArray->ClearChildren();
		}
	}

	//最后创建指定的Widget
	UserObjectElement = CreateWidget<UserObject>(ThisClass->GetWorld(), AssistClass);

	//进行判断
	if (UserObjectElement)
	{
		//如果有效就将当前UI添加到SizeBox上
		if (WidgetArray->AddChild(UserObjectElement))
		{

		}
		else
		{
			//如果无效就移除
			UserObjectElement->RemoveFromParent();
		}
	}

	return UserObjectElement;	//最后返回当前Widget
}


void UUI_MainHall::NativeConstruct()
{
	Super::NativeConstruct();

	//如果当前UI中的HallMenuSystem为真的话
	if (HallMenuSystem)
	{
		//GameStart
		{
			FOnButtonReleasedEvent Delegate;  //创建一个动态多播代理
			Delegate.AddDynamic(this, &UUI_MainHall::GameStart);	//通过代理进行绑定函数，方法和常规的按键点击事件的绑定方法相同
			HallMenuSystem->BindGameStart(Delegate);  //最后将点击GameStart的那个代理进行传递到HallMenuSystem当中
		}
		//SecretTerritory
		{
			FOnButtonReleasedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::SecretTerritory);
			HallMenuSystem->BindSecretTerritory(Delegate);
		}
		//History
		{
			FOnButtonReleasedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::Histroy);
			HallMenuSystem->BindHistory(Delegate);
		}
		//GameSettings
		{
			FOnButtonReleasedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::GameSettings);
			HallMenuSystem->BindGameSettings(Delegate);
		}
		//TutorialsWebsite
		{
			FOnButtonReleasedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::TutorialsWebsite);
			HallMenuSystem->BindTutorialWebsite(Delegate);
		}
		//Brower
		{
			FOnButtonReleasedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::Brower);
			HallMenuSystem->BindBrower(Delegate);
		}
		//SpecialContent
		{
			FOnButtonReleasedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::SpecialContent);
			HallMenuSystem->BindSpecialContent(Delegate);
		}
		//QuitGame
		{
			FOnButtonReleasedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::QuitGame);
			HallMenuSystem->BindQuitGame(Delegate);
		}
	}

}


void UUI_MainHall::GameStart()
{
	UGameplayStatics::OpenLevel(GetWorld(), "SelectMap");
}

void UUI_MainHall::SecretTerritory()
{
	
}

void UUI_MainHall::Histroy()
{
	//使用模板类进行对应的UI创建
	CreateAssistWidget<UUI_MainHall, UUI_ArchivesSystem>(this, AcrchivesSystemClass, BoxList);
}

void UUI_MainHall::GameSettings()
{
	CreateAssistWidget<UUI_MainHall, UUI_GameSettingsSystem>(this, GameSettingsSystemClass, BoxList);
}

void UUI_MainHall::TutorialsWebsite()
{
	CreateAssistWidget<UUI_MainHall, UUI_TutorialsWebsite>(this, TutorialsSystemClass, BoxList);
}

void UUI_MainHall::Brower()
{

}


void UUI_MainHall::SpecialContent()
{

}

void UUI_MainHall::QuitGame()
{
	//退出游戏
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
}
