// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LMA_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LEAVEMEALONE_API ALMA_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ALMA_PlayerController();
};
