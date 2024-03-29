#include <iostream>
#include <raylib.h>
using namespace std;

struct Ball{
    float x,y;
    float x_speed,y_speed;
    float radius;

    void Draw()
    {
        DrawCircle((int)x,(int)y,radius, WHITE);
    }
};
struct Paddle{
    float x,y;
    float speed;
    float width,height;

    Rectangle GetRect(){
        return Rectangle{x-width/2,y-height/2,10,100};
    }
    void Draw(){
        DrawRectangleRec(GetRect(),WHITE);
    }
};
int main () {

    InitWindow(800, 600, "My first RAYLIB program!");
    SetTargetFPS(60);
    
    Ball ball;
    ball.x=800/2.0f;
    ball.y=600/2.0f;
    ball.radius=5;
    ball.x_speed=200;
    ball.y_speed=300;

    Paddle leftPaddle;
    leftPaddle.x=50;
    leftPaddle.y=GetScreenHeight()/2;
    leftPaddle.width=10;
    leftPaddle.height=100;
    leftPaddle.speed=500;
    
    Paddle rightPaddle;
    rightPaddle.x=GetScreenWidth()-50;
    rightPaddle.y=GetScreenHeight()/2;
    rightPaddle.width=10;
    rightPaddle.height=100;
    rightPaddle.speed=500;

    const char* winnerText = nullptr;

    while (WindowShouldClose() == false){
        ball.x+=ball.x_speed*GetFrameTime();
        ball.y+=ball.y_speed*GetFrameTime();
        if(ball.y<0) ball.y_speed*=-1;
        if(ball.y>600) ball.y_speed*=-1;
        
        if(IsKeyDown(KEY_W))leftPaddle.y-=leftPaddle.speed*GetFrameTime();
        if(IsKeyDown(KEY_S))leftPaddle.y+=leftPaddle.speed*GetFrameTime();
        if(IsKeyDown(KEY_UP))rightPaddle.y-=rightPaddle.speed*GetFrameTime();
        if(IsKeyDown(KEY_DOWN))rightPaddle.y+=rightPaddle.speed*GetFrameTime();
        
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,rightPaddle.GetRect())){
            ball.x_speed*=-1.1f;
            ball.y_speed = (ball.y-leftPaddle.y)/(leftPaddle.height/2)*ball.x_speed;
        }
         if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,leftPaddle.GetRect())){
            ball.x_speed*=-1.1f;
            ball.y_speed = (ball.y-rightPaddle.y)/(rightPaddle.height/2)*-ball.x_speed;
        }
        if(leftPaddle.y<0) leftPaddle.y=0;
        if(leftPaddle.y>GetScreenHeight()) leftPaddle.y=GetScreenHeight();

        if(rightPaddle.y<0) rightPaddle.y=0;
        if(rightPaddle.y>GetScreenHeight()) rightPaddle.y=GetScreenHeight();
        if(ball.x<0) winnerText ="Right Player Wins";
        if(ball.x>GetScreenWidth()) winnerText ="Left Player Wins";

        BeginDrawing();
        ClearBackground(BLACK);
        ball.Draw();
        leftPaddle.Draw();
        rightPaddle.Draw();
        if(winnerText){
            int textWidth = MeasureText(winnerText,60);
             DrawText(winnerText,GetScreenWidth()/2-textWidth/2,GetScreenHeight()/2-30,60,YELLOW);
        }
        if(winnerText && IsKeyPressed(KEY_SPACE)){
            ball.x=GetScreenWidth()/2;
            ball.y=GetScreenHeight()/2;
            ball.x_speed=300;
            ball.y_speed=300;
            winnerText=nullptr;
        }
           
        DrawFPS(10,10);
     

        EndDrawing();
    }

    CloseWindow();
    return 0;
}