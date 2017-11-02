#include <QCoreApplication>
#include <SDL2/SDL_image.h>

//把一张大图分割成小图，然后显示出动态图的效果，并把图像的背景设置成透明色
int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

//    return a.exec();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("sdl_test5",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);

    SDL_Renderer *render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(render);

    SDL_Surface *imgSurface = IMG_Load("0.png");

    //设置背景色为透明色
//    SDL_SetColorKey(imgSurface,SDL_TRUE,SDL_MapRGB(imgSurface->format,238,242,251));
    SDL_Texture *ture = SDL_CreateTextureFromSurface(render,imgSurface);

    SDL_Rect imgRect[4];
    int width  = imgSurface->w/4;
    int height = imgSurface->h;
    for(int i=0;i<4;i++)
    {
        imgRect[i].x = i*width;
        imgRect[i].y = 0;
        imgRect[i].w = width;
        imgRect[i].h = height;
    }

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;


    SDL_Event event;
    bool quit = false;
    int index=0;
    while(quit==false)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_RenderClear(render);//使用之前先清空
        SDL_RenderCopy(render,ture,&imgRect[index],&rect);//使用 SDL_RenderCopy函数把图像贴到Renderer上面
        index = (index+1)%4;


        SDL_Delay(500);//由于一直占用cpu所以会导致对cpu的过度使用，而在视觉上来说，一般图像25ms转换图像都是连续的，所以使用了等待函数
        SDL_RenderPresent(render);//把render进行显示
        rect.x =rect.x + rect.w/2;
        if(rect.x>=800)
        {
            rect.x = 0;
        }

    }

    SDL_DestroyTexture(ture);
    SDL_DestroyRenderer(render);

    SDL_FreeSurface(imgSurface);
    SDL_DestroyWindow(window);
    SDL_QUIT;
}
