#include "Tool/ScreenMove.h"
#include "GameFramework/PlayerController.h"
#include <GameFramework/Controller.h>


bool FScreenMoveUnits::ListenScreenMove(APlayerController* PlayerController, const float& ScreenMoveSpeed /*= 100.f*/)
{
	//���ؼ���
	return MoveDirection(PlayerController, CursorMove(PlayerController), ScreenMoveSpeed);
}

//ʹ��ǰ���������ں������Խ���������ݴ���Ϊ.DLL��ֻ����.h
//�ڲ����slate���н���������Ϊ��̬������Ľ̳�

EScreenMoveState FScreenMoveUnits::CursorMove(const APlayerController* PlayerController)
{

	//���COntroller��Ч����ô������ֵ����
	if (PlayerController)
	{
		//��Ļλ��
		//INDEX_NONE = -1
		int32 SizeX = INDEX_NONE;
		int32 SizeY = INDEX_NONE;

		//���λ��,����Ĭ��ֵ
		float MousePositionX = -107374176.f;
		float MousePositionY = -107374176.f;

		//��̬��ȡ��Ļλ��
		PlayerController->GetViewportSize(SizeX, SizeY);

		//��̬��ȡ��Ļλ��
		PlayerController->GetMousePosition(MousePositionX, MousePositionY);

		//�ж����X��Y���λ��
		//Ҫ�����������Ļ�ߴ緶Χ��
		if (MousePositionX >= 0 && MousePositionX <= SizeX &&
			MousePositionY >= 0 && MousePositionY <= SizeY)
		{
			//�жϸ��ӽ�˭����A��MousePosition - B��0 �Ƿ�����5���ݴ�ֵ���ķ�Χ��
			float ErrorTolerance = 5.0f;

			//������жϣ�һ��Ҫ��б������������������жϣ�����ᱻ��������ֱ�ӽض�
			if (FMath::IsNearlyEqual(MousePositionX, 0.f, ErrorTolerance) && FMath::IsNearlyEqual(MousePositionY, 0.f, ErrorTolerance))
			{
				return EScreenMoveState::Screen_LeftAndUp;	//����
			}
			else if (FMath::IsNearlyEqual(MousePositionX, SizeX, ErrorTolerance) && FMath::IsNearlyEqual(MousePositionY, 0.f, ErrorTolerance))
			{
				return EScreenMoveState::Screen_RightAndUp;	//����
			}
			else if (FMath::IsNearlyEqual(MousePositionX, 0.f, ErrorTolerance) && FMath::IsNearlyEqual(MousePositionY, SizeY, ErrorTolerance))
			{
				return EScreenMoveState::Screen_LeftAndDown;	//����
			}
			else if (FMath::IsNearlyEqual(MousePositionX, SizeX, ErrorTolerance) && FMath::IsNearlyEqual(MousePositionY, SizeY, ErrorTolerance))
			{
				return EScreenMoveState::Screen_RightAndDown;	//����
			}
			else if (FMath::IsNearlyEqual(MousePositionX, 0.f, ErrorTolerance))
			{
				return EScreenMoveState::Screen_Left;		//��
			}
			else if (FMath::IsNearlyEqual(SizeX, MousePositionX, ErrorTolerance))
			{
				return EScreenMoveState::Screen_Right;		//��
			}
			else if (FMath::IsNearlyEqual(MousePositionY, 0.f, ErrorTolerance))
			{
				return EScreenMoveState::Screen_Up;			//��
			}
			else if (FMath::IsNearlyEqual(MousePositionY, SizeY, ErrorTolerance))
			{
				return EScreenMoveState::Screen_Down;		//��
			}
		}
	}

	//���Controller��Ч����ô�ͷ���None
	return EScreenMoveState::Screen_None;

}

bool FScreenMoveUnits::MoveDirection(APlayerController* PlayerController, EScreenMoveState ScreenMoveState, const float& ScreenMoveSpeed /*= 100.f*/)
{
	//����ƫ��ֵ
	FVector OffsetValue = FVector::ZeroVector;

	//���Controller��Pawn��Ϊ��
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

		//���ƫ��ֵ
		PlayerController->GetPawn()->AddActorWorldOffset(OffsetValue);

	}

	//�ж��Ƿ񲻵���0������Ǿ���Ϊ��
	return OffsetValue != FVector::ZeroVector;
}

