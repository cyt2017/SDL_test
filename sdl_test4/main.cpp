#include <QCoreApplication>
#include <SDL2/SDL_image.h>

//实现功能：使图像在显示面上往右下方移动，当碰到边框后成90度方向移动
SDL_Rect rect;
bool Right = true;
bool Down = true;
void UpdataPosition()
{
    if(Right)
    {
        rect.x++;
        if(rect.x + rect.w >= 800)
        {
            Right = false;
        }
    }
    else
    {
        rect.x--;
        if(rect.x<=0)
        {
            Right = true;
        }
    }

    if(Down)
    {
        rect.y++;
        if(rect.y + rect.h >= 600)
        {
            Down = false;
        }
    }
    else
    {
        rect.y--;
        if(rect.y<=0)
        {
            Down = true;
        }
    }
}

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

//    return a.exec();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("sdl_test4",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);

    //Renderer  渲染,创建成功之后，一定要清空，防止有乱码,最后一个参数表示：硬件加速
    SDL_Renderer *render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(render);

    //Texture   纹理,在Renderer上面贴图像，首先需要把surface转换成Texture，才能使用 SDL_RenderCopy函数把图像贴到Renderer上面。
    SDL_Surface *imgSurface = IMG_Load("0.png");
    SDL_Texture *ture = SDL_CreateTextureFromSurface(render,imgSurface);

    //在使用SDL_Rect时，需要把它的x，y，w，h值全部都要设定好，虽然不会出错，但是显示面上会没有显示
//    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = imgSurface->w;
    rect.h = imgSurface->h;


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
        }
        UpdataPosition();
        SDL_RenderClear(render);//使用之前先清空
        SDL_RenderCopy(render,ture,NULL,&rect);//使用 SDL_RenderCopy函数把图像贴到Renderer上面

        SDL_Delay(25);//由于一直占用cpu所以会导致对cpu的过度使用，而在视觉上来说，一般图像25ms转换图像都是连续的，所以使用了等待函数
        SDL_RenderPresent(render);//把render进行显示
    }

    SDL_DestroyTexture(ture);
    SDL_DestroyRenderer(render);

    SDL_FreeSurface(imgSurface);
    SDL_DestroyWindow(window);
    SDL_QUIT;
}
