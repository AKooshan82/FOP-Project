
//-------proje BP kooshan fattah 401102191 va Hossein Yaghobizade vanini 
#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <string>
#include <cstring>
#include <time.h>
#include <vector>
#include <SDL2/SDL2_gfxPrimitives_font.h>
#include <SDL2/SDL_mixer.h>
using namespace std;
bool reguser, regpass, loguser, logpass;
bool exists;
bool is_music = 0;
bool is_sound = 0;
//bool sound = 0;
bool music = 0;
bool is_mode = 0;
bool first_start = 1;
bool pause_to_start = 0;
bool first_firstmap = 1;
bool first_secondmap = 1;
bool first_thirdmap = 1;
bool musicchanged = 0;
int first_map_x_path[1000];
int second_map_x_path[1000];
int third_map_x_path[1000];
short int mode_game;
double zdfgh;
SDL_Renderer * m_renderer;
Mix_Music * music_1; //=Mix_LoadMUS("resources/music/forest.mp3");
Mix_Music * music_2; //=Mix_LoadMUS("resources/music/startmenu.mp3");
Mix_Music * music_3; //=Mix_LoadMUS("resources/music/zuma delux.mp3");
Mix_Music * music_4; //=Mix_LoadMUS("resources/music/zume revenge.mp3");
Mix_Music * music_5; //=Mix_LoadMUS("resources/music/marbleblast.mp3");
Mix_Chunk * click_sound = Mix_LoadWAV("resources/music/click.wav");
bool sound = true;
string s1;
string s2;
string m[3] = {
    "music : marble",
    "music : zuma1",
    "music : zuma2"
};
int music_number = 0;
string username;
string password;
double angle;
int r = 0, g = 255, b = 255;
void map_random(SDL_Renderer *renderer);
void pausemenu(SDL_Renderer * renderer, int & mod);
class Image {
    SDL_Texture * texture;
    int w, h;

    public:
        Image(string addressOfImage, SDL_Renderer * renderer) {
            //        int n = addressOfImage.length();
            //        char char_array[n+1];
            //        strcpy(char_array, addressOfImage.c_str());
            this -> texture = IMG_LoadTexture(renderer, addressOfImage.c_str());
            SDL_QueryTexture(texture, NULL, NULL, & w, & h);

        }

        ~Image() {
            SDL_DestroyTexture(texture);
        }
    int getW() {
        return w;
    }
    int getH() {
        return h;
    }
    void render(SDL_Renderer * m_renderer, int xp, int yp, int width, int height);
    void render(SDL_Renderer * m_renderer, int xp, int yp) {
        render(m_renderer, xp, yp, w, h);
    }
};
void Help(SDL_Renderer * renderer);
void mapmenu(SDL_Renderer * renderer);
void modemenu(SDL_Renderer * renderer);
//void startmenu(SDL_Renderer *renderer);
void first_map(SDL_Renderer * renderer);
void second_map(SDL_Renderer * renderer);
void third_map(SDL_Renderer * renderer);
void angledImage(SDL_Renderer * renderer, string addressOfImage, int x, int y, int width, int height, double angle) {
    int n = addressOfImage.length();
    char char_array[n + 1];
    strcpy(char_array, addressOfImage.c_str());
    SDL_Texture * myTexture;
    myTexture = IMG_LoadTexture(renderer, char_array);
    SDL_Rect rectangle {
        x,
        y,
        width,
        height
    };
    SDL_Point center = {
        width / 2,
        height / 2-20};
    SDL_QueryTexture(myTexture, NULL, NULL, & width, & height);
    SDL_RenderCopyEx(renderer, myTexture, NULL, & rectangle, angle, &center, SDL_FLIP_NONE);
    SDL_DestroyTexture(myTexture);
}
void betterText(SDL_Renderer * renderer, string S, int x, int y, int r, int g, int b, int a, int size, string Font /*def = arial */ );
/* Function that take input as Control Point x_coordinates and
Control Point y_coordinates and draw bezier curve */
//void angledImage(SDL_Renderer *renderer,string addressOfImage , int x, int y, int width, int height, double angle){
//    int n=addressOfImage.length();
//    char char_array[n+1];
//    strcpy(char_array, addressOfImage.c_str());
//    SDL_Texture *myTexture;
//    myTexture = IMG_LoadTexture(renderer, char_array);
//    SDL_Rect rectangle{x,y,width,height};
//    SDL_QueryTexture (myTexture,NULL,NULL,&width,&height);
//    SDL_RenderCopyEx(renderer,myTexture,NULL,&rectangle,angle,NULL,SDL_FLIP_NONE);
//    SDL_DestroyTexture(myTexture);
//}
void bezierCurve(int x[], int y[], SDL_Renderer * renderer) {
    double xu = 0.0, yu = 0.0, u = 0.0;
    int i = 0;

    for (u = 0.0; u <= 1.0; u += 0.001) {
        xu = pow(1 - u, 9) * x[0] + 9 * u * pow(1 - u, 8) * x[1] + 36 * pow(u, 2) * pow(1 - u, 7) * x[2] + 84 * pow(u, 3) * pow(1 - u, 6) * x[3] +
            126 * pow(u, 4) * pow(1 - u, 5) * x[4] + 126 * pow(u, 5) * pow(1 - u, 4) * x[5] + 84 * pow(u, 6) * pow(1 - u, 3) * x[6] + 36 * pow(u, 7) * pow(1 - u, 2) * x[7] + 9 * pow(u, 8) * (1 - u) * x[8] + pow(u, 9) * x[9];
        yu = pow(1 - u, 9) * y[0] + 9 * u * pow(1 - u, 8) * y[1] + 36 * pow(u, 2) * pow(1 - u, 7) * y[2] + 84 * pow(u, 3) * pow(1 - u, 6) * y[3] +
            126 * pow(u, 4) * pow(1 - u, 5) * y[4] + 126 * pow(u, 5) * pow(1 - u, 4) * y[5] + 84 * pow(u, 6) * pow(1 - u, 3) * y[6] + 36 * pow(u, 7) * pow(1 - u, 2) * y[7] + 9 * pow(u, 8) * (1 - u) * y[8] + pow(u, 9) * y[9];
        SDL_RenderDrawPoint(renderer, (int) xu, (int) yu);
      
//        filledEllipseRGBA(renderer,(int)xu,(int)yu,15,15,125,125,125,255);
    }
}
void TextBox(SDL_Renderer * renderer, int x, int y, int w, int h, string & name) {
    int font = 2;
    bool caps_lock = false;
    int x_position = x;
    int y_position = y;
    int R = 0;
    int G = 0;
    int B = 0;
    int A = 0.5;
    int W = w;
    int H = h;
    bool quit = false;
    SDL_Rect textbackground {
        x - 10, y - 5, w - 25, h - 5
    };
    SDL_RenderFillRect(renderer, & textbackground);
    SDL_RenderPresent(renderer);
    char ch = 0;
    SDL_Event * event = new SDL_Event();
    while (!quit) {
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(event)) {
            if (event -> type == SDL_KEYUP) {
                switch (event -> key.keysym.sym) {
                case SDLK_SPACE:
                    //quit = true;
                    ch = ' ';
                    break;
                case SDLK_RETURN:
                    quit = true;
                    break;
                case SDLK_CAPSLOCK:
                    ch = 0;
                    caps_lock = !caps_lock;
                    break;
                case SDLK_BACKSPACE:
                    ch = 0;
                    if (name.length() != 0) {
                        //drawing a rectanlge over the removed letters
                        SDL_RenderFillRect(renderer, & textbackground);
                        name = name.substr(0, name.length() - 1);
 //                       textRGBA(renderer, x_position, y_position, name.c_str(), font, 35, 255, 255, 0, 255);
                    }
                    break;
                default:
                    if (event -> key.keysym.sym != SDLK_UP && event -> key.keysym.sym != SDLK_DOWN && event -> key.keysym.sym != SDLK_LEFT && event -> key.keysym.sym != SDLK_RIGHT)
                        ch = event -> key.keysym.sym;
                    break;
                }
                if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == ' ') && name.length() < 25 && !quit) {
                    if (caps_lock == 1 && ch != ' ')
                        name += ch + 'A' - 'a';
                    else
                        name += ch;
                }
   //             if (name != "" && !quit)
   //                 textRGBA(renderer, x_position, y_position, name.c_str(), font, 35, 255, 255, 0, 255);
            }
        }
    }
}
void register_page(SDL_Renderer * renderer);
void login_page(SDL_Renderer * renderer);
void quit(SDL_Renderer * renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    //SDL_DestroyWindow( window );
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
}
class image {
    private: SDL_Renderer * ren;
    SDL_Rect img_rect;
    public: string path;
    SDL_Texture * img;
    int img_w,
    img_h;
    int x;
    int y;
    float sc_x;
    float sc_y;
    void run() {
        img = IMG_LoadTexture(ren, path.c_str());
        SDL_QueryTexture(img, NULL, NULL, & img_w, & img_h);
    }
    void load() {
        //const char* cpath = path.c_str();
        img_rect.x = x;
        img_rect.y = y;
        img_rect.w = sc_x;
        img_rect.h = sc_y;
        SDL_RenderCopy(ren, img, NULL, & img_rect);
        //delete cpath;
    }
    image(string Path, int X, int Y, float SCX, float SCY, SDL_Renderer * Ren) {
        x = X;
        y = Y;
        path = Path;
        sc_x = SCX;
        sc_y = SCY;
        ren = Ren;
        run();
        load();
    }
    void setCenter(int X, int Y) {
        x = X - img_w * sc_x / 2;
        y = Y - img_h * sc_y / 2;
        load();
    }
    void render() {
        SDL_RenderCopy(ren, img, NULL, & img_rect);
    }
    ~image() {
        SDL_DestroyTexture(img);
    }
};
class btn {

    private: int x;
    int y;
    int he;
    int wi;
    public: image * pic;
    btn(int X, int Y, string Path, float SCX, float SCY, SDL_Renderer * Ren) {
        pic = new image(Path, X, Y, SCX, SCY, Ren);
        x = X;
        y = Y;
        he = pic -> img_h;
        wi = pic -> img_w;
    }
    ~btn() {
        delete pic;
    }
    void setXY(int X, int Y) {
        x = X;
        y = Y;
        pic -> x = X;
        pic -> y = Y;
        pic -> load();
    }
    void setCenter(int X, int Y) {
        x = X - wi * pic -> sc_x / 2;
        y = Y - he * pic -> sc_y / 2;
        pic -> x = x;
        pic -> y = y;
        pic -> load();
    }
    bool btn_clicked(int mouse_x, int mouse_y) {
        if (mouse_x >= x && mouse_x <= x + wi * pic -> sc_x &&
            mouse_y >= y && mouse_y <= y + he * pic -> sc_y)
            return true;
        else
            return false;
    }
};
struct ball{
    int x;
    int y;
    int radius;
    int counter;
    int color;
    bool given_color;
    bool shoot;
    double dx,dy;
};
//textures //////////////////////////////
image * loginbg;
image * loginform;
image * backbutt;
image * log_butt;
image * registerbg;
image * registerform;
image * reg_butt;
image * kirbg;
image * mapmenubg;
image * sm_mb;
image * sm_quitb;
image * sm_rb;
image * mapmenu_closeb1;
image * mapmenu_closeb2;
image * map2bg;
image * third_mapbg;
image * sm_xb;
image * startbuttonsbg;
image * pm_gbb;
image * pm_conb;
image * pm_eb;
image * pausemenu_closb;
image * image_startmenu;
image * play1_button;
image * play2_button;
image * map1_button;
image * exit1_button;
image * setting1_button;
image * leaderboard1_button;
image * exit2_button;
image * map2_button;
image * setting2_button;
image * leaderboard2_button;
image * music2_button;
image * music1_button;
image * music3_button;
image * music4_button;
image * sound2_button;
image * sound1_button;
image * sound3_button;
image * sound4_button;
image * help2_button;
image * help1_button;
image * close2_button;
image * close1_button;
image * help_table;
image * help_closb;
image * pm_sb;
image * pm_mb;
image * pre_butt;
image * next_butt;
image * change_music;
image * start_hole1;
image * end_hole1;
image * start_hole2;
image * end_hole2;
image * start_hole3;
image * end_hole3;
image * time1_mode;
image * time2_mode;
image * rock1_mode;
image * rock2_mode;
image * bird1_mode;
image * bird2_mode;
image * clear1_mode;
image * clear2_mode;
image * mode_table;
image * close1_modetable;
image * close2_modetable;
Image * yellow_ball;
Image * green_ball;
Image * blue_ball;
Image * red_ball;
//textures ////////////////////////////////
void startmenu(SDL_Renderer * renderer) {
    SDL_RenderClear(renderer);
    music_number = 0;

    SDL_Event * event = new SDL_Event();
    Mix_Chunk * click_sound = Mix_LoadWAV("resources/music/click.wav");
    Mix_PauseMusic();
    if (first_start) {
       Mix_PlayMusic(music_2, -1);
        Mix_ResumeMusic();
        first_start = 0;
        sound = 0;
        music = 0;
    } else {
        if (pause_to_start) {
            if (is_music) {
                //          Mix_PauseMusic();

                music = 1;
            } else {
                Mix_PlayMusic(music_2, -1);
                pause_to_start = 0;
                music = 0;
            }
            if (is_sound) {
                sound = 1;
            } else {
                sound = 0;
            }
        } else {
            if (is_music) {
               Mix_PauseMusic();

                music = 1;
            } else {
                Mix_ResumeMusic();

                music = 0;
            }
            if (is_sound) {
                sound = 1;
            } else {
                sound = 0;
            }
        }
    }

    bool b = 0;

    bool table = 0;
    image_startmenu -> render();
    play1_button -> render();
    map1_button -> render();
    exit1_button -> render();
    setting1_button -> render();
    leaderboard1_button -> render();
    //SDL_RenderPresent(renderer);
    SDL_Event * event2 = new SDL_Event();
    bool c = 1;

    while (c) {

        event -> type = 0;
        SDL_PollEvent(event);
        if (SDL_PollEvent(event)) {
            if (event -> type == SDL_QUIT) {
                quit(renderer);
                break;
            }
        }
        if (event -> type == SDL_MOUSEMOTION) {
            int x, y;
            SDL_GetMouseState( & x, & y);
            if (x > 590 && x < 790) {
                if (y > 540 && y < 600) {
                    play2_button -> render();

                } else if (y > 610 && y < 670) {
                    map2_button -> render();

                } else if (y > 680 && y < 740) {
                    exit2_button -> render();

                } else {
                    play1_button -> render();
                    map1_button -> render();
                    exit1_button -> render();
                }
            } else if (x > 1190 && x < 1280) {
                if (y < 800 && y > 710) {
                    setting2_button -> render();

                } else {
                    setting1_button -> render();

                }
            } else if (x > 0 && x < 90) {
                if (y < 800 && y > 710) {
                    leaderboard2_button -> render();

                } else {
                    leaderboard1_button -> render();

                }
            } else {
                play1_button -> render();
                map1_button -> render();
                exit1_button -> render();
                setting1_button -> render();
                leaderboard1_button -> render();

            }
        }

        if (event -> type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState( & x, & y);
            if (x > 590 && x < 790) {
                if (y > 680 && y < 740) {
                    if (event -> button.button == SDL_BUTTON_LEFT) {
                        if (!is_sound) {
                           Mix_PlayChannel(-1, click_sound, 0);
                        }

                        SDL_Delay(200);
                        quit(renderer);
                        break;
                    }
                } else if (y > 540 && y < 600) {
                    if (event -> button.button == SDL_BUTTON_LEFT) {
                        if (!is_sound) {
                           Mix_PlayChannel(-1, click_sound, 0);
                        }
                        if (is_mode) {

                            mapmenu(renderer);
                            c = 0;
                            break;
                        } else {
                            betterText(renderer, "WARNING : you should choose a mode to start", 640, 110, 255, 0, 0, 255, 40, "YoungBarse");
                            SDL_RenderPresent(renderer);
                            SDL_Delay(2000);
                            SDL_RenderClear(renderer);
                            startmenu(renderer);
                        }

                        //                  SDL_RenderPresent(m_renderer);
                        break;

                    }
                } else if (y > 610 && y < 670) {
                    if (event -> button.button == SDL_BUTTON_LEFT) {
                        if (!is_sound) {
                            Mix_PlayChannel(-1, click_sound, 0);
                        }

                        modemenu(renderer);
                        c = 0;
                        break;

                        //                  SDL_RenderPresent(m_renderer);

                    }
                }
            } else if (x > 1190 && x < 1280) {
                if (y > 710 && y < 800) {
                    if (event -> button.button == SDL_BUTTON_LEFT) {
                        if (!is_sound) {
                            Mix_PlayChannel(-1, click_sound, 0);
                        }
                        b = 1;
                        table = 0;
                        setting2_button -> render();
                        help1_button -> render();
                        if (sound) {
                            sound3_button -> render();
                        } else {
                            sound1_button -> render();
                        }
                        if (music) {
                            music3_button -> render();
                        } else {
                            music1_button -> render();
                        }

                        while (b) {

                            setting2_button -> render();
                            //
                            int x, y;
                            SDL_GetMouseState( & x, & y);
                            event -> type = 0;
                            SDL_PollEvent(event);
                            if (event -> type == SDL_QUIT) {
                                {
                                    quit(renderer);
                                    break;
                                }
                            } else if (event -> type == SDL_MOUSEBUTTONDOWN) {
                                if (event -> button.button == SDL_BUTTON_LEFT) {
                                    if (x > 1190 && x < 1280 && y > 710 && y < 800) {
                                        event -> type = 0;
                                        b = 0;
                                        if (!is_sound) {
                                           Mix_PlayChannel(-1, click_sound, 0);
                                        }
                                        SDL_RenderClear(renderer);
                                        image_startmenu -> render();
                                        play1_button -> render();
                                        map1_button -> render();
                                        exit1_button -> render();
                                        setting1_button -> render();
                                        leaderboard1_button -> render();
                                        break;
                                    } else if (x > 1190 && x < 1280 && y > 618 && y < 708 && !table) {
                                        SDL_RenderClear(renderer);
                                        image_startmenu -> render();
                                        play1_button -> render();
                                        map1_button -> render();
                                        exit1_button -> render();
                                        setting2_button -> render();
                                        leaderboard1_button -> render();
                                        help1_button -> render();

                                        if (music) {
                                            music3_button -> render();
                                        } else {
                                            music1_button -> render();
                                        }
                                        if (sound) {

                                           Mix_Chunk * click_sound = Mix_LoadWAV("resources/music/click.wav");
                                           Mix_PlayChannel(-1, click_sound, 0);
                                            sound1_button -> render();
                                            is_sound = 0;
                                            sound = 0;
                                            SDL_Delay(1);
                                            sound2_button -> render();

                                        } else {

                                            sound3_button -> render();
                                            is_sound = 1;
                                            sound = 1;
                                            SDL_Delay(1);
                                            sound4_button -> render();
                                        }
                                        //
                                    } else if (x > 1098 && x < 1188 && y > 710 && y < 800 && !table) {
                                        if (!is_sound) {
                                            Mix_PlayChannel(-1, click_sound, 0);
                                        }
                                        SDL_RenderClear(renderer);
                                        image_startmenu -> render();
                                        play1_button -> render();
                                        map1_button -> render();
                                        exit1_button -> render();
                                        setting2_button -> render();
                                        leaderboard1_button -> render();
                                        help1_button -> render();

                                        if (sound) {
                                            sound3_button -> render();
                                        } else {
                                            sound1_button -> render();
                                        }
                                        if (music) {
                                            music1_button -> render();
                                            music = 0;

                                            is_music = 0;
                                            SDL_Delay(1);
                                            if (pause_to_start) {
                                                Mix_PlayMusic(music_2, -1);
                                                pause_to_start = 0;
                                            } else {
                                               Mix_ResumeMusic();
                                            }

                                            music2_button -> render();

                                        } else {
                                            music3_button -> render();
                                            music = 1;
                                            is_music = 1;

                                           Mix_PauseMusic();
                                            SDL_Delay(1);

                                            music4_button -> render();

                                        }

                                    } else if (x > 1098 && x < 1188 && y > 618 && y < 708 && !table) {
                                        if (!is_sound) {
                                            Mix_PlayChannel(-1, click_sound, 0);
                                        }
                                        SDL_RenderClear(renderer);
                                        image_startmenu -> render();
                                        play1_button -> render();
                                        map1_button -> render();
                                        exit1_button -> render();
                                        setting2_button -> render();
                                        leaderboard1_button -> render();
                                        help2_button -> render();
                                        if (music) {
                                            music3_button -> render();
                                        } else {
                                            music1_button -> render();
                                        }
                                        if (sound) {
                                            sound3_button -> render();
                                        } else {
                                            sound1_button -> render();

                                        }
                                        help_table -> render();
                                        SDL_GetMouseState( & x, & y);
                                        table = 1;
                                        event -> type = 0;
                                        SDL_PollEvent(event);
                                        close1_button -> render();
                                    }

                                    if (table && x > 623 && x < 663 && y > 550 && y < 590) {
                                        SDL_RenderClear(renderer);
                                        table = 0;
                                        image_startmenu -> render();
                                        play1_button -> render();
                                        map1_button -> render();
                                        exit1_button -> render();
                                        setting2_button -> render();
                                        leaderboard1_button -> render();

                                        if (music) {
                                            music3_button -> render();
                                        } else {
                                            music1_button -> render();
                                        }
                                        if (sound) {
                                            sound3_button -> render();
                                        } else {
                                            sound1_button -> render();

                                        }
                                        help2_button -> render();
                                        SDL_Delay(1);
                                        help1_button -> render();

                                    }

                                }
                            }
                            if (event -> type == SDL_MOUSEMOTION) {

                                if (x > 1098 && x < 1188 && y > 618 && y < 708) {
                                    setting2_button -> render();
                                    if (sound) {
                                        sound3_button -> render();
                                    } else {
                                        sound1_button -> render();
                                    }
                                    if (music) {
                                        music3_button -> render();
                                    } else {
                                        music1_button -> render();
                                    }

                                    help2_button -> render();
                                    //
                                } else if (x > 1190 && x < 1280 && y > 618 && y < 708) {

                                    setting2_button -> render();
                                    if (table) {
                                        help2_button -> render();
                                    } else {
                                        help1_button -> render();
                                    }

                                    if (sound) {
                                        sound4_button -> render();

                                    } else {
                                        sound2_button -> render();

                                    }
                                    if (music) {
                                        music3_button -> render();

                                    } else {
                                        music1_button -> render();

                                    }

                                } else if (x > 1098 && x < 1188 && y > 710 && y < 800) {
                                    setting2_button -> render();
                                    if (table) {
                                        help2_button -> render();
                                    } else {
                                        help1_button -> render();
                                    }
                                    if (sound) {
                                        sound3_button -> render();
                                    } else {
                                        sound1_button -> render();
                                    }
                                    if (music) {
                                        music4_button -> render();
                                    } else {
                                        music2_button -> render();
                                    }

                                } else {
                                    if (table) {
                                        if (x > 623 && x < 663 && y > 550 && y < 590) {
                                            help_table -> render();
                                            close2_button -> render();
                                        } else {
                                            help_table -> render();
                                            close1_button -> render();
                                        }

                                    }
                                    setting2_button -> render();
                                    if (table) {
                                        help2_button -> render();
                                    } else {
                                        help1_button -> render();
                                    }
                                    if (sound) {
                                        sound3_button -> render();
                                    } else {
                                        sound1_button -> render();
                                    }
                                    if (music) {
                                        music3_button -> render();
                                    } else {
                                        music1_button -> render();
                                    }
                                    //

                                }
                            }

                            SDL_RenderPresent(renderer);
                        }

                    }
                }
            }

        }
        SDL_RenderPresent(renderer);
    }

}
void first_page(SDL_Renderer * renderer, string & modfirstpage, int & mouse_x, int & mouse_y) {
    SDL_RenderClear(renderer);
    image * bg = new image("resources/pics/background1.jpg", 0, 0, 1280, 800, renderer);
    bg -> render();
    image * logbutt = new image("resources/pics/logbbg.png", 150, 150, 150, 56, renderer);
    logbutt -> render();
    betterText(renderer, "Login", 220, 180, 255, 255, 0, 255, 35, "chrustyrock");
    image * regbutt = new image("resources/pics/registerbbg.png", 150, 220, 150, 56, renderer);
    regbutt -> render();
    betterText(renderer, "Register", 225, 250, 255, 255, 0, 255, 35, "chrustyrock");

    image * quitbutt = new image("resources/pics/quitfpb.png", 150, 290, 150, 56, renderer);
    quitbutt -> render();
    betterText(renderer, "Quit", 225, 320, 0, 255, 255, 255, 35, "chrustyrock");

    bool firstpage = true;
    SDL_Event * e = new SDL_Event();
    bool go_out = false;
    SDL_RenderPresent(renderer);
    while (firstpage) {
        SDL_PollEvent(e);
        if (e -> type == SDL_QUIT) {
            quit(renderer);
        }

        SDL_GetMouseState( & mouse_x, & mouse_y);
        if (mouse_x >= 150 && mouse_x <= 300 && mouse_y >= 150 && mouse_y <= 206) {
            if (e -> type == SDL_MOUSEBUTTONDOWN) {
                modfirstpage = "login";
                break;
            } else {
                betterText(renderer, "Login", 220, 180, 255, 0, 0, 255, 35, "chrustyrock");
                SDL_RenderPresent(renderer);
            }
        } else {
            betterText(renderer, "Login", 220, 180, 255, 255, 0, 255, 35, "chrustyrock");
            SDL_RenderPresent(renderer);
        }
        if (mouse_x >= 150 && mouse_x <= 300 && mouse_y >= 220 && mouse_y <= 276) {
            if (e -> type == SDL_MOUSEBUTTONDOWN) {
                modfirstpage = "Register";
                break;
            } else {
                betterText(renderer, "Register", 225, 250, 255, 0, 0, 255, 35, "chrustyrock");
                SDL_RenderPresent(renderer);
            }
        } else {
            betterText(renderer, "Register", 225, 250, 255, 255, 0, 255, 35, "chrustyrock");
            SDL_RenderPresent(renderer);
        }
        if (mouse_x >= 150 && mouse_x <= 300 && mouse_y >= 290 && mouse_y <= 346) {
            if (e -> type == SDL_MOUSEBUTTONDOWN) {
                quit(renderer);
                firstpage = 0;
            } else {
                betterText(renderer, "Quit", 225, 320, 255, 0, 0, 255, 35, "chrustyrock");
                SDL_RenderPresent(renderer);
            }
        } else {
            betterText(renderer, "Quit", 225, 320, 255, 255, 0, 255, 35, "chrustyrock");
            SDL_RenderPresent(renderer);
        }

        //        else if(e->type == SDL_MOUSEMOTION){
        //                SDL_RenderClear(renderer);
        //                bg->render();
        //        logbutt->setCenter(150,150);
        //        regbutt->setCenter(150,220);
        //        quitbutt->setCenter(150,290);
        //             SDL_GetMouseState(&mouse_x,&mouse_y);
        //             if(mouse_x >= 150 && mouse_x <= 300 && mouse_y >= 150 && mouse_y <= 206 ){
        //
        //betterText(renderer,"Login",220,180,255,0,0,255,35,"chrustyrock");
        //
        //            }
        //             if(mouse_x >= 150 && mouse_x <= 300 && mouse_y >= 220 && mouse_y <= 276 ){
        //
        //                    betterText(renderer,"Register",225,250,255,0,0,255,35,"chrustyrock");
        //
        //            }
        //             if(mouse_x >= 150 && mouse_x <= 300 && mouse_y >= 290 && mouse_y <= 346 ){
        //
        //                betterText(renderer,"Quit",225,320,0,255,0,0,35,"chrustyrock");
        //            }
        //        }
    }
    SDL_Event * e2 = new SDL_Event();
    SDL_RenderClear(renderer);
    //login page
    if (modfirstpage == "login") {
        string choice;
        login_page(renderer);
        while (1) {
            SDL_PollEvent(e2);
            if (e2 -> type == SDL_QUIT) {
                break;
            }
            int x, y;
            SDL_GetMouseState( & x, & y);
            if (x > 100 && x < 156 && y > 650 && y < 706) {

                if (e2 -> type == SDL_MOUSEBUTTONDOWN) {
                    choice = "firstpage";
                    SDL_RenderClear(renderer);

                }
            }

            if (x > 705 && x < 855 && y > 450 && y < 556) {

                if (e2 -> type == SDL_MOUSEBUTTONDOWN) {

                    if (loguser == false || logpass == false) {
                        betterText(renderer, "Please Enter Full Information", 680, 650, 255, 0, 0, 255, 38, "chrustyrock");
                        SDL_RenderPresent(renderer);
                    }
                    if (loguser == true && logpass == true && exists == false) {
                        betterText(renderer, "Unfortunatley there is no account with this info", 650, 100, 255, 0, 0, 255, 38, "chrustyrock");
                        SDL_RenderPresent(renderer);
                    }
                    if (loguser == true && logpass == true && exists == true) {
                        s2 = username.erase(username.length() - 1);
                        s1 = "Welcome to The GAME " + s2;
                        betterText(renderer, s1, 670, 650, 255, 0, 0, 255, 45, "chrustyrock");

                        //                   Mix_PausedMusic();
                        choice = "start";
                        SDL_RenderPresent(renderer);
                        SDL_Delay(1500);
                        //                   break;
                    }
                } else {
                    betterText(renderer, "Login", 778, 480, 255, 0, 0, 255, 25, "chrustyrock");
                    SDL_RenderPresent(renderer);
                }
            } else {
                betterText(renderer, "Login", 778, 480, 0, 255, 255, 255, 25, "chrustyrock");
                SDL_RenderPresent(renderer);
            }

            if (choice == "firstpage") {
                first_page(renderer, modfirstpage, mouse_x, mouse_y);
            }
            if (choice == "start") {
                startmenu(renderer);
            }
        }
    }
    SDL_Event * e3 = new SDL_Event();
    SDL_RenderClear(renderer);
    //register page
    if (modfirstpage == "Register") {
        string choice;
        register_page(renderer);
        while (1) {
            SDL_PollEvent(e3);
            if (e3 -> type == SDL_QUIT) {
                break;
            }
            int x, y;
            SDL_GetMouseState( & x, & y);
            if (x > 100 && x < 156 && y > 650 && y < 706 && e3 -> type == SDL_MOUSEBUTTONDOWN) {
                choice = "firstpage";
                SDL_RenderClear(renderer);
                break;
            }
            if (x > 705 && x < 855 && y > 450 && y < 556) {
                if (e3 -> type == SDL_MOUSEBUTTONDOWN) {
                    if (reguser == false || regpass == false) {
                        betterText(renderer, "Please Enter Full Information", 680, 650, 0, 255, 255, 255, 38, "chrustyrock");
                        SDL_RenderPresent(renderer);
                    }
                    if (reguser == true && regpass == true && exists == false) {
                        betterText(renderer, "Register Complete ! WELCOME", 680, 650, 0, 255, 255, 255, 38, "chrustyrock");
                        SDL_RenderPresent(renderer);
                    }
                    if (reguser == true && regpass == true && exists == true) {
                        betterText(renderer, "A user already exists with this information", 680, 650, 0, 255, 255, 255, 38, "chrustyrock");
                        SDL_RenderPresent(renderer);
                    }
                } else {
                    betterText(renderer, "Register", 778, 480, 255, 0, 0, 255, 25, "chrustyrock");
                    SDL_RenderPresent(renderer);
                }
            } else {
                betterText(renderer, "Register", 778, 480, 0, 255, 255, 255, 25, "chrustyrock");
                SDL_RenderPresent(renderer);
            }
        }
        if (choice == "firstpage") {
            first_page(renderer, modfirstpage, mouse_x, mouse_y);
        }
    }
}
void login_page(SDL_Renderer * renderer) {
    exists = false;
    loguser = false;
    logpass = false;

    loginbg -> render();

    loginform -> render();

    backbutt -> render();
    log_butt -> render();
    betterText(renderer, "Login", 778, 480, 0, 255, 255, 255, 25, "chrustyrock");
    SDL_RenderPresent(renderer);
    username = "";
    password = "";
    string stored;
    TextBox(renderer, 550, 325, 330, 50, username);
    cout << username << endl;
    if (username != "") loguser = true;
    TextBox(renderer, 550, 395, 330, 50, password);
    cout << password << endl;
    if (password != "") logpass = true;
    fstream file1;
    file1.open("resources/users/userpass.txt");
    string s;
    stored = username.substr(0, username.length() - 1) + ":" + password.substr(0, password.length() - 1);
    while (file1.good() && !file1.eof()) {
        file1 >> s;
        if (s == stored) {
            exists = true;
            break;
        }
    }
    file1.close();
}
void register_page(SDL_Renderer * renderer) {
    exists = false;
    reguser = false;
    regpass = false;

    registerbg -> render();

    registerform -> render();

    backbutt -> render();
    reg_butt -> render();
    betterText(renderer, "Register", 778, 480, 0, 255, 255, 255, 25, "chrustyrock");
    SDL_RenderPresent(renderer);
    username = "";
    password = "";
    string stored;
    TextBox(renderer, 550, 325, 330, 50, username);
    cout << username << endl;
    if (username != "") reguser = true;
    TextBox(renderer, 550, 395, 330, 50, password);
    cout << password << endl;
    if (password != "") regpass = true;
    fstream file1;
    file1.open("resources/users/userpass.txt");
    string s;
    stored = username.substr(0, username.length() - 1) + ":" + password.substr(0, password.length() - 1);
    while (file1.good() && !file1.eof()) {
        file1 >> s;
        if (s == stored) {
            exists = true;
            break;
        }
    }
    file1.close();
    if (exists == false && reguser == true && regpass == true) {
        string filename("resources/users/userpass.txt");
        ofstream file_out;
        file_out.open(filename, ios_base::app);
        file_out << stored << endl;
        file_out.close();
    }
}
image * map1g;
int main(int argc, char * argv[]) {
    //Initialization of SDL windows
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO;
    Uint32 WND_flags = SDL_WINDOW_SHOWN; //SDL_WINDOW_BORDERLESS ;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
   Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music * music_1 = NULL;
    music_1 = Mix_LoadMUS("resources/music/forest.mp3");
    music_2 = Mix_LoadMUS("resources/music/music_2.mp3");
    music_3 = Mix_LoadMUS("resources/music/music_3.mp3");
    music_4 = Mix_LoadMUS("resources/music/music_4.mp3");
    music_5 = Mix_LoadMUS("resources/music/music_5.mp3");
    Mix_Chunk * click_sound = Mix_LoadWAV("resources/music/click.wav");
    Mix_PlayMusic(music_1, -1);
    //Texture for loading image
    int mouse_x, mouse_y; // mouse location to detect if hovering has occured
    int img_w, img_h;
    string modfirstpage;
    SDL_Rect img_rect;
    SDL_Init(SDL_flags);
    SDL_CreateWindowAndRenderer(1280, 800, WND_flags, & m_window, & m_renderer);
    //Pass the focus to the drawing window
    SDL_RaiseWindow(m_window);
    //Get screen resolution
    loginbg = new image("resources/pics/loginpageback.jpg", 0, 0, 1280, 800, m_renderer);
    loginform = new image("resources/pics/loginform.png", 450, 200, 429, 400, m_renderer);
    backbutt = new image("resources/pics/backbutt.png", 100, 650, 56, 56, m_renderer);
    log_butt = new image("resources/pics/quitfpb.png", 705, 450, 150, 56, m_renderer);
    registerbg = new image("resources/pics/registerpageback.png", 0, 0, 1280, 800, m_renderer);
    registerform = new image("resources/pics/registerform.png", 450, 200, 429, 400, m_renderer);
    reg_butt = new image("resources/pics/quitfpb.png", 705, 450, 150, 56, m_renderer);
    mapmenubg = new image("resources/pics/startbuttonsbg.png", 500, 100, 366, 497, m_renderer);
    sm_xb = new image("resources/pics/startmenubuttonbg.png", 550, 150, 280, 73, m_renderer);
    sm_mb = new image("resources/pics/startmenubuttonbg.png", 550, 240, 280, 73, m_renderer);
    sm_quitb = new image("resources/pics/startmenubuttonbg.png", 550, 335, 280, 73, m_renderer);
    sm_rb = new image("resources/pics/startmenubuttonbg.png", 550, 435, 280, 73, m_renderer);
    mapmenu_closeb1 = new image("resources/close1_button.png", 900, 70, 50, 50, m_renderer);
    mapmenu_closeb2 = new image("resources/close2_button.png", 900, 70, 50, 50, m_renderer);
    map2bg = new image("resources/map2.png", 0, 0, 1280, 800, m_renderer);
    third_mapbg = new image("resources/map.png", 0, 0, 1280, 800, m_renderer);
    map1g = new image("resources/map.png", 0, 0, 1280, 800, m_renderer);
    startbuttonsbg = new image("resources/pics/startbuttonsbg.png", 500, 100, 366, 497, m_renderer);
    //pm_gbb= new image("resources/pics/startmenubuttonbg.png",550,150,280,73,m_renderer);
    pm_conb = new image("resources/pics/startmenubuttonbg.png", 550, 150, 280, 73, m_renderer);
    pm_eb = new image("resources/pics/startmenubuttonbg.png", 550, 465, 280, 73, m_renderer);
    pm_sb = new image("resources/pics/startmenubuttonbg.png", 550, 230, 280, 73, m_renderer);
    pm_mb = new image("resources/pics/startmenubuttonbg.png", 550, 315, 280, 73, m_renderer);
    pre_butt = new image("resources/prebutt.png", 540, 400, 56, 56, m_renderer);
    next_butt = new image("resources/nextbutt.png", 784, 397, 56, 56, m_renderer);
    change_music = new image("resources/pics/registerbhobg.png", 550, 403, 214, 45, m_renderer);
    pausemenu_closb = new image("resources/pics/closeb.png", 900, 70, 45, 45, m_renderer);
    image_startmenu = new image("resources/start_menu.jpeg", 0, 0, 1280, 800, m_renderer);
    play1_button = new image("resources/play1_button.jpg", 590, 540, 200, 60, m_renderer);
    play2_button = new image("resources/play2_button.jpg", 590, 540, 200, 60, m_renderer);
    map1_button = new image("resources/mode1_button.jpg", 590, 610, 200, 60, m_renderer);
    exit1_button = new image("resources/exit1_button.jpg", 590, 680, 200, 60, m_renderer);
    setting1_button = new image("resources/setting1_button.png", 1190, 710, 90, 90, m_renderer);
    leaderboard1_button = new image("resources/leaderboard_button.jpg", 0, 710, 90, 90, m_renderer);
    exit2_button = new image("resources/exit2_button.jpg", 590, 680, 200, 60, m_renderer);
    map2_button = new image("resources/mode2_button.jpg", 590, 610, 200, 60, m_renderer);
    setting2_button = new image("resources/setting2_button.jpg", 1190, 710, 90, 90, m_renderer);
    leaderboard2_button = new image("resources/leaderboard2_button.png", 0, 710, 90, 90, m_renderer);
    music2_button = new image("resources/music2_button.png", 1098, 710, 90, 90, m_renderer);
    music1_button = new image("resources/music1_button.jpg", 1098, 710, 90, 90, m_renderer);
    music3_button = new image("resources/music3_button.png", 1098, 710, 90, 90, m_renderer);
    music4_button = new image("resources/music4_button.png", 1098, 710, 90, 90, m_renderer);
    sound2_button = new image("resources/sound2_button.png", 1190, 618, 90, 90, m_renderer);
    sound1_button = new image("resources/sound1_button.jpg", 1190, 618, 90, 90, m_renderer);
    sound3_button = new image("resources/sound3_button.png", 1190, 618, 90, 90, m_renderer);
    sound4_button = new image("resources/sound4_button.png", 1190, 618, 90, 90, m_renderer);
    help2_button = new image("resources/help2_button.png", 1098, 618, 90, 90, m_renderer);
    help1_button = new image("resources/help1_button.png", 1098, 618, 90, 90, m_renderer);
    close2_button = new image("resources/close2_button.png", 623, 560, 40, 40, m_renderer);
    close1_button = new image("resources/close1_button.png", 623, 560, 40, 40, m_renderer);
    help_table = new image("resources/help_table.png", 390, 200, 500, 400, m_renderer);
    start_hole1 = new image("resources/start_hole1.png", -3, 539, 80, 80, m_renderer);
    end_hole1 = new image("resources/end_hole.png", 1074, 629, 80, 80, m_renderer);
    start_hole2 = new image("resources/start_hole2.png", 250, 52, 80, 80, m_renderer);
    end_hole2 = new image("resources/end_hole.png", 65, 612, 80, 80, m_renderer);
    start_hole3 = new image("resources/start_hole1.png", -45, 190, 80, 80, m_renderer);
    end_hole3 = new image("resources/end_hole.png", 750, 738, 80, 80, m_renderer);
    time1_mode = new image("resources/time1_mode.png", 715, 240, 150, 110, m_renderer);
    time2_mode = new image("resources/time2_mode.png", 715, 240, 150, 110, m_renderer);
    rock1_mode = new image("resources/rock1_mode.png", 485, 410, 150, 110, m_renderer);
    rock2_mode = new image("resources/rock2_mode.png", 485, 410, 150, 110, m_renderer);
    bird1_mode = new image("resources/bird1_mode.png", 715, 410, 150, 110, m_renderer);
    bird2_mode = new image("resources/bird2_mode.png", 715, 410, 150, 110, m_renderer);
    clear1_mode = new image("resources/clear1_mode.png", 485, 240, 150, 110, m_renderer);
    clear2_mode = new image("resources/clear2_mode.png", 485, 240, 150, 110, m_renderer);
    mode_table = new image("resources/mode_table.png", 380, 130, 600, 500, m_renderer);
    close1_modetable = new image("resources/close1_button.png", 665, 557, 40, 40, m_renderer);
    close2_modetable = new image("resources/close2_button.png", 665, 557, 40, 40, m_renderer);
    yellow_ball = new Image("resources/Yeloow.png",m_renderer);
    blue_ball = new Image("resources/Blue.png",m_renderer);
    red_ball = new Image("resources/Red.png",m_renderer);
    green_ball = new Image("resources/Green.png",m_renderer);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, & DM);
    int W = DM.w;
    int H = DM.h;
    //first page
    first_page(m_renderer, modfirstpage, mouse_x, mouse_y);
    //first page
}
// better function to render ttf text
void betterText(SDL_Renderer * renderer, string S, int x, int y, int r, int g, int b, int a, int size, string Font /*def = arial */ ) {
    if (!TTF_WasInit())
        TTF_Init();
    string fontDir = "resources/fonts/" + Font + ".ttf"; // should have fonts as .ttf files in ./fonts folder from project path
    TTF_Font * font = TTF_OpenFont(fontDir.c_str(), size);
    SDL_Color color = {
        r,
        g,
        b,
        a
    };
    SDL_Surface * surface = TTF_RenderText_Solid(font, S.c_str(), color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect;
    int h, w;
    SDL_QueryTexture(texture, NULL, NULL, & w, & h);
    rect.h = h;
    rect.w = w;
    rect.x = x - w / 2;
    rect.y = y - h / 2;
    SDL_RenderCopy(renderer, texture, NULL, & rect);
    // free resources
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
void mapmenu(SDL_Renderer * renderer) {

    //    mapmenu_closb->render(renderer,900,70,45,45);
    mapmenubg -> render();
    sm_xb -> render();
    sm_mb -> render();
    sm_quitb -> render();
    sm_rb -> render();
    mapmenu_closeb1 -> render();
    betterText(renderer, "khoone ame", 700, 185, 0, 255, 255, 255, 25, "chrustyrock");
    betterText(renderer, "khoone baba", 700, 275, 0, 255, 255, 255, 25, "chrustyrock");
    betterText(renderer, "khone khale", 700, 370, 0, 255, 255, 255, 25, "chrustyrock");
    betterText(renderer, "khoone random", 700, 470, 0, 255, 255, 255, 25, "chrustyrock");
    SDL_RenderPresent(renderer);
    SDL_Event * e7 = new SDL_Event();
    int x4, y4;
    bool map_bool = 1;
    while (map_bool) {
        SDL_GetMouseState( & x4, & y4);
        SDL_PollEvent(e7);
        if (e7 -> type == SDL_QUIT) {
            quit(renderer);
        }
        if (x4 > 900 && x4 < 945 && y4 > 70 && y4 < 115) {
            if (e7 -> type == SDL_MOUSEBUTTONDOWN) {
                SDL_RenderClear(renderer);

                startmenu(renderer);
                break;
            } else {
                mapmenu_closeb2 -> render();
            }

        } else {
            mapmenu_closeb1 -> render();
        }
        if (x4 > 550 && x4 < 830 && y4 > 150 && y4 < 223) {
            if (e7 -> type == SDL_MOUSEBUTTONDOWN) {

                first_map(renderer);
                map_bool = 0;

                break;
            } else {
                betterText(renderer, "khoone ame", 700, 185, 255, 0, 0, 255, 25, "chrustyrock");
                SDL_RenderPresent(renderer);
            }
        } else {
            betterText(renderer, "khoone ame", 700, 185, 0, 255, 255, 255, 25, "chrustyrock");
            SDL_RenderPresent(renderer);
        }
        //        if( x4 > 550 && x4 < 830 && y4 > 150 && y4 < 223 && e7->type == SDL_MOUSEMOTION ){
        //          map_1->render(renderer,550,150,280,73);
        ////          SDL_RenderPresent(renderer);
        //
        //        }
        if (x4 > 550 && x4 < 830 && y4 > 235 && y4 < 308) {
            if (e7 -> type == SDL_MOUSEBUTTONDOWN) {
                second_map(renderer);
                break;
            } else {
                betterText(renderer, "khoone baba", 700, 275, 255, 0, 0, 255, 25, "chrustyrock");
                SDL_RenderPresent(renderer);
            }
        } else {
            betterText(renderer, "khoone baba", 700, 275, 0, 255, 255, 255, 25, "chrustyrock");
            SDL_RenderPresent(renderer);
        }
        if (x4 > 550 && x4 < 830 && y4 > 335 && y4 < 408) {
            if (e7 -> type == SDL_MOUSEBUTTONDOWN) {
                third_map(renderer);
                break;
            } else {
                betterText(renderer, "khone khale", 700, 370, 255, 0, 0, 255, 25, "chrustyrock");
                SDL_RenderPresent(renderer);
            }
        } else {
            betterText(renderer, "khone khale", 700, 370, 0, 255, 255, 255, 25, "chrustyrock");
            SDL_RenderPresent(renderer);
        }
        if (x4 > 550 && x4 < 830 && y4 > 435 && y4 < 512) {
            if (e7 -> type == SDL_MOUSEBUTTONDOWN) {
                map_random(renderer);
                break;
            } else {
                betterText(renderer, "khoone random", 700, 470, 255, 0, 0, 255, 25, "chrustyrock");
                SDL_RenderPresent(renderer);
            }
        } else {
            betterText(renderer, "khoone random", 700, 470, 0, 255, 255, 255, 25, "chrustyrock");
            SDL_RenderPresent(renderer);
        }

        SDL_RenderPresent(renderer);

    }

}
void modemenu(SDL_Renderer * renderer) {
    Mix_Chunk * click_sound = Mix_LoadWAV("resources/music/click.wav");
    //    mapmenu_closb->render(renderer,900,70,45,45);
    mode_table -> render();
    close1_modetable -> render();
    bird1_mode -> render();
    clear1_mode -> render();
    rock1_mode -> render();
    time1_mode -> render();
    SDL_RenderPresent(renderer);
    SDL_Event * e14 = new SDL_Event();
    int x14, y14;
    bool mode_bool = 1;
    while (mode_bool) {
        SDL_GetMouseState( & x14, & y14);
        SDL_PollEvent(e14);
        if (e14 -> type == SDL_QUIT) {
            quit(renderer);
        }
        if (x14 > 665 && x14 < 705 && y14 > 557 && y14 < 597) {
            if (e14 -> type == SDL_MOUSEBUTTONDOWN) {
                SDL_RenderClear(renderer);
                mode_bool = 0;
                startmenu(renderer);
                break;
            } else {
                close2_modetable -> render();
            }

        } else {
            close1_modetable -> render();
        }
        if (x14 > 489 && x14 < 635 && y14 > 244 && y14 < 349) {
            if (e14 -> type == SDL_MOUSEBUTTONDOWN) {
                SDL_RenderClear(renderer);
                mode_game = 1;
                is_mode = 1;
                if (!is_sound) {
                    Mix_PlayChannel(-1, click_sound, 0);
                }
                startmenu(renderer);
                break;
            } else {
                clear2_mode -> render();

            }
        } else {
            clear1_mode -> render();
        }
        //        if( x4 > 550 && x4 < 830 && y4 > 150 && y4 < 223 && e7->type == SDL_MOUSEMOTION ){
        //          map_1->render(renderer,550,150,280,73);
        ////          SDL_RenderPresent(renderer);
        //
        //        }
        if (x14 > 719 && x14 < 861 && y14 > 415 && y14 < 520) {
            if (e14 -> type == SDL_MOUSEBUTTONDOWN) {
                SDL_RenderClear(renderer);
                mode_game = 4;
                is_mode = 1;
                if (!is_sound) {
                   Mix_PlayChannel(-1, click_sound, 0);
                }
                startmenu(renderer);
                break;
            } else {
                bird2_mode -> render();

            }
        } else {
            bird1_mode -> render();
        }
        if (x14 > 719 && x14 < 861 && y14 > 244 && y14 < 349) {
            if (e14 -> type == SDL_MOUSEBUTTONDOWN) {
                SDL_RenderClear(renderer);
                mode_game = 2;
                is_mode = 1;
                if (!is_sound) {
                    Mix_PlayChannel(-1, click_sound, 0);
                }
                startmenu(renderer);
                break;
            } else {
                time2_mode -> render();

            }
        } else {
            time1_mode -> render();
        }
        if (x14 > 492 && x14 < 632 && y14 > 415 && y14 < 520) {
            if (e14 -> type == SDL_MOUSEBUTTONDOWN) {
                SDL_RenderClear(renderer);
                mode_game = 3;
                is_mode = 1;
                if (!is_sound) {
                    Mix_PlayChannel(-1, click_sound, 0);
                }
                startmenu(renderer);
                break;
            } else {
                rock2_mode -> render();

            }
        } else {
            rock1_mode -> render();
        }
        SDL_RenderPresent(renderer);
    }

}
void third_map(SDL_Renderer * renderer) {
    if (first_thirdmap) {
        if (!is_music) {
            if (musicchanged) {

                if (music_number % 3 == 0) {
                    Mix_PlayMusic(music_5, -1);
                } else if (music_number % 3 == 1) {
                   Mix_PlayMusic(music_3, -1);
                } else {
                    Mix_PlayMusic(music_4, -1);
                }

            } else {
               Mix_PlayMusic(music_5, -1);
            }

            first_thirdmap = 0;
        }

    } else {
        if (musicchanged) {
            if (is_music) {
               Mix_PauseMusic();
            } else {
                if (music_number % 3 == 0) {
                    Mix_PlayMusic(music_5, -1);
                } else if (music_number % 3 == 1) {
                    Mix_PlayMusic(music_3, -1);
                } else {
                    Mix_PlayMusic(music_4, -1);
                }

            }
        } else {
            if (is_music) {
               Mix_PauseMusic();
            } else {

                Mix_ResumeMusic();

            }
        }

    }
    int h = 1280, w = 800;
    int mod;
    int third_x[10] = {20,450,600,730,800,1090,1100,110,890,790}, third_y[10] = {220,100,150,45,50,300,400,520,700,750};
    int color = rand()%4;
    if(color == 0){
        yellow_ball->render(renderer,345,485,35,35);
    }
    if(color == 1){
        green_ball->render(renderer,345,485,35,35);
    }
    if(color == 2){
        red_ball->render(renderer,345,485,35,35);
    }
    if(color == 3){
        blue_ball->render(renderer,345,485,35,35);
    }
    int points_x[10100],points_y[10100];
    int point_counter=0;
    int ball_color;
    int count_sb=0;
    double xu = 0,yu=0;
    for(double u = 0;u <=1.0;u+=0.0001){
        xu = pow(1 - u, 9) * third_x[0] + 9 * u * pow(1 - u, 8) * third_x[1] + 36 * pow(u, 2) * pow(1 - u, 7) * third_x[2] + 84 * pow(u, 3) * pow(1 - u, 6) * third_x[3] +
            126 * pow(u, 4) * pow(1 - u, 5) * third_x[4] + 126 * pow(u, 5) * pow(1 - u, 4) * third_x[5] +
            84 * pow(u, 6) * pow(1 - u, 3) * third_x[6] + 36 * pow(u, 7) * pow(1 - u, 2) * third_x[7] + 9 * pow(u, 8) * (1 - u) * third_x[8] + pow(u, 9) * third_x[9];
        yu = pow(1 - u, 9) * third_y[0] + 9 * u * pow(1 - u, 8) * third_y[1] + 36 * pow(u, 2) * pow(1 - u, 7) * third_y[2] + 84 * pow(u, 3) * pow(1 - u, 6) * third_y[3] +
            126 * pow(u, 4) * pow(1 - u, 5) * third_y[4] + 126 * pow(u, 5) * pow(1 - u, 4) * third_y[5] +
            84 * pow(u, 6) * pow(1 - u, 3) * third_y[6] + 36 * pow(u, 7) * pow(1 - u, 2) * third_y[7] + 9 * pow(u, 8) * (1 - u) * third_y[8] + pow(u, 9) * third_y[9];
        points_x[point_counter] = xu;
        points_y[point_counter] = yu;
        point_counter++;
    }
    SDL_Event * e8 = new SDL_Event();
    bool added = false;
    vector<ball> balls(1000);
    vector<ball> shooted_balls(10000);
    int shootcounter=0;
    int ball_counter = 0;
    int same_color = 0;
    for(int j=0;j<100;j++){
        balls[j].x = points_x[0];
        balls[j].y = points_y[0];
        balls[j].counter = 0;
    }
    bool endgame = true;
    while (true) {
        SDL_PollEvent(e8);
        SDL_RenderClear(renderer);
        if (e8 -> type == SDL_QUIT) {
            quit(renderer);
        }
        if (e8 -> type == SDL_KEYDOWN && e8 -> key.keysym.sym == SDLK_ESCAPE) {
            mod = 3;
            //         Mix_PauseMusic();
            pausemenu(renderer, mod);
            break;
        }
        int x8, y8;
        if (e8 -> type == SDL_MOUSEMOTION) {
            SDL_GetMouseState( & x8, & y8);
            angle = atan2((y8 - (485)), (x8 - (345)));
            //            cout << angle << endl;
        }
        if (e8 -> type == SDL_KEYDOWN && e8 -> key.keysym.sym == SDLK_SPACE){
            color = rand()%4;
        }
        third_mapbg -> render();
        start_hole3 -> render();
        end_hole3 -> render();
        bezierCurve(third_x, third_y, renderer);
        // aalineRGBA(renderer,350,450,x8,y8,255,0,0,255);
        angledImage(renderer, "resources/pics/cannon.png", 220, 360, 250, 250, (angle * 180) / M_PI - 90);
        for(int i=0;i<=ball_counter && endgame;i++){
            if(balls[i].given_color == false){
                ball_color = rand()%4;
                balls[i].color = ball_color;
                balls[i].given_color = true;
            }
            double frombehind = sqrt((balls[i].x - balls[i+1].x)*(balls[i].x - balls[i+1].x) + (balls[i].y - balls[i+1].y)*(balls[i].y - balls[i+1].y));
            while( frombehind <= 42 ){
                balls[i].x = points_x[balls[i].counter++];
                balls[i].y = points_y[balls[i].counter++];
                frombehind = sqrt((balls[i].x - balls[i+1].x)*(balls[i].x - balls[i+1].x) + (balls[i].y - balls[i+1].y)*(balls[i].y - balls[i+1].y));
            }
            balls[i].x = points_x[balls[i].counter++];
            balls[i].y = points_y[balls[i].counter++];
            if(balls[i].color == 0){
                yellow_ball->render(renderer,balls[i].x,balls[i].y,35,35);
            }
            if(balls[i].color == 1){
                green_ball->render(renderer,balls[i].x,balls[i].y,35,35);
            }
            if(balls[i].color == 2){
                red_ball->render(renderer,balls[i].x,balls[i].y,35,35);
            }
            if(balls[i].color == 3){
                blue_ball->render(renderer,balls[i].x,balls[i].y,35,35);
            }
            if (e8 -> type == SDL_KEYDOWN && e8 -> key.keysym.sym == SDLK_SPACE){
                color = rand()%4;
            }
            if(sqrt((balls[ball_counter].x - points_x[0])* (balls[ball_counter].x - points_x[0]) + (balls[ball_counter].y - points_y[0]) * (balls[ball_counter].y - points_y[0])) > 72){
                if(ball_counter<30) ball_counter++;
                else continue;
            }
        }
        if(sqrt((balls[0].x - points_x[point_counter-1])* (balls[0].x - points_x[point_counter-1]) +
                (balls[0].y - points_y[point_counter-1]) * (balls[0].y - points_y[point_counter-1]))< 40){
                    balls.erase(balls.begin());
                    ball_counter--;
                    //endgame = false;
        }
        if(color == 0){
            yellow_ball->render(renderer,315,485,35,35);

        }
        if(color == 1){
            green_ball->render(renderer,315,485,35,35);
        }
        if(color == 2){
            red_ball->render(renderer,315,485,35,35);
        }
        if(color == 3){
            blue_ball->render(renderer,315,485,35,35);
        }
        if(e8->type == SDL_MOUSEBUTTONDOWN){
            SDL_GetMouseState( & x8, & y8);
            zdfgh = atan2((y8 - (485)), (x8 - (345)));
            shooted_balls[shootcounter].x = 345;
            shooted_balls[shootcounter].y = 485;
            shooted_balls[shootcounter].dx = 8*cos(zdfgh);
            shooted_balls[shootcounter].dy = 8*sin(zdfgh);
            shooted_balls[shootcounter].color = color;
            shooted_balls[shootcounter].shoot = true;
        }
        if(shooted_balls[shootcounter].color == 0&& shooted_balls[shootcounter].shoot == true)
            {
            yellow_ball->render(renderer,shooted_balls[shootcounter].x,shooted_balls[shootcounter].y,35,35);
            shooted_balls[shootcounter].x+=shooted_balls[shootcounter].dx;
            shooted_balls[shootcounter].y+=shooted_balls[shootcounter].dy;
        }
        if(shooted_balls[shootcounter].color == 1&& shooted_balls[shootcounter].shoot == true){
            green_ball->render(renderer,shooted_balls[shootcounter].x,shooted_balls[shootcounter].y,35,35);
            shooted_balls[shootcounter].x+=shooted_balls[shootcounter].dx;
            shooted_balls[shootcounter].y+=shooted_balls[shootcounter].dy;
        }
        if(shooted_balls[shootcounter].color == 2&& shooted_balls[shootcounter].shoot == true){
            red_ball->render(renderer,shooted_balls[shootcounter].x,shooted_balls[shootcounter].y,35,35);
            shooted_balls[shootcounter].x+=shooted_balls[shootcounter].dx;
            shooted_balls[shootcounter].y+=shooted_balls[shootcounter].dy;
        }
        shooted_balls[shootcounter].given_color =true;
        if(shooted_balls[shootcounter].color == 3 && shooted_balls[shootcounter].shoot == true){
            blue_ball->render(renderer,shooted_balls[shootcounter].x,shooted_balls[shootcounter].y,35,35);
            shooted_balls[shootcounter].x+=shooted_balls[shootcounter].dx;
            shooted_balls[shootcounter].y+=shooted_balls[shootcounter].dy;
        }
        for(int i = 0;i<=ball_counter;i++){
            same_color =0;
            if(sqrt((shooted_balls[shootcounter].x - balls[i].x)* (shooted_balls[shootcounter].x - balls[i].x) +
                    (shooted_balls[shootcounter].y - balls[i].y) * (shooted_balls[shootcounter].y - balls[i].y)) < 15 && shooted_balls[shootcounter].shoot == true
               &&shooted_balls[shootcounter].color == balls[i].color ){
                for(int j=i;j<=ball_counter;j++){
                    if(balls[j].color == balls[j+1].color){
                        same_color++;
                    }
                    else {
                        break;
                    }
                }
                for(int j=i;j>=0;j--){
                    if(balls[j].color == balls[j+1].color){
                        same_color++;
                    }
                    else {
                        break;
                    }
                }
                if(same_color >=2){
                    shooted_balls[shootcounter].shoot = false;
                    shooted_balls[shootcounter].counter = balls[i].counter;
                    balls.erase(balls.begin()+i,balls.begin()+i+same_color);
                    ball_counter-=same_color;
                    cout << "HIT " << i  << endl;
                    cout << ball_counter << endl;
                }
                else{
                    shooted_balls[shootcounter].shoot = false;
                    shooted_balls[shootcounter].counter = balls[i].counter;
                    balls.insert(balls.begin()+i,shooted_balls[shootcounter]);
                    cout << "HIT " << i  << endl;
                    ball_counter++;
                    cout << ball_counter << endl;
                    break;
                }
            }
            else if(sqrt((shooted_balls[shootcounter].x - balls[i].x)* (shooted_balls[shootcounter].x - balls[i].x) +
                    (shooted_balls[shootcounter].y - balls[i].y) * (shooted_balls[shootcounter].y - balls[i].y)) < 15 && shooted_balls[shootcounter].shoot == true
               &&shooted_balls[shootcounter].color != balls[i].color ){
                    shooted_balls[shootcounter].shoot = false;
                    shooted_balls[shootcounter].counter = balls[i].counter;
                    balls.insert(balls.begin()+i,shooted_balls[shootcounter]);
                    cout << "HIT " << i  << endl;
                    ball_counter++;
                    cout << ball_counter << endl;
                    break;
                }
        }
        SDL_RenderPresent(renderer);
    }
}
void second_map(SDL_Renderer * renderer) {
    if (first_secondmap) {
        if (!is_music) {
            if (musicchanged) {

                if (music_number % 3 == 0) {
                    Mix_PlayMusic(music_5, -1);
                } else if (music_number % 3 == 1) {
                    Mix_PlayMusic(music_3, -1);
                } else {
                    Mix_PlayMusic(music_4, -1);
                }
            } else {
               Mix_PlayMusic(music_5, -1);
            }

            first_secondmap = 0;
        }

    } else {
        if (musicchanged) {
            if (is_music) {
               Mix_PauseMusic();
            } else {
                if (music_number % 3 == 0) {
                    Mix_PlayMusic(music_5, -1);
                } else if (music_number % 3 == 1) {
                   Mix_PlayMusic(music_3, -1);
                } else {
                   Mix_PlayMusic(music_4, -1);
                }

            }
        } else {
            if (is_music) {
                Mix_PauseMusic();
            } else {

               Mix_ResumeMusic();

            }
        }

    }
    int h = 1280, w = 800;
    int mod;
    int second_x[10] = {300,550,660,60,1070,1090,1100,1090,1090,110}, second_y[10] = {120,70,50,450,50,100,40,120,643,650};
    //angledImage(renderer,"resources/pics/frog.png",w/2-100,h/2-50,200,200,-(angle*180)/M_PI+90);
    //bezierCurve(second_x ,second_y,renderer);
    int points_x[10100],points_y[10100];
    int point_counter=0;
    int ball_color;
    double xu = 0,yu=0;
    for(double u = 0;u <=1.0;u+=0.0001){
        xu = pow(1 - u, 9) * second_x[0] + 9 * u * pow(1 - u, 8) * second_x[1] + 36 * pow(u, 2) * pow(1 - u, 7) * second_x[2] + 84 * pow(u, 3) * pow(1 - u, 6) * second_x[3] +
            126 * pow(u, 4) * pow(1 - u, 5) * second_x[4] + 126 * pow(u, 5) * pow(1 - u, 4) * second_x[5] +
            84 * pow(u, 6) * pow(1 - u, 3) * second_x[6] + 36 * pow(u, 7) * pow(1 - u, 2) * second_x[7] + 9 * pow(u, 8) * (1 - u) * second_x[8] + pow(u, 9) * second_x[9];
        yu = pow(1 - u, 9) * second_y[0] + 9 * u * pow(1 - u, 8) * second_y[1] + 36 * pow(u, 2) * pow(1 - u, 7) * second_y[2] + 84 * pow(u, 3) * pow(1 - u, 6) * second_y[3] +
            126 * pow(u, 4) * pow(1 - u, 5) * second_y[4] + 126 * pow(u, 5) * pow(1 - u, 4) * second_y[5] +
            84 * pow(u, 6) * pow(1 - u, 3) * second_y[6] + 36 * pow(u, 7) * pow(1 - u, 2) * second_y[7] + 9 * pow(u, 8) * (1 - u) * second_y[8] + pow(u, 9) * second_y[9];
        points_x[point_counter] = xu;
        points_y[point_counter] = yu;
        point_counter++;
    }
    SDL_Event * e9 = new SDL_Event();
    int color = rand()%4;
    if(color == 0){
        yellow_ball->render(renderer,415,485,35,35);
    }
    if(color == 1){
        green_ball->render(renderer,415,485,35,35);
    }
    if(color == 2){
        red_ball->render(renderer,415,485,35,35);
    }
    if(color == 3){
        blue_ball->render(renderer,415,485,35,35);
    }
    bool added = false;
    vector<ball> balls(1000);
    vector<ball> shooted_balls(10000);
    int shootcounter=0;
    int ball_counter = 0;
    for(int j=0;j<100;j++){
        balls[j].x = points_x[0];
        balls[j].y = points_y[0];
        balls[j].counter = 0;
    }
    bool endgame = true;
    int same_color = 0;
    while (true) {
        SDL_PollEvent(e9);
        SDL_RenderClear(renderer);
        if (e9 -> type == SDL_QUIT){
            quit(renderer);
        }
        if (e9 -> type == SDL_KEYDOWN && e9 -> key.keysym.sym == SDLK_ESCAPE) {
            mod = 2;
            //          Mix_PauseMusic();
            pausemenu(renderer, mod);
            break;
        }
        int x9, y9;
        if (e9 -> type == SDL_MOUSEMOTION) {
            SDL_GetMouseState( & x9, & y9);
            angle = atan2((y9 - (485)), (x9 - (415)));
            //            cout << angle << endl;
        }
        map2bg -> render();
        end_hole2 -> render();
        start_hole2 -> render();
        bezierCurve(second_x, second_y, renderer);
        //lineRGBA(renderer,750,450,x9,y9,255,0,0,255);
        angledImage(renderer, "resources/pics/cannon.png", 290, 370, 250, 250, (angle * 180) / M_PI - 90);
        for(int i=0;i<=ball_counter && endgame;i++){
            if(balls[i].given_color == false){
                ball_color = rand()%4;
                balls[i].color = ball_color;
                balls[i].given_color = true;
            }
            double frombehind = sqrt((balls[i].x - balls[i+1].x)*(balls[i].x - balls[i+1].x) + (balls[i].y - balls[i+1].y)*(balls[i].y - balls[i+1].y));
            while( frombehind <= 42 ){
                balls[i].x = points_x[balls[i].counter++];
                balls[i].y = points_y[balls[i].counter++];
                frombehind = sqrt((balls[i].x - balls[i+1].x)*(balls[i].x - balls[i+1].x) + (balls[i].y - balls[i+1].y)*(balls[i].y - balls[i+1].y));
            }
            balls[i].x = points_x[balls[i].counter++];
            balls[i].y = points_y[balls[i].counter++];
            if(balls[i].color == 0){
                yellow_ball->render(renderer,balls[i].x,balls[i].y,35,35);
            }
            if(balls[i].color == 1){
                green_ball->render(renderer,balls[i].x,balls[i].y,35,35);
            }
            if(balls[i].color == 2){
                red_ball->render(renderer,balls[i].x,balls[i].y,35,35);
            }
            if(balls[i].color == 3){
                blue_ball->render(renderer,balls[i].x,balls[i].y,35,35);
            }
            if (e9 -> type == SDL_KEYDOWN && e9 -> key.keysym.sym == SDLK_SPACE){
                color = rand()%4;
            }
            if(sqrt((balls[ball_counter].x - points_x[0])* (balls[ball_counter].x - points_x[0]) + (balls[ball_counter].y - points_y[0]) * (balls[ball_counter].y - points_y[0])) > 72){
                if(ball_counter<30) ball_counter++;
                else continue;
            }
        }
        if(sqrt((balls[0].x - points_x[point_counter-1])* (balls[0].x - points_x[point_counter-1]) +
                (balls[0].y - points_y[point_counter-1]) * (balls[0].y - points_y[point_counter-1]))< 40){
                    balls.erase(balls.begin());
                    ball_counter--;
                    //endgame = false;
        }
        if (e9 -> type == SDL_KEYDOWN && e9 -> key.keysym.sym == SDLK_SPACE){
            color = rand()%4;
        }
        if(color == 0){
            yellow_ball->render(renderer,415,485,35,35);
        }
        if(color == 1){
            green_ball->render(renderer,415,485,35,35);
        }
        if(color == 2){
            red_ball->render(renderer,415,485,35,35);
        }
        if(color == 3){
            blue_ball->render(renderer,415,485,35,35);
        }
        if(e9->type == SDL_MOUSEBUTTONDOWN){
            SDL_GetMouseState( & x9, & y9);
            zdfgh = atan2((y9 - (485)),(x9 - (415)));
            shooted_balls[shootcounter].x = 415;
            shooted_balls[shootcounter].y = 485;
            shooted_balls[shootcounter].dx = 8*cos(zdfgh);
            shooted_balls[shootcounter].dy = 8*sin(zdfgh);
            shooted_balls[shootcounter].color = color;
            shooted_balls[shootcounter].shoot = true;
        }
        if(shooted_balls[shootcounter].color == 0&& shooted_balls[shootcounter].shoot == true)
            {
            yellow_ball->render(renderer,shooted_balls[shootcounter].x,shooted_balls[shootcounter].y,35,35);
            shooted_balls[shootcounter].x+=shooted_balls[shootcounter].dx;
            shooted_balls[shootcounter].y+=shooted_balls[shootcounter].dy;
        }
        if(shooted_balls[shootcounter].color == 1&& shooted_balls[shootcounter].shoot == true){
            green_ball->render(renderer,shooted_balls[shootcounter].x,shooted_balls[shootcounter].y,35,35);
            shooted_balls[shootcounter].x+=shooted_balls[shootcounter].dx;
            shooted_balls[shootcounter].y+=shooted_balls[shootcounter].dy;
        }
        if(shooted_balls[shootcounter].color == 2&& shooted_balls[shootcounter].shoot == true){
            red_ball->render(renderer,shooted_balls[shootcounter].x,shooted_balls[shootcounter].y,35,35);
            shooted_balls[shootcounter].x+=shooted_balls[shootcounter].dx;
            shooted_balls[shootcounter].y+=shooted_balls[shootcounter].dy;
        }
        shooted_balls[shootcounter].given_color =true;
        if(shooted_balls[shootcounter].color == 3 && shooted_balls[shootcounter].shoot == true){
            blue_ball->render(renderer,shooted_balls[shootcounter].x,shooted_balls[shootcounter].y,35,35);
            shooted_balls[shootcounter].x+=shooted_balls[shootcounter].dx;
            shooted_balls[shootcounter].y+=shooted_balls[shootcounter].dy;
        }
        for(int i = 0;i<=ball_counter;i++){
            same_color =0;
            if(sqrt((shooted_balls[shootcounter].x - balls[i].x)* (shooted_balls[shootcounter].x - balls[i].x) +
                    (shooted_balls[shootcounter].y - balls[i].y) * (shooted_balls[shootcounter].y - balls[i].y)) < 15 && shooted_balls[shootcounter].shoot == true
               &&shooted_balls[shootcounter].color == balls[i].color ){
                for(int j=i;j<=ball_counter;j++){
                    if(balls[j].color == balls[j+1].color){
                        same_color++;
                    }
                    else {
                        break;
                    }
                }
                for(int j=i;j>=0;j--){
                    if(balls[j].color == balls[j+1].color){
                        same_color++;
                    }
                    else {
                        break;
                    }
                }
                if(same_color >=2){
                    shooted_balls[shootcounter].shoot = false;
                    shooted_balls[shootcounter].counter = balls[i].counter;
                    balls.erase(balls.begin()+i,balls.begin()+i+same_color);
                    ball_counter-=same_color;
                    cout << "HIT " << i  << endl;
                    cout << ball_counter << endl;
                }
                else{
                    shooted_balls[shootcounter].shoot = false;
                    shooted_balls[shootcounter].counter = balls[i].counter;
                    balls.insert(balls.begin()+i,shooted_balls[shootcounter]);
                    cout << "HIT " << i  << endl;
                    ball_counter++;
                    cout << ball_counter << endl;
                    break;
                }
            }
            else if(sqrt((shooted_balls[shootcounter].x - balls[i].x)* (shooted_balls[shootcounter].x - balls[i].x) +
                    (shooted_balls[shootcounter].y - balls[i].y) * (shooted_balls[shootcounter].y - balls[i].y)) < 15 && shooted_balls[shootcounter].shoot == true
               &&shooted_balls[shootcounter].color != balls[i].color ){
                    shooted_balls[shootcounter].shoot = false;
                    shooted_balls[shootcounter].counter = balls[i].counter;
                    balls.insert(balls.begin()+i,shooted_balls[shootcounter]);
                    cout << "HIT " << i  << endl;
                    ball_counter++;
                    cout << ball_counter << endl;
                    break;
                }
        }
        SDL_RenderPresent(renderer);
    }
}
void first_map(SDL_Renderer * renderer) {
    if (first_firstmap) {
        if (!is_music) {
            if (musicchanged) {

                if (music_number % 3 == 0) {
                   Mix_PlayMusic(music_5, -1);
                } else if (music_number % 3 == 1) {
                   Mix_PlayMusic(music_3, -1);
                } else {
                    Mix_PlayMusic(music_4, -1);
                }

            } else {
                Mix_PlayMusic(music_5, -1);
            }

            first_firstmap = 0;
        }

    } else {
        if (musicchanged) {
            if (is_music) {
               Mix_PauseMusic();
            } else {
                if (music_number % 3 == 0) {
                   Mix_PlayMusic(music_5, -1);
                } else if (music_number % 3 == 1) {
                   Mix_PlayMusic(music_3, -1);
                } else {
                   Mix_PlayMusic(music_4, -1);
                }

            }
        } else {
            if (is_music) {
                Mix_PauseMusic();
            } else {

               Mix_ResumeMusic();

            }
        }

    }
    int h = 800, w = 1280;
    int mod;

    SDL_RenderClear(renderer);
    int first_x[10] = {1100,250,1100,1140,1120,1140,100,110,1090,55}, first_y[10] = {655,10,610,550,50,172,10,150,300,570};
    int points_x[10100],points_y[10100];
    int point_counter=0;
    int ball_color;
    double xu = 0,yu=0;
    for(double u = 0;u <=1.0;u+=0.0001){
        xu = pow(1 - u, 9) * first_x[0] + 9 * u * pow(1 - u, 8) * first_x[1] + 36 * pow(u, 2) * pow(1 - u, 7) * first_x[2] + 84 * pow(u, 3) * pow(1 - u, 6) * first_x[3] +
            126 * pow(u, 4) * pow(1 - u, 5) * first_x[4] + 126 * pow(u, 5) * pow(1 - u, 4) * first_x[5] +
            84 * pow(u, 6) * pow(1 - u, 3) * first_x[6] + 36 * pow(u, 7) * pow(1 - u, 2) * first_x[7] + 9 * pow(u, 8) * (1 - u) * first_x[8] + pow(u, 9) * first_x[9];
        yu = pow(1 - u, 9) * first_y[0] + 9 * u * pow(1 - u, 8) * first_y[1] + 36 * pow(u, 2) * pow(1 - u, 7) * first_y[2] + 84 * pow(u, 3) * pow(1 - u, 6) * first_y[3] +
            126 * pow(u, 4) * pow(1 - u, 5) * first_y[4] + 126 * pow(u, 5) * pow(1 - u, 4) * first_y[5] +
            84 * pow(u, 6) * pow(1 - u, 3) * first_y[6] + 36 * pow(u, 7) * pow(1 - u, 2) * first_y[7] + 9 * pow(u, 8) * (1 - u) * first_y[8] + pow(u, 9) * first_y[9];
        points_x[point_counter] = xu;
        points_y[point_counter] = yu;
        point_counter++;
    }
    bezierCurve(first_x, first_y, renderer);
    SDL_RenderPresent(renderer);
    SDL_Event * e11 = new SDL_Event();
    int color = rand()%4;
    if(color == 0){
        yellow_ball->render(renderer,605,585,20,20);
    }
    if(color == 1){
        green_ball->render(renderer,605,585,20,20);
    }
    if(color == 2){
        red_ball->render(renderer,605,585,20,20);
    }
    if(color == 3){
        blue_ball->render(renderer,605,585,20,20);
    }
    bool added = false;
    vector<ball> balls(1000);
    vector<ball> shooted_balls(10000);
    int shootcounter=0;
    int ball_counter = 0;
    for(int j=0;j<100;j++){
        balls[j].x = points_x[0];
        balls[j].y = points_y[0];
        balls[j].counter = 0;
    }
    int same_color = 0;
    int x9, y9;
    bool endgame = true;
    while (true) {
        SDL_PollEvent(e11);
        SDL_RenderClear(renderer);
        if (e11 -> type == SDL_QUIT) {
            quit(renderer);
        }
        if (e11 -> type == SDL_KEYDOWN && e11 -> key.keysym.sym == SDLK_ESCAPE) {
            mod = 1;
            //           Mix_PauseMusic();
            pausemenu(renderer, mod);
        }

        if (e11 -> type == SDL_MOUSEMOTION) {
            SDL_GetMouseState( & x9, & y9);
            angle = atan2((y9 - (585)), (x9 - (605)));
            //            cout << angle << endl;
        }
        if(e11 -> type == SDL_KEYDOWN && e11 -> key.keysym.sym == SDLK_SPACE){
            color = rand()%4;
        }
        map1g -> render();
        end_hole1 -> render();
        start_hole1 -> render();
        bezierCurve(first_x, first_y, renderer);
        //       lineRGBA(renderer,750,450,x9,y9,255,0,0,255);
        angledImage(renderer, "resources/pics/cannon.png", 469, 470.5, 300, 300, (angle * 180) / M_PI - 90);
        for(int i=0;i<=ball_counter && endgame;i++){
            if(balls[i].given_color == false){
                ball_color = rand()%4;
                balls[i].color = ball_color;
                balls[i].given_color = true;
            }
            double frombehind = sqrt((balls[i].x - balls[i+1].x)*(balls[i].x - balls[i+1].x) + (balls[i].y - balls[i+1].y)*(balls[i].y - balls[i+1].y));
            while( frombehind <= 42 ){
                balls[i].x = points_x[balls[i].counter++];
                balls[i].y = points_y[balls[i].counter++];
                frombehind = sqrt((balls[i].x - balls[i+1].x)*(balls[i].x - balls[i+1].x) + (balls[i].y - balls[i+1].y)*(balls[i].y - balls[i+1].y));
            }
            balls[i].x = points_x[balls[i].counter++];
            balls[i].y = points_y[balls[i].counter++];
            if(balls[i].color == 0){
                yellow_ball->render(renderer,balls[i].x-13,balls[i].y-20,35,35);
            }
            if(balls[i].color == 1){
                green_ball->render(renderer,balls[i].x-13,balls[i].y-20,35,35);
            }
            if(balls[i].color == 2){
                red_ball->render(renderer,balls[i].x-13,balls[i].y-20,35,35);
            }
            if(balls[i].color == 3){
                blue_ball->render(renderer,balls[i].x-13,balls[i].y-20,35,35);
            }
            if (e11 -> type == SDL_KEYDOWN && e11 -> key.keysym.sym == SDLK_SPACE){
                cout << "space" << endl;
                color = rand()%4;
            }
            if(sqrt((balls[ball_counter].x - points_x[0])* (balls[ball_counter].x - points_x[0]) + (balls[ball_counter].y - points_y[0]) * (balls[ball_counter].y - points_y[0])) > 78){
                if(ball_counter<30) ball_counter++;
                else continue;
            }
        }
        if(sqrt((balls[0].x - points_x[point_counter-1])* (balls[0].x - points_x[point_counter-1]) +
                (balls[0].y - points_y[point_counter-1]) * (balls[0].y - points_y[point_counter-1]))< 40){
                    balls.erase(balls.begin());
                    ball_counter--;
                    //endgame = false;
        }
        if(color == 0){
            yellow_ball->render(renderer,605,585,35,35);
        }
        if(color == 1){
            green_ball->render(renderer,605,585,35,35);
        }
        if(color == 2){
            red_ball->render(renderer,605,585,35,35);
        }
        if(color == 3){
            blue_ball->render(renderer,605,585,35,35);
        }
        if(e11->type == SDL_MOUSEBUTTONDOWN){
            SDL_GetMouseState( & x9, & y9);
            zdfgh = atan2((y9 - (585)),(x9 - (605)));
            shooted_balls[shootcounter].x = 605;
            shooted_balls[shootcounter].y = 585;
            shooted_balls[shootcounter].dx = 8*cos(zdfgh);
            shooted_balls[shootcounter].dy = 8*sin(zdfgh);
            shooted_balls[shootcounter].color = color;
            shooted_balls[shootcounter].shoot = true;
        }
        if(shooted_balls[shootcounter].color == 0&& shooted_balls[shootcounter].shoot == true)
            {
            yellow_ball->render(renderer,shooted_balls[shootcounter].x,shooted_balls[shootcounter].y,35,35);
            shooted_balls[shootcounter].x+=shooted_balls[shootcounter].dx;
            shooted_balls[shootcounter].y+=shooted_balls[shootcounter].dy;
        }
        if(shooted_balls[shootcounter].color == 1&& shooted_balls[shootcounter].shoot == true){
            green_ball->render(renderer,shooted_balls[shootcounter].x,shooted_balls[shootcounter].y,35,35);
            shooted_balls[shootcounter].x+=shooted_balls[shootcounter].dx;
            shooted_balls[shootcounter].y+=shooted_balls[shootcounter].dy;
        }
        if(shooted_balls[shootcounter].color == 2&& shooted_balls[shootcounter].shoot == true){
            red_ball->render(renderer,shooted_balls[shootcounter].x,shooted_balls[shootcounter].y,35,35);
            shooted_balls[shootcounter].x+=shooted_balls[shootcounter].dx;
            shooted_balls[shootcounter].y+=shooted_balls[shootcounter].dy;
        }
        shooted_balls[shootcounter].given_color =true;
        if(shooted_balls[shootcounter].color == 3 && shooted_balls[shootcounter].shoot == true){
            blue_ball->render(renderer,shooted_balls[shootcounter].x,shooted_balls[shootcounter].y,35,35);
            shooted_balls[shootcounter].x+=shooted_balls[shootcounter].dx;
            shooted_balls[shootcounter].y+=shooted_balls[shootcounter].dy;
        }
        for(int i = 0;i<=ball_counter;i++){
            same_color =0;
            if(sqrt((shooted_balls[shootcounter].x - balls[i].x)* (shooted_balls[shootcounter].x - balls[i].x) +
                    (shooted_balls[shootcounter].y - balls[i].y) * (shooted_balls[shootcounter].y - balls[i].y)) < 15 && shooted_balls[shootcounter].shoot == true
               &&shooted_balls[shootcounter].color == balls[i].color ){
                for(int j=i;j<=ball_counter;j++){
                    if(balls[j].color == balls[j+1].color){
                        same_color++;
                    }
                    else {
                        break;
                    }
                }
                for(int j=i;j>=0;j--){
                    if(balls[j].color == balls[j+1].color){
                        same_color++;
                    }
                    else {
                        break;
                    }
                }
                if(same_color >=2){
                    shooted_balls[shootcounter].shoot = false;
                    shooted_balls[shootcounter].counter = balls[i].counter;
                    balls.erase(balls.begin()+i,balls.begin()+i+same_color);
                    ball_counter-=same_color;
                    cout << "HIT " << i  << endl;
                    cout << ball_counter << endl;
                }
                else{
                    shooted_balls[shootcounter].shoot = false;
                    shooted_balls[shootcounter].counter = balls[i].counter;
                    balls.insert(balls.begin()+i,shooted_balls[shootcounter]);
                    cout << "HIT " << i  << endl;
                    ball_counter++;
                    cout << ball_counter << endl;
                    break;
                }
            }
            else if(sqrt((shooted_balls[shootcounter].x - balls[i].x)* (shooted_balls[shootcounter].x - balls[i].x) +
                    (shooted_balls[shootcounter].y - balls[i].y) * (shooted_balls[shootcounter].y - balls[i].y)) < 15 && shooted_balls[shootcounter].shoot == true
               &&shooted_balls[shootcounter].color != balls[i].color ){
                    shooted_balls[shootcounter].shoot = false;
                    shooted_balls[shootcounter].counter = balls[i].counter;
                    balls.insert(balls.begin()+i,shooted_balls[shootcounter]);
                    cout << "HIT " << i  << endl;
                    ball_counter++;
                    cout << ball_counter << endl;
                    break;
                }
        }

        SDL_RenderPresent(renderer);
    }
}
void pausemenu(SDL_Renderer * renderer, int & mod) {
    //   Mix_Music *music_2=Mix_LoadMUS("resources/music/marbleblast1.mp3");
    //    music_2=Mix_LoadMUS("resources/music/marbleblast1.mp3");
    pause_to_start = 0;

    if (!is_music) {
        musicchanged = 0;
       Mix_PauseMusic();
    }
    startbuttonsbg -> render();
    pm_sb -> render();
    pm_mb -> render();
    //  pm_gbb->render();
    pm_conb -> render();
    pm_eb -> render();

    next_butt -> render();
    change_music -> render();
    pausemenu_closb -> render();

    betterText(renderer, m[(music_number) % 3], 650, 424, 0, 0, 0, 255, 18, "YoungBarse");

    betterText(renderer, "Resume", 700, 185, 0, 255, 255, 255, 25, "chrustyrock");
    if (is_music) {

        betterText(renderer, "Music OFF", 700, 350, 0, 255, 255, 255, 25, "chrustyrock");
    } else {
        betterText(renderer, "Music ON", 700, 350, 0, 255, 255, 255, 25, "chrustyrock");
    }
    if (is_sound) {
        betterText(renderer, "Sound OFF", 700, 266, 0, 255, 255, 255, 25, "chrustyrock");
    } else {
        betterText(renderer, "Sound ON", 700, 266, 0, 255, 255, 255, 25, "chrustyrock");
    }
    betterText(renderer, "Exit", 700, 500, 0, 255, 255, 255, 25, "chrustyrock");

    SDL_RenderPresent(renderer);
    SDL_Event * e10 = new SDL_Event();
    int x5, y5;
    bool first = false;
    while (1) {
        SDL_PollEvent(e10);
        SDL_GetMouseState( & x5, & y5);
        if (e10 -> type == SDL_QUIT) {
            quit(renderer);
        }
        if (x5 > 784 && x5 < 840 && y5 > 397 && y5 < 453) {

            if (e10 -> type == SDL_MOUSEBUTTONDOWN) {
                musicchanged = 1;
                music_number++;
                change_music -> render();
                SDL_Delay(2);
                betterText(renderer, m[(music_number) % 3], 650, 424, 0, 0, 0, 255, 18, "YoungBarse");
                SDL_Delay(150);
                //            SDL_RenderPresent(renderer);
            }
        }

        if (x5 > 545 && x5 < 825 && y5 > 155 && y5 < 218) {
            if (e10 -> type == SDL_MOUSEBUTTONDOWN) {
                //                       if(first_puase){
                if (is_music) {
                    Mix_PauseMusic();
                } else {
                    if (musicchanged) {
                        if (music_number % 3 == 0) {
                            Mix_PlayMusic(music_5, -1);
                        } else if (music_number % 3 == 1) {
                         Mix_PlayMusic(music_3, -1);
                        } else {
                            Mix_PlayMusic(music_4, -1);
                        }
                    } else {
                       Mix_ResumeMusic();
                    }

                }
                //                      }
                //                     else{
                //                         if(is_music){
                //                  Mix_PauseMusic();                    }
                //                 else{
                //                     Mix_ResumeMusic();
                //                  }
                //                     }
                if (mod == 1) {

                    first_map(renderer);

                    break;
                } else if (mod == 2) {

                    second_map(renderer);
                    break;

                } else if (mod == 3) {
                    //                if(is_music){
                    //                    Mix_PauseMusic();
                    //                    }
                    //                    else{
                    //                        Mix_ResumeMusic();
                    //                    }
                    third_map(renderer);

                    break;
                }
                else{
                    map_random(renderer);
                    break;
                }

            } else {
                betterText(renderer, "Resume", 700, 185, 255, 0, 0, 255, 25, "chrustyrock");
                SDL_RenderPresent(renderer);
            }
        } else {
            betterText(renderer, "Resume", 700, 185, 0, 255, 255, 255, 25, "chrustyrock");
            SDL_RenderPresent(renderer);
        }
        if (x5 > 545 && x5 < 825 && y5 > 235 && y5 < 298) {
            if (e10 -> type == SDL_MOUSEBUTTONDOWN) {

                if (is_sound) {
                    is_sound = 0;

                    pm_sb -> render();
                    SDL_Delay(2);
                    betterText(renderer, "Sound ON", 700, 266, 255, 0, 0, 255, 25, "chrustyrock");
                    SDL_RenderPresent(renderer);
                    SDL_Delay(150);

                } else {
                    is_sound = 1;

                    pm_sb -> render();
                    SDL_Delay(2);
                    betterText(renderer, "Sound OFF", 700, 266, 255, 0, 0, 255, 25, "chrustyrock");
                    SDL_RenderPresent(renderer);
                    SDL_Delay(150);

                }

            } else {
                if (is_sound) {
                    betterText(renderer, "Sound OFF", 700, 266, 255, 0, 0, 255, 25, "chrustyrock");
                    SDL_RenderPresent(renderer);
                } else {
                    betterText(renderer, "Sound ON", 700, 266, 255, 0, 0, 255, 25, "chrustyrock");
                    SDL_RenderPresent(renderer);
                }
            }
        } else {
            if (is_sound) {
                betterText(renderer, "Sound OFF", 700, 266, 0, 255, 255, 255, 25, "chrustyrock");
                SDL_RenderPresent(renderer);
            } else {
                betterText(renderer, "Sound ON", 700, 266, 0, 255, 255, 255, 25, "chrustyrock");
                SDL_RenderPresent(renderer);
            }
        }

        if (x5 > 545 && x5 < 825 && y5 > 320 && y5 < 378) {
            if (e10 -> type == SDL_MOUSEBUTTONDOWN) {
                if (is_music) {
                    is_music = 0;
                    pm_mb -> render();
                    SDL_Delay(2);
                    betterText(renderer, "Music ON", 700, 350, 255, 0, 0, 255, 25, "chrustyrock");
                    SDL_RenderPresent(renderer);
                    SDL_Delay(150);
                } else {
                    is_music = 1;
                    pm_mb -> render();
                    SDL_Delay(2);
                    betterText(renderer, "Music OFF", 700, 350, 255, 0, 0, 255, 25, "chrustyrock");
                    SDL_RenderPresent(renderer);
                    SDL_Delay(150);
                }

            } else {
                if (is_music) {
                    betterText(renderer, "Music OFF", 700, 350, 255, 0, 0, 255, 25, "chrustyrock");
                    SDL_RenderPresent(renderer);
                } else {
                    betterText(renderer, "Music ON", 700, 350, 255, 0, 0, 255, 25, "chrustyrock");
                    SDL_RenderPresent(renderer);
                }
            }
        } else {
            if (is_music) {
                betterText(renderer, "Music OFF", 700, 350, 0, 255, 255, 255, 25, "chrustyrock");
                SDL_RenderPresent(renderer);
            } else {
                betterText(renderer, "Music ON", 700, 350, 0, 255, 255, 255, 25, "chrustyrock");
                SDL_RenderPresent(renderer);
            }
        }
        if (x5 > 540 && x5 < 825 && y5 > 470 && y5 < 533) {
            if (e10 -> type == SDL_MOUSEBUTTONDOWN) {
                //                if(!is_music){
                //                 Mix_PlayMusic(music_2,-1);
                //                }
                pause_to_start = 1;
                first_firstmap = 1;
                first_secondmap = 1;
                first_thirdmap = 1;
                is_mode = 0;
                startmenu(renderer);
                //              is_music=0;
                //              is_sound=0;
                break;
            } else {
                betterText(renderer, "Exit", 700, 500, 255, 0, 0, 255, 25, "chrustyrock");
                SDL_RenderPresent(renderer);
            }
        } else {
            betterText(renderer, "Exit", 700, 500, 0, 255, 255, 255, 25, "chrustyrock");
            SDL_RenderPresent(renderer);
        }
        //        if(e10->type == SDL_KEYDOWN){
        //            if(mod == 1)first_map(renderer);
        //            else if(mod == 2) second_map(renderer);
        //            else third_map(renderer);
        //            break;
        //        }
        if (e10 -> type == SDL_MOUSEBUTTONDOWN && x5 > 900 && x5 < 945 && y5 > 70 && y5 < 115) {
            if (mod == 1) {
                if (is_music) {
                   Mix_PauseMusic();
                } else {
                    if (musicchanged) {
                        if (music_number % 3 == 0) {
                           Mix_PlayMusic(music_5, -1);
                        } else if (music_number % 3 == 1) {
                           Mix_PlayMusic(music_3, -1);
                        } else {
                        Mix_PlayMusic(music_4, -1);
                        }
                    } else {
                       Mix_ResumeMusic();
                    }

                }
                first_map(renderer);

            } else if (mod == 2) {
                if (is_music) {
                   Mix_PauseMusic();
                } else {
                    if (musicchanged) {
                        if (music_number % 3 == 0) {
                            Mix_PlayMusic(music_5, -1);
                        } else if (music_number % 3 == 1) {
                           Mix_PlayMusic(music_3, -1);
                        } else {
                           Mix_PlayMusic(music_4, -1);
                        }
                    } else {
                       Mix_ResumeMusic();
                    }

                }
                second_map(renderer);

            } else {
                if (is_music) {
                    Mix_PauseMusic();
                } else {
                    if (musicchanged) {
                        if (music_number % 3 == 0) {
                         Mix_PlayMusic(music_5, -1);
                        } else if (music_number % 3 == 1) {
                           Mix_PlayMusic(music_3, -1);
                        } else {
                            Mix_PlayMusic(music_4, -1);
                        }
                    } else {
                        Mix_ResumeMusic(); 
                    }

                }
                third_map(renderer);

                break;
            }
        }
        if (first == true) {
            int forsample1, forsmaple2;
            string example1;
            first_page(renderer, example1, forsample1, forsample1);
        }
    }
}
void Image::render(SDL_Renderer * m_renderer, int xp, int yp, int width, int height) {
    SDL_Rect texr1;
    texr1.x = xp;
    texr1.y = yp;
    texr1.w = width;
    texr1.h = height;
    SDL_RenderCopy(m_renderer, texture, NULL, & texr1);
}
void map_random(SDL_Renderer *renderer){
    int h = 1280,w = 800;
    int color=0,mod=0;
    int random_x[10],random_y[10];
    for(int i=0;i<10;i++){
        random_x[i] = rand()%1180;
        random_y[i] = rand()%700;
    }
    SDL_RenderClear(renderer);
    bezierCurve(random_x, random_y, renderer);
    SDL_RenderPresent(renderer);
    SDL_Event*e13 = new SDL_Event();
    while (true) {
        SDL_PollEvent(e13);
        SDL_RenderClear(renderer);
        if (e13 -> type == SDL_QUIT) {
            quit(renderer);
        }
        if (e13 -> type == SDL_KEYDOWN && e13 -> key.keysym.sym == SDLK_ESCAPE) {
            mod = 4;
            //           Mix_PauseMusic();
            pausemenu(renderer, mod);
        }
        int x9, y9;
        if (e13 -> type == SDL_MOUSEMOTION) {
            SDL_GetMouseState( & x9, & y9);
            angle = atan2((y9 - (585)), (x9 - (605)));
            //            cout << angle << endl;
        }
        if(e13 -> type == SDL_KEYDOWN && e13-> key.keysym.sym == SDLK_SPACE){
            color = rand()%4;
        }
        map1g -> render();
        //end_hole1 -> render();
        //start_hole1 -> render();
        bezierCurve(random_x, random_y, renderer);
        //lineRGBA(renderer,750,450,x9,y9,255,0,0,255);
        SDL_RenderPresent(renderer);
    }
}
