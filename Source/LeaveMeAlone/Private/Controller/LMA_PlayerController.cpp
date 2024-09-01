// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Controller/LMA_PlayerController.h"

ALMA_PlayerController::ALMA_PlayerController() {}


void ALMA_PlayerController::BeginPlay() {
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}