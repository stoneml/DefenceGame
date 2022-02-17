#pragma once

#include "CoreMinimal.h"

enum EScreenMoveState
{
	Screen_None,
	Screen_Up,				//��
	Screen_Down,			//��
	Screen_Right,			//��
	Screen_Left,			//��
	Screen_RightAndUp,		//����
	Screen_RightAndDown,	//����
	Screen_LeftAndUp,		//����
	Screen_LeftAndDown,		//����
	Screen_Max
};

//ǰ������һ��PlayerController
class APlayerController;

//STONETOOLCLASS_API  ��Ҫ������ӵ�����
struct STONETOOLCLASS_API FScreenMoveUnits
{

	//������Ļ�ƶ�״̬   ���ں�����չ
	// @param PlayerController  ��ҵĿ���
	// @param ScreenMoveSpeed	��Ļ�ƶ��ٶ�
	// @Return ���ص�ǰ�Ƿ��ƶ��ɹ�
	bool ListenScreenMove(APlayerController* PlayerController, const float& ScreenMoveSpeed = 100.f);


	//����������ƶ���ʱ�򣬷����ƶ�����
	//@param PlayerController ��ҵĿ���
	//@return ���ص�ǰ��׽����״̬
	EScreenMoveState CursorMove(const APlayerController* PlayerController);



	//�жϵ�ǰ�����Ƿ�����ƶ���
	//@param PlayerController   ��ҵĿ���
	//@param ScreenMoveState	�ƶ�״̬
	//@param ScreenMoveSpeed	��Ļ�ƶ��ٶ�
	//@return ���ص�ǰ�Ƿ��ƶ��ɹ�
	bool MoveDirection(APlayerController* PlayerController, EScreenMoveState ScreenMoveState,const float& ScreenMoveSpeed = 100.f);


};