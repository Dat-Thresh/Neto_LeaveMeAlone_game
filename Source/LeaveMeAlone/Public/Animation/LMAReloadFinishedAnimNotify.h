// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "LMAReloadFinishedAnimNotify.generated.h"


UCLASS()
class LEAVEMEALONE_API ULMAReloadFinishedAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	


//***VALUSES***//
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifyReloadFinishedSignature, USkeletalMeshComponent*);
	FOnNotifyReloadFinishedSignature OnNotifyReloadFinished;


//***METHODS***//
public:
	void virtual Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
