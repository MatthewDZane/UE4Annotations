// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Annotation.h"
#include "Group.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonParser.generated.h"

/**
 * 
 */
UCLASS()
class ANTHROPOLOGY_API UJsonParser : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Parses the Annotations String and converts the contents into a TArray of
	 * FAnnotation structs. Annotations String may be in array form or just a
	 * singular annotation form. If the Annotations String only contains one
	 * annotation, the return TArray will contain only one FAnnotation struct
	 * element.
	 */
	UFUNCTION(BlueprintCallable)
	static TArray<FAnnotation> StringToFAnnotations(FString AnnotationsString);

	/**
	 * Parses the Groups String and converts the contents into a TArray of
	 * FGroup structs. Groups String may be in array form or just a
	 * singular group form. If the Groups String only contains one
	 * group, the return TArray will contain only one FGroup struct
	 * element.
	 */
	UFUNCTION(BlueprintCallable)
	static TArray<FGroup> StringToFGroups(FString GroupsString);

	UFUNCTION(BlueprintCallable)
	static FString AnnotationToString(FAnnotation Annotation);
	UFUNCTION(BlueprintCallable)
	static FString GroupToString(FGroup Group);
};
