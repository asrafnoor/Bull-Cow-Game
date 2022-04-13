// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
//  #include "Math/UnrealMathUtiliy.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words);

    SetupGame(); 

    // PrintLine(TEXT("The number of posible words is %i"), Words.Num());
    // PrintLine(TEXT("The number of valid words is: %i. "),  GetValidWords(Words).Num());
    // PrintLine(TEXT("ValidWords - 1 is: %i"), GetValidWords(Words).Num() - 1);
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{ 
    /* 
    if the game is over then do - ClearScreen() and SetupGame() the game
    */
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // else Checking PlayerGuess
    {   
        ProcessGuess(PlayerInput);
    }
    
   
}

void UBullCowCartridge::SetupGame()
{
   
    // Welcoming the Player
    PrintLine(TEXT("Hi there! Welcome to the Bull Cow Game!"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() -1)]; // Set the HiddenWord
    Lives = HiddenWord.Len() * 2; // Set Lives
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); 
    // PrintLine(TEXT("The Hidden Word is: %s."), *HiddenWord);  //Debug Line that will turn on/off
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess. \nPress enter to continue..."));   // Prompt  player for guess

    // int32 i = 0;       LOOP EXAMPLES
    // while (i < 2)
    // {
    //     PrintLine(TEXT("%i"), i);
    //     i++;
    // }

    // for  (int32 Index = 0; Index < 2; Index++)
    // {
    //     PrintLine(TEXT("%i"), Index);
    // }

    // int32 j = 0;
    // do 
    // {
    //     PrintLine(TEXT("%i"), j);
    //     j++;
    // } while (j < 2);   LOOP EXAMPLES

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if(Guess == HiddenWord)
    {
        PrintLine(TEXT("You won!"));
        EndGame();
        return;
    }
    
    // Check if right number of characters
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden Word is %i characters long."), HiddenWord.Len());
        PrintLine(TEXT("You have %i lives left."), Lives);  // Prompt to GuessAgain
        return;
    }

    // Check if Isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again."));
        return;
    }

    // Remove Life
    PrintLine(TEXT("\nLost a life!"));
    --Lives;

    // check if live > 0
    if (Lives <= 0)
    {   
        ClearScreen();
        PrintLine(TEXT("You have no lives left."));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
        // else
        // {
        // PrintLine(TEXT("You guessed wrong."));
        // PrintLine(TEXT("You have %i lives left."), Lives);
        // }
    }

    // Show the Player Bulls and Cows
   
    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

    PrintLine(TEXT("Guess again, you have %i left"), Lives);


    // if yes GuessAgain
    // Show lives left
    // if no Show GameOver and HiidenWord?
    // Prompt to play again, Press Enter to play again?
    //Check user input
    // PlayAgain
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{

    for (int32 Index = 0; Index < Word.Len(); ++Index)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}


FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    // for every index Guess is same as index Hidden, BullCount++
    // if not a bull was it a cow? if yes CowCount++

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {

            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}












    // int32 Index = 0;
    // int32 Comparison = Index +1;

    // for (int32 Index = 0, Comparison = Index + 1; Comparison < Word.Len(); Comparison++)  WRONG IMPLEMENTATION
    // {
    //     for (int32 Index = 1, Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
    //     {
    //         for (int32 Index = 2, Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
    //         {
    //             for (int32 Index = 3, Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
    //             {
    //                 if (Word[Index] == Word[Comparison])
    //                 {
    //                     return false;
    //                 }
    //             }
    //         }
            
    //     }
        
    // }

    