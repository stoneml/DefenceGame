#include <SScreenLoading.h>
#include <Widgets/Images/SImage.h>
#include <Widgets/Notifications/SProgressBar.h>



void SScreenLoading::Construct(const FArguments& InArgs, const FString& InMapName)
{
	//��ȡ�����Map����
	MapName = InMapName;

	//�����slot��������ʱ��Ч��
	ChildSlot
		[
			SNew(SProgressBar)//Slate����������һ�����ɽ�����
			.Percent(this,&SScreenLoading::GetProgress)  //���ݰ󶨷�������UMG��Bindwidget���ơ�
		];

}

TOptional<float> SScreenLoading::GetProgress() const
{
	//ͨ���첽����ȡ���ؿ���ȡ�ٷֱ�
	//��û�м��غ���ɵ�ʱ�򷵻�ֵΪ-1��Ȼ���ڼ��ع����о��ǻ���һ����ֵ�仯
	float LoadPercentage = GetAsyncLoadPercentage(*MapName);

	//��󷵻ض�ȡ�ٷֱ�
	//Ĭ�Ϸ��ص�ֵ��0-100������progressbar��0-1
	return LoadPercentage*0.01;

}

