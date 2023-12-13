#include "SceneGame.h"
#include "./GameLib/game_lib.h"
#include "WinMain.h"
#include "SpriteData.h"
#include "Obj2d.h"

// �萔�錾
static constexpr int BACK_MAX = 2;
static constexpr int ENEMY_MAX = 10;

// �ϐ��錾
OBJ2D player;
OBJ2D backs[BACK_MAX];
OBJ2D enemies[ENEMY_MAX];

// �v���g�^�C�v�錾
void backUpdate(OBJ2D* obj);
void playerUpdate(OBJ2D* obj);
void enemySample(OBJ2D* obj);
void enemyKadai1(OBJ2D* obj);
void enemyKadai2(OBJ2D* obj);

void SceneGame::init()
{
    // �e�N�X�`���̃��[�h
    GameLib::texture::load(loadTexture);

    // �w�i�����ݒ�
    const VECTOR2 backPosition[] = {
        { 0,0 },
        { 1280,0 },
    };
    int index = 0;
    for (auto& back : backs)
    {
        back.position = backPosition[index++];
    }

    // �v���C���[�����ݒ�
    player.sprData = &sprPlayer;
    player.position = { 640, 360 };

    // �G�L���������ݒ�
    //enemies[0].init();
    for (auto& enemy : enemies)
    {
        enemy.init();
    }
}

void SceneGame::deinit()
{
    GameLib::texture::release(loadTexture);
}

void SceneGame::update()
{
    // �w�i�X�V
    for (auto& back : backs)
    {
        backUpdate(&back);
    }

    // �v���C���[�X�V
    playerUpdate(&player);

    // �G�L�����X�V
    enemySample(&enemies[0]);
    enemyKadai1(&enemies[1]);
    enemyKadai2(&enemies[2]);

    // �V�[���؂�ւ��`�F�b�N
    if (GameLib::input::TRG(0) & GameLib::input::PAD_START) { setScene(SCENE::TITLE); }
}

void backUpdate(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        obj->sprData = &sprBack;
        obj->state++;
        break;

    case 1:
        obj->position.x -= 4;

        // �X�N���[������
        if (obj->position.x < -1280)
        {
            obj->position.x += 1280 * 2;
        }
        break;
    }
}

void playerUpdate(OBJ2D* obj)
{
    if (GameLib::input::STATE(0) & GameLib::input::PAD_UP)      obj->position.y -= 8;
    if (GameLib::input::STATE(0) & GameLib::input::PAD_DOWN)    obj->position.y += 8;
    if (GameLib::input::STATE(0) & GameLib::input::PAD_LEFT)    obj->position.x -= 8;
    if (GameLib::input::STATE(0) & GameLib::input::PAD_RIGHT)   obj->position.x += 8;
}

//----------------------------------------------------------------
// �G�T���v��
void enemySample(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        obj->sprData = &sprEnemy;
        obj->position = { 1280 + 64, 160 };
        obj->state++;
        break;

    case 1:
        obj->position.x -= 8;
        if (obj->position.x < 128)
        {
            obj->state++;
        }
        break;

    case 2:
        obj->position.x += 8;
        obj->position.y += 8;
        if (obj->position.y > 480)
        {
            obj->state++;
        }
        break;

    case 3:
        obj->position.x += 8;
        break;
    }
}

//----------------------------------------------------------------
// �G�ړ������@
void enemyKadai1(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        obj->sprData = &sprEnemy;
        obj->position = { 1280 + 200, 160 };
        obj->state++;
        break;

    case 1:
        obj->position.x -= 8;
        if (obj->position.x < 960)
            obj->state++;
        break;

    case 2:
        obj->position += VECTOR2(8, 8);
        if (obj->position.y > 320)
            obj->state++;
        break;

    case 3:
        obj->position.x -= 8;
        if (obj->position.x < 180)
            obj->state++;
        break;

    case 4:
        obj->position += VECTOR2(8, 8);
        if (obj->position.y > 480)
            obj->state++;
        break;

    case 5:
        obj->position.x += 8;
        break;
    }
}

//----------------------------------------------------------------
// �G�ړ������A
void enemyKadai2(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        obj->sprData = &sprEnemy;
        obj->position = { 1280 + 200, 360 };
        obj->velocity = { -4, -8 };
        obj->state++;
        break;

    case 1:
        obj->position += obj->velocity;

        if (obj->position.y < 360 - 160)
        {
            obj->position.y = 360 - 160;
            obj->velocity.y = -obj->velocity.y;
        }
        if (obj->position.y > 360 + 160)
        {
            obj->position.y = 360 + 160;
            obj->velocity.y = -obj->velocity.y;
        }
        break;
    }
}

void SceneGame::draw()
{
    // ��ʂ��N���A
    GameLib::clear(0, 0, 0);

    // �w�i�`��
    for (auto& back : backs)
    {
        back.draw();
    }

    // �v���C���[�`��
    player.draw();

    // �G�L�����`��
    //enemies[0].draw();
    for (auto& enemy : enemies)
    {
        enemy.draw();
    }

    // ������`��
    GameLib::font::textOut(4, "SAMPLE",  enemies[0].position + VECTOR2(0, -48), { 1, 1 }, { 1,1,1,1 }, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::font::textOut(4, "KADAI_1", enemies[1].position + VECTOR2(0, -48), { 1, 1 }, { 0,1,1,1 }, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::font::textOut(4, "KADAI_2", enemies[2].position + VECTOR2(0, -48), { 1, 1 }, { 0,1,1,1 }, GameLib::TEXT_ALIGN::MIDDLE);

    GameLib::font::textOut(4, "PRESS [SPACE] TO TITLE", { 0, 700 }, { 2, 2 },
        { 1, 1, 0, 1 }, GameLib::TEXT_ALIGN::MIDDLE_LEFT);
}
