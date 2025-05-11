#include <stdio.h>
#include <SDL2/SDL.h>

#define HEIGHT 800
#define WIDTH 800

int main(void){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "SDL_error: %s\n", SDL_GetError());
    }
    SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,HEIGHT, 0);
    if (!window) {
        fprintf(stderr, "Window Creation Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *surface = SDL_GetWindowSurface(window);
    if (!surface) {
        fprintf(stderr, "Surface Creation Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    SDL_Rect player = {.x = 20, .y = HEIGHT/2, .w = 15, .h = 80};
    SDL_FillRect(surface, &player, 0xffffff);
    SDL_UpdateWindowSurface(window);
    
    SDL_Rect player2 = {.x = WIDTH-player.x-10, .y = player.y, .w = player.w, .h = player.h};
    SDL_FillRect(surface, &player2, 0xffffff);
    SDL_UpdateWindowSurface(window);
    
    //line
    SDL_Rect line = {.x = WIDTH/2, .y = 0, .w=1, .h =HEIGHT};
    SDL_FillRect(surface, &line, 0xffffff);
    SDL_UpdateWindowSurface(window);

    //ball
    SDL_Rect ball = {.x = WIDTH/2, .y = HEIGHT/2, .w=20, .h =20};
    SDL_FillRect(surface, &ball, 0xffffff);
    SDL_UpdateWindowSurface(window);
    int ball_speed_x = 5;
    int ball_speed_y = 5;
    
    
    int score_player = 0;
    int score_player2 = 0;
    float coef = 1;
    int runnig = 1;
    int reset = 0;

    while(runnig){
        SDL_Event ev;
        while(SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT){
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 2;
            }

            switch (ev.key.keysym.sym)
            {
            case (SDLK_DOWN):
                SDL_FillRect(surface, &player2, 0x000000);
                if (HEIGHT-player2.h > player2.y){
                    player2.y+=15;
                }
                SDL_FillRect(surface, &player2, 0xffffff);
                SDL_UpdateWindowSurface(window);
                break;

            case (SDLK_UP):
                SDL_FillRect(surface, &player2, 0x000000);
                if(player2.y > 0)
                    player2.y-=15;
                SDL_FillRect(surface, &player2, 0xffffff);
                SDL_UpdateWindowSurface(window);
                break;
            
            case (SDLK_z):
                SDL_FillRect(surface, &player, 0x000000);
                if(player.y > 0)
                    player.y-=15;
                SDL_FillRect(surface, &player, 0xffffff);
                SDL_UpdateWindowSurface(window);
                break;
            
            case (SDLK_s):
                SDL_FillRect(surface, &player, 0x000000);
                if (HEIGHT-player.h > player.y)
                    player.y+=15;
                SDL_FillRect(surface, &player, 0xffffff);
                SDL_UpdateWindowSurface(window);
                break;

            default:
                break;
            }
        }
        SDL_FillRect(surface, &ball, 0x000000);
        ball.x += ball_speed_x * coef;
        ball.y += ball_speed_y * coef;

        if (0 >= ball.y || ball.y >= HEIGHT - ball.h){
            ball_speed_y = -ball_speed_y;
        }

        if ((ball.x <= player.x + player.w && 
            ball.y + ball.h >= player.y && 
            ball.y <= player.y + player.h) ||
            (ball.x + ball.w >= player2.x && 
            ball.y + ball.h >= player2.y && 
            ball.y <= player2.y + player2.h)) {
            ball_speed_x = -ball_speed_x;
            coef+=0.04;
        }

        if (ball.x <= 0) {
            ball.x = WIDTH / 2;
            ball.y = HEIGHT / 2;
            score_player2++;
            reset = 1;

        }

        if(ball.x >= WIDTH - ball.w){
            ball.x = WIDTH / 2;
            ball.y = HEIGHT / 2;
            score_player++;
            reset = 1;
        }

        SDL_FillRect(surface, &ball, 0xffffff);
        SDL_FillRect(surface, &line, 0xffffff);
        SDL_UpdateWindowSurface(window);
        
        
        if (score_player == 10){
            printf("Player 1 Win\n");
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(0);
        }

        if(score_player2 == 10){
            printf("Player 2 Win\n");
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(0);
        }

        if (reset == 1){
            printf(" Score player 1 : %d\n", score_player);
            printf(" Score player 2 : %d\n", score_player2);
            //printf("%f", coef);
        }
        reset = 0;
        SDL_Delay(16); //60fps
    }
}  