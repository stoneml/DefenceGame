#pragma once
#include "Widgets/SCompoundWidget.h"


//Slate课程内容在slate课程中有详细讲解
//这是使用Slate的方法进行创建，而不是普通的UMG

class SScreenLoading :public SCompoundWidget
{

public:

	//UE自己的宏，创建Slate，这是个全局的，里面填写的类就是对应创建为Slate的类。
	SLATE_BEGIN_ARGS(SScreenLoading)
	{}
	SLATE_END_ARGS();

	//初始化函数
	//初始化的参数可以支持扩展的，默认就是获取FArguments，扩展后可以添加MapName
	void Construct(const FArguments& InArgs,const FString& InMapName);


private:

	//添加一个进度条返回检查，可以和读取关卡进度的代理进行绑定，然后获取到当前的读取进度。
	//TOptional 就是传入一个可选择值。
	//加上const 代表内部内容无法被修改,只能够访问
	TOptional<float> GetProgress() const;

	//保存地图地图名字
	FString MapName;



};