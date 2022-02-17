#include "Tool/ScreenMove.h"
#include "GameFramework/PlayerController.h"
#include <GameFramework/Controller.h>


bool FScreenMoveUnits::ListenScreenMove(APlayerController* PlayerController, const float& ScreenMoveSpeed /*= 100.f*/)
{
	//返回监听
	return MoveDirection(PlayerController, CursorMove(PlayerController), ScreenMoveSpeed);
}

//使用前置声明，在后续可以将插件的内容创建为.DLL，只公开.h
//在插件与slate中有将功能设置为动态函数库的教程

EScreenMoveState FScreenMoveUnits::CursorMove(const APlayerController* PlayerController)
{

	//如果COntroller有效，那么进行有值返回
	if (PlayerController)
	{
		//屏幕位置
		//INDEX_NONE = -1
		int32 SizeX = INDEX_NONE;
		int32 SizeY = INDEX_NONE;

		//鼠标位置,随意默认值
		float MousePositionX = -107374176.f;
		float MousePositionY = -107374176.f;

		//动态获取屏幕位置
		PlayerController->GetViewportSize(SizeX, SizeY);

		//动态获取屏幕位置
		PlayerController->GetMousePosition(MousePositionX, MousePositionY);

		//判断鼠标X、Y轴的位置
		//要满足鼠标在屏幕尺寸范围内
		if (MousePositionX >= 0 && MousePositionX <= SizeX &&
			MousePositionY >= 0 && MousePositionY <= SizeY)
		{
			//判断更接近谁，用A：MousePosition - B：0 是否是在5（容错值）的范围内
			float ErrorTolerance = 5.0f;

			//这里的判断，一定要让斜向方向的条件进行先行判断，否则会被左右上下直接截断
			if (FMath::IsNearlyEqual(MousePositionX, 0.f, ErrorTolerance) && FMath::IsNearlyEqual(MousePositionY, 0.f, ErrorTolerance))
			{
				return EScreenMoveState::Screen_LeftAndUp;	//左上
			}
			else if (FMath::IsNearlyEqual(MousePositionX, SizeX, ErrorTolerance) && FMath::IsNearlyEqual(MousePositionY, 0.f, ErrorTolerance))
			{
				return EScreenMoveState::Screen_RightAndUp;	//右上
			}
			else if (FMath::IsNearlyEqual(MousePositionX, 0.f, ErrorTolerance) && FMath::IsNearlyEqual(MousePositionY, SizeY, ErrorTolerance))
			{
				return EScreenMoveState::Screen_LeftAndDown;	//左下
			}
			else if (FMath::IsNearlyEqual(MousePositionX, SizeX, ErrorTolerance) && FMath::IsNearlyEqual(MousePositionY, SizeY, ErrorTolerance))
			{
				return EScreenMoveState::Screen_RightAndDown;	//右下
			}
			else if (FMath::IsNearlyEqual(MousePositionX, 0.f, ErrorTolerance))
			{
				return EScreenMoveState::Screen_Left;		//左
			}
			else if (FMath::IsNearlyEqual(SizeX, MousePositionX, ErrorTolerance))
			{
				return EScreenMoveState::Screen_Right;		//右
			}
			else if (FMath::IsNearlyEqual(MousePositionY, 0.f, ErrorTolerance))
			{
				return EScreenMoveState::Screen_Up;			//上
			}
			else if (FMath::IsNearlyEqual(MousePositionY, SizeY, ErrorTolerance))
			{
				return EScreenMoveState::Screen_Down;		//下
			}
		}
	}

	//如果Controller无效，那么就返回None
	return EScreenMoveState::Screen_None;

}

bool FScreenMoveUnits::MoveDirection(APlayerController* PlayerController, EScreenMoveState ScreenMoveState, const float& ScreenMoveSpeed /*= 100.f*/)
{
	//计算偏移值
	FVector OffsetValue = FVector::ZeroVector;

	//如果Controller和Pawn都为真
	if (PlayerController&&PlayerController->GetPawn())
	{
		switch (ScreenMoveState)
		{
		case Screen_Up:
			OffsetValue = FVector(ScreenMoveSpeed, 0.0f, 0.0f);
			break;
		case Screen_Down:
			OffsetValue = FVector(-ScreenMoveSpeed, 0.0f, 0.0f);
			break;
		case Screen_Right:
			OffsetValue = FVector(0.0f, ScreenMoveSpeed, 0.0f);
			break;
		case Screen_Left:
			OffsetValue = FVector(0.0f, -ScreenMoveSpeed, 0.0f);
			break;
		case Screen_RightAndUp:
			OffsetValue = FVector(ScreenMoveSpeed, ScreenMoveSpeed, 0.0f);
			break;
		case Screen_RightAndDown:
			OffsetValue = FVector(-ScreenMoveSpeed, ScreenMoveSpeed, 0.0f);
			break;
		case Screen_LeftAndUp:
			OffsetValue = FVector(ScreenMoveSpeed, -ScreenMoveSpeed, 0.0f);
			break;
		case Screen_LeftAndDown:
			OffsetValue = FVector(-ScreenMoveSpeed, -ScreenMoveSpeed, 0.0f);
			break;
		}

		//添加偏移值
		PlayerController->GetPawn()->AddActorWorldOffset(OffsetValue);

	}

	//判断是否不等于0，如果是就是为真
	return OffsetValue != FVector::ZeroVector;
}

