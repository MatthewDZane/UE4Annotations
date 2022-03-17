// Fill out your copyright notice in the Description page of Project Settings.


#include "RestAPITool.h"

#include "JsonObjectConverter.h"
#include "JsonParser.h"

URestAPITool::URestAPITool()
{
	Http = &FHttpModule::Get();
}

URestAPITool::URestAPITool(FString AnnotationAPIUrlIn)
	: AnnotationAPIUrl(AnnotationAPIUrlIn)
{
	Http = &FHttpModule::Get();
}

URestAPITool::~URestAPITool()
{

}

// Getter Functions for Endpoints
FString URestAPITool::GetAnnotationsEndPoint()
{
	return AnnotationsEndPoint;
}

FString URestAPITool::GetAnnotationsByIdEndPoint()
{
	return AnnotationsByIdEndPoint;
}

FString URestAPITool::GetAnnotationsByGroupEndPoint()
{
	return AnnotationsByGroupEndPoint;
}

FString URestAPITool::GetAnnotationsByUrlEndPoint()
{
	return AnnotationsByUrlEndPoint;
}

FString URestAPITool::GetGroupsEndPoint()
{
	return GroupsEndPoint;
}

FString URestAPITool::GetGroupsByGroupNameEndPoint()
{
	return GroupsByGroupNameEndPoint;
}

FResponse URestAPITool::GetResponseData()
{
	return ResponseData;
}

bool URestAPITool::GetResponseDataReady()
{
	return bResponseDataReady;
}

// Get Request Functions
void URestAPITool::GetAnnotations()
{
	bResponseDataReady = false;
	
	const FHttpRequestPtr Request = Http->CreateRequest();

	const FString Url = AnnotationAPIUrl + AnnotationsEndPoint;
	Request->SetURL(Url);

	Request->SetVerb("GET");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->OnProcessRequestComplete().BindUObject(this, &URestAPITool::OnAnnotationsResponse);

	Request->ProcessRequest();
	
	PrintRequest(Request);
}

void URestAPITool::GetAnnotationsById(int Id)
{
	bResponseDataReady = false;
	
	const FHttpRequestPtr Request = Http->CreateRequest();

	const FString Url = AnnotationAPIUrl + AnnotationsByIdEndPoint + \
						"?id=" + FString::FromInt(Id);
	Request->SetURL(Url);

	Request->SetVerb("GET");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->OnProcessRequestComplete().BindUObject(this, &URestAPITool::OnAnnotationsResponse);

	Request->ProcessRequest();
	
	PrintRequest(Request);
}

void URestAPITool::GetAnnotationsByGroup(FString GroupName)
{
	bResponseDataReady = false;
	
	const FHttpRequestPtr Request = Http->CreateRequest();

	FString Url = AnnotationAPIUrl + AnnotationsByGroupEndPoint + \
				  "?group_name=" + GroupName;
	Url = Url.Replace(TEXT(" "), TEXT("%20"));
	Request->SetURL(Url);

	Request->SetVerb("GET");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->OnProcessRequestComplete().BindUObject(this, &URestAPITool::OnAnnotationsResponse);

	Request->ProcessRequest();
	
	PrintRequest(Request);
}

void URestAPITool::GetAnnotationsByUrl(FString UrlIn)
{
	bResponseDataReady = false;
	
	const FHttpRequestPtr Request = Http->CreateRequest();

	FString Url = AnnotationAPIUrl + AnnotationsByUrlEndPoint + \
				  "?url=" + UrlIn;
	Url = Url.Replace(TEXT(" "), TEXT("%20"));
	Request->SetURL(Url);

	Request->SetVerb("GET");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->OnProcessRequestComplete().BindUObject(this, &URestAPITool::OnAnnotationsResponse);

	Request->ProcessRequest();
	
	PrintRequest(Request);
}

void URestAPITool::GetGroups()
{
	bResponseDataReady = false;
	
	const FHttpRequestPtr Request = Http->CreateRequest();

	const FString Url = AnnotationAPIUrl + GroupsEndPoint;
	Request->SetURL(Url);

	Request->SetVerb("GET");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->OnProcessRequestComplete().BindUObject(this, &URestAPITool::OnGroupsResponse);

	Request->ProcessRequest();
	
	PrintRequest(Request);
}

void URestAPITool::GetGroupsByGroupName(FString GroupName)
{
	bResponseDataReady = false;
	
	const FHttpRequestPtr Request = Http->CreateRequest();

	FString Url = AnnotationAPIUrl + GroupsByGroupNameEndPoint + \
		     	  "?group_name=" + GroupName;
	Url = Url.Replace(TEXT(" "), TEXT("%20"));
	Request->SetURL(Url);

	Request->SetVerb("GET");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->OnProcessRequestComplete().BindUObject(this, &URestAPITool::OnGroupsResponse);

	Request->ProcessRequest();
	
	PrintRequest(Request);
}

void URestAPITool::OnAnnotationsResponse(FHttpRequestPtr Request,
													 FHttpResponsePtr Response,
													 bool bWasSuccessful)
{
	PrintRequestSuccess(Request, bWasSuccessful);
	if (bWasSuccessful) {
		const FString ResponseBody = Response->GetContentAsString();
		TArray<FAnnotation> Annotations;
		
		ResponseData.Annotations = UJsonParser::StringToFAnnotations(ResponseBody);
		ResponseData.Groups = TArray<FGroup>();
	}
	else
	{
		ResponseData.Annotations = TArray<FAnnotation>();
		ResponseData.Groups = TArray<FGroup>(); ;
	}

	bResponseDataReady = true;
}

void URestAPITool::OnGroupsResponse(FHttpRequestPtr Request,
												FHttpResponsePtr Response,
												bool bWasSuccessful)
{
	PrintRequestSuccess(Request, bWasSuccessful);
	if (bWasSuccessful) {
		const FString ResponseBody = Response->GetContentAsString();

		ResponseData.Annotations = TArray<FAnnotation>();
		ResponseData.Groups = UJsonParser::StringToFGroups(ResponseBody); ;
	}
	else
	{
		ResponseData.Annotations = TArray<FAnnotation>();
		ResponseData.Groups = TArray<FGroup>(); ;
	}

	bResponseDataReady = true;
}

void URestAPITool::PostAnnotation(FAnnotation Annotation)
{
	bResponseDataReady = false;
	
	const FHttpRequestPtr Request = Http->CreateRequest();

	FString Url = AnnotationAPIUrl + AnnotationsEndPoint;
	Url = Url.Replace(TEXT(" "), TEXT("%20"));
	Request->SetURL(Url);

	Request->SetVerb("POST");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->OnProcessRequestComplete().BindUObject(this, &URestAPITool::OnUpdateResponse);


	const FString ContentString = UJsonParser::AnnotationToString(Annotation);
	Request->SetContentAsString(ContentString);
	
	Request->ProcessRequest();
	
	PrintRequest(Request, ContentString);
}

void URestAPITool::PostGroup(FGroup Group)
{
	bResponseDataReady = false;
	
	const FHttpRequestPtr Request = Http->CreateRequest();

	FString Url = AnnotationAPIUrl + GroupsEndPoint;
	Url = Url.Replace(TEXT(" "), TEXT("%20"));
	Request->SetURL(Url);

	Request->SetVerb("POST");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->OnProcessRequestComplete().BindUObject(this, &URestAPITool::OnUpdateResponse);

	const FString ContentString = UJsonParser::GroupToString(Group);
	Request->SetContentAsString(ContentString);
	
	Request->ProcessRequest();
	
	PrintRequest(Request, ContentString);
}

void URestAPITool::PutAnnotationById(FAnnotation Annotation)
{
	bResponseDataReady = false;
	
	const FHttpRequestPtr Request = Http->CreateRequest();

	FString Url = AnnotationAPIUrl + AnnotationsByIdEndPoint;
	Url = Url.Replace(TEXT(" "), TEXT("%20"));
	Request->SetURL(Url);

	Request->SetVerb("PUT");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->OnProcessRequestComplete().BindUObject(this, &URestAPITool::OnUpdateResponse);

	const FString ContentString = UJsonParser::AnnotationToString(Annotation);
	Request->SetContentAsString(ContentString);
	
	Request->ProcessRequest();
	
	PrintRequest(Request, ContentString);
}

void URestAPITool::PutGroupByGroupName(FString CurrentGroupName,
                                                   FGroup Group)
{
	bResponseDataReady = false;
	
	const FHttpRequestPtr Request = Http->CreateRequest();

	FString Url = AnnotationAPIUrl + GroupsByGroupNameEndPoint;
	Url = Url.Replace(TEXT(" "), TEXT("%20"));
	Request->SetURL(Url);

	Request->SetVerb("PUT");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->OnProcessRequestComplete().BindUObject(this, &URestAPITool::OnUpdateResponse);

	const FString GroupString = UJsonParser::GroupToString(Group);
	const FString ContentString = "{ \"current_group_name\": \"" +
		CurrentGroupName + "\", \"group\": " + GroupString + "}";
	Request->SetContentAsString(ContentString);
	
	Request->ProcessRequest();
	
	PrintRequest(Request, ContentString);
}

void URestAPITool::OnUpdateResponse(FHttpRequestPtr Request,
								    FHttpResponsePtr Response,
								    bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Response Code = %d"), Response->GetResponseCode());
	UE_LOG(LogTemp, Warning, TEXT("Request String = %s"), *Response->GetContentAsString());

	if (bWasSuccessful && Response->GetResponseCode() == 200)
	{
		const FString ResponseBody = Response->GetContentAsString();
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);
		TSharedPtr<FJsonObject> JsonObject;
		if(FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			FString Message = JsonObject->GetStringField("message");
			if (Message.Find(" successfully") != -1)
			{
				ResponseData.bUpdateSuccessful = true;
				bResponseDataReady = true;
				return;
			}
		}
	}

	ResponseData.bUpdateSuccessful = false;
	bResponseDataReady = true;
}

void URestAPITool::PrintRequest(FHttpRequestPtr Request, FString ContentString)
{
	UE_LOG(LogTemp, Warning, TEXT("%s %s"), *Request->GetVerb(), *Request->GetURL());

	if (Request->GetVerb().Equals("POST") || Request->GetVerb().Equals("PUT"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Request Body = %s"), *ContentString);
	}
}

void URestAPITool::PrintRequestSuccess(FHttpRequestPtr Request,
												   bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("%s %s was %s"), *Request->GetVerb(),
		   *Request->GetURL(), bWasSuccessful ? TEXT("Successful") : TEXT("Unsuccessful"));
}



