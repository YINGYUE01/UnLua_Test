--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type BP_PlayerController_C
local EnhancedInput = require "UnLua.EnhancedInput"

local MOVE_ACTION = "/Game/Blueprint/Character/Input/Action/IA_MoveAction.IA_MoveAction"
local LOOK_ACTION = "/Game/Blueprint/Character/Input/Action/IA_Look.IA_Look"
local JUMP_ACTION = "/Game/Blueprint/Character/Input/Action/IA_Jump.IA_Jump"
local M = UnLua.Class()

function M:Look(InputActionValue)
    self:AddYawInput(InputActionValue.X)
    self:AddPitchInput(InputActionValue.Y)
end

function M:Move(InputActionValue)
    local YawRotation = UE.FRotator(0, self:GetControlRotation().Yaw, 0)
    local Forward = UE.UKismetMathLibrary.GetForwardVector(YawRotation)
    local Right = UE.UKismetMathLibrary.GetRightVector(YawRotation)
    local Pawn = self:K2_GetPawn()
    if not Pawn then
        return
    end
    Pawn:AddMovementInput(Forward, InputActionValue.Y)
    Pawn:AddMovementInput(Right, InputActionValue.X)
end
function M:Jump(InputValue)
    local Pawn = self:K2_GetPawn()
    if not Pawn then
        return
    end
    Pawn:Jump()
end
-- function M:Initialize(Initializer)
-- end

-- function M:UserConstructionScript()
-- end

function M:ReceiveBeginPlay()
    print("Hello!!1111111")
end

EnhancedInput.BindAction(M, MOVE_ACTION, "Triggered", M.Move)
EnhancedInput.BindAction(M, LOOK_ACTION, "Triggered", M.Look)
EnhancedInput.BindAction(M, JUMP_ACTION, "Triggered", M.Jump)
-- function M:ReceiveEndPlay()
-- end

-- function M:ReceiveTick(DeltaSeconds)
-- end

-- function M:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
-- end

-- function M:ReceiveActorBeginOverlap(OtherActor)
-- end

-- function M:ReceiveActorEndOverlap(OtherActor)
-- end

return M
