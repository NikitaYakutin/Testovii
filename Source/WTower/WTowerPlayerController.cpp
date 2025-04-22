#include "WTowerPlayerController.h"
#include "PlayerCharacter.h"
#include "WTowerGameState.h"
#include "GameFramework/PlayerInput.h"
#include "Engine/World.h"
#include "Menu/MenuWidget/WPauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Menu/MenuGameMode.h"
#include "Menu/WUIManager.h"

AWTowerPlayerController::AWTowerPlayerController()
{
    // Set this controller to receive input
    bShowMouseCursor = false;
    bEnableClickEvents = false;
    bEnableMouseOverEvents = false;
    bIsSettingsOpenFromPause = false;

    // Load widget classes - using the correct syntax for ConstructorHelpers
    static ConstructorHelpers::FClassFinder<UUserWidget> PauseWidgetClassFinder(TEXT("/Game/Blueprints/Menu/WBP_PauseMenu"));
    if (PauseWidgetClassFinder.Succeeded())
    {
        PauseMenuWidgetClass = PauseWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> SettingsWidgetClassFinder(TEXT("/Game/Blueprints/Menu/WBP_SettingsMenu"));
    if (SettingsWidgetClassFinder.Succeeded())
    {
        SettingsMenuWidgetClass = SettingsWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> VictoryWidgetClassFinder(TEXT("/Game/Blueprints/Menu/WBP_VictoryScreen"));
    if (VictoryWidgetClassFinder.Succeeded())
    {
        VictoryScreenWidgetClass = VictoryWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetClassFinder(TEXT("/Game/Blueprints/Menu/WBP_MainMenu"));
    if (MainMenuWidgetClassFinder.Succeeded())
    {
        MainMenuWidgetClass = MainMenuWidgetClassFinder.Class;
    }
}

void AWTowerPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    
    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(InPawn);
    if (PlayerCharacter)
    {
        UE_LOG(LogTemp, Log, TEXT("WTowerPlayerController: Possessed PlayerCharacter"));
    }
}

void AWTowerPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize UI Manager
    if (!UIManager)
    {
        UIManager = NewObject<UWUIManager>(this);
        if (UIManager)
        {
            UIManager->Initialize(this);
            
            // Try to find widget classes from GameMode (if available)
            AMenuGameMode* MenuGameMode = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
            if (MenuGameMode)
            {
                UIManager->SetWidgetClasses(
                    MenuGameMode->MainMenuWidgetClass,
                    MenuGameMode->PauseMenuWidgetClass,
                    MenuGameMode->SettingsMenuWidgetClass,
                    MenuGameMode->VictoryScreenWidgetClass,
                    nullptr,  // DefeatMenuWidgetClass - may need to add to MenuGameMode
                    nullptr   // HUDWidgetClass - may need to add to MenuGameMode
                );
            }
            
            // Show HUD if in gameplay level
            if (UGameplayStatics::GetCurrentLevelName(this) != "MainMenu")
            {
                UIManager->ShowHUD();
            }
        }
    }
    
    // Set default controller input mode to game only
    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);
    
    // Hide the mouse cursor by default
    SetShowMouseCursor(false);
}

void AWTowerPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    // All core movement and camera controls are set up in PlayerCharacter
    
    // Add pause game key binding
    InputComponent->BindAction("TogglePause", IE_Pressed, this, &AWTowerPlayerController::TogglePauseMenu);
}

void AWTowerPlayerController::TogglePauseMenu()
{
    // Check if we have UIManager
    if (!UIManager)
    {
        UIManager = NewObject<UWUIManager>(this);
        UIManager->Initialize(this);
    }
    
    // Use UIManager to toggle pause menu
    UIManager->TogglePauseMenu();
}

void AWTowerPlayerController::OpenSettingsFromPause()
{
    bIsSettingsOpenFromPause = true;
    
    if (UIManager)
    {
        UIManager->OpenSettings();
    }
}

void AWTowerPlayerController::ReturnToPauseFromSettings()
{
    bIsSettingsOpenFromPause = false;
    
    if (UIManager)
    {
        UIManager->ReturnToPreviousMenu();
    }
}

void AWTowerPlayerController::ClosePauseMenu()
{
    if (UIManager)
    {
        UIManager->CloseCurrentMenu();
        UIManager->ShowHUD(); // Make sure HUD is visible
    }
}
void AWTowerPlayerController::SetUIManager(UWUIManager* InUIManager)
{
    UIManager = InUIManager;
}