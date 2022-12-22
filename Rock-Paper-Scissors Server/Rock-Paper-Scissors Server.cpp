#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <list>

#pragma warning(disable: 4996)

SOCKET newConnection;
int Counter = 1;

//класс соединения для хранения номера соединения и соответствующего сокета
class Connections {
    int index;
    SOCKET Connection;

public:

    void Connections_info(int _index, SOCKET _Connection) {
        index = _index;
        Connection = _Connection;
    }

    int get_index() {
        return index;
    }

    int Recv(char* msg, int len) {
        return recv(Connection, msg, len, NULL);
    }

    int Send(char* msg, int len) {
        return send(Connection, msg, len, NULL);
    }
};

//список для хранения функционирующих соединений
std::list<Connections> ConnectionsList;

//функция для поиска соединения под конкретным номером
std::list<Connections>::iterator Find_Connection(int index) {
    for (std::list<Connections>::iterator element = ConnectionsList.begin(); element != ConnectionsList.end(); element++) {
        int _index = (*element).get_index();
        if (_index == index) {
            return element;
            break;
        }
    }
}

//класс клиента для хранения id клиента, имени и статуса
class Client {
    char name[13];
    int id;
    int status;
    char msg[50] = "";

public:
    ~Client() {

    }

    void Client_info(char* _name, int index, int stat) {
        strcpy(name, _name);
        id = index;
        status = stat;
    }

    char* GetInfo() {
        memset(msg, '\0', 50);
        std::string _id = std::to_string(id);
        strcpy(msg, _id.c_str());
        strncat(msg, " ", 1);
        strncat(msg, name, 10);
        //strncat(msg, " ", 1);
        //_id = std::to_string(status);
        //strcat(msg, _id.c_str());

        return msg;
    }

    int get_status() {
        return status;
    }

    int get_id() {
        return id;
    }

    char* get_name() {
        return name;
    }
};

//список для хранения подключённых клиентов
std::list < Client > ClientsList;

//функция для поиска клиента с конкретным id
std::list<Client>::iterator Find_Client(int index) {
    for (std::list<Client>::iterator element = ClientsList.begin(); element != ClientsList.end(); element++) {
        int _index = (*element).get_id();
        if (_index == index) {
            return element;
            break;
        }
    }
}

//структура для хранения информации о том, что один игрок пригласил другого игрока и ожидает ответа
struct waiting
{
    int waiter;
    int player;

    waiting(int _waiter_id, int _player_id) {
        waiter = _waiter_id;
        player = _player_id;
    }
};

//список для хранения информации о текущих ожиданиях
std::list<waiting> WaitersList;

//структура для хранения информации о том, какие два игрока играют
struct Game {
    int player1;
    int player2;

    Game(int pl1, int pl2) {
        player1 = pl1;
        player2 = pl2;
    }

};

//список для хранения информации о текущих играх
std::list<Game> GamesList;

//класс для хранения имён игроков в текущей игре и функций логики игры
class Rock_Paper_Scissors {

    std::string player1, player2, player;
    char key;

public:

    //Ввод имен игроков
    void playersnames(char* name1, char* name2) {
        player1 = name1;
        player2 = name2;
        std::cout << player1 << "  vs  " << player2 << std::endl;
    }
    int gameplay(char _key, int inputnumb, int round, char grid[2][3]) { //ход игры
        if (round <= 3 && grid[inputnumb-1][round]==NULL)
        {
            switch (_key) {
            case 'r':
                grid[inputnumb-1][round] = 'r';
                break;
            case 'p':
                grid[inputnumb - 1][round] = 'p';
                break;
            case 's':
                grid[inputnumb - 1][round] = 's';
                break;
            default:
                break;
            }
            if (inputnumb==1)
            {
                if (grid[1][round] != NULL) {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            if (inputnumb == 2)
            {
                if (grid[0][round] != NULL) {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }
        else
        {
            return -1;
        }

    }
    //Определение победителя
    int whowon(int inputnumb, char grid[2][3]) {
        int result = 0;
        int i;
        for (i = 0; i < 3; i++) {
            if (grid[0][i]!=NULL && grid[1][i] != NULL ) {
                if (grid[0][i] != grid[1][i])
                {
                    if (inputnumb == 1)
                    {
                        switch (grid[0][i])
                        {
                        case 'r':
                            switch (grid[1][i])
                            {
                            case 'p':
                                result--;
                                break;
                            case 's':
                                result++;
                                break;
                            default:
                                break;
                            }
                            break;
                        case 'p':
                            switch (grid[1][i])
                            {
                            case 's':
                                result--;
                                break;
                            case 'r':
                                result++;
                                break;
                            default:
                                break;
                            }
                            break;
                        case 's':
                            switch (grid[1][i])
                            {
                            case 'r':
                                result--;
                                break;
                            case 'p':
                                result++;
                                break;
                            default:
                                break;
                            }
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        switch (grid[1][i])
                        {
                        case 'r':
                            switch (grid[0][i])
                            {
                            case 'p':
                                result--;
                                break;
                            case 's':
                                result++;
                                break;
                            default:
                                break;
                            }
                            break;
                        case 'p':
                            switch (grid[0][i])
                            {
                            case 's':
                                result--;
                                break;
                            case 'r':
                                result++;
                                break;
                            default:
                                break;
                            }
                            break;
                        case 's':
                            switch (grid[0][i])
                            {
                            case 'r':
                                result--;
                                break;
                            case 'p':
                                result++;
                                break;
                            default:
                                break;
                            }
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
            else
            {
            i = 5;
            break;
            }
        }
        if (i != 5) {
            if (result > 0) {
                return 1;//win
            }
            if (result < 0) {
                return -1;//lose
            }
            if (result == 0) {
                return 0;//draw
            }
        }
        else return 3;
    }

};

//функция изменения статуса игрока с конкретным id
void change_status(int id, int stat) {
    std::list <Client>::iterator a;
    char name1[10];
    int reason_of_delete = 0;
    for (std::list <Client>::iterator element = ClientsList.begin(); element != ClientsList.end(); element++)
    {
        if ((*element).get_id() == id) {
            memset(name1, '\0', 10);
            strcpy(name1, (*element).get_name());
            (*element).~Client();
            a = element;
            reason_of_delete = 1;
        }

    }
    if (reason_of_delete == 1) {
        ClientsList.erase(a);
        Client new_client1;
        new_client1.Client_info(name1, id, stat);
        ClientsList.push_back(new_client1);
    }
}

//функция записи списка первой сотни свободных игроков на сервере для игрока с конкретным id
char* Delivery(int index) {
    char msg[2500] = { 0 };
    int id = 0;
    for (Client element : ClientsList)
    {
        if ((element).get_id() == index) {
            continue;
        }
        if (id < 101) {
            if ((element).get_status() == 1) {
                strcat(msg, (element).GetInfo());
                strcat(msg, "\n");
                id++;
            }
        }
        else {
            break;
        }
    }

    return msg;

}

//функция составления сообщения для игрока с конкретным id о текущем онлайне
void Build_msg(int index, char* msg) {
    memset(msg, '\0', sizeof(msg));
    strcpy(msg, "02");
    strcat(msg, Delivery(index));
    strcat(msg, "\n");
}

//функция оповещения всех свободных игроков, кроме игрока с конкретным id, об изменении списка игроков
void Updates(int index, int iResult) {
    char msg[2500] = { 0 };
    for (Connections element : ConnectionsList)
    {
        if ((element).get_index() == index) {
            continue;
        }
        if (iResult > 0) {
            for (Client client_element : ClientsList)
            {
                if ((client_element).get_id() == (element).get_index() && (client_element.get_status() == 1)) {
                    Build_msg((element).get_index(), msg);
                    (element).Send(msg, sizeof(msg));
                    break;
                }
            }
        }
    }
}


//функция для обмена сообщений между сервером и конкретным клиентом
int ClientHandler(int index) {
    char grid[2][3];//история игры на сервере
    int round = 0;//проверка раунда
    Rock_Paper_Scissors obj;//элемент игровой логики для игрока на сервере
    char key;//переменная для хранения хода игрока

    int num = 0;
    int apponent_num = 0;
    char name[10];
    char msg[2500] = { 0 };
    int iResult = 1;//переменная для проверки функционирования соединения клиента с сервером
    char code[3] = "";
    char id[5];
    int opponent = 0;//переменная для проверки функционирования соединения противника с сервером
    int reason_of_wait = 0;//переменная для проверки необходимости удаления элемента из списка ожиданий
    int reason_of_exit = 0;//переменная для проверки необходимости удаления элемента из списка игр
    int not_found = 1;//перемекнная для проверки отсутствия искомого элемента в списке клиентов
    std::string _id;//переменная для перевода числовых значений в строковые
    std::list <waiting>::iterator w;//переменная для поиска элемента в списке ожиданий
    std::list <Connections>::iterator c;//переменная для поиска элемента в списке соединений
    std::list <Game>::iterator g;//переменная для поиска элемента в списке игр
    std::list <Client>::iterator a;//переменная для поиска элемента в списке клиентов

    Client new_client;

    int opponent1 = 0;//переменная для проверки функционирования соединения игрока с сервером во время подключения к игре
    int opponent2 = 0;//переменная для проверки функционирования соединения противника с сервером во время подключения к игре

    while (iResult > 0) {
        iResult = (*Find_Connection(index)).Recv(msg, 25);//получение сообщения клиента
        strncpy(code, msg, 2);//определение кода операции
        switch (atoi(code))
        {
        case 1://код регистрации клиента
            strcpy(name, msg + 2);
            new_client.Client_info(name, index, 1);

            Build_msg(index, msg);
            iResult = (*Find_Connection(index)).Send(msg, 2500);

            ClientsList.push_back(new_client);
            std::cout << new_client.GetInfo() << " is registered" << std::endl;

            Updates(index, iResult);

            break;
        case 2://код запроса списка игроков
            Build_msg(index, msg);
            iResult = (*Find_Connection(index)).Send(msg, sizeof(msg));
            break;
        case 3://код приглашения игрока
            opponent = 0;
            strcpy(id, msg + 2);
            if (id[0] != '\0') {
                for (Client client_element : ClientsList)
                {
                    if ((client_element).get_id() != index) {


                        if ((client_element).get_id() == atoi(id) && client_element.get_status() == 1) {

                            memset(msg, '\0', sizeof(msg));
                            strcpy(msg, "13");
                            _id = std::to_string(index);
                            strcat(msg, _id.c_str());
                            opponent = (*Find_Connection(atoi(id))).Send(msg, sizeof(msg));
                            if (opponent <= 0) {
                                not_found = 1;
                            }
                            waiting wait(index, atoi(id));
                            WaitersList.push_back(wait);

                            break;
                        }
                        if ((client_element).get_id() == atoi(id) && client_element.get_status() == 0) {
                            (*Find_Connection(index)).Send(msg, sizeof(msg));
                            memset(id, '\0', 5);
                            not_found = 0;

                            break;
                        }
                        opponent = 0;
                    }
                }
                if (opponent > 0) {
                    change_status(index, 0);
                    change_status(atoi(id), 0);
                    Updates(index, iResult);
                }

                if (opponent <= 0) {
                    if (not_found == 1) {
                        memset(msg, '\0', sizeof(msg));
                        strcpy(msg, "03");
                        strcat(msg, id);
                        (*Find_Connection(index)).Send(msg, sizeof(msg));
                        memset(id, '\0', 5);
                    }
                    not_found = 1;
                }

                for (Client element : ClientsList)
                {
                    std::cout << element.GetInfo();

                }
            }


            break;
        case 23://код принятия приглашения 
            strcpy(id, msg + 2);
            memset(msg, '\0', sizeof(msg));
            strcpy(msg, "23");
            _id = std::to_string(index);
            strcat(msg, _id.c_str());

            for (Client client_element : ClientsList)
            {
                if ((client_element).get_id() == atoi(id)) {
                    opponent = (*Find_Connection(atoi(id))).Send(msg, sizeof(msg));
                }
            }
            if (!(WaitersList.empty())) {
                for (std::list <waiting>::iterator element = WaitersList.begin(); element != WaitersList.end(); element++) {
                    if ((*element).player == index) {
                        w = element;
                        reason_of_wait = 1;
                        break;
                    }
                }
                if (reason_of_wait == 1) {
                    WaitersList.erase(w);
                    reason_of_wait = 0;
                }
            }

            std::cout << id << "accepted" << std::endl;
            if (opponent > 0) {
                memset(msg, '\0', sizeof(msg));
                strcpy(msg, "23");
                strcat(msg, id);
                opponent = (*Find_Connection(index)).Send(msg, sizeof(msg));
                if (opponent <= 0) {
                    memset(msg, '\0', sizeof(msg));
                    strcpy(msg, "03");
                    strcat(msg, _id.c_str());
                    opponent = (*Find_Connection(atoi(id))).Send(msg, sizeof(msg));
                    change_status(atoi(id), 1);
                    Updates(atoi(id), iResult);
                }
                else
                {
                    goto start;
                }
            }
            else {
                memset(msg, '\0', sizeof(msg));
                strcpy(msg, "03");
                strcat(msg, id);
                opponent = (*Find_Connection(index)).Send(msg, sizeof(msg));

                change_status(index, 1);
                Updates(index, iResult);
            }
            break;

        case 33://код отказа на предложение
            opponent = 0;
            strcpy(id, msg + 2);
            memset(msg, '\0', sizeof(msg));
            strcpy(msg, "33");
            _id = std::to_string(index);
            strcat(msg, _id.c_str());
            for (Client client_element : ClientsList)
            {
                if ((client_element).get_id() == atoi(id)) {
                    opponent = (*Find_Connection(atoi(id))).Send(msg, sizeof(msg));
                }
            }
            change_status(index, 1);
            if (opponent > 0) {
                change_status(atoi(id), 1);
                opponent = 0;
            }
            for (Connections element : ConnectionsList)
            {
                if ((element).get_index() == index) {
                    Build_msg((element).get_index(), msg);
                    (element).Send(msg, sizeof(msg));
                    continue;
                }
                if (iResult > 0) {
                    for (Client client_element : ClientsList)
                    {
                        if ((client_element).get_id() == (element).get_index() && (client_element.get_status() == 1)) {
                            Build_msg((element).get_index(), msg);
                            (element).Send(msg, sizeof(msg));
                            break;
                        }
                    }
                }
            }

            break;

        start://подключение игроков к игре
            memset(msg, '\0', sizeof(msg));
            strcpy(msg, "04");

            opponent1 = (*Find_Connection(index)).Send(msg, sizeof(msg));

            memset(msg, '\0', sizeof(msg));
            strcpy(msg, "04");

            for (Client client_element : ClientsList)
            {
                if ((client_element).get_id() == atoi(id)) {
                    opponent2 = (*Find_Connection(atoi(id))).Send(msg, sizeof(msg));
                }
            }

            if (opponent1 > 0 && opponent2 > 0) {
                Game new_game(index, atoi(id));
                GamesList.push_back(new_game);
                opponent1 = 0;
                opponent2 = 0;
            }
            else {
                if (opponent1 > 0) {
                    memset(msg, '\0', sizeof(msg));
                    strcpy(msg, "03");
                    strcat(msg, id);
                    (*Find_Connection(index)).Send(msg, sizeof(msg));
                    change_status(index, 1);
                    Updates(index, iResult);
                    opponent1 = 0;
                }
                if (opponent2 > 0) {
                    memset(msg, '\0', sizeof(msg));
                    strcpy(msg, "03");
                    _id = std::to_string(index);
                    strcat(msg, _id.c_str());
                    (*Find_Connection(atoi(id))).Send(msg, sizeof(msg));
                    change_status(atoi(id), 1);
                    Updates(atoi(id), iResult);
                    opponent2 = 0;
                }
            }
            break;
        case 4://запрос об очерёдности игроков
            if (!(GamesList.empty())) {
                for (std::list <Game>::iterator game_element = GamesList.begin(); game_element != GamesList.end(); game_element++) {
                    if ((*game_element).player1 == index) {
                        if (round == 0) {
                            obj.playersnames((*Find_Client(index)).get_name(), (*Find_Client((*game_element).player2)).get_name());
                            num = 1;
                        }
                        break;
                    }
                    if ((*game_element).player2 == index) {
                        if (round == 0) {
                            obj.playersnames((*Find_Client(index)).get_name(), (*Find_Client((*game_element).player1)).get_name());
                            num = 2;
                        }
                        break;
                    }
                }
            }
            break;
        case 44://ход игрока
            key = msg[2];
            if (key != '\0') {
                if (!(GamesList.empty())) {
                    for (std::list <Game>::iterator game_element = GamesList.begin(); game_element != GamesList.end(); game_element++) {
                        if ((*game_element).player1 == index || (*game_element).player2 == index) {
                            switch (obj.gameplay(key, num, round,grid)) {
                            case 0://первым сходил
                                memset(msg, '\0', sizeof(msg));
                                strcpy(msg, "06");//обновить противнику инфу на сервере
                                _id = key;
                                strcat(msg, _id.c_str());
                                if ((*game_element).player1 == index) {
                                    (*Find_Connection((*game_element).player2)).Send(msg, sizeof(msg));
                                }
                                if ((*game_element).player2 == index) {
                                    (*Find_Connection((*game_element).player1)).Send(msg, sizeof(msg));
                                }
                                break;
                            case 1://вторым сходил
                                if ((*game_element).player1 == index) {
                                    (*Find_Connection((*game_element).player2)).Send(msg, sizeof(msg));
                                }
                                if ((*game_element).player2 == index) {
                                    (*Find_Connection((*game_element).player1)).Send(msg, sizeof(msg));
                                }
                                memset(msg, '\0', sizeof(msg));
                                strcpy(msg, "07");
                                if (num==1)
                                {
                                    _id = grid[1][round];
                                }
                                else
                                {
                                    _id = grid[0][round];
                                }
                                strcat(msg, _id.c_str());
                                (*Find_Connection(index)).Send(msg, sizeof(msg));
                                round++;

                                switch (obj.whowon(num, grid)) {
                                case 1:
                                    memset(msg, '\0', sizeof(msg));
                                    strcpy(msg, "54");
                                    (*Find_Connection(index)).Send(msg, sizeof(msg));
                                    memset(msg, '\0', sizeof(msg));
                                    strcpy(msg, "64");
                                    if ((*game_element).player1 == index) {
                                        (*Find_Connection((*game_element).player2)).Send(msg, sizeof(msg));
                                    }
                                    if ((*game_element).player2 == index) {
                                        (*Find_Connection((*game_element).player1)).Send(msg, sizeof(msg));
                                    }
                                    std::cout << "win";
                                    reason_of_exit = 1;
                                    g = game_element;

                                    break;
                                case -1:
                                    memset(msg, '\0', sizeof(msg));
                                    strcpy(msg, "64");
                                    (*Find_Connection(index)).Send(msg, sizeof(msg));
                                    memset(msg, '\0', sizeof(msg));
                                    strcpy(msg, "54");
                                    if ((*game_element).player1 == index) {
                                        (*Find_Connection((*game_element).player2)).Send(msg, sizeof(msg));
                                    }
                                    if ((*game_element).player2 == index) {
                                        (*Find_Connection((*game_element).player1)).Send(msg, sizeof(msg));
                                    }

                                    reason_of_exit = 1;
                                    g = game_element;

                                    break;
                                case 0:
                                    memset(msg, '\0', sizeof(msg));
                                    strcpy(msg, "94");
                                    (*Find_Connection(index)).Send(msg, sizeof(msg));
                                    if ((*game_element).player1 == index) {
                                        (*Find_Connection((*game_element).player2)).Send(msg, sizeof(msg));
                                    }
                                    if ((*game_element).player2 == index) {
                                        (*Find_Connection((*game_element).player1)).Send(msg, sizeof(msg));
                                    }

                                    reason_of_exit = 1;
                                    g = game_element;
                                    break;
                                case 3:
                                    break;
                                }
                                break;
                            case -1://уже сходил
                                memset(msg, '\0', sizeof(msg));
                                strcpy(msg, "24");
                                (*Find_Connection(index)).Send(msg, sizeof(msg));
                                break;
                            };
                            break;
                        }
                    }

                    if (reason_of_exit == 1) {
                        GamesList.erase(g);
                        reason_of_exit = 0;
                    }
                }
            }
            break;
        case 74://код обновления поля игрока после полученного хода аппонента на сервере
            key = msg[2];

            if (num==1)
            {
                apponent_num = 2;
            }
            else
            {
                apponent_num = 1;
            }

            grid[apponent_num-1][round] = key;
            if (grid[num-1][round] != NULL) {
                round++;
            }
            break;

        case 84://код сообщения об завершении игры и перехода к списку игроков
            for (int i = 0; i < 2; i++)           //очистка значений для повторной игры
                for (int j = 0; j < 3; j++)
                {
                    grid[i][j] = NULL;
                }
            round = 0;
            change_status(index, 1);
            Build_msg(index, msg);
            iResult = (*Find_Connection(index)).Send(msg, 2500);
            Updates(index, iResult);
            break;
        default:
            break;


        }
    }

    //удаление клиента с конкретным id
    for (std::list <Client>::iterator element = ClientsList.begin(); element != ClientsList.end(); element++) {
        if ((*element).get_id() == index) {
            a = element;
            break;
        }
    }
    ClientsList.erase(a);

    //удаление соединения с конкретным номером и оповещение об изменении других свободных игроков
    int exception = 0;
    for (std::list <Connections>::iterator element = ConnectionsList.begin(); element != ConnectionsList.end(); element++)
    {
        if ((*element).get_index() == index) {
            c = element;
            if (!(WaitersList.empty())) {
                for (std::list <waiting>::iterator wait_element = WaitersList.begin(); wait_element != WaitersList.end(); wait_element++) {
                    if ((*wait_element).player == index) {

                        change_status((*wait_element).waiter, 1);
                        w = wait_element;
                        reason_of_wait = 1;
                        exception = (*wait_element).waiter;
                        break;
                    }
                    if ((*wait_element).waiter == index) {
                        w = wait_element;
                        reason_of_wait = 1;
                        break;
                    }
                }
                if (reason_of_wait == 1) {
                    WaitersList.erase(w);
                    if (exception != 0) {
                        reason_of_wait = 2;
                    }
                    else
                    {
                        reason_of_wait = 0;
                    }
                }

            }
            if (!(GamesList.empty())) {
                for (std::list <Game>::iterator game_element = GamesList.begin(); game_element != GamesList.end(); game_element++) {
                    if ((*game_element).player1 == index) {

                        change_status((*game_element).player2, 1);
                        g = game_element;
                        reason_of_exit = 1;
                        exception = (*game_element).player2;
                        break;
                    }
                    if ((*game_element).player2 == index) {

                        change_status((*game_element).player1, 1);
                        g = game_element;
                        reason_of_exit = 1;
                        exception = (*game_element).player1;
                        break;
                    }
                }
                if (reason_of_exit == 1) {
                    GamesList.erase(g);
                    reason_of_exit = 2;
                }

            }
            continue;
        }

        for (Client client_element : ClientsList)
        {
            if ((client_element).get_id() == (*element).get_index() && (client_element.get_status() == 1)) {
                if ((client_element).get_id() != exception) {
                    Build_msg((*element).get_index(), msg);
                    (*element).Send(msg, sizeof(msg));
                    break;
                }
            }
        }
    }
    ConnectionsList.erase(c);

    //оповещение игрока, находящегося в игре с конкретным игроком либо ожидающий ответа на приглашение 
    if (reason_of_exit == 2 || reason_of_wait == 2) {
        memset(msg, '\0', sizeof(msg));
        strcpy(msg, "03");
        _id = std::to_string(index);
        strcat(msg, _id.c_str());
        for (Client client_element : ClientsList)
        {
            if ((client_element).get_id() == exception) {
                (*Find_Connection(exception)).Send(msg, sizeof(msg));
            }
        }
    }

    //закрытие потока
    GetExitCodeThread;
    return 0;
}


int main()
{
    std::string ip;
    std::cout << "server_ip: ";
    std::cin >> ip;

    //создание сервера
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0)
    {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    //подключение клиентов к серверу
    while (true) {
        newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

        if (newConnection == 0) {
            std::cout << "Error 2" << std::endl;
        }
        else {
            Connections NewConnection;
            NewConnection.Connections_info(Counter, newConnection);
            ConnectionsList.push_back(NewConnection);

            std::cout << "Client " << Counter << " Connected\n";
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(Counter), NULL, NULL);
            Counter++;
        }
    }

    system("pause");
    return 0;


}
