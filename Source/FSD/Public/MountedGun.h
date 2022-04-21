#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponFireOwner.h"
#include "Steerable.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "MountedGun.generated.h"

class USkeletalMeshComponent;
class APlayerCharacter;
class UWeaponFireComponent;
class UGunLogicComponent;

UCLASS()
class AMountedGun : public AActor, public ISteerable, public IWeaponFireOwner {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Export, VisibleAnywhere, meta=(AllowPrivateAccess=true))
    USkeletalMeshComponent* Mesh;
    
protected:
    UPROPERTY(BlueprintReadWrite, Export, Transient, meta=(AllowPrivateAccess=true))
    UWeaponFireComponent* WeaponFire;
    
    UPROPERTY(BlueprintReadWrite, Export, Transient, meta=(AllowPrivateAccess=true))
    UGunLogicComponent* GunLogic;
    
public:
    AMountedGun();
    UFUNCTION(BlueprintCallable, Reliable, Server, WithValidation)
    void Server_Test();
    
    
    // Fix for true pure virtual functions not being implemented
    UFUNCTION(BlueprintCallable)
    APlayerCharacter* GetPlayerCharacter() const override PURE_VIRTUAL(GetPlayerCharacter, return NULL;);
    
    UFUNCTION(BlueprintCallable)
    FQuat GetMuzzleQuat() const override PURE_VIRTUAL(GetMuzzleQuat, return FQuat{};);
    
    UFUNCTION(BlueprintCallable)
    FVector GetMuzzleLocation() const override PURE_VIRTUAL(GetMuzzleLocation, return FVector{};);
    
    UFUNCTION(BlueprintCallable)
    bool GetIsLocallyControlled() const override PURE_VIRTUAL(GetIsLocallyControlled, return false;);
    
    UFUNCTION(BlueprintCallable)
    bool GetIsFirstPerson() const override PURE_VIRTUAL(GetIsFirstPerson, return false;);
    
};

