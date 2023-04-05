// Including all the required libraries
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <string>
#include <direct.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

#define keyup 72
#define keydown 80
#define keyleft 75
#define keyright 77

using namespace std;

// Class for user validation
class Start
{
public:
    int age;
    string username = "raj123";
    string password;

    // Function to check user data
    int check_data(string u1, int a1)
    {
        if (u1 == "raj123" && a1 >= 7)
            return 1;
        else
            return 0;
    }

    // Function to check user data
    int check_data(string p1)
    {
        if (p1 == "12345")
            return 1;
        else
            return 0;
    }

    // Function to input user data
    int set_data()
    {
        cout << "\n\n********************************";
        cout << "\n           USER DETAILS" << endl;
        cout << "********************************";
        cout << "\n       USERNAME:- ";
        cin >> username;
        cout << "\n       PASSWORD:- ";
        cin >> password;
        cout << "\n       AGE:- ";
        cin >> age;
        int checking1 = check_data(username, age);
        int checking2 = check_data(password);
        if (checking1 && checking2)
        {
            cout << "\n\n\n\n\n\n";
            cout << "\t\t\tLoading :";
            char x = 219;
            for (int i = 0; i < 50; i++)
            {
                cout << x;
                Sleep(10);
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }
};

class Info
{
public:
    // Declaring and Initializing all the variables
    int minimum = 0, row, col, currentscore = 0;
    vector<int> score = {60, 40, 20};
    vector<int> bodyX;
    vector<int> bodyY;
    bool is_snake_alive = true;
    bool player_status = false;
    int field_width = 30, field_height = 20;
    int X = field_width / 2, Y = field_height / 2;
    int food_posX = rand() % (field_width - 4) + 2;
    int food_posY = rand() % (field_height - 4) + 2;

    // Function for updating current score
    void update_score()
    {
        for (int i = 0; i < score.size(); i++)
        {
            if (currentscore > score[i])
            {
                score.insert(score.begin() + i, currentscore);
                score.erase(score.begin() + score.size());
                return;
            }
        }
    }
};

// Class for snake functions
class SnakeFunctions : public Info
{
public:
    void snake_function()
    {
        bodyX.insert(bodyX.begin(), X);
        bodyY.insert(bodyY.begin(), Y);
    }

    void snake_reset()
    {
        for (int i = 0; i < bodyX.size(); i++)
        {
            bodyX.erase(bodyX.begin() + i);
            bodyY.erase(bodyY.begin() + i);
        }
    }

    // Function to randomly place the food
    void food_position()
    {
        bool Unique = false;
        while (!Unique)
        {
            food_posX = rand() % (field_width - 4) + 2;
            food_posY = rand() % (field_height - 4) + 2;

            for (int i = 0; i < bodyX.size(); i++)
            {
                if (food_posY == bodyY[i] && food_posX == bodyX[i])
                    break;
                else
                    Unique = true;
            }
        }
    }

    // Function to check whether snake is dead or alive
    void snake_status()
    {
        if (food_posX == X && food_posY == Y)
        {
            currentscore += 10;
            food_position();
        }

        if (X == 0 || X == field_width - 1 || Y == 0 || Y == field_height - 1)
        {
            is_snake_alive = false;
        }

        for (int i = 1; i <= currentscore / 10; i++)
        {
            if (bodyX[i] == X && bodyY[i] == Y)
            {
                is_snake_alive = false;
            }
        }
    }
};

// Class for Controlling the snake
class ControlSnake : public SnakeFunctions, Start
{
public:
    enum directions
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    directions dir;

    // Function to get input from the player
    void get_input()
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'w':
            case 'W':
            case keyup:
                if (dir != DOWN)
                    dir = UP;
                break;

            case 'a':
            case 'A':
            case keyleft:
                if (dir != RIGHT)
                    dir = LEFT;
                break;

            case 's':
            case 'S':
            case keydown:
                if (dir != UP)
                    dir = DOWN;
                break;

            case 'd':
            case 'D':
            case keyright:
                if (dir != LEFT)
                    dir = RIGHT;
                break;

            case 'p':
                cout << "\nEXITTED...";
                exit(0);
                break;
            }
        }
    }

    // Function to add color
    void sp(int choosecolor)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), choosecolor);
    }

    // Function to remove the color
    void s()
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

    // Function to clear the screen after every movement without flickering
    void clearscreen()
    {
        HANDLE hOut;
        COORD Position;

        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        Position.X = 0;
        Position.Y = 0;
        SetConsoleCursorPosition(hOut, Position);
    }

    // Function for creating the field and the snake's body
    void set_field()
    {
        new char[2000];
        clearscreen();
        for (row = 0; row < field_height; row++)
        {
            for (col = 0; col < field_width; col++)
            {
                if (row == 0 || row == field_height - 1)
                    cout << char(219);
                else if (col == 0 || col == field_width - 1)
                    cout << char(219);
                else if (row == Y && col == X)
                {
                    sp(900);
                    cout << char(219);
                    s();
                }

                else if (row == food_posY && col == food_posX)
                    cout << "O";
                else
                {
                    bool flag = true;
                    for (int body = 1; body < (currentscore + 10) / 10; body++)
                    {
                        if (bodyX[body] == col && bodyY[body] == row)
                        {
                            sp(450);
                            cout << char(219);
                            s();
                            flag = false;
                        }
                    }
                    if (flag)
                    {
                        cout << " ";
                    }
                }
            }
            set_scoreboard(row);
            cout << endl;
        }
    }

    // Function for setting up the scoreboard
    void set_scoreboard(int row)
    {
        if (row == 1)
            cout << setw(18) << "Username: " << setw(17) << username;
        if (row == 3)
            cout << setw(22) << "Current Score:" << setw(13) << currentscore;
    }

    // Function for snake's movement
    void snake_movement()
    {
        if (dir == UP)
            Y--;
        else if (dir == DOWN)
            Y++;
        else if (dir == LEFT)
            X--;
        else if (dir == RIGHT)
            X++;
        else
            return;
    }

    // Structure for storing choice of whether wants to play again
    struct playagain
    {
        int choice;
    };

    // Play game function
    void play_game()
    {
        while (is_snake_alive)
        {
            set_field();
            get_input();
            snake_movement();
            snake_function();
            snake_status();
            if (!is_snake_alive)
            {
                struct playagain s1;
                cout << "\n\n\n\n\n\n";
                cout << "\t\t\tLoading :";
                char x = 219;
                for (int i = 0; i < 50; i++)
                {
                    cout << x;
                    Sleep(10);
                }
                cout << "\n\nPlay Again?: Press 1 For Yes / 2 For No\n";
                cin >> s1.choice;
                if (s1.choice == 1)
                {
                    system("cls");
                    srand(time(NULL));
                    ControlSnake play;
                    play.play_game();
                    system("PAUSE");
                }
                else if (s1.choice == 2)
                {
                    system("cls");
                    cout << R"(
                                                                                                                                                                                                                                    
                                                                                                                                                                                                        
        GGGGGGGGGGGGG               AAA               MMMMMMMM               MMMMMMMMEEEEEEEEEEEEEEEEEEEEEE          OOOOOOOOO     VVVVVVVV           VVVVVVVVEEEEEEEEEEEEEEEEEEEEEERRRRRRRRRRRRRRRRR   
     GGG::::::::::::G              A:::A              M:::::::M             M:::::::ME::::::::::::::::::::E        OO:::::::::OO   V::::::V           V::::::VE::::::::::::::::::::ER::::::::::::::::R  
   GG:::::::::::::::G             A:::::A             M::::::::M           M::::::::ME::::::::::::::::::::E      OO:::::::::::::OO V::::::V           V::::::VE::::::::::::::::::::ER::::::RRRRRR:::::R 
  G:::::GGGGGGGG::::G            A:::::::A            M:::::::::M         M:::::::::MEE::::::EEEEEEEEE::::E     O:::::::OOO:::::::OV::::::V           V::::::VEE::::::EEEEEEEEE::::ERR:::::R     R:::::R
 G:::::G       GGGGGG           A:::::::::A           M::::::::::M       M::::::::::M  E:::::E       EEEEEE     O::::::O   O::::::O V:::::V           V:::::V   E:::::E       EEEEEE  R::::R     R:::::R
G:::::G                        A:::::A:::::A          M:::::::::::M     M:::::::::::M  E:::::E                  O:::::O     O:::::O  V:::::V         V:::::V    E:::::E               R::::R     R:::::R
G:::::G                       A:::::A A:::::A         M:::::::M::::M   M::::M:::::::M  E::::::EEEEEEEEEE        O:::::O     O:::::O   V:::::V       V:::::V     E::::::EEEEEEEEEE     R::::RRRRRR:::::R 
G:::::G    GGGGGGGGGG        A:::::A   A:::::A        M::::::M M::::M M::::M M::::::M  E:::::::::::::::E        O:::::O     O:::::O    V:::::V     V:::::V      E:::::::::::::::E     R:::::::::::::RR  
G:::::G    G::::::::G       A:::::A     A:::::A       M::::::M  M::::M::::M  M::::::M  E:::::::::::::::E        O:::::O     O:::::O     V:::::V   V:::::V       E:::::::::::::::E     R::::RRRRRR:::::R 
G:::::G    GGGGG::::G      A:::::AAAAAAAAA:::::A      M::::::M   M:::::::M   M::::::M  E::::::EEEEEEEEEE        O:::::O     O:::::O      V:::::V V:::::V        E::::::EEEEEEEEEE     R::::R     R:::::R
G:::::G        G::::G     A:::::::::::::::::::::A     M::::::M    M:::::M    M::::::M  E:::::E                  O:::::O     O:::::O       V:::::V:::::V         E:::::E               R::::R     R:::::R
 G:::::G       G::::G    A:::::AAAAAAAAAAAAA:::::A    M::::::M     MMMMM     M::::::M  E:::::E       EEEEEE     O::::::O   O::::::O        V:::::::::V          E:::::E       EEEEEE  R::::R     R:::::R
  G:::::GGGGGGGG::::G   A:::::A             A:::::A   M::::::M               M::::::MEE::::::EEEEEEEE:::::E     O:::::::OOO:::::::O         V:::::::V         EE::::::EEEEEEEE:::::ERR:::::R     R:::::R
   GG:::::::::::::::G  A:::::A               A:::::A  M::::::M               M::::::ME::::::::::::::::::::E      OO:::::::::::::OO           V:::::V          E::::::::::::::::::::ER::::::R     R:::::R
     GGG::::::GGG:::G A:::::A                 A:::::A M::::::M               M::::::ME::::::::::::::::::::E        OO:::::::::OO              V:::V           E::::::::::::::::::::ER::::::R     R:::::R
        GGGGGG   GGGGAAAAAAA                   AAAAAAAMMMMMMMM               MMMMMMMMEEEEEEEEEEEEEEEEEEEEEE          OOOOOOOOO                 VVV            EEEEEEEEEEEEEEEEEEEEEERRRRRRRR     RRRRRRR
                                                                                                                                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                                                                          
                        )"
                         << '\n';
                    exit(0);
                }
            }
            Sleep(30);
        }
    }
};

// Main function
int main()
{

    Start s1;
    cout << R"(
                                                                                                                                                                                         
                                                                                                                                                                                 
   SSSSSSSSSSSSSSS                                   kkkkkkkk                                         GGGGGGGGGGGGG                                                              
 SS:::::::::::::::S                                  k::::::k                                      GGG::::::::::::G                                                              
S:::::SSSSSS::::::S                                  k::::::k                                    GG:::::::::::::::G                                                              
S:::::S     SSSSSSS                                  k::::::k                                   G:::::GGGGGGGG::::G                                                              
S:::::S          nnnn  nnnnnnnn      aaaaaaaaaaaaa    k:::::k    kkkkkkk eeeeeeeeeeee          G:::::G       GGGGGG  aaaaaaaaaaaaa      mmmmmmm    mmmmmmm       eeeeeeeeeeee    
S:::::S          n:::nn::::::::nn    a::::::::::::a   k:::::k   k:::::kee::::::::::::ee       G:::::G                a::::::::::::a   mm:::::::m  m:::::::mm   ee::::::::::::ee  
 S::::SSSS       n::::::::::::::nn   aaaaaaaaa:::::a  k:::::k  k:::::ke::::::eeeee:::::ee     G:::::G                aaaaaaaaa:::::a m::::::::::mm::::::::::m e::::::eeeee:::::ee
  SS::::::SSSSS  nn:::::::::::::::n           a::::a  k:::::k k:::::ke::::::e     e:::::e     G:::::G    GGGGGGGGGG           a::::a m::::::::::::::::::::::me::::::e     e:::::e
    SSS::::::::SS  n:::::nnnn:::::n    aaaaaaa:::::a  k::::::k:::::k e:::::::eeeee::::::e     G:::::G    G::::::::G    aaaaaaa:::::a m:::::mmm::::::mmm:::::me:::::::eeeee::::::e
       SSSSSS::::S n::::n    n::::n  aa::::::::::::a  k:::::::::::k  e:::::::::::::::::e      G:::::G    GGGGG::::G  aa::::::::::::a m::::m   m::::m   m::::me:::::::::::::::::e 
            S:::::Sn::::n    n::::n a::::aaaa::::::a  k:::::::::::k  e::::::eeeeeeeeeee       G:::::G        G::::G a::::aaaa::::::a m::::m   m::::m   m::::me::::::eeeeeeeeeee  
            S:::::Sn::::n    n::::na::::a    a:::::a  k::::::k:::::k e:::::::e                 G:::::G       G::::Ga::::a    a:::::a m::::m   m::::m   m::::me:::::::e           
SSSSSSS     S:::::Sn::::n    n::::na::::a    a:::::a k::::::k k:::::ke::::::::e                 G:::::GGGGGGGG::::Ga::::a    a:::::a m::::m   m::::m   m::::me::::::::e          
S::::::SSSSSS:::::Sn::::n    n::::na:::::aaaa::::::a k::::::k  k:::::ke::::::::eeeeeeee          GG:::::::::::::::Ga:::::aaaa::::::a m::::m   m::::m   m::::m e::::::::eeeeeeee  
S:::::::::::::::SS n::::n    n::::n a::::::::::aa:::ak::::::k   k:::::kee:::::::::::::e            GGG::::::GGG:::G a::::::::::aa:::am::::m   m::::m   m::::m  ee:::::::::::::e  
 SSSSSSSSSSSSSSS   nnnnnn    nnnnnn  aaaaaaaaaa  aaaakkkkkkkk    kkkkkkk eeeeeeeeeeeeee               GGGGGG   GGGG  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmm    eeeeeeeeeeeeee  
                                                                                                                                                                                                                                                                                                                                                     
)" << '\n';
    cout << endl;
    int flag = s1.set_data();
    system("cls");
    if (flag)
    {
        srand(time(NULL));
        ControlSnake play;
        play.play_game();
        system("PAUSE");
    }
    else
    {
        cout << "\n***********************************\n";
        cout << "            LOGIN FAILED";
        exit(0);
    }
}
