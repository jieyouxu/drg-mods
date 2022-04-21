#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/ActorComponent.h"
#include "CrossbowProjectileControlled.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class FSD_API UCrossbowProjectileControlled : public UActorComponent {
    GENERATED_BODY()
public:
    UCrossbowProjectileControlled();
private:
    UFUNCTION(BlueprintCallable)
    void UpdateHomingTarget();
    
    UFUNCTION(BlueprintCallable, Reliable, Server)
    void Server_UpdateHomingTarget(const FVector& Target);
    
    UFUNCTION(BlueprintCallable)
    void CancelControl();
    
    UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
    void All_UpdateHomingTarget(const FVector& Target);
    
};

