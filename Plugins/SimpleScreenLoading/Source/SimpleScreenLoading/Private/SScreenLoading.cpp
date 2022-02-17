#include <SScreenLoading.h>
#include <Widgets/Images/SImage.h>
#include <Widgets/Notifications/SProgressBar.h>



void SScreenLoading::Construct(const FArguments& InArgs, const FString& InMapName)
{
	//获取传入的Map名称
	MapName = InMapName;

	//子类的slot创建，临时看效果
	ChildSlot
		[
			SNew(SProgressBar)//Slate创建，创建一个换成进度条
			.Percent(this,&SScreenLoading::GetProgress)  //数据绑定方法，和UMG的Bindwidget类似。
		];

}

TOptional<float> SScreenLoading::GetProgress() const
{
	//通过异步来获取到关卡读取百分比
	//在没有加载和完成的时候返回值为-1，然后在加载过程中就是会有一个数值变化
	float LoadPercentage = GetAsyncLoadPercentage(*MapName);

	//最后返回读取百分比
	//默认返回的值是0-100，但是progressbar是0-1
	return LoadPercentage*0.01;

}

