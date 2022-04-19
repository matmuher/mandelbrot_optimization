#include "include/raylib.h"
#include <stdio.h>
#include <stdlib.h>

Color mondelbrot_point_color (float x0, float y0, const int screenWidth, const int screenHeight);

void draw_mondelbrot (const int screenWidth, const int screenHeight, float scale_factor, float shift_x, float shift_y);

int main ()
	{
	const int screenWidth = 600, screenHeight = 400;
	InitWindow(screenWidth, screenHeight, "My dear Mondelbrot...");

	// Draw FPS
	char StringFPS[10] = {};
	sprintf(StringFPS,"%d", GetFPS());
	DrawText(StringFPS, 0, 0, 20, VIOLET);

	// Movement values
	float scale_factor = 0.01, shift_x = 0, shift_y = 0;
	const float shift_factor = 0.2;
	bool show_controls = true;

	while (!WindowShouldClose())
		{
		BeginDrawing();

			ClearBackground(RAYWHITE);

			// Check if user wants zoom in/out
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
				{
				scale_factor = scale_factor / 2;
				}
			else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				{
				scale_factor = scale_factor * 2;
                }

			// User interface
			if (IsKeyPressed(KEY_ESCAPE))
				{
				break;
				}
			else if (IsKeyPressed(KEY_LEFT))
				{
				shift_x -= screenWidth * shift_factor * scale_factor;
				}
			else if (IsKeyPressed(KEY_RIGHT))
				{
				shift_x += screenWidth * shift_factor * scale_factor;
				}
			else if (IsKeyPressed(KEY_UP))
				{
				shift_y -= screenHeight * shift_factor * scale_factor;
				}
			else if (IsKeyPressed(KEY_DOWN))
				{
				shift_y += screenHeight * shift_factor * scale_factor;
				}

            draw_mondelbrot(screenWidth, screenHeight, scale_factor, shift_x, shift_y);

			if (show_controls)
				{
				DrawText("Press LEFT/RIGHT MOUSE BUTTON to zoom out/in", 10, 10, 15, GREEN);
				DrawText("Press LEFT/RIGHT/UP/DOWN KEYS to displace respectively", 10, 30, 15, GREEN);
				}

			// Draw FPS
			char StringFPS[10] = {};
			sprintf(StringFPS,"%d", GetFPS());
			DrawText(StringFPS, 0, 0, 20, VIOLET);

		EndDrawing();
		}

	CloseWindow();

	return 0;
	}


void draw_mondelbrot (const int screenWidth, const int screenHeight, float scale_factor, float shift_x, float shift_y)
	{
	// Draw pixels than belong Mondelbrot's set
	for (int y = 0; y < screenHeight; y++)
		{
		for (int x = 0; x < screenWidth; x++)
			{
            // Transform coords from left-conored coord system to centered one
            float scaled_x = (x - screenWidth / 2) * scale_factor + shift_x;
            float scaled_y = (y - screenHeight / 2) * scale_factor + shift_y;

            Color pixel_color = mondelbrot_point_color(scaled_x, scaled_y, screenWidth, screenHeight);

            DrawPixel(x, y, pixel_color);
            }
		}
	}


// Count whether point belongs to the Mondelbrot set or not and return respective color
Color mondelbrot_point_color (float x0, float y0, const int screenWidth, const int screenHeight)
	{
	const size_t MAX_STEP = 256;
	const float MAX_R_SQUARE = 100.f;

	size_t step_id = 0;

	float x = x0, y = y0;

	for (; step_id < MAX_STEP; step_id++)
		{
		float xx = x * x;
		float xy = x * y;
		float yy = y * y;

		if (xx + yy > MAX_R_SQUARE)
			{
			break;
			}

		y = 2*xy + y0;
		x = xx - yy + x0;
        }

	return step_id == MAX_STEP? BLACK : WHITE;
	}
