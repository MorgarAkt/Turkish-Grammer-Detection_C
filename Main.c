#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>

// defining functions on the top
int isConsonant(char a);
int isVowel(char a);
void connexion(char *dictionary[100], int *connexionCount, int wordCount);
void findCount(char sentence[10000], int size, int *letterCount, int *wordCount);
void plural(char *(dictionary[500]), int wordcount);
int isEnd(char sentence[10000]);
void palatalHarmony(char *(dictionary[500]), int wordCount);
void labialHarmony(char *(dictionary[500]), int wordCount);
int totalVowel(char A[], int lenA);
void menu(char sentence[], char *(dictionary[500]), int size, int letterCount, int wordCount, int connexionCount);
void wordSearch(char *(dictionary[500]), int wordcount, char word[100]);
void strongSoftConsonant(char *(dictionary[500]), int wordCount);

int main()
{
    setlocale(LC_ALL, "Turkish_turkish.1254");
    SetConsoleOutputCP(1254);
    SetConsoleCP(1254);
    char sentence[10000] = "\0";
    char sentencetemp[10000] = "\0";
    char *dictionary[500];
    int connexionCount = 0;
    int wordCount = 0, letterCount = 0, size = sizeof(sentence) / sizeof(sentence[1]);
    int a = 0;
    printf("\n enter the paragraph\n");
    fgets(sentence, 10000, stdin);
    findCount(sentence, size, &letterCount, &wordCount); // finds the number of letters and words
    strcpy(sentencetemp, sentence);
    dictionary[0] = strtok(sentencetemp, " ");
    for (int i = 1; i < wordCount; i++)
    {
        dictionary[i] = strtok(NULL, " ");
    }
    menu(sentence, dictionary, size, letterCount, wordCount, connexionCount);
    return 0;
}

// a menu function for making a choice
void menu(char sentence[], char *(dictionary[500]), int size, int letterCount, int wordCount, int connexionCount)
{

    printf("\nnumber of words = %d\n\n", wordCount);
    printf("\nnumber of letters = %d\n\n", letterCount);
    printf("\nnumber of sentence = %d\n\n", isEnd(sentence));
    palatalHarmony(dictionary, wordCount);
    labialHarmony(dictionary, wordCount);
    plural(dictionary, wordCount);
    connexion(dictionary, &connexionCount, wordCount);
    strongSoftConsonant(dictionary, wordCount);

    char menuChoice[50] = "\0";
    do
    {
        printf("\n\n-----Turkish Grammar Detector-----\n\n");
        printf("What do you want to check for?\n\n");
        printf("Word Count\nLetter Count\nSentence Count\nPalatal Harmony\nLabial Harmony\nPlural Words\nConnexions\nStrong Consonant\nWord Search\n\nExit\n");
        fgets(menuChoice, 50, stdin);
        for (int i = 0; i < 50; i++)
        {
            menuChoice[i] = tolower(menuChoice[i]);
        }
        if (strcmp(menuChoice, "word count\n") == 0)
        {
            wordCount = 0;
            printf("\nnumber of words = %d\n\n", wordCount);
        }
        else if (strcmp(menuChoice, "letter count\n") == 0)
        {
            letterCount = 0;
            printf("\nnumber of letters = %d\n\n", letterCount);
        }
        else if (strcmp(menuChoice, "sentence count\n") == 0)
        {
            printf("\nnumber of sentence = %d\n\n", isEnd(sentence));
        }
        else if (strcmp(menuChoice, "palatal harmony\n") == 0)
        {
            palatalHarmony(dictionary, wordCount);
        }
        else if (strcmp(menuChoice, "labial harmony\n") == 0)
        {
            labialHarmony(dictionary, wordCount);
        }
        else if (strcmp(menuChoice, "plural words\n") == 0)
        {
            plural(dictionary, wordCount);
        }
        else if (strcmp(menuChoice, "connexions\n") == 0)
        {
            connexionCount = 0;
            connexion(dictionary, &connexionCount, wordCount);
        }
        else if (strcmp(menuChoice, "strong consonant\n") == 0)
        {
            strongSoftConsonant(dictionary, wordCount);
        }
        else if (strcmp(menuChoice, "word search\n") == 0)
        {
            char word[100];
            printf("Which word you are looking for\n");
            gets(word);
            wordSearch(dictionary, wordCount, word);
        }
        else if (strcmp(menuChoice, "exit\n") == 0)
        {
            system("cls");
            printf("\nGoodbye\n");
            break;
        }
        else
        {
            printf("Wrong Choice. Enter again\n");
        }

    } while (strcmp(menuChoice, "Exit\n") != 0);
}

// a function that finds the number of vowels in given word
int totalVowel(char A[], int lenA)
{
    char vowel[8] = {'a', 'e', 'i', 'ı', 'o', 'u', 'ü', 'ö'};
    int counter = 0;
    for (int i = 0; i < lenA; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (A[i] == vowel[j])
            {
                counter++;
            }
        }
    }
    return counter;
}

// it checks all words separately and each word's each letter
// it finds the first vowel of the word and draws a path according to the following vowels
void labialHarmony(char *(dictionary[500]), int wordCount)
{
    printf("\nlabial harmony =\n");
    int totalLabial = 0;
    for (int i = 0; i < wordCount; i++)
    {
        int len = strlen(dictionary[i]) - 1;
        int duzUnluCheck = 0, totalNumOfVowel = totalVowel(dictionary[i], len);
        char vowel1;
        for (int u = 0; u < len; u++)
        {
            if (dictionary[i][u] == 'e' || dictionary[i][u] == 'i' || dictionary[i][u] == 'ü' || dictionary[i][u] == 'ö' || dictionary[i][u] == 'a' || dictionary[i][u] == 'o' || dictionary[i][u] == 'u' || dictionary[i][u] == 'ı')
            {
                vowel1 = dictionary[i][u];
            }
        }
        if (vowel1 == 'a' || vowel1 == 'e' || vowel1 == 'i' || vowel1 == 'ı')
        {
            for (int j = 0; j < len; j++)
            {
                if (dictionary[i][j] == 'a' || dictionary[i][j] == 'e' || dictionary[i][j] == 'i' || dictionary[i][j] == 'ı')
                {
                    duzUnluCheck++;
                }
            }
        }
        else if (vowel1 == 'o' || vowel1 == 'ö' || vowel1 == 'u' || vowel1 == 'ü')
        {
            for (int j = 0; j < len; j++)
            {
                if (dictionary[i][j] == 'u' || dictionary[i][j] == 'e' || dictionary[i][j] == 'ü' || dictionary[i][j] == 'a')
                {
                    duzUnluCheck++;
                }
            }
        }
        if (duzUnluCheck == totalNumOfVowel)
        {
            printf("%s\n", dictionary[i]);
            totalLabial++;
        }
    }
    printf("%d word has labial harmony\n\n", totalLabial);
}

// it checks every vowel in given word and checks if vowels match the condition
void palatalHarmony(char *(dictionary[500]), int wordCount)
{
    int totalcounter = 0;
    printf("\npalatal harmony = \n");
    for (int i = 0; i < wordCount; i++)
    {
        int counterVowel1 = 0;
        int counterVowel2 = 0;
        int len = strlen(dictionary[i]);
        for (int j = 0; j < len; j++)
        {
            char c = dictionary[i][j];
            if (dictionary[i][j] == 'a' || dictionary[i][j] == 'ı' || dictionary[i][j] == 'u' || dictionary[i][j] == 'o')
            {
                counterVowel1++;
            }
            if (dictionary[i][j] == 'e' || dictionary[i][j] == 'i' || dictionary[i][j] == 'ü' || dictionary[i][j] == 'ö')
            {
                counterVowel2++;
            }
        }
        if (counterVowel1 == totalVowel(dictionary[i], len) || counterVowel2 == totalVowel(dictionary[i], len))
        {
            printf("%s\n", dictionary[i]);
            totalcounter++;
        }
    }
    printf("%d word has palatal harmony\n\n", totalcounter);
}

// finds the number of words
void findCount(char sentence[10000], int size, int *letterCount, int *wordCount)
{
    for (int p = 0; p < size; p++)
    {
        sentence[p] = tolower(sentence[p]);
    }

    char alphabet[29] = {'a', 'b', 'c', 'ç', 'd', 'e', 'f', 'g', 'ğ', 'h', 'ı', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'ö', 'p', 'r', 's', 'ş', 't', 'u', 'ü', 'v', 'y', 'z'};
    for (int i = 0; i < size; i++)
    {
        for (int k = 0; k < 29; k++)
        {
            if (sentence[i] == alphabet[k])
            {
                *letterCount = *letterCount + 1;
            }
        }

        if (isspace(sentence[i]) != 0 || ispunct(sentence[i]) != 0)
        {
            if (isspace(sentence[i - 1]) != 0 || ispunct(sentence[i]) != 0)
            {
                *wordCount = *wordCount - 1;
            }
            *wordCount = *wordCount + 1;
        }
    }
}

// is a subfunction for finding count of the sentence
int isEnd(char sentence[10000])
{
    int counter = 0;
    char punc[3] = {'.', '?', '!'};
    for (int i = 0; i < strlen(sentence); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (sentence[i] == punc[j])
                counter = counter + 1;
        }
        if (sentence[i] == punc[0] && sentence[i + 1] == punc[0] && sentence[i + 2] == punc[0])
        {
            counter = counter - 2;
        }
    }
    return counter;
}

// checks if the char that used in function is vowel
int isVowel(char a)
{
    int returnCount = 0;
    if (a != '?' && a != 'ö' && a != 'ü')
    {
        a = tolower(a); // converting all chars to lowercase for avoid errors
    }
    char sesli[8] = {'a', 'e', 'ı', 'i', 'o', 'ö', 'u', 'ü'};
    for (int i = 0; i < 8; i++)
    {
        if (a == sesli[i])
        {
            returnCount++;
        }
    }
    return returnCount;
}

// checks if the char that used in function is consonant
int isConsonant(char a)
{
    int returnCount = 0;
    a = tolower(a); // converting all chars to lowercase for avoid errors
    char consonant[21] = "bcçdfgğhjklmnprsştvyz";
    for (int i = 0; i < 21; i++)
    {
        if (a == consonant[i])
        {
            returnCount++;
        }
    }
    return returnCount;
}

// it finds the connexions with checking the last char of the first word, and the first char of the second word
void connexion(char *(dictionary[500]), int *connexionCount, int wordCount)
{
    printf("\nconnexions are = \n");
    for (int k = 0; k < wordCount - 1; k++)
    {
        int len1 = strlen(dictionary[k]);
        int len2 = strlen(dictionary[k + 1]);
        if (isConsonant(dictionary[k][len1 - 1]) != 0 && isVowel(dictionary[k + 1][0]) != 0)
        {
            *connexionCount = *connexionCount + 1;
            printf("'%s %s'\n", dictionary[k], dictionary[k + 1]);
        }
    }
    printf("\ntotal number of connexion  = %d\n\n", *connexionCount);
}

// plural word finder -- but i just used word searching algorithm that i wrote, for finding plural suffixes
void plural(char *(dictionary[500]), int wordcount)
{
    char word1[100] = "ler";
    wordSearch(dictionary, wordcount, word1);
    char word2[100] = "lar";
    wordSearch(dictionary, wordcount, word2);
}

// the hidden one is an algorithm that searches all words until it finds identical characters in word, then it searches for lenght of the searched word with the chars of "word".
// The open code checks for words based on whether the strstr function returns null
void wordSearch(char *(dictionary[500]), int wordcount, char word[100])
{
    int wordcounter = 0;
    int len1;
    int *ptr;
    len1 = strlen(word);

    printf("These words are containing %s :\n", word);
    for (int i = 0; i < wordcount; i++)
    {
        ptr = strstr(dictionary[i], word);
        if (ptr != NULL)
        {
            wordcounter++;
            printf("%s\n", dictionary[i]);
        }
    }

    printf("%d word contains %s\n\n", wordcounter, word);
    /*
    for (int i = 0; i < wordcount; i++)
    {
        int counter = 0;
        int len2 = strlen(dictionary[i]);
        for (int j = 0; j < len2; j++)
        {
            if (dictionary[i][j] == word[0])
            {
                for (int k = 0; k < len1; k++)
                {
                    if (dictionary[i][j + k] == word[k])
                    {
                        counter++;
                    }
                }
                if (counter == len1)
                {
                    wordcounter++;
                    printf("%s\n", dictionary[i]);
                }
            }
            if (counter == len1)
            {
                break;
            }
        }
    }*/
}

// a funtion that writes the words that contains strong consonant inside
// it checks every char in every words every letter with StrongConsonant[] array
void strongSoftConsonant(char *(dictionary[500]), int wordCount)
{
    printf("These words are containing strong consonants :\n");
    int wordcounter = 0;
    for (int i = 0; i < wordCount; i++)
    {
        int counter = 0;
        int len = strlen(dictionary[i]);
        for (int j = 0; j < len; j++)
        {
            char a = dictionary[i][j];
            a = tolower(a); // converting all chars to lowercase for avoid errors
            char StrongConsonant[8] = {'t', 'ç', 'f', 's', 'p', 'k', 'h', 'ş'};
            for (int j = 0; j < 8; j++)
            {
                if (a == StrongConsonant[j])
                {
                    counter++;
                }
            }
        }
        if (counter != 0)
        {
            printf("%s\n", dictionary[i]);
            wordcounter++;
        }
    }
    printf("%d word has strong Consonent\n\n", wordcounter);
    printf("These words are containing soft consonants :\n");
    int wordcounter2 = 0;
    for (int i = 0; i < wordCount; i++)
    {
        int counter = 0;
        int len = strlen(dictionary[i]);
        for (int j = 0; j < len; j++)
        {
            char a = dictionary[i][j];
            a = tolower(a); // converting all chars to lowercase for avoid errors
            char SoftConsonant[13] = {'b', 'c', ' d', ' g', ' ğ', 'j', 'l', 'm', 'n', 'r', 'v', 'y', 'z'};
            for (int j = 0; j < 13; j++)
            {
                if (a == SoftConsonant[j])
                {
                    counter++;
                }
            }
        }
        if (counter != 0)
        {
            printf("%s\n", dictionary[i]);
            wordcounter2++;
        }
    }
    printf("%d word has Soft Consonent", wordcounter2);
}
