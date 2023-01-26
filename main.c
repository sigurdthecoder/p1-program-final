#include <stdio.h> //Vi bruger stdio.h til at kunne bruge printf og scanf
#include <stdlib.h> //Vi bruger stdlib.h til at kunne bruge exit
#include <string.h> //Vi bruger string.h til at kunne bruge strcmp
#include <conio.h> //
#include <unistd.h> //Vi bruger unistd.h til at kunne bruge sleep
#include "header.h" //Vi bruger header.h til at kunne bruge funktionerne i header.h


int main()
{

    int function_index = 0, file_index = 0, climate_anxiety_counter = 0, end_of_tree = 16; // Vi definerer funktion_index, file_index, climate_anxiety_counter og end_of_tree som int. 
    int climate_anxiety[3]; // Vi definerer climate_anxiety som en int-array med 3 pladser.
    char username[20]; // Vi definerer username som en char-array med 20 pladser.
    char context[3][650]; // Vi definerer context som en char-array med 3 rækker og 650 pladser.
    char *file_names[3] = {"manuscript1.txt", "manuscript2.txt", "manuscript3.txt"}; // Vi definerer file_names som en char-array med 3 pladser. Sammenhængen mellem file_index og file_names -- file_names[file_index]

    printf("\nHej med dig! Hvad hedder du? ");
    scanf("%s", &username);
    printf("\nGodt at moede dig %s!\n\n", username);

    manuscript *manuscript_ptr = read_manuscript(file_index, file_names);
    read_context(context); // forholder sig til vores array af manuscriptstructs som en pointer. funktionen sørger for at få det indlæst og lagt det rigtigt ind i structen.
    
    // chat_log.txt åbnes her i stedet for i funktionen chat_log, da write-mode ellers overwriter filens indhold.
    // .txt-filen åbnes altså her og bliver appended i chat_log funktionen.
    FILE *file = fopen("chat_log.txt", "w");
    if (file == NULL)
    {
        printf("\nKunne ikke indlaese fil");
        exit(EXIT_FAILURE);
    }

    fclose(file);



    while (function_index < end_of_tree) // Vi bruger while-loop til at køre programmet indtil funktion_index er større end end_of_tree.
    {
        if (function_index == 0) //Vi giver her brugeren et spørgsmål og en context ved starten af hvert træ.
        {
            anxiety_tracker(climate_anxiety, climate_anxiety_counter);
            print_context(context, file_index);
            climate_anxiety_counter++;
        }


        if (function_index > 8 && function_index < end_of_tree && function_index != 8 && function_index != 12)
        {
            chat_log(function_index, manuscript_ptr, 1);
            function_index = print_comment(manuscript_ptr, function_index);
        }
        else
        {
            function_index = chat_with_user(function_index, manuscript_ptr);
        }
        

        if (function_index >= end_of_tree && climate_anxiety_counter > 2)
        {
            print_anxiety_graph(climate_anxiety);
            print_graph_comment(climate_anxiety);
        }

        else if (function_index >= end_of_tree)
        {
            function_index = 0;
            file_index++;
            free(manuscript_ptr);
            manuscript_ptr = read_manuscript(file_index, file_names);
        }
    }

    return 0;
}