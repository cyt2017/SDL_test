#include <QCoreApplication>
#include <SDL2/SDL_image.h>

//实验1：使用SDL的SDL_FillRect和SDL_BlitSurface函数，实现的图像在移动时的实时更新，但是一旦遇到大型的工程这种方法将会出现严重闪屏。
int main01(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);
//    return a.exec();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("sdl_test3",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);

    //Renderer
//    SDL_Renderer *render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
//    SDL_RenderClear(render);

    SDL_Surface *surface = SDL_GetWindowSurface(window);
    //Texture
    SDL_Surface *imgSurface = IMG_Load("0.png");
//    SDL_Texture *ture = SDL_CreateTextureFromSurface(render,imgSurface);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = imgSurface->w;
    rect.h = imgSurface->h;

    SDL_BlitSurface(imgSurface,NULL,surface,&rect);
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
                int x = event.motion.x /*- rect.w/2*/;//
                int y = event.motion.y/* - rect.h/2*/;
                rect.x = x;
                rect.y = y;
                SDL_FillRect(surface,NULL,0);
                SDL_BlitSurface(imgSurface,NULL,surface,&rect);
               SDL_UpdateWindowSurface(window);
            }
        }

    }

    SDL_FreeSurface(surface);
    SDL_FreeSurface(imgSurface);
    SDL_DestroyWindow(window);
    SDL_QUIT;
}


//实验2：为了防止图像出现闪屏，于是出现了两个工具 Renderer（渲染）和Texture（纹理）
int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("sdl_test3",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);

    //Renderer  渲染,创建成功之后，一定要清空，防止有乱码
    SDL_Renderer *render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(render);

    //Texture   纹理,在Renderer上面贴图像，首先需要把surface转换成Texture，才能使用 SDL_RenderCopy函数把图像贴到Renderer上面。
    SDL_Surface *imgSurface = IMG_Load("0.png");
    SDL_Texture *ture = SDL_CreateTextureFromSurface(render,imgSurface);

    //在使用SDL_Rect时，需要把它的x，y，w，h值全部都要设定好，虽然不会出错，但是显示面上会没有显示
    SDL_Rect rect;
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
            else if(event.type == SDL_MOUSEMOTION)
            {
                int x = event.motion.x - rect.w/2;//
                int y = event.motion.y - rect.h/2;
                rect.x = x;
                rect.y = y;
                SDL_RenderClear(render);//使用之前先清空
                SDL_RenderCopy(render,ture,NULL,&rect);//使用 SDL_RenderCopy函数把图像贴到Renderer上面
            }
        }
        SDL_Delay(5);//由于一直占用cpu所以会导致对cpu的过度使用，而在视觉上来说，一般图像25ms转换图像都是连续的，所以使用了等待函数
        SDL_RenderPresent(render);//把render进行显示
    }

    SDL_DestroyTexture(ture);
    SDL_DestroyRenderer(render);

    SDL_FreeSurface(imgSurface);
    SDL_DestroyWindow(window);
    SDL_QUIT;
}
