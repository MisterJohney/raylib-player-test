#include "raylib.h"
#include <stdio.h>

#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

typedef struct Player {
    Vector2 position;
    float speed;
} Player;

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta, Rectangle *playerRect);
void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Player player = { 0 };
    player.position = (Vector2){screenWidth/2, screenHeight/2};
    player.speed = 0;
    EnvItem envItems[] = {
        /* {{ 0, 0, 1000, 400 }, 0, LIGHTGRAY }, */
        {{ 0, 400, 1000, 200 }, 1, GRAY },
        {{ 300, 200, 400, 10 }, 1, GRAY },
        {{ 250, 300, 100, 10 }, 1, GRAY },
        {{ 650, 300, 100, 10 }, 1, GRAY }
    };

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();
        Rectangle playerRect = { player.position.x - 20, player.position.y -40, 40, 40 };
        UpdatePlayer(&player, envItems, envItemsLength, deltaTime, &playerRect);

        camera.zoom += ((float)GetMouseWheelMove()*0.05f);
        UpdateCameraCenter(&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);


        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color);
                DrawRectangleRec(playerRect, RED);
                DrawCircle(player.position.x, player.position.y, 5, GOLD);
            EndMode2D();


            //DrawText("My totaly original code.", 0, 0, 20, DARKBLUE);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}




void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta, Rectangle *playerRect)
{
    if (IsKeyDown(KEY_LEFT)) player->position.x -= PLAYER_HOR_SPD*delta;
    if (IsKeyDown(KEY_RIGHT)) player->position.x += PLAYER_HOR_SPD*delta;
    if (IsKeyDown(KEY_UP)) player->position.y -= PLAYER_HOR_SPD*delta;
    if (IsKeyDown(KEY_DOWN)) player->position.y += PLAYER_HOR_SPD*delta;


    bool hitObstacle = false;
    for (int i = 0; i < envItemsLength; i++)
    {

        EnvItem *ei = envItems + i;
        Vector2 *p = &(player->position);
        /* if (ei->blocking && */
        /*     ei->rect.x <= p->x && */
        /*     ei->rect.x + ei->rect.width >= p->x && */
        /*     ei->rect.y >= p->y && */
        /*     ei->rect.y <= p->y + player->speed*delta) */

        /* if (CheckCollisionRecs(*playerRect, *ei)) */
        /* { */
        /*     hitObstacle = true; */
        /*     player->speed = 0.0f; */
        /*     /1* p->y = ei->rect.y; *1/ */
        /*     break; */
        /* } */
    }
}

void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    camera->target = player->position;
}

