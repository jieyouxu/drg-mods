#pragma once
#include "CoreMinimal.h"
#include "VanityMasterySave.generated.h"

USTRUCT(BlueprintType)
struct FVanityMasterySave {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    int32 Level;
    
    UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    int32 XP;
    
    UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    bool HasAwardedForOldPurchases;
    
    UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    int32 FashionitesAwaredForOldPurchases;
    
    FSD_API FVanityMasterySave();
};

