// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

//给TowerUI创建一个单独的ID
//添加Extren是提供给外部一个全局的变量，这个变量只要是这个项目的就谁都能拿到
extern FGuid TowerICOGuid;

//全局Actor
extern AActor* TowerDoll;

//全局bool锁
extern bool bLockGUID;