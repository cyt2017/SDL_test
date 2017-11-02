#include <QCoreApplication>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_events.h>

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("SDL Window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);

    SDL_Rect  rect;
    rect.x = 0;
    rect.y = 0;

    SDL_Surface *surface = SDL_GetWindowSurface(window);
//    SDL_Surface *image   = SDL_LoadBMP("0.bmp");//获取图像
    SDL_Surface *image1   = IMG_Load("0.png");
    if (image1 == NULL)
        printf("SDL_LoadBMP failed: %s\n", SDL_GetError());
    SDL_Surface *image2   = IMG_Load("2.png");

    SDL_BlitSurface(image1,NULL,surface,&rect);

    //窗口响应事件，实现
    SDL_Event event;
    //创建一个图像,为当前图像
    SDL_Surface *currentImg = image1;
    bool quit = false;
    while(quit == false)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)//当在窗口上选择了x按钮时
            {
                printf("hello world\n");
//                exit(0);//表示退出窗口,方法1,不合理，因为会使程序整个退出，占用的内存没有得到释放
                quit = true;//退出窗口，方法2，采用了标志，使用标志可以不进入循环，很好的完成释放内存，同时也能完成其他的操作。
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN)//当在窗口上按下鼠标左键时
            {
                printf("clicke\n");
                SDL_FillRect(surface,NULL,0);//把窗口的显示面全部涂成黑色0
                if(event.button.button == SDL_BUTTON_LEFT)
                {
//                    printf("LEFT\n");
//                    SDL_BlitSurface(image1,NULL,surface,&rect);
                    currentImg = image1;
                }
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
//                    printf("RIGHT\n");
//                    SDL_BlitSurface(image2,NULL,surface,&rect);
                    currentImg = image2;
                }
                SDL_BlitSurface(currentImg,NULL,surface,&rect);
            }
            else if(event.type == SDL_KEYDOWN)//当在窗口上按下键盘上的按键时
            {
                printf("key\n");
                if(event.key.keysym.sym == SDLK_UP)
                {
                    rect.y -= 10;
                }
                else if(event.key.keysym.sym == SDLK_DOWN)
                {
                    rect.y += 10;
                }
                else if(event.key.keysym.sym == SDLK_LEFT)
                {
                    rect.x -= 10;
                }
                else if(event.key.keysym.sym == SDLK_RIGHT)
                {
                    rect.x += 10;
                }
                SDL_FillRect(surface,NULL,0);//把窗口的显示面全部涂成黑色0
                SDL_BlitSurface(currentImg,NULL,surface,&rect);//根据按键设置rect的移动后更新显示
            }

        }
        SDL_UpdateWindowSurface(window);//
    }



//    SDL_Delay(3000);//waitkey 3s
    SDL_FreeSurface(image1);
    SDL_FreeSurface(image2);
    SDL_FreeSurface(surface);

    SDL_DestroyWindow(window);
    //步骤5:
    SDL_QUIT;
//    return a.exec();
}
