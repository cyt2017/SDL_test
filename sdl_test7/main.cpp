#include <QCoreApplication>
#include <SDL2/SDL_image.h>
//#include <EGL/egl.h>
//#include <GLES2/gl2.h>

#define SPOTCOUNT 100
typedef struct{
    int x;
    int y;
    int r;
    int speed;
}SPOT;

void downSpot(SPOT *spot)
{
    spot->y += spot->speed;
    if(spot->y>=600)
    {
        spot->y = 0;
    }
}

void DrawSpot(SPOT *spot,SDL_Renderer *render,SDL_Texture *ture)
{
    SDL_Rect rect;
    rect.x = spot->x;
    rect.y = spot->y;
    rect.w = spot->r;
    rect.h = spot->r;

    SDL_RenderCopy(render,ture,NULL,&rect);
}

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

//    return a.exec();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("sdl_test7",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);

    SDL_Renderer *render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(render);

    SDL_Surface *imgSurface0 = IMG_Load("0.png");
    SDL_Surface *imgSurface1 = IMG_Load("black.png");
    SDL_SetColorKey(imgSurface0,SDL_TRUE,SDL_MapRGB(imgSurface0->format,0,0,0));

    SDL_Texture *ture0 = SDL_CreateTextureFromSurface(render,imgSurface0);
    SDL_Texture *ture1 = SDL_CreateTextureFromSurface(render,imgSurface1);

    //设置图像半透明的函数
    SDL_SetTextureBlendMode(ture0,SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(ture1,SDL_BLENDMODE_BLEND);

    SDL_SetTextureColorMod(ture0,255,0,255);

    SDL_SetTextureAlphaMod(ture1,40);//使用了半透明函数后，设置半透明参数大小

    SDL_Rect rect1;
    rect1.x = 0;
    rect1.y = 0;
    rect1.w = 800;
    rect1.h = 600;


    SPOT spot[SPOTCOUNT];
    for(int i=0;i<SPOTCOUNT;i++)
    {
        spot[i].x = rand()%800;
        spot[i].y = rand()%600;
        spot[i].r = rand()%4+1;
        spot[i].speed = rand()%3+1;
    }


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

        }
        //语句1：清空图像
//        SDL_RenderClear(render);
        //语句2：利用设置透明度的图像，进行清空
        SDL_RenderCopy(render,ture1,NULL,&rect1);
//        SDL_RenderCopy(render,ture0,NULL,&rect);
        for(int i=0;i<SPOTCOUNT;i++)
        {
            DrawSpot(&spot[i],render,ture0);
            downSpot(&spot[i]);
        }
        SDL_Delay(10);
        SDL_RenderPresent(render);
    }

    SDL_DestroyTexture(ture0);
    SDL_DestroyTexture(ture1);
    SDL_DestroyRenderer(render);

    SDL_FreeSurface(imgSurface1);
    SDL_FreeSurface(imgSurface0);
    SDL_DestroyWindow(window);
    SDL_QUIT;
}
