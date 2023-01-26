#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> //her bruger vi conio.h til at kunne bruge getch
#include <time.h>
#include <unistd.h>
#include "header.h"

manuscript *read_manuscript(int file_index, char *file_names[3])
{
    FILE *file = fopen(file_names[file_index], "r");

    if (file == NULL)
    {
        printf("\nKunne ikke indlaese fil");
        exit(EXIT_FAILURE);
    }

    manuscript *manuscript_ptr = (manuscript *) malloc(16 * sizeof(manuscript));
    int i = 0;

    for (i = 0; i < 16; i++)
    {
        fgets(manuscript_ptr[i].question, 650, file);

        fgets(manuscript_ptr[i].answer_1, 300, file);

        fgets(manuscript_ptr[i].answer_2, 300, file);
    }

    fclose(file);

    return manuscript_ptr;
}

int chat_with_user(int function_index, manuscript *manuscript_ptr)
{
    int user_answer;

    if (function_index == 0)
    {
        printf("\n\n--------------\n");
        printf("\nSpoergsmaal: %s\n\n", manuscript_ptr[function_index].question);
        printf("1) %s\n", manuscript_ptr[function_index].answer_1);
        printf("2) %s\n", manuscript_ptr[function_index].answer_2);
        printf("4) Afslut samtalen ...\n");
    }
    else
    {
        printf("\n\n--------------\n");
        printf("\nSpoergsmaal: %s\n\n", manuscript_ptr[function_index].question);
        printf("1) %s\n", manuscript_ptr[function_index].answer_1);
        printf("2) %s\n", manuscript_ptr[function_index].answer_2);
        printf("3) Gaa tilbage til sidste spoergsmaal\n");
        printf("\n4) Afslut samtalen ...\n");
    }

    printf("\nVaelg dit svar: ");
    scanf("%d", &user_answer);

    if (user_answer > 2 && function_index == 0)
    {
        printf("\nEXIT - Du har valgt at afslutte samtalen");
        exit(EXIT_FAILURE);
    }

    chat_log(function_index, manuscript_ptr, user_answer);

    if (user_answer != 1 && user_answer != 2 && user_answer != 3)
    {
        printf("\nEXIT - Du har valgt at afslutte samtalen\n");
        exit(EXIT_FAILURE);
    }

    if (user_answer == 1 && function_index != 0)
    {
        function_index = function_index * 2;
        return function_index;
    }
    else if (user_answer == 2 && function_index != 0)
    {
        function_index = function_index * 2 + 1;
        return function_index;
    }
    else if (user_answer == 1 && function_index == 0)
    {
        function_index = 2;
        return function_index;
    }
    else if (user_answer == 2 && function_index == 0)
    {
        function_index = 3;
        return function_index;
    }
    else if (user_answer == 3 && function_index % 2 == 0)
    {
        function_index = function_index / 2;
        return function_index;
    }
    else if (user_answer == 3 && function_index % 2 != 0)
    {
        function_index = (function_index - 1) / 2;
        return function_index;
    }
}

void chat_log(int function_index, manuscript *manuscript_ptr, int user_answer)
{
    FILE *file = fopen("chat_log.txt", "a");

    if (file == NULL)
    {
        printf("\nKunne ikke indlaese fil");
        exit(EXIT_FAILURE);
    }

    if (function_index > 8 && function_index < 16 && function_index != 8 && function_index != 12)
    {
        fprintf(file, "\nKommentar: %s---------\n", manuscript_ptr[function_index].question);
    }
    else
    {
        fprintf(file, "\nSpoergsmaal: %s---------\n", manuscript_ptr[function_index].question);
        fprintf(file, "1) %s\n", manuscript_ptr[function_index].answer_1);
        fprintf(file, "2) %s\n", manuscript_ptr[function_index].answer_2);

        if (user_answer == 1)
        {
            fprintf(file, "Du valgte: %s\n", manuscript_ptr[function_index].answer_1);
        }
        else if (user_answer == 2)
        {
            fprintf(file, "Du valgte: %s\n", manuscript_ptr[function_index].answer_2);
        }
        else if (user_answer == 3)
        {
            fprintf(file, "Du valgte: At gå tilbage til sidste spørgsmål\n\n");
        }
    }

    fclose(file);
}

void anxiety_tracker(int climate_anxiety[3], int climate_anxiety_counter)
{
    int user_answer;

    printf("\nHvor meget klima-angst foeler du lige nu paa en skala fra 1-10? ");
    scanf("%d", &user_answer);
    printf("\nTak! :-) \n\n");

    climate_anxiety[climate_anxiety_counter] = user_answer;
}

void print_anxiety_graph(int climate_anxiety[3])
{
    char empty_line[300] = {"|                                                    \n"};
    char graph_lines[15][500];
    int i, k, s;
    char char_integers[12][3] = {"-", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    char *ptr;

    for (i = 0; i < 14; i++)
    {
        strcpy(graph_lines[i], empty_line);
    }

    strcpy(graph_lines[14], "|__________________________________\n");

    for (i = 0; i < 3; i++)
    {
        for (k = 0; k < 14; k++)
        {
            if (climate_anxiety[i] == k && i == 0)
            {
                ptr = graph_lines[13 - k];

                strcat(ptr, "|start");

                for (s = 0; s < 4; s++)
                {
                    strcat(ptr, char_integers[0]);
                }

                strcat(ptr, char_integers[k]);
            }

            else if (climate_anxiety[i] == k && i == 1)
            {
                ptr = graph_lines[13 - k];

                strcat(ptr, "|midt ");

                if (climate_anxiety[1] == climate_anxiety[0])
                {
                    for (s = 0; s < 4; s++)
                    {
                        strcat(ptr, char_integers[0]);
                    }
                }
                else
                {
                    for (s = 0; s < 8; s++)
                    {
                        strcat(ptr, char_integers[0]);
                    }
                }

                strcat(ptr, char_integers[k]);
            }

            else if (climate_anxiety[i] == k && i == 2)
            {
                ptr = graph_lines[13 - k];

                strcat(ptr, "|slut ");

                if (climate_anxiety[2] == climate_anxiety[0] && climate_anxiety[2] != climate_anxiety[1])
                {
                    for (s = 0; s < 8; s++)
                    {
                        strcat(ptr, char_integers[0]);
                    }
                }
                else if (climate_anxiety[2] == climate_anxiety[1] && climate_anxiety[2] == climate_anxiety[0])
                {
                    for (s = 0; s < 4; s++)
                    {
                        strcat(ptr, char_integers[0]);
                    }
                }
                else if (climate_anxiety[0] == climate_anxiety[1])
                {
                    for (s = 0; s < 20; s++)
                    {
                        strcat(ptr, char_integers[0]);
                    }
                }
                else if (climate_anxiety[2] == climate_anxiety[1] && climate_anxiety[2] != climate_anxiety[0])
                {
                    for (s = 0; s < 8; s++)
                    {
                        strcat(ptr, char_integers[0]);
                    }
                }
                else
                {
                    for (s = 0; s < 16; s++)
                    {
                        strcat(ptr, char_integers[0]);
                    }
                }

                strcat(ptr, char_integers[k]);
            }
        }
    }

    FILE *file = fopen("chat_log.txt", "a");

    if (file == NULL)
    {
        printf("\nKunne ikke indlaese fil");
        exit(EXIT_FAILURE);
    }

    printf("\n----------------------------\n\n");
    fprintf(file, "\n----------------------------\n\n");

    printf("Her er progressionen over din klima-angst igennem samtalen: \n\n");
    fprintf(file, "Her er progressionen over din klima-angst igennem samtalen: \n\n");

    printf("\n       ____________________");
    printf("\n      |x-akse : tid        |\n      |y-akse : klima-angst|\n");
    printf("      |____________________| \n");

    fprintf(file, "\n       ____________________");
    fprintf(file, "\n      |x-akse : tid        |\n      |y-akse : klima-angst|\n");
    fprintf(file, "      |____________________| \n");

    printf("\n");
    fprintf(file, "\n");

    for (i = 0; i < 15; i++)
    {
        printf("%s", graph_lines[i]);
        fprintf(file, graph_lines[i]);
    }

    fclose(file);
}

void print_graph_comment(int climate_anxiety[3])
{
    FILE *file = fopen("chat_log.txt", "a");

    if (file == NULL)
    {
        printf("\nKunne ikke indlaese fil");
        exit(EXIT_FAILURE);
    }

    if (climate_anxiety[0] == climate_anxiety[1] && climate_anxiety[1] == climate_anxiety[2])
    {
        printf("\nDin klima-angst er helt uaendret! Maaske vi kunne chatte igen snart?\n");
        fprintf(file, "\nDin klima-angst er helt uaendret! Maaske vi kunne chatte igen snart?\n");

        if (climate_anxiety[2] > 5)
        {
            printf("\nDin klima-angst er nemlig paa et hoejt niveau\n");
            fprintf(file, "\nDin klima-angst er nemlig paa et hoejt niveau\n");
        }
        else
        {
            printf("\nDin klima-angst er heldigvis paa et lavt niveau og det er rigtig godt at se! :)\n");
            fprintf(file, "\nDin klima-angst er heldigvis paa et lavt niveau og det er rigtig godt at se! :)\n");
        }
    }

    else if (climate_anxiety[0] >= climate_anxiety[1] && climate_anxiety[1] >= climate_anxiety[2])
    {
        printf("\nDet er godt at se, at jeg kunne hjaelpe med at nedbringe din klima-angst!\n");
        fprintf(file, "\nDet er godt at se, at jeg kunne hjaelpe med at nedbringe din klima-angst!\n");

        if (climate_anxiety[2] > 5)
        {
            printf("\nDin klima-angst er dog stadig paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
            fprintf(file, "\nDin klima-angst er dog stadig paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
        }
        else
        {
            printf("\nDin klima-angst er heldigvis paa et lavt niveau og det er rigtig godt at se! :)\n");
            fprintf(file, "\nDin klima-angst er heldigvis paa et lavt niveau og det er rigtig godt at se! :)\n");
        }
    }

    else if (climate_anxiety[0] <= climate_anxiety[1] && climate_anxiety[1] <= climate_anxiety[2])
    {
        printf("\nSikke noget! Du har faaet mere klima-angst af at chatte med mig! Det er jeg ked af :(\n");
        fprintf(file, "\nSikke noget! Du har faaet mere klima-angst af at chatte med mig! Det er jeg ked af :(\n");

        if (climate_anxiety[2] > 5)
        {
            printf("\nDin klima-angst er paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
            fprintf(file, "\nDin klima-angst er paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
        }
        else
        {
            printf("\nDin klima-angst er heldigvis paa et lavt niveau og det er rigtig godt at se! :)\n");
            fprintf(file, "\nDin klima-angst er dog stadig paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
        }
    }

    else if (climate_anxiety[0] >= climate_anxiety[1] && climate_anxiety[1] <= climate_anxiety[2])
    {
        printf("\nSikke noget! Du har faaet mere klima-angst af at chatte med mig! Det er jeg ked af :(\n");
        fprintf(file, "\nSikke noget! Du har faaet mere klima-angst af at chatte med mig! Det er jeg ked af :(\n");

        if (climate_anxiety[2] > 5)
        {
            printf("\nDin klima-angst er paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
            fprintf(file, "\nDin klima-angst er paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
        }
        else
        {
            printf("\nDin klima-angst er heldigvis paa et lavt niveau og det er rigtig godt at se! :)\n");
            fprintf(file, "\nDin klima-angst er dog stadig paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
        }
    }

    else if (climate_anxiety[0] <= climate_anxiety[1] && climate_anxiety[1] >= climate_anxiety[2])
    {
        printf("\nDet er godt at se, at jeg kunne hjaelpe med at nedbringe din klima-angst!\n");
        fprintf(file, "\nDet er godt at se, at jeg kunne hjaelpe med at nedbringe din klima-angst!\n");

        if (climate_anxiety[2] > 5)
        {
            printf("\nDin klima-angst er dog stadig paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
            fprintf(file, "\nDin klima-angst er dog stadig paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
        }
        else
        {
            printf("\nDin klima-angst er heldigvis paa et lavt niveau og det er rigtig godt at se! :)\n");
            fprintf(file, "\nDin klima-angst er dog stadig paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
        }
    }

    fclose(file);
}

void read_context(char context[3][650])
{
    FILE *file = fopen("context.txt", "r");

    if (file == NULL)
    {
        printf("\nKunne ikke indlaese fil");
        exit(EXIT_FAILURE);
    }

    int i;

    for (i = 0; i < 3; i++)
    {
        fgets(context[i], 650, file);
    }

    fclose(file);
}

void print_context(char context[3][650], int file_index)
{
    printf("\n%s\n", context[file_index]);
    // sleep funktionen bruges for at give brugeren tid til at læse.
    sleep(5);
}

int print_comment(manuscript *manuscript_ptr, int function_index)
{
    printf("\n%s\n", manuscript_ptr[function_index].question);
    // sleep funktionen bruges for at give brugeren tid til at læse.

    sleep(5);

    // 16 returneres fordi det genstarter det binære træ.
    return 16;
}
