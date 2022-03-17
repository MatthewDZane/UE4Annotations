#pragma once

#include "Annotation.h"
#include "Group.h"

#include "Response.generated.h"

USTRUCT(BlueprintType)
struct FResponse
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FAnnotation> Annotations;
	UPROPERTY(BlueprintReadWrite)
	TArray<FGroup> Groups;
	UPROPERTY(BlueprintReadWrite)
	bool bUpdateSuccessful;
};
