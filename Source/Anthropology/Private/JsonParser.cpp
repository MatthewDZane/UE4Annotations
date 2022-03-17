// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParser.h"

#include "JsonObjectConverter.h"

TArray<FAnnotation> UJsonParser::StringToFAnnotations(FString AnnotationsString)
{
	TArray<FAnnotation> Annotations = TArray<FAnnotation>();
	if (AnnotationsString.StartsWith("["))
	{
		if (FJsonObjectConverter::JsonArrayStringToUStruct<FAnnotation>(AnnotationsString,
															&Annotations))
		{
			return Annotations;
		}

		UE_LOG(LogTemp, Warning, TEXT("Error: could not parse string %s"),
		       *AnnotationsString);
		return TArray<FAnnotation>();
	}
	
	FAnnotation Annotation;
	if (FJsonObjectConverter::JsonObjectStringToUStruct(AnnotationsString,
														&Annotation))
	{
		Annotations.Add(Annotation);
		return Annotations;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Error: could not parse string"));
	return TArray<FAnnotation>();
}

TArray<FGroup> UJsonParser::StringToFGroups(FString GroupsString)
{
	TArray<FGroup> Groups = TArray<FGroup>();
	if (GroupsString.StartsWith("["))
	{
		if (FJsonObjectConverter::JsonArrayStringToUStruct(GroupsString,
															&Groups))
		{
			return Groups;
		}

		UE_LOG(LogTemp, Warning, TEXT("Error: could not parse string"));
		return TArray<FGroup>();
	}
	
	FGroup Group;
	if (FJsonObjectConverter::JsonObjectStringToUStruct(GroupsString, &Group))
	{
		Groups.Add(Group);
		return Groups;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Error: could not parse string"));
	return TArray<FGroup>();
}

FString UJsonParser::AnnotationToString(FAnnotation Annotation)
{
	FString AnnotationString;
	FJsonObjectConverter::UStructToJsonObjectString(Annotation, AnnotationString);
	return AnnotationString;
}

FString UJsonParser::GroupToString(FGroup Group)
{
	FString GroupString;
	FJsonObjectConverter::UStructToJsonObjectString(Group, GroupString);
	return GroupString;
}
