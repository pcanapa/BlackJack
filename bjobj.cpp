/*
programma ispirato da Turbocotoletta. :D
*/

#include<iostream>
#include<string>
#include<cstdlib>
#include<time.h>


using namespace std;

struct typeCard
{
    int val;
    string seed;
    int f;
    struct typeCard *next;
};

struct typePlayer
{
    string nickname;
    int points;
    int sum;
    int nCards;

    struct typePlayer *next;
};

class Player
{
    private:
        int i, j;
    public:
        struct typePlayer *head;
        struct typePlayer *p;

        void initPlayers()
        {
            cout<<"In quanti siete?\n>";
            cin>>j;
            for(i = 0;i < j;i++)
            {
                Player::addPlayer();
            }
        }

        void addPlayer()
        {
            p = new(typePlayer);
            p->nCards = 0;
            p->points = 0;
            p->sum = 0;
            cout<<"\nNickname?\n>";
            cin>>p->nickname;
            p->next = head;
            head = p;
        }

        void printPoints()
        {
            for(p = head; p != NULL; p = p->next)
            {
                cout<<p->nickname<<" : "<<p->points<<endl;
            }
        }

};

class Deck
{
    public:
        struct typeCard deck[52];
        struct typeCard *head;
        struct typeCard *p;


        void loadDeck()
        {
            int i;
            int flag = 0;
            for(i = flag;i < 13;i++)
            {
                deck[i].val = i + 1;
                deck[i].seed = "di Picche";

            }
            flag = flag + 13;
            for(i = flag;i < flag + 13;i++)
            {
                deck[i].val = i + 1 - flag;
                deck[i].seed = "di Quadri";

            }
            flag = flag + 13;
            for(i = flag;i < flag + 13;i++)
            {
                deck[i].val = i + 1 - flag;
                deck[i].seed = "di Cuori";

            }
            flag = flag + 13;
            for(i = flag;i < flag + 13;i++)
            {
                deck[i].val = i + 1 - flag;
                deck[i].seed = "di Fiori";

            }
        }

        void mixDeck()
        {
            int ran, i;
            typeCard temp;
            for(i = 0; i < 52; i++)
            {
                ran = rand()%52;
                temp = deck[i];
                deck[i] = deck[ran];
                deck[ran] = temp;
            }
        }

        void transferToStack()
        {
            int i;

            for(i = 0;i < 52;i++)
            {
                p = new(typeCard);
                p->val = deck[i].val;
                p->seed = deck[i].seed;
                p->next = head;
                head = p;
            }
        }

        void popCard()
        {
            p = head;
            head = p->next;
            delete(p);
        }

        void printFromStack()
        {
            for(p = head; p != NULL; p = p->next)
            {
                cout<<p->val<<" "<<p->seed<<endl;
            }
        }
};

int main()
{
    srand(time(NULL));

    Deck deck;
    deck.head = NULL;
    deck.loadDeck();
    deck.mixDeck();
    deck.transferToStack();

    Player players;
    players.head = NULL;
    players.initPlayers();

    int scelta, max, s, j;
    struct typePlayer *maxP;

    j = 0;
    do
    {
        j++;
        cout<<"Inizio turno numero: "<<j<<"\n\n";
        if(deck.head->next == NULL)
        {
            deck.popCard();
            deck.loadDeck();
            deck.mixDeck();
            deck.transferToStack();
        }

        for(players.p = players.head; players.p != NULL; players.p = players.p->next)
        {
            cout<<"Tocca a "<<players.p->nickname<<endl<<endl;
            players.p->nCards = 0;
            players.p->sum = 0;
            do
            {
                cout<<"1) Dai Carta\n2)Stop\nCosa vuoi fare?\n>";
                cin>>scelta;
                switch(scelta)
                {
                    case 1:
                        deck.p = deck.head;
                        deck.head = deck.p->next;
                        if(deck.p->val > 10)
                        {
                            players.p->sum += 10;
                        }
                        else if(deck.p->val == 1)
                        {
                            int asso;
                            do
                            {
                                cout<<"L'asso vale 1 o 11?\n>";
                                cin>>asso;

                            }while(asso != 1 && asso != 11);
                            players.p->sum += asso;

                        }
                        else
                        {
                            players.p->sum += deck.p->val;
                        }

                        cout<<"\n\nCarta uscita: "<<deck.p->val<<" "<<deck.p->seed<<endl<<endl;
                        cout<<"Totale punteggio: "<<players.p->sum<<endl<<endl;

                        if(players.p->sum > 21)
                        {
                            cout<<"\nhai perso!\n\n";
                            scelta = 2;
                            players.p->sum = -1;
                        }
                        else if(players.p->sum == 21)
                        {
                            if(players.p->nCards == 2)
                            {
                                cout<<"Blackjack!\n\n";
                                players.p->sum += 1;
                            }
                            else
                                cout<<"\n21!\n\n";
                            scelta = 2;
                        }
                        delete(deck.p);
                        break;
                    case 2:
                        break;
                    default:
                        cout<<"Comando non riconosciuto\n\n";
                }
            }while(scelta != 2);
        }
        max = -1;
        for(players.p = players.head; players.p != NULL; players.p = players.p->next)
        {
            if(players.p->sum > max)
            {
                max = players.p->sum;
                maxP = players.p;
            }
        }
        maxP->points++;
        cout<<"Vuoi fare un'altro turno?[1 = Si, Altro numero = No]\n>";
        cin>>s;
    }while(s == 1);

    players.printPoints();
    return 0;
}
