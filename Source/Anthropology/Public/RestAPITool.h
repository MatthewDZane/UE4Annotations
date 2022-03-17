// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Http.h"

#include "Response.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RestAPITool.generated.h"



/**
 * 
 */
UCLASS(Blueprintable)
class ANTHROPOLOGY_API URestAPITool : public UObject
{
	GENERATED_BODY()

public:
	URestAPITool();
	URestAPITool(FString AnnotationAPIUrlIn);
	~URestAPITool();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString AnnotationAPIUrl;
	
private:
	FHttpModule* Http;

	// Endpoints
	const FString AnnotationsEndPoint = "/annotations";
	const FString AnnotationsByIdEndPoint = "/annotations/byId";
	const FString AnnotationsByGroupEndPoint = "/annotations/byGroup";
	const FString AnnotationsByUrlEndPoint = "/annotations/byUrl";
	const FString GroupsEndPoint = "/groups";
	const FString GroupsByGroupNameEndPoint = "/groups/byGroupName";
	
	FResponse ResponseData;
	bool bResponseDataReady = false;
	
public:
	// Getter Functions for Endpoints
	UFUNCTION(BlueprintCallable)
	FString GetAnnotationsEndPoint();
	UFUNCTION(BlueprintCallable)
	FString GetAnnotationsByIdEndPoint();
	UFUNCTION(BlueprintCallable)
	FString GetAnnotationsByGroupEndPoint();
	UFUNCTION(BlueprintCallable)
	FString GetAnnotationsByUrlEndPoint();
	UFUNCTION(BlueprintCallable)
	FString GetGroupsEndPoint();
	UFUNCTION(BlueprintCallable)
	FString GetGroupsByGroupNameEndPoint();

	UFUNCTION(BlueprintCallable)
	FResponse GetResponseData();
	UFUNCTION(BlueprintCallable)
	bool GetResponseDataReady();

	/* Get Request Functions */
	// Get Annotation Functions
	UFUNCTION(BlueprintCallable)
	void GetAnnotations();
	UFUNCTION(BlueprintCallable)
	void GetAnnotationsById(int Id);
	UFUNCTION(BlueprintCallable)
	void GetAnnotationsByGroup(FString GroupName);
	UFUNCTION(BlueprintCallable)
	void GetAnnotationsByUrl(FString UrlIn);
	
	// Get Group Functions
	UFUNCTION(BlueprintCallable)
	void GetGroups();
	UFUNCTION(BlueprintCallable)
	void GetGroupsByGroupName(FString GroupName);

	void OnAnnotationsResponse(FHttpRequestPtr Request,
							   FHttpResponsePtr Response,
							   bool bWasSuccessful);
	void OnGroupsResponse(FHttpRequestPtr Request,
						  FHttpResponsePtr Response,
						  bool bWasSuccessful);

	/* Post Request Functions */
	// Post Annotations Functions
	UFUNCTION(BlueprintCallable)
	void PostAnnotation(FAnnotation Annotation);
	UFUNCTION(BlueprintCallable)
	void PostGroup(FGroup Group);

	UFUNCTION(BlueprintCallable)
	void PutAnnotationById(FAnnotation Annotation);
	UFUNCTION(BlueprintCallable)
	void PutGroupByGroupName(FString CurrentGroupName, FGroup Group);

	void OnUpdateResponse(FHttpRequestPtr Request,
						 FHttpResponsePtr Response,
						 bool bWasSuccessful);
	/**
	 * Prints the Verb, the Url, and, if the verb is POST or PUSH, the Request
	 * Body of the Request.
	 */
	static void PrintRequest(FHttpRequestPtr Request, FString ContentString = "");

	/**
	* Prints the Verb and the Url of the Request, along with whether the
	* Request was successful.
	*/
	static void PrintRequestSuccess(FHttpRequestPtr Request,
									bool bWasSuccessful);
	
};
