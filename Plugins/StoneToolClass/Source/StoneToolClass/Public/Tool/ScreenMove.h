#pragma once

#include "CoreMinimal.h"

enum EScreenMoveState
{
	Screen_None,
	Screen_Up,				//上
	Screen_Down,			//下
	Screen_Right,			//右
	Screen_Left,			//左
	Screen_RightAndUp,		//右上
	Screen_RightAndDown,	//右下
	Screen_LeftAndUp,		//左上
	Screen_LeftAndDown,		//左下
	Screen_Max
};

//前向声明一个PlayerController
class APlayerController;

//STONETOOLCLASS_API  不要忘记添加导出宏
struct STONETOOLCLASS_API FScreenMoveUnits
{

	//监听屏幕移动状态   用于后续扩展
	// @param PlayerController  玩家的控制
	// @param ScreenMoveSpeed	屏幕移动速度
	// @Return 返回当前是否移动成功
	bool ListenScreenMove(APlayerController* PlayerController, const float& ScreenMoveSpeed = 100.f);


	//当进行鼠标移动的时候，返回移动方向
	//@param PlayerController 玩家的控制
	//@return 返回当前捕捉到的状态
	EScreenMoveState CursorMove(const APlayerController* PlayerController);



	//判断当前方向是否可以移动的
	//@param PlayerController   玩家的控制
	//@param ScreenMoveState	移动状态
	//@param ScreenMoveSpeed	屏幕移动速度
	//@return 返回当前是否移动成功
	bool MoveDirection(APlayerController* PlayerController, EScreenMoveState ScreenMoveState,const float& ScreenMoveSpeed = 100.f);


};