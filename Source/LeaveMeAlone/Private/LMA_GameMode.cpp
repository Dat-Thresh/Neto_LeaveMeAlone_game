// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "LMA_GameMode.h"
#include "Player\LMADefaultCharacter.h"
#include "Controller\LMA_PlayerController.h"

ALMA_GameMode::ALMA_GameMode() {
	DefaultPawnClass = ALMADefaultCharacter::StaticClass();
	PlayerControllerClass = ALMA_PlayerController::StaticClass();
}