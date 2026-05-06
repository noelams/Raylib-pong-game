#include "raylib.h"

int const screenHeight = 500;
int const screenWidth = 800;

struct Ball
{
	Vector2 ballPosition;
	float ballRadius;
	Color color;
	Vector2 ballVelocity;
};
struct Block
{
	Vector2 blockPosition;
	Vector2 blockSize;
	Color color;
};

int main()
{

	InitWindow(screenWidth, screenHeight, "Raylib ping pong");
	InitAudioDevice();
	SetTargetFPS(120);

	Ball pongBall = {{(float)screenWidth / 2, (float)screenHeight / 2}, 10, BLACK, {200.0f, -200.0f}};
	Block paddle1 = {{(float)screenWidth / 3, (float)screenHeight / 1.1}, {250, 20}, BLUE};
	Sound collision_sound = LoadSound("resources/collision_sound.wav");
	Sound paddle_sound = LoadSound("resources/paddle_sound.mp3");

	while (!WindowShouldClose())
	{
		float halfWidth = paddle1.blockSize.x / 2;

		if (IsKeyDown(KEY_LEFT) && paddle1.blockPosition.x - halfWidth > 0)
			paddle1.blockPosition.x -= 2.0f;

		if (IsKeyDown(KEY_RIGHT) && paddle1.blockPosition.x + halfWidth < screenWidth)
			paddle1.blockPosition.x += 2.0f;

		pongBall.ballPosition.y += GetFrameTime() * pongBall.ballVelocity.y;
		pongBall.ballPosition.x += GetFrameTime() * pongBall.ballVelocity.x;

		// ball collision with left and right
		if (pongBall.ballPosition.x + pongBall.ballRadius >= screenWidth || pongBall.ballPosition.x - pongBall.ballRadius <= 0)
		{
			PlaySound(collision_sound);
			pongBall.ballVelocity.x *= -1;
			// prevents ball from getting stuck outside the walls
			if (pongBall.ballPosition.x - pongBall.ballRadius < 0)
				pongBall.ballPosition.x = pongBall.ballRadius;
			if (pongBall.ballPosition.x + pongBall.ballRadius > screenWidth)
				pongBall.ballPosition.x = screenWidth - pongBall.ballRadius;
		}

		// ball collision with top
		if (pongBall.ballPosition.y - pongBall.ballRadius <= 0)
		{
			PlaySound(collision_sound);
			pongBall.ballVelocity.y *= -1;
			pongBall.ballPosition.y = pongBall.ballRadius;
		}

		Rectangle paddleRect = {
			paddle1.blockPosition.x - paddle1.blockSize.x / 2,
			paddle1.blockPosition.y - paddle1.blockSize.y / 2,
			paddle1.blockSize.x,
			paddle1.blockSize.y};

		// collision with paddle
		if (CheckCollisionCircleRec(pongBall.ballPosition, pongBall.ballRadius, paddleRect))
		{
			PlaySound(paddle_sound);
			pongBall.ballVelocity.y *= -1;
			pongBall.ballPosition.y = paddleRect.y - pongBall.ballRadius;
		}

		// ball falling off screen
		if (pongBall.ballPosition.y - pongBall.ballRadius > screenHeight)
		{
			pongBall.ballPosition = (Vector2){screenWidth / 2, screenHeight / 2};
			pongBall.ballVelocity = {200.0f, -200.0f};
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawCircleV(pongBall.ballPosition, pongBall.ballRadius, BLACK);
		DrawRectangleRec(paddleRect, paddle1.color);
		EndDrawing();
	}

	UnloadSound(collision_sound);
	UnloadSound(paddle_sound);

	CloseAudioDevice();

	CloseWindow();

	return 0;
}
