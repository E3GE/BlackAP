#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define NB_DECK 6
#define MISE_MIN 1
#define MISE_MAX 100
#define AUTO 1
#define NB_PARTIE 1000
#define NB_MONEY 1000

#define KING 1
#define QUEEN 2
#define JACK 3
#define TEN 4
#define NINE 5
#define HEIGHT 6
#define SEVEN 7
#define SIX 8
#define FIVE 9
#define FOUR 10
#define THREE 11
#define TWO 12
#define ACE 13

using namespace std;

HANDLE  hConsole;

int main();
void stats();
void win();
void loose();
int autochoose();
void fuif01();
int tirerAs(int player);
void miser(int &mise, int &money);
int tirer(int &totalcards, int &card, int &king, int &queen,
          int &jack, int &ten, int &nine,
          int &height, int &seven, int &six, int &five, int &four,
          int &three, int &two, int &ace, int player );

int money = NB_MONEY;
int mise = 0;
int card = 0;
int totalcards = 52 * NB_DECK;
int pts_player = 0;
int p_ace = 0;
int c_ace = 0;
int c_ace_use = 0;
int pts_banque = 0;
int choix = -1;
bool first = 1;
int hi_lo = 0;
int out = 0;
int c_out = 0;
int mise_before = 0;


int act =0;
int aup = 0;


/***** STAT ******/
int nb_round = 0;
int nb_win = 0;
int nb_null = 0;
int loose_cons = 0;
int tmp_loose_cons = 0;
int tmp_win_cons = 0;
int win_cons = 0;
int bj = 0;
int win_x_time = 0;
int loose_x_time = 0;

int king = 4 * NB_DECK;
int queen = 4 * NB_DECK;
int jack = 4 * NB_DECK;
int ten = 4 * NB_DECK;
int nine = 4 * NB_DECK;
int height = 4 * NB_DECK;
int seven = 4 * NB_DECK;
int six = 4 * NB_DECK;
int five = 4 * NB_DECK;
int four = 4 * NB_DECK;
int three = 4 * NB_DECK;
int two = 4 * NB_DECK;
int ace = 4 * NB_DECK;

int main()
{
    if(first)
    {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        srand(time(NULL));
        first = 0;
    }

    if(totalcards <= 10)
    {
        if(!AUTO)
        {
            cout << endl << "********************************************************************************" << endl;
            cout << endl << " Le sabot est presque vide ! On melange les cartes et hop le sabot est remplie !" << endl;
            cout << endl << "********************************************************************************" << endl;
        }

        hi_lo = 0;
        totalcards = 52 * NB_DECK;
        king = 4 * NB_DECK;
        queen = 4 * NB_DECK;
        jack = 4 * NB_DECK;
        ten = 4 * NB_DECK;
        nine = 4 * NB_DECK;
        height = 4 * NB_DECK;
        seven = 4 * NB_DECK;
        six = 4 * NB_DECK;
        five = 4 * NB_DECK;
        four = 4 * NB_DECK;
        three = 4 * NB_DECK;
        two = 4 * NB_DECK;
        ace = 4 * NB_DECK;
        hi_lo = 0;
    }

    choix = -1;
    pts_banque = 0;
    pts_player = 0;
    mise = 0;
    card = 0;
    p_ace = 0;
    c_ace = 0;
    c_ace_use = 0;

    cout << "Partie n " << nb_round+ nb_null << "..." << endl;

    if(!AUTO)
        cout << "*********************************   BlackAP   **********************************" << endl << endl;

    if(AUTO)
        fuif01();

    else
        miser(mise, money);


    if(!AUTO)
    {
        cout << "********************************************************************************" << endl;
        cout << " 1ere carte joueur : ";
    }

    pts_player = tirer(totalcards,card,king,queen,jack,ten,nine,height,seven,six,five,four,three,two,ace,1);
    if(!AUTO)
        cout << endl << " 1ere carte croupier : ";
    pts_banque = tirer(totalcards,card,king,queen,jack,ten,nine,height,seven,six,five,four,three,two,ace,0);
    if(!AUTO)
        cout << endl << " 2eme carte joueur : ";
    pts_player += tirer(totalcards,card,king,queen,jack,ten,nine,height,seven,six,five,four,three,two,ace,1);

    if(!AUTO)
        cout << endl << endl << " (hi-lo : " << hi_lo << ")" << endl;

    /********************** GESTION DES AS ***************************************/
    if(p_ace != 0 && pts_player +10 <= 21 && !AUTO)
        cout << endl << " Total joueur : " << pts_player << "/" << pts_player +10 << endl << endl;
    else
    {
        if(!AUTO)
            cout << endl << " Total joueur : " << pts_player << endl << endl;
    }

    if(!AUTO)
        cout << "********************************************************************************" << endl;

    /********************** BJ ? ***********************/
    ///si le joueur a black jack
    if( pts_player == 21 || p_ace != 0 && pts_player +10 == 21)
    {
        /// si le croupier n'a pas d'as ou de bûche
        if(c_ace == 0 || pts_banque < 10 && pts_banque > 1)
        {
            if(!AUTO)
                cout << " BlackJack ! Vous avez remportez " << (int)(mise *1.5) << "e" << endl;
            money += (int)(mise *1.5);
            if(!AUTO)
                cout << " Appuyez sur une touche pour continuer..";

            if (!AUTO)
                getch();
            system("CLS");
            nb_round ++;
            nb_win ++;
            bj++;
            /****** CALCUL DEFEAT ******/
            if(tmp_loose_cons > loose_cons)
                loose_cons = tmp_loose_cons;
            tmp_loose_cons = 0;
            /***************************/
            /****** CALCUL Victoire ******/
            tmp_win_cons ++;
            if(tmp_win_cons > win_cons)
                win_cons = tmp_win_cons;
            /***************************/
            win();

            main();

        }
        else
        {
            if(!AUTO)
                cout << endl << " 2eme carte croupier : ";
            pts_banque += tirer(totalcards,card,king,queen,jack,ten,nine,height,seven,six,five,four,three,two,ace,0);

            if(c_ace != 0 && pts_banque +10 <= 21 && !AUTO)
                cout << " (Total : " << pts_banque << "/" << pts_banque +10 << ")" << endl;
            else
            {
                if(!AUTO)
                    cout << " (Total : " << pts_banque << ")" << endl;
            }


            if(c_ace == 1 && pts_banque +10 == 21)
            {
                if(!AUTO)
                    cout << " egalite ! Vous avez recuperer " << mise << "e" << endl;
                money += mise;
                if(!AUTO)
                    cout << " Appuyez sur une touche pour continuer..";
                if (!AUTO)
                    _getch();
                system("CLS");
                nb_null ++;
                main();
            }
            else
            {
                if(!AUTO)
                    cout << " BlackJack ! Vous avez remportez " << (int)(mise *1.5) << "e" << endl;
                money += (int)(mise *1.5);
                if(!AUTO)
                    cout << " Appuyez sur une touche pour continuer..";
                if (!AUTO)
                    getch();
                system("CLS");
                nb_round ++;
                nb_win ++;
                bj++;
                /****** CALCUL DEFEAT ******/
                if(tmp_loose_cons > loose_cons)
                    loose_cons = tmp_loose_cons;
                tmp_loose_cons = 0;
                /***************************/
                /****** CALCUL Victoire ******/
                tmp_win_cons ++;
                if(tmp_win_cons > win_cons)
                    win_cons = tmp_win_cons;
                /***************************/
                win();
                main();
            }
        }
    }

    /************ CHOIX DU JOUEUR *****************/
    while(choix != 0)
    {
        if(!AUTO)
            cout << " Appuyez sur 1 pour tirer, 2 pour doubler, 0 pour rester" << endl;
        if(!AUTO)
            cout << " Choix : ";
        if(!AUTO)
            cin >> choix;
        else
            choix = autochoose();
        if(!AUTO)
            cout << endl;

        ///Si on reste
        if (choix == 0)
        {
            /***************** GESTION DES AS *********************/
            if(p_ace != 0 && pts_player +10 <= 21)
                pts_player += 10;

            while( pts_banque < 17)
            {

                if(pts_banque > 21 && c_ace_use == 1)
                {
                    pts_banque -= 10;
                    c_ace_use = 0;
                }

                if(!AUTO)
                    cout << " Carte croupier : ";
                pts_banque += tirer(totalcards,card,king,queen,jack,ten,nine,height,seven,six,five,four,three,two,ace,0);

                if(c_ace != 0 && pts_banque +10 <= 21 && !AUTO)
                    cout << " (Total : " << pts_banque << "/" << pts_banque +10 << ")" << endl;
                else
                {
                    if(!AUTO)
                        cout << " (Total : " << pts_banque << ")" << endl;
                }


                if(c_ace != 0 && pts_banque +10 <= 21 && pts_banque+10 >= pts_player && pts_banque+10 >= 11)
                {
                    pts_banque += 10;
                    c_ace_use = 1;
                }

            }
            if(!AUTO)
                cout << endl << "********************************************************************************" << endl;
            if(pts_banque > 21)
            {
                c_out ++;
                if(!AUTO)
                    cout << " Gagne ! Vous remportez " << mise *2 << "e" << endl;
                money += mise *2;
                if(!AUTO)
                    cout << " Appuyez sur une touche pour continuer..";
                if (!AUTO)
                    _getch();
                system("CLS");
                nb_round ++;
                nb_win ++;
                /****** CALCUL DEFEAT ******/
                if(tmp_loose_cons > loose_cons)
                    loose_cons = tmp_loose_cons;
                tmp_loose_cons = 0;
                /***************************/
                /****** CALCUL Victoire ******/
                tmp_win_cons ++;
                if(tmp_win_cons > win_cons)
                    win_cons = tmp_win_cons;
                /***************************/
                win();
                main();
            }
            else if (pts_banque == pts_player)
            {
                if(!AUTO)
                    cout << " egalite ! Vous avez recuperer " << mise << "e" << endl;
                money += mise;
                if(!AUTO)
                    cout << " Appuyez sur une touche pour continuer..";
                if (!AUTO)
                    _getch();
                system("CLS");
                nb_null++;
                main();
            }
            else if ( pts_banque > 16 && pts_banque < pts_player)
            {
                if(!AUTO)
                    cout << " Gagne ! Vous remportez " << mise *2 << "e" << endl;
                money += mise *2;
                if(!AUTO)
                    cout << " Appuyez sur une touche pour continuer..";
                if (!AUTO)
                    _getch();
                system("CLS");
                nb_round ++;
                nb_win ++;
                /****** CALCUL DEFEAT ******/
                if(tmp_loose_cons > loose_cons)
                    loose_cons = tmp_loose_cons;
                tmp_loose_cons = 0;
                /***************************/
                /****** CALCUL Victoire ******/
                tmp_win_cons ++;
                if(tmp_win_cons > win_cons)
                    win_cons = tmp_win_cons;
                /***************************/
                win();
                main();
            }
            else
            {
                if(!AUTO)
                {
                    cout  << " Dommage ! Vous avez perdu " << mise << "e" << endl;
                    cout << " Appuyez sur une touche pour continuer..";
                }

                if (!AUTO)
                    _getch();
                system("CLS");
                nb_round ++;
                /********* defeat cons *******/
                tmp_loose_cons ++;
                if (tmp_loose_cons > loose_cons)
                    loose_cons = tmp_loose_cons;
                /********************************/
                /****** CALCUL Victoire ******/
                if(tmp_win_cons > win_cons)
                    win_cons = tmp_win_cons;
                tmp_win_cons = 0;
                /***************************/
                loose();
                main();
            }
        }

        ///Si on tire
        if (choix == 1)
        {
            if(!AUTO)
                cout << " Carte joueur : ";
            pts_player += tirer(totalcards,card,king,queen,jack,ten,nine,height,seven,six,five,four,three,two,ace,1);

            if(p_ace != 0 && pts_player + 10 <= 21)
            {
                if(!AUTO)
                    cout << " (Total "<< pts_player  << "/" << pts_player +10  << ")" << endl;
            }
            else
            {
                if(!AUTO)
                    cout << " (Total "<< pts_player  << ")" << endl;
            }

            if( pts_player > 21)
            {
                out ++;
                if(!AUTO)
                {
                    cout << " Dommage ! Vous avez perdu " << mise << "e" << endl;
                    cout << " Appuyez sur une touche pour continuer..";
                }

                if (!AUTO)
                    _getch();
                system("CLS");
                nb_round ++;
                /********* defeat cons *******/
                tmp_loose_cons ++;
                if (tmp_loose_cons > loose_cons)
                    loose_cons = tmp_loose_cons;
                /********************************/
                /****** CALCUL Victoire ******/
                if(tmp_win_cons > win_cons)
                    win_cons = tmp_win_cons;
                tmp_win_cons = 0;
                /***************************/
                loose();
                main();
            }

        }

        ///si on double
        if(choix == 2)
        {
            /// on regarde si le joueur peut doubler
            if(money - mise >= 0)
            {
                money -= mise;
                mise*= 2;
            }

            if(!AUTO)
                cout << " Carte joueur : ";
            pts_player += tirer(totalcards,card,king,queen,jack,ten,nine,height,seven,six,five,four,three,two,ace,1);

            if(p_ace != 0 && pts_player + 10 <= 21)
            {
                if(!AUTO)
                    cout << " (Total "<< pts_player  << "/" << pts_player +10  << ")" << endl;
            }
            else
            {
                if(!AUTO)
                    cout << " (Total "<< pts_player  << ")" << endl;
            }

            /***************** GESTION DES AS *********************/
            if(p_ace != 0 && pts_player +10 <= 21)
                pts_player += 10;

            while( pts_banque < 17)
            {

                if(pts_banque > 21 && c_ace_use == 1)
                {
                    pts_banque -= 10;
                    c_ace_use = 0;
                }

                if( pts_player > 21)
                {
                    if(!AUTO)
                    {
                        cout << " Dommage ! Vous avez perdu " << mise << "e" << endl;
                        cout << " Appuyez sur une touche pour continuer..";
                    }

                    if (!AUTO)
                        _getch();
                    system("CLS");
                    nb_round ++;
                    /********* defeat cons *******/
                    tmp_loose_cons ++;
                    if (tmp_loose_cons > loose_cons)
                        loose_cons = tmp_loose_cons;
                    /********************************/
                    /****** CALCUL Victoire ******/
                    if(tmp_win_cons > win_cons)
                        win_cons = tmp_win_cons;
                    tmp_win_cons = 0;
                    /***************************/
                    loose();
                    main();
                }

                if(!AUTO)
                    cout << " Carte croupier : ";
                pts_banque += tirer(totalcards,card,king,queen,jack,ten,nine,height,seven,six,five,four,three,two,ace,0);

                if(c_ace != 0 && pts_banque +10 <= 21 && !AUTO)
                    cout << " (Total : " << pts_banque << "/" << pts_banque +10 << ")" << endl;
                else
                {
                    if(!AUTO)
                        cout << " (Total : " << pts_banque << ")" << endl;
                }


                if(c_ace != 0 && pts_banque +10 <= 21 && pts_banque+10 >= pts_player && pts_banque+10 >= 11)
                {
                    pts_banque += 10;
                    c_ace_use = 1;
                }

            }
            if(!AUTO)
                cout << endl << "********************************************************************************" << endl;
            if(pts_banque > 21)
            {
                if(!AUTO)
                    cout << " Gagne ! Vous remportez " << mise *2 << "e" << endl;
                money += mise *2;
                if(!AUTO)
                    cout << " Appuyez sur une touche pour continuer..";
                if (!AUTO)
                    _getch();
                system("CLS");
                nb_round ++;
                nb_win ++;
                /****** CALCUL DEFEAT ******/
                if(tmp_loose_cons > loose_cons)
                    loose_cons = tmp_loose_cons;
                tmp_loose_cons = 0;
                /***************************/
                /****** CALCUL Victoire ******/
                tmp_win_cons ++;
                if(tmp_win_cons > win_cons)
                    win_cons = tmp_win_cons;

                /***************************/
                win();
                main();
            }
            else if (pts_banque == pts_player)
            {
                if(!AUTO)
                    cout << " egalite ! Vous avez recuperer " << mise << "e" << endl;
                money += mise;
                if(!AUTO)
                    cout << " Appuyez sur une touche pour continuer..";
                if (!AUTO)
                    _getch();
                system("CLS");
                nb_round ++;
                main();
            }
            else if ( pts_banque > 16 && pts_banque < pts_player)
            {
                if(!AUTO)
                    cout << " Gagne ! Vous remportez " << mise *2 << "e" << endl;
                money += mise *2;
                if(!AUTO)
                    cout << " Appuyez sur une touche pour continuer..";
                if (!AUTO)
                    _getch();
                system("CLS");
                nb_round ++;
                nb_win ++;
                /****** CALCUL DEFEAT ******/
                if(tmp_loose_cons > loose_cons)
                    loose_cons = tmp_loose_cons;
                tmp_loose_cons = 0;
                /***************************/
                /****** CALCUL Victoire ******/
                tmp_win_cons ++;
                if(tmp_win_cons > win_cons)
                    win_cons = tmp_win_cons;

                /***************************/
                win();
                main();
            }
            else
            {
                if(!AUTO)
                {
                    cout  << " Dommage ! Vous avez perdu " << mise << "e" << endl;
                    cout << " Appuyez sur une touche pour continuer..";
                }

                if (!AUTO)
                    _getch();
                system("CLS");
                nb_round ++;
                /********* defeat cons *******/
                tmp_loose_cons ++;
                if (tmp_loose_cons > loose_cons)
                    loose_cons = tmp_loose_cons;
                /********************************/
                /****** CALCUL Victoire ******/
                if(tmp_win_cons > win_cons)
                    win_cons = tmp_win_cons;
                tmp_win_cons = 0;

                /***************************/
                loose();
                main();
            }
        }
    }
    return 0;
}

void miser(int &mise, int &money)
{

    cout << " Solde : " << money << "e" << endl;
    cout << endl;
    cout << " Mise min : " << MISE_MIN << "e" << endl;
    cout << " Mise max : " << MISE_MAX << "e" << endl;
    cout << endl << " Mise : ";
    cin >> mise;

    if(mise == -1)
    {
        stats();
    }

    if(mise < MISE_MIN || MISE_MAX > 100)
    {
        system("CLS");
        cout << " La mise doit etre entre 1e et 100e" << endl << endl;
        miser(mise,money);
    }
    else
    {
        system("CLS");
        money -= mise;
        cout << endl << " Mise : " << mise << "e                  Sabot : " << totalcards << " cartes                  Solde : " << money << "e" << endl << endl;
    }
}



int tirer(int &totalcards, int &card, int &king, int &queen,
          int &jack, int &ten, int &nine,
          int &height, int &seven, int &six, int &five, int &four,
          int &three, int &two, int &ace, int player)
{
    int tmp_totalcards = totalcards;
    while(totalcards == tmp_totalcards)
    {
        card = rand()%(13-0) +0;
        switch(card)
        {
        case KING:
            if(king > 0)
            {
                if(!AUTO)
                    cout << "Roi";
                king-= 1;
                totalcards --;
                hi_lo --;
                return 10;
            }
            break;
        case QUEEN:
            if(queen > 0)
            {
                if(!AUTO)
                    cout << "Dame";
                queen-= 1;
                totalcards --;
                hi_lo --;
                return 10;
            }
            break;
        case JACK:
            if(jack > 0)
            {
                if(!AUTO)
                    cout << "Valet";
                jack-= 1;
                totalcards --;
                hi_lo --;
                return 10;
            }
            break;
        case TEN:
            if(ten > 0)
            {
                if(!AUTO)
                    cout << "10";
                ten-= 1;
                totalcards --;
                hi_lo --;
                return 10;
            }
            break;
        case NINE:
            if(nine > 0)
            {
                if(!AUTO)
                    cout << "9";
                nine-= 1;
                totalcards --;
                return 9;
            }
            break;
        case HEIGHT:
            if(height > 0)
            {
                if(!AUTO)
                    cout << "8";
                height-= 1;
                totalcards --;
                return 8;
            }
            break;
        case SEVEN:
            if(seven > 0)
            {
                if(!AUTO)
                    cout << "7";
                seven-= 1;
                totalcards --;
                return 7;
            }
            break;
        case SIX:
            if(six > 0)
            {
                if(!AUTO)
                    cout << "6";
                six-= 1;
                totalcards --;
                hi_lo ++;
                return 6;
            }
            break;
        case FIVE:
            if(five > 0)
            {
                if(!AUTO)
                    cout << "5";
                five-= 1;
                totalcards --;
                hi_lo ++;
                return 5;
            }
            break;
        case FOUR:
            if(four > 0)
            {
                if(!AUTO)
                    cout << "4";
                four-= 1;
                totalcards --;
                hi_lo ++;
                return 4;
            }
            break;
        case THREE:
            if(three > 0)
            {
                if(!AUTO)
                    cout << "3";
                three-= 1;
                totalcards --;
                hi_lo ++;
                return 3;
            }
            break;
        case TWO:
            if(two > 0)
            {
                if(!AUTO)
                    cout << "2";
                two-= 1;
                totalcards --;
                hi_lo ++;
                return 2;
            }
            break;
        default:
            if(ACE > 0)
            {
                if(!AUTO)
                    cout << "As";
                ace-= 1;
                totalcards --;

                if(player == 1)
                    p_ace ++;
                else
                    c_ace ++;

                hi_lo --;
                return 1;
            }
            break;
        }
    }
}

int tirerAs(int player)
{
    if(!AUTO)
        cout << "As";
    ace-= 1;
    totalcards --;
    if(player == 1)
        p_ace ++;
    else
        c_ace ++;
    return 1;
}

void stats()
{
    system("CLS");
    cout << endl;

    cout << " Nombre de parties joues : ";
    SetConsoleTextAttribute(hConsole, 6);
    cout << nb_null + nb_round << endl;

    SetConsoleTextAttribute(hConsole, 7);
    cout << " Nombre de parties gagnes : ";
    SetConsoleTextAttribute(hConsole, 2);
    cout << nb_win << endl;

    SetConsoleTextAttribute(hConsole, 7);
    cout << " Nombre de parties perdus : ";
    SetConsoleTextAttribute(hConsole, 4);
    cout << nb_round - nb_win << endl;

    SetConsoleTextAttribute(hConsole, 7);
    cout << " Nombre de parties nulles : ";
    SetConsoleTextAttribute(hConsole, 6);
    cout << nb_null << endl;

    SetConsoleTextAttribute(hConsole, 7);
    cout << " Nombre de defaites consecutives  : " ;
    SetConsoleTextAttribute(hConsole, 4);
    cout << loose_cons << endl;

    SetConsoleTextAttribute(hConsole, 7);
    cout << " Nombre de victoires consecutives  : " ;
    SetConsoleTextAttribute(hConsole, 2);
    cout << win_cons << endl;

    SetConsoleTextAttribute(hConsole, 7);
    cout << " Nombre de BlackJack  : ";
    SetConsoleTextAttribute(hConsole, 2);
    cout << bj << endl;

    SetConsoleTextAttribute(hConsole, 7);

    cout << " Argent depart  : " << NB_MONEY << "e" << endl;
    cout << " Argent fin  : ";

    if(money < NB_MONEY)
        SetConsoleTextAttribute(hConsole, 4);
    else if (money > NB_MONEY)
        SetConsoleTextAttribute(hConsole, 2);
    else
        SetConsoleTextAttribute(hConsole, 6);

    cout << money << "e" << endl;

    SetConsoleTextAttribute(hConsole, 7);

    cout << " Argent gagne : ";
    if(money - NB_MONEY < 0)
        SetConsoleTextAttribute(hConsole, 4);
    else if (money - NB_MONEY > 0)
        SetConsoleTextAttribute(hConsole, 2);
    else
        SetConsoleTextAttribute(hConsole, 6);
    cout << money - NB_MONEY << "e" << endl;
    SetConsoleTextAttribute(hConsole, 7);


    cout << " 3 victoires consecutives : " << win_x_time << endl;
    cout << " 3 defaites consecutives : " << loose_x_time << endl;

    cout << " Joueur > 21 : " << out << endl;
    cout << " Croupier > 21 : " << c_out << endl;

    if(nb_round != 0)
    {
        cout << " Pourcentage de victoire : " << (nb_win* 100)/nb_round << "%" << endl;
        cout << " Pourcentage de parties nulles : " << (nb_null* 100)/nb_round << "%" << endl;

        SetConsoleTextAttribute(hConsole, 7);
        cout << " Pourcentage de BJ : " ;
        SetConsoleTextAttribute(hConsole, 2);
        cout << (bj * 100)/nb_round << "%" << endl;

        SetConsoleTextAttribute(hConsole, 7);
        cout << " Variation d'argent : " ;
        if(money - NB_MONEY < 0)
            SetConsoleTextAttribute(hConsole, 4);
        else if (money - NB_MONEY > 0)
            SetConsoleTextAttribute(hConsole, 2);
        else
            SetConsoleTextAttribute(hConsole, 6);
        cout << (double)(money - NB_MONEY )/NB_MONEY*100 << "%" << endl;
        SetConsoleTextAttribute(hConsole, 7);
    }


    cout << endl << " Appuyez sur une touche pour continuer.." ;
    _getch();
    system("CLS");

}

void fuif01()
{

    if(!tmp_loose_cons)
        mise = 5;
    else if(tmp_loose_cons == 1)
        mise = 5;
    else if(tmp_loose_cons == 2)
        mise = 5;
    else if (tmp_loose_cons == 3)
        mise = 15;
    else if (tmp_loose_cons == 4)
        mise = 40;
    else if (tmp_loose_cons == 5)
        mise = 100;
    else if (tmp_loose_cons == 6)
        mise = 250;
    else if (tmp_loose_cons == 7)
        mise = 500;
    else if (tmp_loose_cons == 8)
        mise = 5;
    else if (tmp_loose_cons== 9)
        mise = 5;
    else if (tmp_loose_cons== 10)
        mise = 5;

    else
        mise = 5;


    if(money <= 0)
        stats();

    money -= mise;


    // 1 1 1

    /*if(tmp_loose_cons < nuberOfOne)
        mise = 1;
    else if (tmp_loose_cons == nuberOfOne)
        mise = 25;
    else if (tmp_loose_cons == nuberOfOne+1)
        mise = 50;
    else if (tmp_loose_cons == nuberOfOne+2)
        mise = 100;
    else
        mise = 25;

    if(money - mise < 0)
        stats();
    else
    {
        money -= mise;
        mise_before = mise;
    }*/

    if(nb_round + nb_null >= NB_PARTIE)
        stats();
}

int autochoose()
{
    /// Si le joueur possède 17 ou +
    if(pts_player >= 17)
        return 0;
    else if (pts_player >= 12 && pts_player <= 16 && pts_banque > 6 || p_ace != 0)
        return 1;
    else if (pts_player >= 12 && pts_player <= 16 && pts_banque < 7)
    {
        if(pts_player == 12 && pts_banque == 2 || pts_banque == 3)
            return 1;
        else
            return 0;
    }
    else if (pts_player == 11 || pts_player == 10 && pts_banque < 10)
        return 2;
    else if (pts_player == 11 || pts_player == 10 && pts_banque > 9 || p_ace != 0)
        return 1;
    else if (pts_player == 9  && pts_banque == 2 || pts_banque > 6 || p_ace != 0)
        return 1;
    else if (pts_player == 9 && pts_banque > 2 && pts_banque < 7)
        return 2;
    else if (pts_player >= 2 && pts_player < 9)
        return 1;
    else
        return 0;
}


void win()
{
    if(tmp_win_cons == 3)
        win_x_time ++;
}

void loose()
{
    if(tmp_loose_cons == 3)
        loose_x_time ++;
}
