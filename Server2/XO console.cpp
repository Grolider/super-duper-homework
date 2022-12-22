#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;

class XO {

public:
    string player1, player2, player;
    int len1, len2;
    char key;

    int interface();
    void playersnames();
    int gameplay();
    int whowon();

};
char grid[10] = { '/0','a','b','c','d','e','f','g','h','i' };
int playagain;
int inputnumb = 0;


//отрисовка интерфейса
int XO::interface() {
    cout << "\t     " << char(219) << "\t   " << char(219) << endl;
    cout << "\t  " << grid[1] << "  " << char(219) << "  " << grid[2] << "  " << char(219) << "  " << grid[3] << endl;
    cout << "\t" << string(5, char(220)) << char(219) << string(5, char(220)) << char(219) << string(5, char(220)) << endl;
    cout << "\t     " << char(219) << "\t   " << char(219) << "\t" << endl;
    cout << "\t  " << grid[4] << "  " << char(219) << "  " << grid[5] << "  " << char(219) << "  " << grid[6] << endl;
    cout << "\t" << string(5, char(220)) << char(219) << string(5, char(220)) << char(219) << string(5, char(220)) << endl;
    cout << "\t     " << char(219) << "     " << char(219) << "     " << endl;
    cout << "\t  " << grid[7] << "  " << char(219) << "  " << grid[8] << "  " << char(219) << "  " << grid[9] << endl;
    cout << "\t     " << char(219) << "\t   " << char(219) << "\t" << endl << endl;
    return 0;
}


//Ввод имен игроков
void XO::playersnames(char* name1,char* name2) {
    
    player1 = name1;
    player2 = name2;
    len1 = player1.length();
    len2 = player2.length();
    cout << "\t";
    for (int j = 0; j < len1; j++) {
        player1[j] = toupper(player1[j]);
        cout << player1[j];
    }
    cout << "(X)  vs  ";

    for (int j = 0; j < len2; j++)
    {
        player2[j] = toupper(player2[j]);
        cout << player2[j];
    }
    cout << "(O)";
    cout << endl << endl;

}


int XO::gameplay(char _key,int inputnumb) { //ход игры

position1: if (inputnumb % 2 == 0) { //первый игрок
    player = player1;
    cout << "\t   " << player << "'s Move:";
    key = _key;

    switch (key) {
    case 'a':
        if (grid[1] != 'O' && grid[1] != 'X')       //проверка на случай если если эта ячейка занята
            grid[1] = 'X';
        else
            goto def1;
        break;
    case 'b':
        if (grid[2] != 'O' && grid[2] != 'X')
            grid[2] = 'X';
        else
            goto def1;
        break;
    case 'c':
        if (grid[3] != 'O' && grid[3] != 'X')
            grid[3] = 'X';
        else
            goto def1;
        break;
    case 'd':
        if (grid[4] != 'O' && grid[4] != 'X')
            grid[4] = 'X';
        else
            goto def1;
        break;
    case 'e':
        if (grid[7] != 'O' && grid[5] != 'X')
            grid[5] = 'X';
        else
            goto def1;
        break;
    case 'f':
        if (grid[8] != 'O' && grid[6] != 'X')
            grid[6] = 'X';
        else
            goto def1;
        break;
    case 'g':
        if (grid[7] != 'O' && grid[7] != 'X')
            grid[7] = 'X';
        else
            goto def1;
        break;
    case 'h':
        if (grid[8] != 'O' && grid[8] != 'X')
            grid[8] = 'X';
        else
            goto def1;
        break;
    case 'i':
        if (grid[9] != 'O' && grid[9] != 'X')
            grid[9] = 'X';
        else
            goto def1;
        break;
    def1: default:
        cout << "\t   Wrong Move, try again." << endl;
        return 0;
    }
}
else position2: if (inputnumb % 2 == 1) { //второй игрок
    player = player2;
    cout << "\t   " << player << "'s move:";
    cin >> key;

    switch (key) {
    case 'a':
        if (grid[1] != 'O' && grid[1] != 'X')
            grid[1] = 'O';
        else
            goto def2;
        break;
    case 'b':
        if (grid[2] != 'O' && grid[2] != 'X')
            grid[2] = 'O';
        else
            goto def2;
        break;
    case 'c':
        if (grid[3] != 'O' && grid[3] != 'X')
            grid[3] = 'O';
        else
            goto def2;
        break;
    case 'd':
        if (grid[4] != 'O' && grid[4] != 'X')
            grid[4] = 'O';
        else
            goto def2;
        break;
    case 'e':
        if (grid[5] != 'O' && grid[5] != 'X')
            grid[5] = 'O';
        else
            goto def2;
        break;
    case 'f':
        if (grid[6] != 'O' && grid[6] != 'X')
            grid[6] = 'O';
        else
            goto def2;
        break;
    case 'g':
        if (grid[7] != 'O' && grid[7] != 'X')
            grid[7] = 'O';
        else
            goto def2;
        break;
    case 'h':
        if (grid[8] != 'O' && grid[8] != 'X')
            grid[8] = 'O';
        else
            goto def2;
        break;
    case 'i':
        if (grid[9] != 'O' && grid[9] != 'X')
            grid[9] = 'O';
        else
            goto def2;
        break;
    def2: default:
        cout << "\t   Wrong Move, try again." << endl;
        return 0;
    }
}
return 1;
}

//Определение победителя
int XO::whowon() {

    if ((grid[1] == grid[2] && grid[1] == grid[3] && grid[2] == grid[3]) ||    //проверка строки
        (grid[4] == grid[5] && grid[4] == grid[6] && grid[5] == grid[6]) ||
        (grid[7] == grid[8] && grid[7] == grid[9] && grid[8] == grid[9]) ||

        (grid[1] == grid[4] && grid[1] == grid[7] && grid[4] == grid[7]) ||  //проверка столбца
        (grid[2] == grid[5] && grid[2] == grid[8] && grid[5] == grid[8]) ||
        (grid[3] == grid[6] && grid[3] == grid[9] && grid[6] == grid[9]) ||

        (grid[1] == grid[5] && grid[1] == grid[9] && grid[5] == grid[9]) ||   //проверка диагоналей
        (grid[3] == grid[5] && grid[3] == grid[7] && grid[5] == grid[7])) {
        return 1;
    }

    else if (grid[1] != 'a' && grid[2] != 'b' && grid[3] != 'c' && grid[4] != 'd' && grid[5] != 'e' && grid[6] != 'f' && grid[7] != 'g' && grid[8] != 'h' && grid[9] != 'i') //тогда ничья
        return -1;
    else
        return 0;
}

/*int main() {
    XO obj;
    int b;
    obj.playersnames();

    do {

        obj.interface();
        do {
            obj.gameplay();
            obj.interface();
            obj.whowon();
            b = obj.whowon();
            inputnumb++;

        } while (b == 0);   

        //ну короче говоря, после того как b присваиваем возвращаемое значение метода whowon (когда будет выполнено условие победы, в случае победы это единица),  мы проверяем чей ход был решающий, соответственно этот
       // игрок и будет победителем. Если выполняется условие ничьи, возвращается -1 и победителя не будет. Вроде как нормас работает.

        if (b == 1) {         
            if (inputnumb % 2 == 1) {
                cout << "\t   " << obj.player1 << " is a winner" << endl;  
            }
            else if (inputnumb % 2 == 0) {
                cout << "\t   " << obj.player2 << " is a winner" << endl;
            }
        }
        else if (b == -1) {
            cout << "\t   Draw." << endl;
        }

        for (int i = 1; i < 10; i++)           //очистка значений для повторной игры
            grid[i] = char(96 + i);
        inputnumb = 0;

        cout << "press 1 to start another round and 2 to exit: "; cin >> playagain; cout << endl << endl;
    } while (playagain == 1);


    if (playagain == 2)
        cout << "\t   ok bye" << endl;
    else
        cout << "\t   wrong choice..." << endl;

    return 0;
}*/