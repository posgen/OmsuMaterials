/**
    Актуальная версия игры.

    Кому не лень, разберитесь со следующими моментами:
        * что за значение (cash - 50) фигурирует ниже в коде? Какой смысл несёт?

        * с чего вдруг начальный балан игрока объявляется по умолчанию? Откуда взялось число 150?

        * наверное, имеет смысл вначале спрашивать - хочет ли игрок продолжить. Если нет - то
          интересоваться, хочется ли перезапустить игру. А вы как думаете?
*/

#include "ffhelpers.h"

using namespace std;
using namespace ffomsu;

int vibor( size_t index)
{
    if (index <= 8) {
        return index + 2;
    }

    if (index==12) {
        return 11;
    }

    return 10;
}

int get_card(bool (&cld)[52], string who)
{
    size_t index;
    while (true)
    {
        index=rand_a_b_incl(1, 52);

        if (cld[index-1])
        {
            continue;
        }
        else
        {
            cld[index-1]=true;
            break;
        }
    }
    int weight = vibor(index % 13);
    print("current card: ", weight);
    print(" for ", who, "\n");
    return weight;
}

void show_stat(int sum_player, int sum_bank)
{
    print("Player: ", sum_player, " Bank: ", sum_bank, "\n");
}

int main()
{
    int cash= 150;
    char choice1 = 'y';
    while (choice1 != 'n') {
        print("Let's play\n");
        print("You have ", cash - 50," $\n");
        print("Enter your rate until ", cash," $\n");
        int rate_player, rate_bank;
        get_value(rate_player);
        cash -= rate_player;
        rate_bank = rand_a_b_incl(1, 20);
        print("Rate bank: ", rate_bank,"$\n");

        bool coloda[52] = {false};
        int summa_player = 0, summa_bank = 0;

        summa_player = get_card(coloda, "p") + get_card(coloda, "p");
        summa_bank = get_card(coloda, "b");
        show_stat(summa_player, summa_bank);

        if (summa_player==21 or summa_player==22) {
            print("You win and get ",rate_bank+rate_player," $\n");
            cash+=rate_bank+rate_player;
        } else {
            char choice = 'y';
            while(choice != 'n') {
                print("Continue?(y/n): ");
                get_value(choice);
                clear_stdin();
                if (choice=='n') {
                    break;
                }

                int buf;
                buf=get_card(coloda, "p");
                print("You get:", buf,"\n");
                summa_player += buf;
                show_stat(summa_player, summa_bank);
                if (summa_player>21) {
                    break;
                }
            }

            if (summa_player == 21) {
                print("You win and get ",rate_bank+rate_player," $\n");
                cash+=rate_bank+rate_player;
            } else if (summa_player < 21) {
                summa_bank+=get_card(coloda, "b");

                while(true) {
                    summa_bank += get_card(coloda, "b");
                    show_stat(summa_player, summa_bank);

                    if (summa_bank >= 17) {
                        break;
                    }
                }

                if (summa_player == summa_bank) {
                    print("~~~~\n");
                    cash += rate_player;
                } else {

                    if ( (summa_bank > 21) or (summa_player-summa_bank) > 0 ) {
                        print("You win and get ", rate_bank + rate_player, " $\n");
                        cash += rate_bank + rate_player;
                    } else {
                        print("Loose ");
                    }
                }

            } else {
                print("Loose ");
            }
        }

        print("You have ", cash-50, " $. Restart?(y/n)\n");
        char choice2 = 'n';
        get_value(choice2);
        if(choice2=='y') {
            cash=150;
        }

        print("You gonna play?(y/n): ");
        get_value(choice1);
    }
}
