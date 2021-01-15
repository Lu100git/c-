#include <iostream>
#include <limits>
using namespace std;

int numeric_valiidation(int variable, string message){
    while(!(cin >> variable))
    {
        cout <<"!enter numbers only! " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << message;
    }
    return variable;
}

void numeric_valiidation2(int row, int column, int**mtx, string message){
    while(!(cin >> *(*(mtx + row)+column)))
    {
        cout <<"!enter numbers only! " << endl;
        //cout << "\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << message << row +1<<": ";
    }

}

int main()
{
    int Teams;
    int rowIndex;
    int mostPoints;
    int most_games_won;
    int highestScore;
    int winersCount;
    int teams_count = 1;

    string messages[] = {
    "Enter the amount of teams ", 
    "enter the amount of games won for team ",
    "enter the amount of tied games for team ",
    "enter the amount of games lost for team ",
    "enter the score difference for team "
    };

    //2d array
    int **Matrix;

    //How many teams?
    cout << "\nEnter the amount of teams ";
    Teams = numeric_valiidation(Teams, messages[0]);

    //cout << "Enter the amount of teams ";
    cout << "\n";

    //reserving memory for the 2d array, we only need 6 columns for this project
    Matrix = new int*[Teams];
    for (int i = 0; i < Teams; i++){
        Matrix[i] = new int[i];
    }
    
    //data input for each team
    for (rowIndex = 0; rowIndex < Teams; rowIndex++)
    {
        cout << "enter the amount of games won for team " << rowIndex + 1 << ": ";
        numeric_valiidation2(rowIndex, 0, Matrix, messages[1]);
        //cin >> *(*(Matrix + rowIndex)+0);

        cout << "enter the amount of tied games for team " << rowIndex + 1 << ": ";
        numeric_valiidation2(rowIndex, 1, Matrix, messages[2]);  
        //cin >> *(*(Matrix + rowIndex)+1);

        cout << "enter the amount of games lost for team  " << rowIndex + 1 << ": ";
        numeric_valiidation2(rowIndex, 2, Matrix, messages[3]);
        //cin >> *(*(Matrix + rowIndex)+2);  
        
        //calculating games played
        *(*(Matrix + rowIndex)+3) = *(*(Matrix + rowIndex) + 0) + *(*(Matrix + rowIndex) + 1) + *(*(Matrix + rowIndex) + 2);  
        
        cout << "enter the score difference for team " << rowIndex + 1 << ": ";
        numeric_valiidation2(rowIndex, 4, Matrix, messages[4]);
        //cin >> *(*(Matrix + rowIndex)+4);  
        
        //calculating points
        *(*(Matrix + rowIndex)+5) = ( *(*(Matrix + rowIndex)+0) *3 ) + ( *(*(Matrix + rowIndex)+1) *1 );                
    
        cout <<"\n";
    }
    
    //Printing results
    cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+\t\t\t\t\t!!!RESULTS!!!\t\t\t\t\t\t\t+" << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Teams\t|Games won\t|Tied Games\t|Lost Games\t|Games played\t|Score difference\t|Points\t|" << endl;

    for (rowIndex = 0; rowIndex < Teams; rowIndex++)
    {
        cout << "Team# " << teams_count <<" " 
         << "| "<< *(*(Matrix + rowIndex) +0) <<"\t\t" 
         << "| "<< *(*(Matrix + rowIndex) +1) <<"\t\t" 
         << "| "<< *(*(Matrix + rowIndex) +2) <<"\t\t"
         << "| "<< *(*(Matrix + rowIndex) +3) <<"\t\t" 
         << "| "<< *(*(Matrix + rowIndex) +4) <<"\t\t\t" 
         << "| "<< *(*(Matrix + rowIndex) +5) << "\t|" << endl;

        teams_count++;
    }
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout <<"\n";

    //conditions to decide who the winer will be after relusts board displays
    
    //Finding the team with most Points
    mostPoints = *(*(Matrix + 0 )+5);
    winersCount = 0;
    for (rowIndex = 1; rowIndex < Teams; rowIndex++)
    {
        if(Matrix[rowIndex][5] > mostPoints){
            mostPoints = Matrix[rowIndex][5];
        }
    }

    //finding winers
    for (rowIndex = 0; rowIndex < Teams; rowIndex++){
        if(Matrix[rowIndex][5] == mostPoints) winersCount++;
    }


    //if there is a winer we find it
    if(winersCount == 1)
    {
        for (rowIndex = 0; rowIndex < Teams; rowIndex++)
        {
            if(Matrix[rowIndex][5] == mostPoints)
            {
                cout << "The winer is [Team # " << rowIndex + 1 << "] --- [" << Matrix[rowIndex][5] << "] points\n" << endl;
                break;
            }
        }
    }

    else{
        //finding winer by games won
        most_games_won = Matrix[0][0];
        winersCount = 0;
        for (rowIndex = 1; rowIndex < Teams; rowIndex++)
        {
            if(Matrix[rowIndex][0] > most_games_won){
                most_games_won = Matrix[rowIndex][0];
            }
        }
        //finding how many winers are per games won
        for (rowIndex = 0; rowIndex < Teams; rowIndex++){
            if(Matrix[rowIndex][0] == most_games_won) winersCount++;
        }

        //if there is only 1 winer we find it
        if(winersCount == 1)
        {
            for (rowIndex = 0; rowIndex < Teams; rowIndex++)
            {
                if(Matrix[rowIndex][0] == most_games_won)
                {
                    cout << "The winer by most games won is Team # [" << rowIndex + 1 << "] --- [" << Matrix[rowIndex][0] << "] games won\n" << endl;
                    break;
                }
            }   
        }

        else
        {
            //finding winer by highest score
            highestScore = Matrix[0][4];
            winersCount = 0;
            for (rowIndex = 1; rowIndex < Teams; rowIndex++)
            {
                if(Matrix[rowIndex][4] > highestScore){
                    highestScore = Matrix[rowIndex][4];
                }
            }

            //how many winers are there by score difference
            for (rowIndex = 0; rowIndex < Teams; rowIndex++){
                if(Matrix[rowIndex][4] == highestScore) winersCount++;
            }

            //what happens when we found 1 winer by higest score
            if(winersCount == 1)
            {
                for (rowIndex = 0; rowIndex < Teams; rowIndex++){
                    if(Matrix[rowIndex][4] == highestScore){ 
                        cout << "The winer is Team # [" << rowIndex+ 1 << "] --- [" << Matrix[rowIndex][4] << "] Score difference\n" << endl;
                    }
                }
            }

            else
            {
                //Tie!!!!!, there are no winers
                cout << "Tie, there is no winer\n" << endl; 
            }    
        }
    }

    //freeing memory
    for (int i = 0; i < Teams; i++){
        delete[] Matrix[i];
    }
    delete[] Matrix;

    return 0;
}
