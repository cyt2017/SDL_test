#include <QCoreApplication>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
//#include <SDL2/SDL.h>
int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

//    return a.exec();
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("sdl_test7",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);

    SDL_Renderer *render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(render);

    //声音
    Mix_OpenAudio( MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048*1024);
    Mix_Music *sound = Mix_LoadMUS("/home/cyt/workspace/OpenGL_SDL/1969.wav");
    printf("%s\n",SDL_GetError());
    Mix_PlayMusic(sound,1);
    //设置渲染的透明度
    SDL_SetRenderDrawBlendMode(render,SDL_BLENDMODE_BLEND);
    //设置在渲染上面的画图颜色
    SDL_SetRenderDrawColor(render,255,0,255,100);


    SDL_Event event;
    bool quit = false;

    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(event.type == SDL_MOUSEMOTION)
            {
                int x = event.motion.x;
                int y = event.motion.y;
                SDL_RenderDrawLine(render,0,0,x,y);//使用渲染的划线工具
            }
        }


        SDL_Delay(10);
        SDL_RenderPresent(render);
    }

//    SDL_DestroyTexture(ture0);
//    SDL_DestroyTexture(ture1);
    SDL_DestroyRenderer(render);

//    SDL_FreeSurface(imgSurface1);
//    SDL_FreeSurface(imgSurface0);
    SDL_DestroyWindow(window);
    SDL_QUIT;
}
