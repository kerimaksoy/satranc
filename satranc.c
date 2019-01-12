#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initializeTheBoard(char **, int, int);
void printScreen(char **, int, int);
void play(char **, int *);
int knightMove(char **,int, int, int, int);
int canMove(char **, int, int, int, int, int);
int kingMove(char **, int, int, int, int);
int queenMove(char **, int, int, int, int);
int rookMove(char **,int ,int ,int ,int);
int pawnMove(char **, int, int, int, int, int);
int bishopMove(char **, int, int ,int ,int);
int destinationCheck(char, int);
int pawnPromotion(char **, int, int);
int isGameOver(char **, int, int);

#define HEIGTH 8
#define WIDTH 8


int main()
{
    char **arr;
    int  i=0, turn=0, gameOver=0;

    //hafizadan alan al
    arr = malloc(sizeof(char *) * HEIGTH);
    for(; i<HEIGTH; i++)
    {
        arr[i] = malloc(sizeof(char) * WIDTH);
    }
    //tahtaya ilk halini ver
    initializeTheBoard(arr, HEIGTH, WIDTH);


    do
    {
        printScreen(arr, HEIGTH, WIDTH);
        play(arr, &turn);
        pawnPromotion(arr, HEIGTH, WIDTH);
    }while( (gameOver=isGameOver(arr, HEIGTH, WIDTH)) == 0);

    printf("%d player wins!", gameOver);
    //hafizayi geri birak
    for(i=0;i<5;i++)
    {
        free(arr[i]);
    }
    free(arr);

    return 0;

}

//kullanicilarin ikisininde sah tasi mevcut mu
//eger oyleyse return 0
//eger 0. oyuncunun tasi yoksa 1 dondur
//eger 1. oyuncunun tasi yoksa 2 dondur
int isGameOver(char ** arr, int nRows, int nCols)
{
    int i,j,a=0,b=0;
    for(i=0 ; i < 8 ;i++)
    {
        for(j=0 ; j < 8 ; j++)
        {
            if(arr[i][j] == 'S')
            {
                a=1;
            }
            if(arr[i][j]== 's')
            {
                b=1;
            }
        }
    }
    if(a==1 && b==1)
    {
        return 0;
    }
    else if(a==0 && b==1)
    {
        return 2;
    }
    else if(a==1 && b==0)
    {
        return 1;
    }
}
int pawnPromotion(char **arr,int nRows,int nCols)
{
    int i,j;
    char piece1='p';
    char piece2='P';
    for(i=0;i<nRows;i++)
    {
        for(j=0;j<nCols;j++)
        {
            if(i==0 && arr[i][j]=='p')
            {
                printf("Chose a piece for promotion(v, k, a, f): ");
                scanf("%c",&piece1);
                switch(piece1)
                {
                    case 'v':
                        arr[i][j]='v';
                        break;
                    case 'k':
                        arr[i][j]='k';
                        break;
                    case 'a':
                        arr[i][j]='a';
                        break;
                    case 'f':
                        arr[i][j]='f';
                        break;
                }
            }
            else if(i==7 && arr[i][j]=='P')
            {
                printf("Chose a piece for promotion(V, K, A, F): ");
                scanf("%c",&piece2);
                switch(piece2)
                {
                    case 'V':
                        arr[i][j]='V';
                        break;
                    case 'K':
                        arr[i][j]='K';
                        break;
                    case 'A':
                        arr[i][j]='A';
                        break;
                    case 'F':
                        arr[i][j]='F';
                        break;
                }
            }

        }
    }
}
//hareket edilecek hedef noktasindaki tas kimin
//eger siranin kendisindeki oyuncunun ise 0
//degilse 1 dondur
int destinationCheck(char destPiece, int turn)
{
    //turn 0 ise
    if ( (destPiece >= 'A' && destPiece <= 'Z') && turn == 0)
    {
        return 0;
    }
    //turn 1 ise
    if ( (destPiece >= 'a' && destPiece <= 'z') && turn == 1)
    {
        return 0;
    }
    return 1;
}
int kingMove(char **arr,int sRow,int sCol,int eRow, int eCol)
{
    if( (eRow==sRow+1&&sCol==eCol) || (eRow==sRow-1&&sCol==eCol) ||
        (eCol==sCol+1&&sRow==eRow) || (eCol==sCol-1&&sRow==eRow) )
    {
        if(arr[eRow][eCol] == ' ')
        {
            return 1;
        }
        if (arr[eRow][eCol] != ' ')
        {
            return 1;
        }
    }
    else if( (eRow==sRow+1&&eCol==sCol+1) || (eRow==sRow-1&&eCol==sCol-1) ||
             (eRow==sRow+1&&eCol==sCol-1) || (eRow==sRow-1&&eCol==sCol+1) )
    {
        if(arr[eRow][eCol] == ' ')
        {
            return 1;
        }
        if (arr[eRow][eCol] != ' ')
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }

}
int queenMove(char **arr,int sRow, int sCol, int eRow, int eCol)
{
    int i,x;

    if(sRow +1 == eRow && sCol +1 == eCol)
    {
        return 1;
    }
    for(i=2;i<=7;i++)
    {
        if( eRow == sRow+i && eCol == sCol+i )
        {
            for( x=1 ; x < i ; x++)
            {
                if(arr[eRow-x][eCol-x] != ' ')
                {
                    return 0;
                }
            }
            return 1;
        }
    }
    if(sRow -1 == eRow && sCol -1 == eCol)
    {
        return 1;
    }
    for(i=2 ; i<=7 ; i++)
    {
        if( eRow ==sRow -i && eCol== sCol -i )
        {
            for( x=1 ; x < i ; x++)
            {
                if(arr[eRow+x][eCol+x] != ' ')
                {
                    return 0;
                }
            }
            return 1;
         }
    }
    if(sRow +1 == eRow && sCol -1 == eCol)
    {
        return 1;
    }
    for(i=2 ; i<=7 ; i++)
    {
        if( eRow == sRow-i && eCol == sCol+i )
        {
            for( x=1 ; x < i ; x++)
            {
                if(arr[eRow+x][eCol-x] != ' ')
                {
                    return 0;
                }
            }
            return 1;
        }
    }
    if(sRow -1 == eRow && sCol +1 == eCol)
    {
        return 1;
    }
    for(i=2 ; i<=7 ; i++)
    {
        if( eRow == sRow+i && eCol == sCol-i )
        {
            for( x=1 ; x < i ; x++)
            {
                if(arr[eRow-x][eCol+x] != ' ')
                {
                    return 0;
                }
            }
            return 1;
        }
    }
    if(eRow > sRow && eCol==sCol )
    {
        for(i= sRow+1 ; i < eRow ; i++)
        {
            if( arr[i][sCol] != ' ' )
            {
                return 0;
            }
        }
        return 1;
    }
    else if(eRow < sRow && eCol==sCol)
    {
        for(i=sRow-1 ; i > eRow ; i--)
        {
            if( arr[i][sCol] != ' ' )
            {
                return 0;
            }
        }
        return 1;
    }
    else if(eCol > sCol && eRow==sRow)
    {
        for(i=sCol+1 ; i < eCol ; i++)
        {
            if( arr[sRow][i] != ' ' )
            {
                return 0;
            }
        }
        return 1;
    }
    else if(eCol < sCol && eRow==sRow)
    {
        for(i=sCol-1 ; i > eCol ; i--)
        {
            if( arr[sRow][i] != ' ' )
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}
int bishopMove(char **arr,int sRow,int sCol,int eRow, int eCol)
{
    int i,x;

      if(sRow +1 == eRow && sCol +1 == eCol)
      {
            return 1;
      }
      for(i=2;i<=7;i++)
      {
            if( eRow == sRow+i && eCol == sCol+i )
          {
             for( x=1 ; x < i ; x++)
             {
                if(arr[eRow-x][eCol-x] != ' ')
                {
                    return 0;
                }

             }
            return 1;
          }
      }

      if(sRow -1 == eRow && sCol -1 == eCol)
      {
            return 1;
      }
      for(i=2 ; i<=7 ; i++)
      {
        if( eRow ==sRow -i && eCol== sCol -i )
         {
            for( x=1 ; x < i ; x++)
             {
                if(arr[eRow+x][eCol+x] != ' ')
                {
                    return 0;
                }

             }
            return 1;

         }
      }

      if(sRow +1 == eRow && sCol -1 == eCol)
        {
            return 1;
        }
      for(i=2 ; i<=7 ; i++)
      {
         if( eRow == sRow-i && eCol == sCol+i )
         {
           for( x=1 ; x < i ; x++)
             {
                if(arr[eRow+x][eCol-x] != ' ')
                {
                    return 0;
                }

             }
            return 1;

         }

      }

      if(sRow -1 == eRow && sCol +1 == eCol)
        {
            return 1;
        }
      for(i=2 ; i<=7 ; i++)
      {
         if( eRow == sRow+i && eCol == sCol-i )
         {
           for( x=1 ; x < i ; x++)
             {
                if(arr[eRow-x][eCol+x] != ' ')
                {
                    return 0;
                }

             }
            return 1;

         }

      }
  return 0;
}
int rookMove(char **arr,int sRow,int sCol,int eRow, int eCol)
{
    int i;

      if(eRow > sRow && eCol==sCol )
      {
          for(i= sRow+1 ; i < eRow ; i++)
          {
                if( arr[i][sCol] != ' ' )
                {
                    return 0;
                }
          }
            return 1;
      }

      else if(eRow < sRow && eCol==sCol)
      {
          for(i=sRow-1 ; i > eRow ; i--)
          {
                if( arr[i][sCol] != ' ' )
                {
                    return 0;
                }
          }
            return 1;
      }

      else if(eCol > sCol && eRow==sRow)
      {
          for(i=sCol+1 ; i < eCol ; i++)
          {
                if( arr[sRow][i] != ' ' )
                {
                    return 0;
                }
          }
              return 1;
      }

      else if(eCol < sCol && eRow==sRow)
      {
          for(i=sCol-1 ; i > eCol ; i--)
          {
                if( arr[sRow][i] != ' ' )
                {
                    return 0;
                }
          }
              return 1;
      }

    return 0;
}

//piyon hareketi. hareket gecerliyse 1 degilse 0 dondurur
int pawnMove(char **arr, int sRow, int sCol, int eRow, int eCol, int direction)
{
    //hareket duz ise ilgili alan bos mu?
    if (eRow == sRow + direction && sCol == eCol)
    {
        if(arr[eRow][eCol] == ' ')
        {
            return 1;
        }
    }
    //hareket capraz ise hedef alan bos olmamalý
    else if (eRow == sRow + direction &&( (sCol == eCol+1) || (sCol == eCol-1) ))
    {
        if (arr[eRow][eCol] != ' ')
        {
            return 1;
        }
    }
    //buraya ulastýysa yukaridaki returnlere ulasamamistir o yuzden 0 dondur
    return 0;
}
int knightMove(char **arr,int sRow, int sCol, int eRow, int eCol)
{
    if(sRow-2==eRow && sCol-1==eCol)
        return 1;
    else if(sRow-1==eRow && sCol-2==eCol)
        return 1;
    else if(sRow-2==eRow && sCol+1==eCol)
        return 1;
    else if(sRow+1==eRow && sCol-2==eCol)
        return 1;
    else if(sRow+2==eRow && sCol-1==eCol)
        return 1;
    else if(sRow+2==eRow && sCol+1==eCol)
        return 1;
    else if(sRow+2==eRow && sCol+1==eCol)
        return 1;
    else if(sRow+1==eRow && sCol+2==eCol)
        return 1;
    else if(sRow-1==eRow && sCol+2==eCol)
        return 1;
    else
        return 0;
}



//hem hareket fonksyionundan gelen deger 1
//hem de destinationCheck fonksiyonundan donen deger 1 ise
//canMove fonksiyonu 1 dondurur.
int canMove(char **arr, int turn, int sRow, int sCol, int eRow, int eCol)
{
    char piece = arr[sRow][sCol];

    if (piece == 'P')
    {
       return pawnMove(arr, sRow, sCol, eRow, eCol, 1) && destinationCheck(arr[eRow][eCol], turn);
    }
    else if ( piece == 'p')
    {
       return pawnMove(arr, sRow, sCol, eRow, eCol, -1) && destinationCheck(arr[eRow][eCol], turn);
    }
    //fil hareketi
    else if (piece == 'F' || piece == 'f')
    {
        return bishopMove(arr,sRow,sCol,eRow,eCol) && destinationCheck(arr[eRow][eCol],turn);
    }
    //at hareketi
    else if (piece == 'A' || piece == 'a')
    {
        return knightMove(arr,sRow,sCol,eRow,eCol) && destinationCheck(arr[eRow][eCol],turn);
    }
    //kale hareketi
    else if (piece == 'K' || piece == 'k')
    {
        return rookMove(arr,sRow,sCol,eRow,eCol) && destinationCheck(arr[eRow][eCol],turn);
    }
    //vezir hareketi
    else if (piece == 'V' || piece == 'v')
    {
        return queenMove(arr,sRow,sCol,eRow,eCol) && destinationCheck(arr[eRow][eCol],turn);
    }
    //sah hareketi
    else //veya else if (piece == 'S' || piece == 's') yazabilirsiniz
    {
        return kingMove(arr,sRow,sCol,eRow,eCol)&& destinationCheck(arr[eRow][eCol],turn);
    }

    return 0;

}

void play(char **arr, int *turn)
{
    char *sMove, *eMove;
    int sRow, sCol, eRow, eCol;
    sMove = malloc(sizeof(char) * 3);
    eMove = malloc(sizeof(char) * 3);
    do
    {
        printf("\t\t\t          coded by Keritto\n");
        printf("%d. player turn: ", *turn+1);
        scanf("%2s %2s", sMove, eMove);

        fflush(stdin);
        sRow = (int)(sMove[0] - 'A');
        sCol = (int)(sMove[1] - '1');
        eRow = (int)(eMove[0] - 'A');
        eCol = (int)(eMove[1] - '1');
        if(
            (sRow >= 0 && sRow <= 7) &&
            (sCol >= 0 && sCol <= 7) &&
            (eCol >= 0 && eCol <= 7) &&
            (eRow >= 0 && eRow <= 7)
           )
        {
            char piece = arr[sRow][sCol];
            //secilen tas sirasi gelen kullanicinin mi
            if (
                 ( *turn == 0 && (piece >= 'A' && piece <= 'Z') )
                  ||
                 ( *turn == 1 && (piece >= 'a' && piece <= 'z') )
               )
            {
                //secilen tas hedef konuma gidebilir mi
                if( canMove(arr, *turn, sRow, sCol, eRow, eCol) == 1 )
                {
                    arr[eRow][eCol] = piece;
                    arr[sRow][sCol] = ' ';
                    *turn = (*turn + 1) % 2;
                    break;
                }
                //eger gidemiyorsa illegal move
                else
                {
                    printf("Illegal move. Try again.\n");
                }

            }
            //secilen tas kullanicinin degil
            else
            {
                printf("It's your opponent's piece\n");
            }
        }
        //istenen konumlar aralikta girilmemis
        else
        {
            printf("Your move is out of boundary\n");
        }
    }while(1);//dogru hareket yapilana kadar devam eder. Dogru hareket yapildiysa
              //yukaridaki break bu while kosulunu kirar ve cikilir.
}
//dizi iceriklerini ekrana yaz.
void printScreen(char ** arr, int nRows, int nCols)
{
    system("@cls||clear");

    int i, j;

    printf("%s", " |");
    for(j=0;j<nCols;)
    {
        printf("  %d  |", ++j);
    }

    printf("\n--");

    for(j=0;j<nCols;j++)
    {
        printf("%s", "------");
    }

    printf("\n");

    for(i=0;i<nRows;i++)
    {
        printf("%c|", 'A'+i);

        for(j=0;j<nCols;j++)
        {
            printf("  %c  |", arr[i][j]);
        }

        printf("\n--");

        for(j=0;j<nCols;j++)
        {
            printf("%s", "------");
        }
        printf("\n");
    }
}
void initializeTheBoard(char **arr, int nRows, int nCols)
{
    int i, j;
    for(i=0;i<nRows-2;i++)
    {
        for(j=0;j<nCols;j++)
        {
            if (i == 0)
            {
                if (j == 0 || j==nCols-1)
                {
                    arr[i][j] = 'K';
                }

                else if (j == 1 || j==nCols-2)
                {
                    arr[i][j] = 'A';
                }

                else if (j == 2 || j==nCols-3)
                {
                    arr[i][j] = 'F';
                }
                else if (j == 3 )
                {
                    arr[i][j] = 'V';
                }
                else
                {
                    arr[i][j] = 'S';
                }
            }
            else if (i == 1)
            {
                arr[i][j] = 'P';
            }
            else
            {
                arr[i][j] = ' ';
            }
        }
    }
    //last 2 rows for opponent
    for(i=nRows-2; i<nRows;i++)
    {
        for(j=0;j<nCols;j++)
        {
            //add 32 to lower the opponent's character
            arr[i][j] = arr[nRows-i-1][j] + 32;
        }
    }
}

