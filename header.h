
struct manuscript
{
    char question[450];
    char answer_1[300];
    char answer_2[300];
};
typedef struct manuscript manuscript;

manuscript *read_manuscript(int file_index, char *file_names[3]);
int chat_with_user(int index, manuscript *manuscript_ptr);
void chat_log(int index, manuscript *manuscript_ptr, int answer);
void anxiety_tracker(int climate_anxiety[3], int climate_anxiety_counter);
void read_context(char context[3][650]);
void print_context(char context[3][650], int file_index);
int print_comment(manuscript *manuscript_ptr, int function_index);
void print_anxiety_graph(int climate_anxiety[3]);
void print_graph_comment(int climate_anxiety[3]);
