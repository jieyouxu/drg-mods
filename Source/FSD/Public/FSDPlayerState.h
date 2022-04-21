#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "SupplyStatusChangedDelegateDelegate.h"
#include "GameFramework/PlayerState.h"
#include "PlayerSpawnedSignatureDelegate.h"
#include "PlayerVoiceSignatureDelegate.h"
#include "SelectedCharacterChangedDelegateDelegate.h"
#include "EnemyKilledSignatureDelegate.h"
#include "PlayerNameChangedSignatureDelegate.h"
#include "FractionLevelGeneratedDelegateDelegate.h"
#include "LevelGenerationStateSignatureDelegate.h"
#include "RewardTexts.h"
#include "XPReward.h"
#include "CharacterProgress.h"
#include "EGameOwnerStatus.h"
#include "CreditsReward.h"
#include "EChatSenderType.h"
#include "FSDPlayerState.generated.h"

class UPlayerResourceComponent;
class UVanityItem;
class APlayerCharacter;
class AFSDPlayerController;
class UPlayerStatsComponent;
class UPlayerRejoinState;
class USaveGameStateComponent;
class UPlayerCharacterID;

UCLASS()
class FSD_API AFSDPlayerState : public APlayerState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FPlayerSpawnedSignature OnPlayerCharacterSpawned;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FPlayerVoiceSignature OnPlayerTalkingChanged;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FSelectedCharacterChangedDelegate OnSelectedCharacterChanged;
    
    UPROPERTY(BlueprintReadWrite, Transient, ReplicatedUsing=OnRep_FractionLevelGenerated, meta=(AllowPrivateAccess=true))
    float FractionLevelGenerated;
    
    UPROPERTY(BlueprintReadWrite, Transient, ReplicatedUsing=OnRep_LevelGenerationState, meta=(AllowPrivateAccess=true))
    FString LevelGenerationState;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FSupplyStatusChangedDelegate OnSupplyStatusChangedEvent;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FEnemyKilledSignature OnEnemyKilledEvent;
    
    UPROPERTY(BlueprintReadWrite, Replicated, Transient, meta=(AllowPrivateAccess=true))
    TArray<UVanityItem*> LatestEquipedVanity;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, ReplicatedUsing=OnRep_SelectedCharacter, meta=(AllowPrivateAccess=true))
    TSubclassOf<APlayerCharacter> SelectedCharacter;
    
    UPROPERTY(BlueprintReadWrite, Replicated, Transient, meta=(AllowPrivateAccess=true))
    bool bIsServer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool ShouldCopyProperties;
    
    UPROPERTY(BlueprintReadWrite, Transient, ReplicatedUsing=OnRep_GameOwnerStatus, meta=(AllowPrivateAccess=true))
    uint8 gameOwnerStatus;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IsOnSpaceRig;
    
    UPROPERTY(BlueprintReadWrite, Export, VisibleAnywhere, meta=(AllowPrivateAccess=true))
    UPlayerStatsComponent* PlayerStatsComponent;
    
    UPROPERTY(BlueprintReadWrite, Export, VisibleAnywhere, meta=(AllowPrivateAccess=true))
    UPlayerRejoinState* RejoinState;
    
    UPROPERTY(BlueprintReadWrite, Export, VisibleAnywhere, meta=(AllowPrivateAccess=true))
    USaveGameStateComponent* SaveGameStateComponent;
    
    UPROPERTY(BlueprintReadWrite, Transient, ReplicatedUsing=OnRep_PlayerCharacter, meta=(AllowPrivateAccess=true))
    APlayerCharacter* PlayerCharacter;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    bool IsInMission;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    bool IsTalking;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    bool HasGeneratedLevel;
    
    UPROPERTY(BlueprintReadWrite, Replicated, Transient, meta=(AllowPrivateAccess=true))
    bool HasSelectedCharacter;
    
    UPROPERTY(BlueprintReadWrite, Replicated, Transient, meta=(AllowPrivateAccess=true))
    int32 PlayerSortId;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FPlayerNameChangedSignature OnPlayerNameChanged;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FFractionLevelGeneratedDelegate OnFractionLevelGenerated;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FLevelGenerationStateSignature OnLevelGenerationStateChanged;
    
    UPROPERTY(BlueprintReadWrite, Export, Transient, meta=(AllowPrivateAccess=true))
    UPlayerResourceComponent* PlayerResources;
    
    UPROPERTY(BlueprintReadWrite, Transient, ReplicatedUsing=OnRep_SupplyAmmoStatus, meta=(AllowPrivateAccess=true))
    uint8 SupplyAmmoStatus;
    
    UPROPERTY(BlueprintReadWrite, Transient, ReplicatedUsing=OnRep_SupplyHealthStatus, meta=(AllowPrivateAccess=true))
    uint8 SupplyHealthStatus;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRewardTexts RewardTexts;
    
public:
    AFSDPlayerState();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    
    UFUNCTION(BlueprintCallable)
    void SetSelectedCharacterID(UPlayerCharacterID* characterID);
    
    UFUNCTION(BlueprintCallable)
    void SetSelectedCharacter(TSubclassOf<APlayerCharacter> NewCharacter);
    
    UFUNCTION(BlueprintCallable)
    void SetHasGeneratedLevel(bool hasgenerated);
    
    UFUNCTION(BlueprintCallable)
    void SetCanOnlySpectate(bool canOnlySpectate);
    
protected:
    UFUNCTION(BlueprintCallable, Reliable, Server)
    void ServerSetSelectedCharacter(TSubclassOf<APlayerCharacter> NewCharacter);
    
    UFUNCTION(BlueprintCallable, Reliable, Server)
    void Server_SetSupplyStatus(uint8 StatusHealth, uint8 StatusAmmo);
    
public:
    UFUNCTION(BlueprintCallable, Reliable, Server)
    void Server_SetGameOwnerStatus(int32 NewGameOwnerStatus);
    
protected:
    UFUNCTION(BlueprintCallable)
    void OnRep_SupplyHealthStatus();
    
    UFUNCTION(BlueprintCallable)
    void OnRep_SupplyAmmoStatus();
    
    UFUNCTION(BlueprintCallable)
    void OnRep_SelectedCharacter();
    
    UFUNCTION(BlueprintCallable)
    void OnRep_PlayerCharacter();
    
    UFUNCTION(BlueprintCallable)
    void OnRep_LevelGenerationState();
    
    UFUNCTION(BlueprintCallable)
    void OnRep_GameOwnerStatus();
    
    UFUNCTION(BlueprintCallable)
    void OnRep_FractionLevelGenerated();
    
public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnLateJoinFinished();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool HasNormalOwnerStatus() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetXPRewardsSum();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    TArray<FXPReward> GetXPRewards();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    TArray<FXPReward> GetXPRewardDeepDive(int32 StagesCompleted);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetUIPing();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetSupplyHealthStatus() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetSupplyAmmoStatus() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetSelectedCharacterLevel() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UPlayerCharacterID* GetSelectedCharacterID() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    TSubclassOf<APlayerCharacter> GetSelectedCharacter() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FCharacterProgress GetSelectCharacterProgress();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UPlayerResourceComponent* GetPlayerResourceComponent() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetPlayerRank() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    AFSDPlayerController* GetPlayerController() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool GetHasGeneratedLevel() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool GetGameOwnerStatus(EGameOwnerStatus Status) const;
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, BlueprintPure)
    TArray<FCreditsReward> GetDeepDiveCreditsReward(int32 StagesCompleted, int32 goldCollected);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    EChatSenderType GetChatSenderType() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FCharacterProgress GetCharacterProgress(UPlayerCharacterID* characterID) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetCharacterLevel(UPlayerCharacterID* characterID) const;
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void CharacterSelected();
    
};

