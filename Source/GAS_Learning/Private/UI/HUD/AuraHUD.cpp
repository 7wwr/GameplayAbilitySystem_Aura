// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/Child/OverlayWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidget == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	//检查一下蓝图里是否设置了相关类，没有的话终止运行并报信息
	checkf(OverlayWidgetClass,TEXT("Overlay Widget class is null, please fill out in BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass,TEXT("Overlay Widget Controller class is null, please fill out in BP_AuraHUD"));

	//构建控件
	UUserWidget* Widget =  CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	//转化为OverlayWidget是要使用其独特的功能（SetWidgetController设置控制器）
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	//构建GetOverlayWidgetController函数所需要的参数结构体
	const FWidgetControllerParams WidgetControllerParams = FWidgetControllerParams(PC,PS,ASC,AS);
	//获取或构建Widget所需要的Controller
	UAuraWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	//将获取到的Controller绑定到相关Widget
	OverlayWidget->SetWidgetController(WidgetController);
	//完成上面操作后将Widget添加到视口上
	Widget->AddToViewport();
}
