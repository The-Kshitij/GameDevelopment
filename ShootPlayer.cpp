#include "ShootPlayer.h"
#include "AIController.h"
#include "MainCharacter.h"
UShootPlayer::UShootPlayer()
{
    NodeName="Shoot Player";
}
EBTNodeResult::Type UShootPlayer::ExecuteTask(UBehaviorTreeComponent &OwnerComp,uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);
    if (OwnerComp.GetAIOwner()==nullptr)
    {
        return EBTNodeResult::Failed;
    }
    AAIController *Controller=OwnerComp.GetAIOwner();
    AMainCharacter *ControlledPlayer=Cast<AMainCharacter>(Controller->GetPawn());
    if (ControlledPlayer==nullptr)
    {
        return EBTNodeResult::Failed;
    }
    ControlledPlayer->Shoot();
    return EBTNodeResult::Succeeded;
}