#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BR_GameMode_Base.generated.h"

UCLASS()
class BULLETRAIN_API ABR_GameMode_Base : public AGameModeBase
{
	GENERATED_BODY()

public:
	//GETTERS
	UFUNCTION(BlueprintCallable)
	int GetKillCount();
	UFUNCTION(BlueprintCallable)
	int GetHighKillCount();

	//SETTERS
	UFUNCTION(BlueprintCallable)
	void SetKillCount(int Value);
	UFUNCTION(BlueprintCallable)
	void SetHighKillCount(int Value);

protected:

private:
	//VARIABLES
	UPROPERTY(VisibleAnywhere)
	int KillCount = 0;
	UPROPERTY(VisibleAnywhere)
	int HighestKillCount = 0;
};
