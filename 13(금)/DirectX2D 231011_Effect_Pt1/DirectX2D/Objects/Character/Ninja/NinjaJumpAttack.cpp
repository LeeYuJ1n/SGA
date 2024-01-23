#include "Framework.h"

NinjaJumpAttack::NinjaJumpAttack(Transform* target)
    : NinjaAttack("Ninja_JumpAttack.xml", target)
{
    power = 100.0f;

    attackCollider = new RectCollider(Vector2(70, 120));
    attackCollider->Pos().x = 50.0f;
    attackCollider->SetParent(target);
    attackCollider->SetActive(false);

    clip->SetEvent(bind(&NinjaAttack::EnableCollider, this), 4);
    clip->SetEvent(bind(&NinjaJumpAttack::DisableCollider, this), 7);
}

void NinjaJumpAttack::Update()
{
    Action::Update();

    if (isFall)
    {
        velocity -= GRAVITY * DELTA;

        target->Pos().y += velocity * DELTA;

        if (KEY_PRESS(VK_RIGHT))
        {
            target->Pos().x += MOVE_SPEED * DELTA;
            target->Rot().y = 0;
        }

        if (KEY_PRESS(VK_LEFT))
        {
            target->Pos().x -= MOVE_SPEED * DELTA;
            target->Rot().y = XM_PI;
        }

        if (target->Pos().y < FLOOR_HEIGHT)
        {
            target->Pos().y = FLOOR_HEIGHT;
            velocity = 0.0f;

            event();
        }
    }
}

void NinjaJumpAttack::Start()
{
    Action::Start();

    velocity = 0.0f;
    isFall = false;
}

void NinjaJumpAttack::DisableCollider()
{    
    NinjaAttack::DisableCollider();

    isFall = true;
}
