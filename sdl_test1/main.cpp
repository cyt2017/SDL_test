#include <QCoreApplication>
//#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);


    //步骤1:SDL是用于显示的工具，需要初始化，
    SDL_Init(SDL_INIT_VIDEO);
    //步骤2:创建一个SDL窗口时，需要设置窗口的名字，左上角的起始点，窗口的宽和高，以及显示的位置
    SDL_Window *window = SDL_CreateWindow("SDL Window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);


    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;

    //设置窗口的面
    SDL_Surface *surface = SDL_GetWindowSurface(window);
//    SDL_Surface *image   = SDL_LoadBMP("0.bmp");//获取图像
    SDL_Surface *image   = IMG_Load("0.png");
    if (image == NULL)
        printf("SDL_LoadBMP failed: %s\n", SDL_GetError());
    SDL_BlitSurface(image,NULL,surface,&rect);//SDL函数:把获得的图像贴在面上
    SDL_UpdateWindowSurface(window);//刷新函数：如果图像不在窗口上显示，那么是因为没有刷新

    //步骤3:窗口暂停，以毫秒为单位
    SDL_Delay(3000);//waitkey 3s
    SDL_FreeSurface(image);
    SDL_FreeSurface(surface);
    //步骤4:窗口创建之后记得销毁
    SDL_DestroyWindow(window);
    //步骤5:
    SDL_QUIT;
   // return a.exec();
}
