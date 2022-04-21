#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DeepDiveBank.h"
#include "UObject/Object.h"
#include "DeepDiveManager.generated.h"

class UFSDEventsHandler;
class UDeepDive;
class UGeneratedMission;

UCLASS(BlueprintType)
class UDeepDiveManager : public UObject {
    GENERATED_BODY()
public:
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeepDiveRefreshDelegate);
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FDeepDiveRefreshDelegate OnDeepDivesRefresh;
    
protected:
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    bool LockSeed;
    
    UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    UFSDEventsHandler* EventsHandler;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    UDeepDive* ActiveNormalDeepDive;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    UDeepDive* ActiveHardDeepDive;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    UDeepDive* ActiveDeepDive;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    UGeneratedMission* CurrentMission;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    float currentDepth;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    TMap<int32, FDeepDiveBank> DeepDiveBank;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    int32 BackendDataValid;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    FDateTime BackendExpirationTime;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    int32 BackendSeed;
    
public:
    UDeepDiveManager();
    UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
    void StartDeepDive(UDeepDive* DeepDive);
    
    UFUNCTION(BlueprintCallable)
    void ReInitialize();
    
    UFUNCTION(BlueprintCallable)
    void MarkGivenRewards();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UGeneratedMission* GetCurrentSingleMission() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetCurrentDeepDiveStage() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UDeepDive* GetActiveNormalDeepDive() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UDeepDive* GetActiveHardDeepDive() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UDeepDive* GetActiveDeepDive() const;
    
    UFUNCTION(BlueprintCallable)
    bool CompleteCurrentSingleMission();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool AreAllSelectedClassesQualified() const;
    
};

