#include "converter.h"

int process_line(IS is, Dllist content);
void modify_content(IS is, Dllist content, int is_delete);
void content_write(Dllist content, int number, char character);
void content_delete(Dllist content, int number, char character);
char convert_token(char *token);
void write_content_to_file(Dllist content, char *output_file);

const char write_command[] = "yaz:";
const char delete_command[] = "sil:";
const char go_end_command[] = "sonagit:";
const char stop_command[] = "dur:";

Dllist cursor;

void convert_file(char *input_file, char *output_file)
{
        printf("INFO: Reading file: %s...\n", input_file);

        Dllist content = new_dllist();
        cursor = content;

        // open file
        IS is = new_inputstruct(input_file);
        if (is == NULL)
        {
                perror(input_file);
                exit(1);
        }

        // read and process file line by line
        while (get_line(is) >= 0)
        {
                if (process_line(is, content))
                {
                        printf("INFO: Stop command found. Parsing successful.\n");
                        break;
                }
        }

        // close input file
        jettison_inputstruct(is);

        // write content to output file
        printf("INFO: Writing to file: %s...\n", output_file);
        write_content_to_file(content, output_file);

        // free memory
        free_dllist(content);
        printf("INFO: Done.\n");
}

/*
 * Processes a line of input.
 * Return 1 if the program should stop 0 otherwise.
 */
int process_line(IS is, Dllist content)
{
        int word_count = is->NF;

        if (word_count == 0)
        {
                printf("DEBUG: Empty line: %d\n", is->line);
                return 0;
        }

        char *command = is->fields[0]; // first word on the line is the command
        if (strcmp(command, write_command) == 0)
        {
                modify_content(is, content, 0);
        }
        else if (strcmp(command, delete_command) == 0)
        {
                modify_content(is, content, 1);
        }
        else if (strcmp(command, go_end_command) == 0)
        {
                cursor = dll_last(content);
        }
        else if (strcmp(command, stop_command) == 0)
        {
                cursor = NULL;
                return 1;
        }
        else
        {
                fprintf(stderr, "ERROR: Invalid command: `%s`\n", command);
                exit(1);
        }

        return 0;
}

/*
 * Modifies the content according to the command.
 * If is_delete argument is 1, the command is delete, otherwise it is write.
 */
void modify_content(IS is, Dllist content, int is_delete)
{
        int word_count = is->NF;

        /*
         * check if the number of parameter is even (command: parameter parameter ...)
         * since the first parameter is the number of times to write and the second parameter is the character to write
         */
        if ((word_count - 1) % 2 != 0)
        {
                fprintf(stderr, "ERROR: The number of parameters should be even. Error on line: %d\n", is->line);
                exit(1);
        }

        int i = 1; // skip the command
        while (i < word_count)
        {
                char *number = is->fields[i];
                char character = convert_token(is->fields[i + 1]);

                if (!is_number(number))
                {
                        fprintf(stderr, "ERROR: The parameter in the odd index should be a number. Error on line: %d\n", is->line);
                        exit(1);
                }

                if (is_delete)
                {
                        content_delete(content, atoi(number), character);
                }
                else
                {
                        content_write(content, atoi(number), character);
                }

                i += 2;
        }
}

void content_write(Dllist content, int number, char character)
{
        for (int j = 0; j < number; j++)
        {
                dll_insert_a(cursor, new_jval_c(character));
                cursor = dll_next(cursor);
        }
}

void content_delete(Dllist content, int number, char character)
{
        int _number = number;

        while (_number > 0 && cursor != content)
        {
                if (jval_c(dll_val(cursor)) == character)
                {
                        Dllist temp = dll_prev(cursor);
                        dll_delete_node(cursor);
                        cursor = temp;
                        _number--;
                }
                else
                {
                        cursor = dll_prev(cursor);
                }
        }
}

char convert_token(char *token)
{
        if (strcmp(token, "\\b") == 0)
        {
                return ' ';
        }
        else if (strcmp(token, "\\n") == 0)
        {
                return '\n';
        }
        else
        {
                return token[0];
        }
}

void write_content_to_file(Dllist content, char *output_file)
{
        FILE *file = fopen(output_file, "w");
        if (file == NULL)
        {
                perror(output_file);
                exit(1);
        }

        Dllist node;
        dll_traverse(node, content)
        {
                fputc(jval_c(dll_val(node)), file);
        }

        fclose(file);
}