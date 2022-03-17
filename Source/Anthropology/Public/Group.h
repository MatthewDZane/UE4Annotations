#pragma once

#include "Group.generated.h"

USTRUCT(BlueprintType)
struct FGroup
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FString Group_name;
	UPROPERTY(BlueprintReadWrite)
	FString Scene_settings;
};

USTRUCT(BlueprintType)
struct FPutGroup
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FString Current_group_name;
	UPROPERTY(BlueprintReadWrite)
	FGroup Group;
};
