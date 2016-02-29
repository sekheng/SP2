#include "scene2_minigame.h"
#include "MyMath.h"
minigame::minigame()
{

}
minigame::~minigame()
{

}
void minigame::init()
{
    piece_state = 1;

    piece1_state = Math::RandIntMinMax(0, 3);
    piece2_state = Math::RandIntMinMax(0, 3);
    piece3_state = Math::RandIntMinMax(0, 3);
    piece4_state = Math::RandIntMinMax(0, 3);
    piece5_state = Math::RandIntMinMax(0, 3);
    piece6_state = Math::RandIntMinMax(0, 3);
    piece7_state = Math::RandIntMinMax(0, 3);
    piece8_state = Math::RandIntMinMax(0, 3);
    piece9_state = Math::RandIntMinMax(0, 3);

    piece1_rotate = 0;
    piece2_rotate = 0;
    piece3_rotate = 0;
    piece4_rotate = 0;
    piece5_rotate = 0;
    piece6_rotate = 0;
    piece7_rotate = 0;
    piece8_rotate = 0;
    piece9_rotate = 0;
}
float minigame::piece1()
{
    piece1_rotate = 90 * piece1_state;
}
float minigame::piece2()
{
    piece2_rotate = 90 * piece2_state;
}
float minigame::piece3()
{
    piece3_rotate = 90 * piece3_state;
}
float minigame::piece4()
{
    piece4_rotate = 90 * piece4_state;
}
float minigame::piece5()
{
    piece5_rotate = 90 * piece5_state;
}
float minigame::piece6()
{
    piece6_rotate = 90 * piece6_state;
}
float minigame::piece7()
{
    piece7_rotate = 90 * piece7_state;
}
float minigame::piece8()
{
    piece8_rotate = 90 * piece8_state;
}
float minigame::piece9()
{
    piece9_rotate = 90 * piece9_state;
}
void minigame::selection_pointer()
{
    //controlling the selector
    if (Application::IsKeyPressed(VK_LEFT))
    {
        piece_state += 1;
    }
    if (Application::IsKeyPressed(VK_RIGHT))
    {
        piece_state -= 1;
    }
    if (Application::IsKeyPressed(VK_UP))
    {
        piece_state -= 3;
    }
    if (Application::IsKeyPressed(VK_DOWN))
    {
        piece_state += 3;
    }
    //if the selector reaches the edges of the puzzle
    if (piece_state < 1)
    {
        piece_state = 1;
    }
    if (piece_state > 9)
    {
        piece_state = 1;
    }
}
void minigame::changePieceRotation()
{
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 1)
    {
        piece1_state += 1;
        if (piece1_state > 3)
        {
            piece1_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 2)
    {
        piece2_state += 1;
        if (piece2_state > 3)
        {
            piece2_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 3)
    {
        piece3_state += 1;
        if (piece3_state > 3)
        {
            piece3_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 4)
    {
        piece4_state += 1;
        if (piece4_state > 3)
        {
            piece4_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 5)
    {
        piece5_state += 1;
        if (piece5_state > 3)
        {
            piece5_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 6)
    {
        piece6_state += 1;
        if (piece6_state > 3)
        {
            piece6_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 7)
    {
        piece7_state += 1;
        if (piece7_state > 3)
        {
            piece7_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 8)
    {
        piece8_state += 1;
        if (piece8_state > 3)
        {
            piece8_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 9)
    {
        piece9_state += 1;
        if (piece9_state > 3)
        {
            piece9_state = 0;
        }
    }
}

void minigame::update(double dt)
{
    selection_pointer();
}