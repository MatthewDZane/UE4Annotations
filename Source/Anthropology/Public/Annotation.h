#pragma once

#include "Annotation.generated.h"

USTRUCT(BlueprintType)
struct FAnnotation
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int Id;
	UPROPERTY(BlueprintReadWrite)
	FString Url;
	UPROPERTY(BlueprintReadWrite)
	FString Title;
	UPROPERTY(BlueprintReadWrite)
	FString Description;
	UPROPERTY(BlueprintReadWrite)
	FString Description_link;
	UPROPERTY(BlueprintReadWrite)
	FString Group_name;
	UPROPERTY(BlueprintReadWrite)
	FTransform Camera_transform;
	UPROPERTY(BlueprintReadWrite)
	FTransform Annotation_transform;
	UPROPERTY(BlueprintReadWrite)
	FString Last_updated;
};
