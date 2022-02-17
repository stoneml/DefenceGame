#pragma once
#include "Widgets/SCompoundWidget.h"


//Slate�γ�������slate�γ�������ϸ����
//����ʹ��Slate�ķ������д�������������ͨ��UMG

class SScreenLoading :public SCompoundWidget
{

public:

	//UE�Լ��ĺ꣬����Slate�����Ǹ�ȫ�ֵģ�������д������Ƕ�Ӧ����ΪSlate���ࡣ
	SLATE_BEGIN_ARGS(SScreenLoading)
	{}
	SLATE_END_ARGS();

	//��ʼ������
	//��ʼ���Ĳ�������֧����չ�ģ�Ĭ�Ͼ��ǻ�ȡFArguments����չ��������MapName
	void Construct(const FArguments& InArgs,const FString& InMapName);


private:

	//���һ�����������ؼ�飬���ԺͶ�ȡ�ؿ����ȵĴ�����а󶨣�Ȼ���ȡ����ǰ�Ķ�ȡ���ȡ�
	//TOptional ���Ǵ���һ����ѡ��ֵ��
	//����const �����ڲ������޷����޸�,ֻ�ܹ�����
	TOptional<float> GetProgress() const;

	//�����ͼ��ͼ����
	FString MapName;



};