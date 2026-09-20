#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_DOCS 50
#define MAX_LEN 5000
#define MAX_TOKENS 500
#define MAX_TOKEN_LEN 50
#define NUM_STOP_WORDS 8
char documents[MAX_DOCS][MAX_LEN];
char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
char stop_words[NUM_STOP_WORDS][MAX_TOKEN_LEN] = {"the", "is", "a", "an", "and", "in", "of", "to"};
char unique_tok[MAX_TOKENS][MAX_TOKEN_LEN];
int last_tok_idx[MAX_DOCS];
int document_count = 0;
int token_count = 0;
int unique_tok_count = 0;
int set_done = 0;
int preprocess_done = 0;
;

void empty()
{
    for (int i = 0; i < MAX_DOCS; i++)
    {
        documents[i][0] = '\0';
    }
    for (int i = 0; i < MAX_TOKENS; i++)
    {
        tokens[i][0] = '\0';
    }
}

void normalize_case_all()
{
    for (int i = 0; i < document_count; i++)
    {
        for (int j = 0; documents[i][j] != '\0'; j++)
        {
            documents[i][j] = tolower(documents[i][j]);
        }
        printf("Document %d: %s\n", i + 1, documents[i]);
    }
    printf("Documents normalized.\n");
}

int break_or_not(char ch)
{
    return !isalnum(ch); // find breaking characters
}

void tokenize_all()
{
    token_count = 0;
    for (int d = 0; d < document_count; d++)
    {
        int len = strlen(documents[d]);
        int i = 0;
        while (i < len)
        {
            // Skip delimiters
            while (i < len && break_or_not(documents[d][i]))
            {
                i++;
            }
            char word[MAX_TOKEN_LEN] = "";
            int pos = 0;
            while (i < len && isalnum(documents[d][i]))
            {
                if (pos < MAX_TOKEN_LEN - 1)
                {
                    word[pos++] = documents[d][i];
                }
                i++;
            }
            word[pos] = '\0';

            if (strlen(word) > 0 && token_count < MAX_TOKENS)
            {
                strcpy(tokens[token_count], word);
                token_count++;
            }
        }
    }

    for (int i = 0; i < token_count; i++)
    {
        printf("%d. %s\n", i + 1, tokens[i]);
    }

    printf("Tokenization complete. Total tokens: %d\n", token_count);
}

void remove_stop_words_all()
{
    int idx = 0, doc_id = 0, token_in_doc = 0;
    for (int i = 0; i < token_count; i++)
    {
        // Detect if this token belonged to the next document
        int stop = 0;
        for (int j = 0; j < NUM_STOP_WORDS; j++)
        {
            if (strcmp(tokens[i], stop_words[j]) == 0)
            {
                stop = 1;
                break;
            }
        }
        if (!stop)
        {
            strcpy(tokens[idx], tokens[i]);
            idx++;
            token_in_doc++;
        }
        // Store last_token_index if next document starts
        if (i == token_count - 1 || (doc_id + 1 < document_count && (i + 1 == token_count / document_count * (doc_id + 1))))
        {
            last_tok_idx[doc_id] = idx - 1;
            doc_id++;
            token_in_doc = 0;
        }
    }
    token_count = idx;
    for (int i = 0; i < token_count; i++)
    {
        printf("%d. %s\n", i + 1, tokens[i]);
    }
    printf("Stop-word removal complete. Tokens remaining: %d\n", token_count);
}

void stem_all_tokens()
{
    for (int i = 0; i < token_count; i++)
    {
        int len = strlen(tokens[i]);

        if (len > 4 && strcmp(&tokens[i][len - 3], "ing") == 0)
        {
            tokens[i][len - 3] = '\0';
        }
        else if (len > 3 && strcmp(&tokens[i][len - 2], "ed") == 0)
        {
            tokens[i][len - 2] = '\0';
        }
        else if (len > 2 && tokens[i][len - 1] == 's')
        {
            tokens[i][len - 1] = '\0';
        }
    }
    for (int i = 0; i < token_count; i++)
    {
        printf("%d. %s\n", i + 1, tokens[i]);
    }
    printf("Stemming complete. Total stemmed tokens: %d\n", token_count);
}

double compute_tf(char word[], int doc_id)
{
    int start = (doc_id == 0) ? 0 : last_tok_idx[doc_id - 1] + 1;
    int end = last_tok_idx[doc_id];
    int count = 0;
    for (int i = start; i <= end; i++)
    {
        if (strcmp(tokens[i], word) == 0)
        {
            count++;
        }
    }
    int total = end - start + 1;
    if (total == 0)
    {
        return 0.0;
    }
    double tf = (double)count / total;
    return tf;
}

double compute_idf(char word[])
{
    int tmp = 0;
    for (int doc = 0; doc < document_count; doc++)
    {
        int start = (doc == 0) ? 0 : last_tok_idx[doc - 1] + 1;
        int end = last_tok_idx[doc];
        for (int i = start; i <= end; i++)
        {
            if (strcmp(tokens[i], word) == 0)
            {
                tmp++;
                break;
            }
        }
    }
    double idf = log10((double)MAX_DOCS / (1 + tmp));
    return idf;
}

void compute_tfidf_all(char word[])
{
    double idf = compute_idf(word);
    printf("TF-IDF for '%s':\n", word);
    for (int i = 0; i < document_count; i++)
    {
        double tf = compute_tf(word, i);
        double tfidf = tf * idf;
        printf("Document %d: %.4lf\n", i + 1, tfidf);
    }
}
void unique_token_list()
{
    unique_tok_count = 0;

    for (int i = 0; i < token_count; i++)
    {
        int found = 0;
        for (int j = 0; j < unique_tok_count; j++)
        {
            if (strcmp(tokens[i], unique_tok[j]) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            strcpy(unique_tok[unique_tok_count], tokens[i]);
            unique_tok_count++;
        }
    }
    // Sort alphabetically
    for (int i = 0; i < unique_tok_count - 1; i++)
    {
        for (int j = i + 1; j < unique_tok_count; j++)
        {
            if (strcmp(unique_tok[i], unique_tok[j]) > 0)
            {
                char temp[MAX_TOKEN_LEN];
                strcpy(temp, unique_tok[i]);
                strcpy(unique_tok[i], unique_tok[j]);
                strcpy(unique_tok[j], temp);
            }
        }
    }
}

void display_stat()
{
    if (document_count == 0)
    {
        printf("No documents set. Use 'set' command first.\n");
        return;
    }
    unique_token_list();
    printf("============== TF ================\n");
    printf("            ");
    for (int i = 0; i < document_count; i++)
    {
        printf("doc%d       ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < unique_tok_count; i++)
    {
        printf("%-9s", unique_tok[i]);
        for (int j = 0; j < document_count; j++)
        {
            printf("  %.4lf   ", compute_tf(unique_tok[i], j));
        }
        printf("\n");
    }
    printf("=============== IDF ===============\n");
    printf("             IDF\n");
    for (int i = 0; i < unique_tok_count; i++)
    {
        double idf = compute_idf(unique_tok[i]);
        printf("%-10s%  .4lf\n", unique_tok[i], idf);
    }
    printf("============= TF-IDF ==============\n");
    printf("            ");
    for (int i = 0; i < document_count; i++)
    {
        printf("doc%d       ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < unique_tok_count; i++)
    {
        double idf = compute_idf(unique_tok[i]);
        printf("%-9s", unique_tok[i]);
        for (int j = 0; j < document_count; j++)
        {
            double tfidf = compute_tf(unique_tok[i], j) * idf;
            printf("  %.4lf   ", tfidf);
        }
        printf("\n");
    }
}

void set()
{
    int n;
    printf("Enter number of documents (1-50): ");
    scanf("%d", &n);
    document_count = n;
    getchar();
    if (n < 1 || n > 50)
    {
        printf("Invalid number of documents. Must be from 1 to 50.\n");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        printf("Enter document %d: ", i + 1);
        if (fgets(documents[i], MAX_LEN, stdin))
        {
            int len = strlen(documents[i]);
            // Check if input was too long
            if (len > 0 && documents[i][len - 1] != '\n')
            {
                printf("Document too long\n");
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF)
                {
                    documents[i][0] = '\0';
                }
                i--;
                continue;
            }
            // Remove trailing newline if present
            if (len > 0 && documents[i][len - 1] == '\n')
            {
                documents[i][len - 1] = '\0';
            }
        }
    }
    printf("Documents set successfully. Please enter 'preprocess' command now. It will not take other commands.\n");
}

void preprocess()
{
    if (documents[0][0] == '\0')
    {
        printf("No documents set. Use 'set' command first.\n");
        return;
    }
    printf("Normalized documents:\n");
    normalize_case_all();
    printf("Tokens:\n");
    tokenize_all();
    printf("Tokens after stop-word removal:\n");
    remove_stop_words_all();
    printf("Stemmed Tokens:\n");
    stem_all_tokens();
}

void Help()
{
    printf("set        - Prompt for the number of documents and their text.\n");
    printf("preprocess - Apply normalization, tokenization, stop-words removal, and stemming orderly.\n");
    printf("tf         - Compute and display Term Frequency for a specified word across documents.\n");
    printf("idf        - Compute and display Inverse Document Frequency for a specified word.\n");
    printf("tfidf      - Compute and display TF-IDF scores for a specified word across documents.\n");
    printf("stat       - Display TF, IDF, and TF-IDF for all tokens across all documents in a matrix format.\n");
    printf("help       - Print the list of all available commands.\n");
    printf("exit       - Exit the program.\n");
}

int main()
{
    empty();
    printf("Welcome to the Document Processing System!\n");
    Help();
    char input[100];
    while (1)
    {
        printf("Enter command: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // removes newline
        if (set_done == 0 && strcmp(input, "set") == 0)
        {
            set();
            set_done = 1;
            preprocess_done = 0;
            continue;
        }
        if (set_done == 1 && preprocess_done == 0)
        {
            if (strcmp(input, "preprocess") == 0)
            {
                preprocess();
                preprocess_done = 1;
                continue;
            }
            else
            {
                printf("Documents set successfully. Please enter 'preprocess' command now. It will not take other commands.\n");
                continue;
            }
        }
        else if (strcmp(input, "preprocess") == 0)
        {
            if (document_count == 0)
            {
                printf("No documents set. Use 'set' command first.\n");
                continue;
            }
            else
            {
                preprocess();
                if (token_count == 0)
                {
                    printf("No tokens available.\n");
                }
            }
        }
        else if (strcmp(input, "tf") == 0)
        {
            if (document_count == 0)
            {
                printf("No documents set. Use 'set' command first.\n");
                continue;
            }
            if (token_count == 0)
            {
                printf("No tokens available. Please preprocess documents with valid content.\n");
                continue;
            }
            char word[100];
            printf("Enter word to compute TF: ");
            fgets(word, sizeof(word), stdin);
            word[strcspn(word, "\n")] = '\0'; // remove newline
            for (int i = 0; i < document_count; i++)
            {
                printf("Document %d: %.4lf\n", i + 1, compute_tf(word, i));
            }
        }
        else if (strcmp(input, "idf") == 0)
        {
            if (document_count == 0)
            {
                printf("No documents set. Use 'set' command first.\n");
                continue;
            }
            if (token_count == 0)
            {
                printf("No tokens available.\n");
                continue;
            }
            char word[100];
            printf("Enter word to compute IDF: ");
            fgets(word, sizeof(word), stdin);
            word[strcspn(word, "\n")] = '\0';
            printf("IDF for '%s': %.4lf\n", word, compute_idf(word));
        }
        else if (strcmp(input, "tfidf") == 0)
        {
            if (document_count == 0)
            {
                printf("No documents set. Use 'set' command first.\n");
                continue;
            }
            if (token_count == 0)
            {
                printf("No tokens available.\n");
                continue;
            }
            char word[100];
            printf("Enter word to compute TF-IDF: ");
            fgets(word, sizeof(word), stdin);
            word[strcspn(word, "\n")] = '\0';
            compute_tfidf_all(word);
        }
        else if (strcmp(input, "stat") == 0)
        {
            if (token_count == 0)
            {
                printf("No tokens available.\n");
                continue;
            }
            display_stat();
        }
        else if (strcmp(input, "help") == 0)
        {
            Help();
        }
        else if (strcmp(input, "exit") == 0)
        {
            printf("Exiting the program.\n");
            return 0;
        }
        else
        {
            printf("Unknown command: Type 'help' for list of commands.\n");
        }
    }
    return 0;
}