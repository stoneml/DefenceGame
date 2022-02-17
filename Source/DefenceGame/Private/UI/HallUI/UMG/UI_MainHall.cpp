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

//ʹ��ģ�庯�����������ݵ����
template<class T, class UserObject >
UserObject *CreateAssistWidget(T* ThisClass, UClass* AssistClass, USizeBox* WidgetArray)
{
	//����һ���Զ�����
	UserObject* UserObjectElement = nullptr;

	//����UI�������ж�
	if (0)
	{
		//���ŵ���
	}

	//�ж�sizebox���Ƿ��ж���
	if (WidgetArray->GetChildAt(0))  //�ж������0λ�Ƿ���Ч
	{
		if (WidgetArray->GetChildAt(0)->IsA(AssistClass))  //�жϵ�ǰ������ǲ�������ָ����class��ʹ�� IsA��
		{
			//���� Borad ��������

			//����ǵ�ǰ��Class����ô��ֱ�ӽ��з���
			return UserObjectElement;
		}
		else
		{
			//������ǵ�ǰ�����assistClass��ô��Ҫ����µ�Ԫ�ص�SizeBox
			//�����ִ�������ǰSizeBox������ChildActor  SizeBox��ֻ�ܷ���һ��Child��Ҳ���ǵ����µĶ��������ʱ���Ƴ��ɵ�
			WidgetArray->ClearChildren();
		}
	}

	//��󴴽�ָ����Widget
	UserObjectElement = CreateWidget<UserObject>(ThisClass->GetWorld(), AssistClass);

	//�����ж�
	if (UserObjectElement)
	{
		//�����Ч�ͽ���ǰUI��ӵ�SizeBox��
		if (WidgetArray->AddChild(UserObjectElement))
		{

		}
		else
		{
			//�����Ч���Ƴ�
			UserObjectElement->RemoveFromParent();
		}
	}

	return UserObjectElement;	//��󷵻ص�ǰWidget
}


void UUI_MainHall::NativeConstruct()
{
	Super::NativeConstruct();

	//�����ǰUI�е�HallMenuSystemΪ��Ļ�
	if (HallMenuSystem)
	{
		//GameStart
		{
			FOnButtonReleasedEvent Delegate;  //����һ����̬�ಥ����
			Delegate.AddDynamic(this, &UUI_MainHall::GameStart);	//ͨ��������а󶨺����������ͳ���İ�������¼��İ󶨷�����ͬ
			HallMenuSystem->BindGameStart(Delegate);  //��󽫵��GameStart���Ǹ�������д��ݵ�HallMenuSystem����
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
	//ʹ��ģ������ж�Ӧ��UI����
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
	//�˳���Ϸ
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
}
