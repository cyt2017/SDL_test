#include <QCoreApplication>
#include <SDL2/SDL_image.h>

//实验1：设置图像的半透明，先由明到暗，再由暗到明
int main01(int argc, char *argv[])
{
    //    QCoreApplication a(argc, argv);

    //    return a.exec();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("sdl_test6",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);

    SDL_Renderer *render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(render);

    SDL_Surface *imgSurface = IMG_Load("0.png");
    SDL_Texture *ture = SDL_CreateTextureFromSurface(render,imgSurface);

    //设置图像半透明的函数
    SDL_SetTextureBlendMode(ture,SDL_BLENDMODE_BLEND);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = imgSurface->w;
    rect.h = imgSurface->h;


    SDL_Event event;
    bool quit = false;
    bool index = false;
    int alpha = 255;
    while(quit==false)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_RenderClear(render);
        if(!index)
        {
            alpha--;
            SDL_SetTextureAlphaMod(ture,alpha);//使用了半透明函数后，设置半透明参数大小
        }
        else
        {
            alpha++;
            SDL_SetTextureAlphaMod(ture,alpha);//使用了半透明函数后，设置半透明参数大小
        }
        SDL_RenderCopy(render,ture,NULL,&rect);

        SDL_Delay(10);
        SDL_RenderPresent(render);

        if(alpha<=0)
        {
            index = true;
            alpha = 0;
        }
        if(alpha>=255)
        {
            index = false;
            alpha = 255;
        }
    }

    SDL_DestroyTexture(ture);
    SDL_DestroyRenderer(render);

    SDL_FreeSurface(imgSurface);
    SDL_DestroyWindow(window);
    SDL_QUIT;
}


//实验2：使用黑点图像和正常图像，实现图像在显示面上移动时，出现长长的拖影
int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("sdl_test6",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);

    SDL_Renderer *render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(render);

    SDL_Surface *imgSurface0 = IMG_Load("0.png");
    SDL_Surface *imgSurface1 = IMG_Load("black.png");

    SDL_Texture *ture0 = SDL_CreateTextureFromSurface(render,imgSurface0);
    SDL_Texture *ture1 = SDL_CreateTextureFromSurface(render,imgSurface1);

    //设置图像半透明的函数
    SDL_SetTextureBlendMode(ture0,SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(ture1,SDL_BLENDMODE_BLEND);

    SDL_SetTextureAlphaMod(ture1,10);//使用了半透明函数后，设置半透明参数大小

    SDL_Rect rect1;
    rect1.x = 0;
    rect1.y = 0;
    rect1.w = 800;
    rect1.h = 600;


    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = imgSurface0->w;
    rect.h = imgSurface0->h;


    SDL_Event event;
    bool quit = false;

    while(quit==false)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(event.type == SDL_MOUSEMOTION)
            {
                rect.x = event.motion.x - rect.w/2;
                rect.y = event.motion.y - rect.h/2;
            }
        }
        //语句1：清空图像
//        SDL_RenderClear(render);
        //语句2：利用设置透明度的图像，进行清空
        SDL_RenderCopy(render,ture1,NULL,&rect1);
        SDL_RenderCopy(render,ture0,NULL,&rect);

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
