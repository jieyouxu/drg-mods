#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EOutline.h"
#include "OutlineComponent.generated.h"

class APlayerCharacter;
class UHealthComponentBase;
class UPrimitiveComponent;
class AItem;
class AActor;

UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))
class UOutlineComponent : public UActorComponent {
    GENERATED_BODY()
public:
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOutlineChanged, EOutline, InOutline);
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FOutlineChanged OnOutlineChanged;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EOutline DefaultOutline;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool ActiveOnHoldTAB;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CustomLaserPointDuration;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    int32 LockCounter;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    EOutline CurrentOutline;
    
    UPROPERTY(BlueprintReadWrite, Export, Transient, meta=(AllowPrivateAccess=true))
    TArray<UPrimitiveComponent*> OutlinedComponents;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, meta=(AllowPrivateAccess=true))
    TArray<UPrimitiveComponent*> ExcludedComponents;
    
    UPROPERTY(BlueprintReadWrite, Transient, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<APlayerCharacter> Character;
    
public:
    UOutlineComponent();
    UFUNCTION(BlueprintCallable)
    void UnlockOutline();
    
    UFUNCTION(BlueprintCallable)
    void ToggleDefaultOutline(bool Visible);
    
    UFUNCTION(BlueprintCallable)
    void SetOutline(EOutline outline);
    
    UFUNCTION(BlueprintCallable)
    void RemoveFromOutline(UPrimitiveComponent* Component);
    
protected:
    UFUNCTION(BlueprintCallable)
    void OnToggleOutline(bool Visible);
    
    UFUNCTION(BlueprintCallable)
    void OnOwnerDeath(UHealthComponentBase* HealthComponent);
    
    UFUNCTION(BlueprintCallable)
    void OnItemUnequipped(AItem* Item);
    
    UFUNCTION(BlueprintCallable)
    void OnItemEquipped(AItem* Item);
    
public:
    UFUNCTION(BlueprintCallable)
    void LockOutline();
    
    UFUNCTION(BlueprintCallable)
    void EnableActivateOnHoldTab();
    
    UFUNCTION(BlueprintCallable)
    void AddToOutline(UPrimitiveComponent* Component);
    
    UFUNCTION(BlueprintCallable)
    void AddActorToOutline(AActor* Actor);
    
};

