#include "scene2_minigame.h"
#include "MyMath.h"
#include "Application.h"

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

    start = false;

    time = 0;
    input_delay = 0.2;
}
float minigame::piece1()
{
    return piece1_rotate = static_cast<float>(90 * piece1_state);
}
float minigame::piece2()
{
    return piece2_rotate = static_cast<float>(90 * piece2_state);
}
float minigame::piece3()
{
    return piece3_rotate = static_cast<float>(90 * piece3_state);
}
float minigame::piece4()
{
    return piece4_rotate = static_cast<float>(90 * piece4_state);
}
float minigame::piece5()
{
    return piece5_rotate = static_cast<float>(90 * piece5_state);
}
float minigame::piece6()
{
    return piece6_rotate = static_cast<float>(90 * piece6_state);
}
float minigame::piece7()
{
    return piece7_rotate = static_cast<float>(90 * piece7_state);
}
float minigame::piece8()
{
    return piece8_rotate = static_cast<float>(90 * piece8_state);
}
float minigame::piece9()
{
    return piece9_rotate = static_cast<float>(90 * piece9_state);
}
void minigame::updatePieceState()
{
    piece1();
    piece2();
    piece3();
    piece4();
    piece5();
    piece6();
    piece7();
    piece8();
    piece9();
}
void minigame::selection_pointer()
{
    //controlling the selector
    if (Application::IsKeyPressed(VK_RIGHT) && time > input_delay)
    {
        time = 0;
        piece_state += 1;
    }
    if (Application::IsKeyPressed(VK_LEFT) && time > input_delay)
    {
        time = 0;
        piece_state -= 1;
    }
    if (Application::IsKeyPressed(VK_UP) && time > input_delay)
    {
        time = 0;
        piece_state -= 3;
    }
    if (Application::IsKeyPressed(VK_DOWN) && time > input_delay)
    {
        time = 0;
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
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 1 && time > input_delay)
    {
        time = 0;
        piece1_state += 1;
        if (piece1_state > 3)
        {
            piece1_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 2 && time > input_delay)
    {
        time = 0;
        piece2_state += 1;
        if (piece2_state > 3)
        {
            piece2_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 3 && time > input_delay)
    {
        time = 0;
        piece3_state += 1;
        if (piece3_state > 3)
        {
            piece3_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 4 && time > input_delay)
    {
        time = 0;
        piece4_state += 1;
        if (piece4_state > 3)
        {
            piece4_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 5 && time > input_delay)
    {
        time = 0;
        piece5_state += 1;
        if (piece5_state > 3)
        {
            piece5_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 6 && time > input_delay)
    {
        time = 0;
        piece6_state += 1;
        if (piece6_state > 3)
        {
            piece6_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 7 && time > input_delay)
    {
        time = 0;
        piece7_state += 1;
        if (piece7_state > 3)
        {
            piece7_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 8 && time > input_delay)
    {
        time = 0;
        piece8_state += 1;
        if (piece8_state > 3)
        {
            piece8_state = 0;
        }
    }
    if (Application::IsKeyPressed(VK_RETURN) && piece_state == 9 && time > input_delay)
    {
        time = 0;
        piece9_state += 1;
        if (piece9_state > 3)
        {
            piece9_state = 0;
        }
    }
}



bool minigame::result()
{
    if (piece1_state == 0 &&
        piece2_state == 0 &&
        piece3_state == 0 &&
        piece4_state == 0 &&
        piece5_state == 0 &&
        piece6_state == 0 &&
        piece7_state == 0 &&
        piece8_state == 0 &&
        piece9_state == 0
        )
    {
        return true;
    }
    else return false;
}
void minigame::update(double dt, bool start_game)
{
    /*if (start)
    {*/
        time += dt;
        start = start_game;
        selection_pointer();
        changePieceRotation();
        updatePieceState();
        result();
    //}
}
bool minigame::minigame_started()
{
    return start;
}

short minigame::get_selector_state()
{
    return piece_state;
}
