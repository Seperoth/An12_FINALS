#include <raylib.h>
#include "iostream"
#include <stdio.h>
#include <chrono>


using namespace std;
using namespace std::chrono;

int status = 0;
const int Cinit = 0, Cdificulty = 1, Cing = 2, Cend = 3; 

int player_score = 0;
int cpu_score = 0;

class Ball {
public:
float x, y;
int speed_x, speed_y;
int radius;

void draw() {
    DrawCircle(x, y, radius, WHITE);
}

void Update() {
    x += speed_x;
    y += speed_y;

    if(y + radius >= GetScreenHeight() || y - radius <= 0)
    {
        speed_y *= -1;
    }
    if(x + radius >= GetScreenWidth()) // CPU WINS
    {
        cpu_score++;
        ResetBall();
    }
    
    if(x - radius <= 0)
    {
        player_score++;
        ResetBall();
    }
}
void ResetBall() //ball go to center
{
    x = GetScreenWidth()/2; //centralize
    y = GetScreenHeight()/2; //centralize

    int speed_choices[2] = {-1,1};
    speed_x = 7;
    speed_x *= speed_choices[GetRandomValue(0,1)];
    speed_y *= speed_choices[GetRandomValue(0,1)]; 
}

};

class Paddle //player paddle movement
{
protected:

void LimitMovement() {
    if(y <= 0 )
        {
            y = 0;
        }
        if(y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;             
        }
}
public: 
    float x, y;
    float width, height;
    int speed;

    void Draw() 
    {
        DrawRectangle(x, y, width, height, BLACK);
    }

    void Update(){
        if(IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if(IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }

        LimitMovement();
    }
};

class cpuPaddle: public Paddle
{
    public:

    void Update(int ball_y)
    {
       if(y + height/2 > ball_y)
       {
            y = y - speed;
       }
       if(y + height/2 <= ball_y)
       {
            y = y + speed;
       }
       LimitMovement();  
    }
};

Ball ball;
Paddle player;
cpuPaddle cpu;

int main()   
{
    cout << "Loading Game!!!" << endl;

    const int screen_width = 1280;
    const int screen_height = 800;

    

    InitWindow(screen_width, screen_height, "Ping Pong Jay");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25; //player rectangle
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height;
    player.speed = 12;

    cpu.height = 120; //cpu rectangle
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screen_height /2 - cpu.height /2;
    cpu.speed = 5;

     

    InitAudioDevice();
    Sound Sound3 = LoadSound("AN12\\resources\\goal.wav");
    Sound Sound2 = LoadSound("AN12\\resources\\Nyam file.wav");
    Music music = LoadMusicStream("AN12\\resources\\Menu.wav");
    PlayMusicStream(music);

    bool toggletutorial = false;

    while(WindowShouldClose() == false) 
{
        UpdateMusicStream(music);
        BeginDrawing();

  if (status == Cinit) 
{
    ClearBackground(BEIGE);
    
    // Calculate center of the screen
    int centerX = screen_width / 2;
    // Define the rectangle dimensions
    int rectWidth = 400;
    int rectHeight = 200;
    int recstart = 250;
    int recstartheight = 90;
    


    // Draw the rectangle centered on the screen
    DrawRectangle(centerX - rectWidth / 2, 200 - rectHeight / 2, rectWidth, rectHeight, DARKBROWN); 

    // Define the text and its size
    

    // Calculate the width and height of the text
    int textWidth = MeasureText("PONGERS", 60);
    int textHeight = 60;  // This is a simplification, some libraries provide a way to measure text height
    int text2_width = MeasureText("NEW GAME [Q]", 25);
    int text2_height = 25; 
    int text3_width = MeasureText("QUIT [W]", 25);
    int text3_height = 25;


    // Draw the text centered in the rectangle
    DrawText("PONGERS", centerX - textWidth / 2, 200 - textHeight / 2, 60, WHITE);

    //START BUTTON
    DrawRectangle(centerX - recstart / 2, 450 - recstartheight / 2, recstart, recstartheight, DARKBROWN); 
    DrawText("NEW GAME [A]", centerX - text2_width /2, 450 - text2_height /2, 25, WHITE);
  
    //QUIT BUTTON
    DrawRectangle(centerX - recstart / 2, 550 - recstartheight / 2, recstart, recstartheight, DARKBROWN); 
    DrawText("QUIT [W]", centerX - text3_width /2, 550 - text3_height /2, 25, WHITE);
    
    if(IsKeyPressed(KEY_A)) {
        cpu_score = 0;
        player_score = 0;
        status = Cdificulty;
        PlaySound(Sound2);

    } else  
    if(IsKeyPressed(KEY_W)) 
    { 
        status = Cend;
        CloseWindow();
        PlaySound(Sound2);
    }
}
    if (status == Cdificulty)
    {
        ClearBackground(BEIGE);

        //button shape
        int rectWidth = 300;
        int rectHeight = 150;

        int textWidth = MeasureText("EASY", 60);
        int textHeight = 60;

        int text2Width = MeasureText("MEDUIM", 60);
        int text2Height = 60;

        int text4Width = MeasureText("HARD", 60);
        int text4Height = 60;

        int text5Width = MeasureText("[Q]", 60);
        int text5Height = 60;

        int text6Width = MeasureText("[W]", 60);
        int text6Height = 60;

        int text7Width = MeasureText("[E]", 60);
        int text7Height = 60;

        DrawRectangle(200 - rectWidth / 2, 200 - rectHeight / 2, rectWidth, rectHeight, DARKBROWN); 
        DrawText("EASY", 200 - textWidth / 2, 200 - textHeight / 2, 60, RAYWHITE);
        DrawRectangle(200 - rectWidth / 2, 400 - rectHeight / 2, rectWidth, rectHeight, DARKBROWN); 
        DrawText("MEDUIM", 200 - text2Width / 2, 400 - text2Height / 2, 60,  RAYWHITE);
        DrawRectangle(200 - rectWidth / 2, 600 - rectHeight / 2, 650, rectHeight, DARKBROWN); 
        DrawText("HARD [impossible]", 200 - text4Width / 2, 600 - text4Height / 2, 60,  RAYWHITE);

        DrawText("[S]", 400 - text5Width / 2, 200 - text5Height / 2, 60,  RAYWHITE);
        DrawText("[W]", 400 - text6Width / 2, 400 - text6Height / 2, 60,  RAYWHITE);
        DrawText("[E]", 750 - text7Width / 2, 600 - text7Height / 2, 60,  RAYWHITE);


              if(IsKeyPressed(KEY_S)) 
         { 
            
            player.height = 180;
            status = Cing;
            PlaySound(Sound2);
         }
                 if(IsKeyPressed(KEY_W)) 
         { 
            cpu.speed = 9;
            player.height = 140;
            status = Cing;
            PlaySound(Sound2);
         }
                 if(IsKeyPressed(KEY_E)) 
         { 
            cpu.speed = 15;
            player.height = 120;
            status = Cing;
            PlaySound(Sound2);
         }

    }


    if (status == Cing) 
    {   
        //update ball
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

         //Collisions for Paddles and Ball 
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1.3;
            PlaySound(Sound2);
        }

        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius, Rectangle{cpu.x, cpu.y, cpu.width,cpu.height}))
        {
            ball.speed_x *= -1.3;
            PlaySound(Sound2);
        }
        
        if(cpu_score >= 10 || player_score >= 10)
        {
            PlaySound(Sound3);
            status = Cend;
        }
                 // Draw Lines and Shapes
        ClearBackground(BEIGE);
        DrawRectangle(screen_width/2, 0, screen_width/2, screen_height, ORANGE);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, ORANGE);
        ball.draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i",cpu_score),screen_width/4 -20, 20, 80, BLACK);
        DrawText(TextFormat("%i",player_score), 3 *screen_width/4 -20, 20, 80, BLACK); 

        int centerX = screen_width / 2;
        int textWidth = MeasureText("First to Score 10 Wins!", 30);
        int textHeight = 30;

        int text2Width = MeasureText("[^][v] To move and [T] To End", 25);
        int text2Height = 25;

        int text4Width = MeasureText("[Q] To close Tutorial", 25);
        int text4Height = 25;

          if(IsKeyPressed(KEY_Q)) 
         { 
            toggletutorial = !toggletutorial;
         }

         if (toggletutorial)
         {
        DrawText("First to Score 10 Wins!", centerX - textWidth / 2, 300 - textHeight / 2, 30, RAYWHITE);
        DrawText("[^][v] To move and [T] To End", centerX - text2Width / 2, 330 - text2Height / 2, 25,  RAYWHITE);
        DrawText("[Q] To close Tutorial", centerX - text4Width / 2, 360 - text4Height / 2, 25,  RAYWHITE);
         }
        else 
        {
        DrawText(" ", centerX - textWidth / 2, 300 - textHeight / 2, 30, BLANK);
        DrawText(" ", centerX - text2Width / 2, 330 - text2Height / 2, 25,  BLANK);
        DrawText(" ", centerX - text4Width / 2, 360 - text4Height / 2, 25,  BLANK);
        }

            if(IsKeyPressed(KEY_T)) 
         { 
            status = Cend;
            PlaySound(Sound3);
         }
    
}
    
    if (status == Cend)
    {
        ClearBackground(BEIGE);
        int centerX = screen_width / 2;
        int textWidth = MeasureText("GAMEOVER", 60);
        int textHeight = 60;
        
        int text2_Width = MeasureText("Try Again?", 30);
        int text2_Height = 30;

        int text3_Width = MeasureText("[SPACE BAR] - Retry", 30);
        int text3_Height = 30;

        int text4_Width = MeasureText("[Q] - QUIT", 30);
        int text4_Height = 30;

        DrawText("GAMEOVER", centerX - textWidth / 2, 300 - textHeight / 2, 60, WHITE);
        
        DrawText("Try again?", centerX - text2_Width / 2, 350 - text2_Height / 2, 30, WHITE);

        DrawText("[SPACE BAR] - Retry", centerX - text3_Width / 2, 400 - text3_Height / 2, 30, WHITE);

        DrawText("[Q] - Menu", centerX - text4_Width / 2, 430 - text4_Height / 2, 30, WHITE);


      if(IsKeyPressed(KEY_SPACE)) 
      {
        status = Cing;
        cpu_score = 0;
        player_score = 0;
        PlaySound(Sound2);
      } else 
      if(IsKeyPressed(KEY_Q)) 
      {
        status = Cinit;
        PlaySound(Sound2);
      }


    }
    EndDrawing();
    }
    UnloadMusicStream(music);  
    UnloadSound(Sound2);
    CloseWindow();
    return 0;
}