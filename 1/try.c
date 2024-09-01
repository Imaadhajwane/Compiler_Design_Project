#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define token types
typedef enum
{
    MESSAGE,
    STRUCT,
    HEADER,
    FIELD,
    IDENTIFIER,
    TYPE,
    SEMICOLON,
    LEFT_BRACE,
    RIGHT_BRACE,
    COLON,
    END_OF_FILE,
    ERROR
} TokenType;

// Define token structure
typedef struct
{
    TokenType type;
    char value[50];
    int line;
} Token;

// Function to get the next character from input stream
char getNextChar(FILE *fp)
{
    return fgetc(fp);
}

// Function to unget the character back to the input stream
void ungetChar(char c, FILE *fp)
{
    ungetc(c, fp);
}

// Function to recognize keywords and identifiers
TokenType checkKeyword(char *str)
{
    if (strcmp(str, "message") == 0)
    {
        return MESSAGE;
    }
    else if (strcmp(str, "struct") == 0)
    {
        return STRUCT;
    }
    else if (strcmp(str, "header") == 0)
    {
        return HEADER;
    }
    else if (strcmp(str, "field") == 0)
    {
        return FIELD;
    }
    else
    {
        return IDENTIFIER;
    }
}

// Function to tokenize the input
Token getNextToken(FILE *fp)
{
    Token token;
    char c = getNextChar(fp);

    // Skip white spaces and count lines
    while (isspace(c))
    {
        if (c == '\n')
        {
            token.line++;
        }
        c = getNextChar(fp);
    }

    // Check for end of file
    if (c == EOF)
    {
        token.type = END_OF_FILE;
        strcpy(token.value, "");
        return token;
    }

    // Check for identifiers or keywords
    if (isalpha(c) || c == '_')
    {
        int i = 0;
        token.value[i++] = c;
        c = getNextChar(fp);
        while (isalnum(c) || c == '_')
        {
            token.value[i++] = c;
            c = getNextChar(fp);
        }
        token.value[i] = '\0';
        ungetChar(c, fp);

        // Check if the token is a keyword or identifier
        token.type = checkKeyword(token.value);
        if (token.type == IDENTIFIER)
        {
            // Check if it's a struct name
            if (getNextChar(fp) == '{')
            {
                ungetChar('{', fp);
                token.type = IDENTIFIER;
            }
            else
            {
                ungetChar(c, fp);
            }
        }
        return token;
    }

    // Check for semicolon
    if (c == ';')
    {
        token.type = SEMICOLON;
        strcpy(token.value, ";");
        token.line++;
        return token;
    }

    // Check for left brace
    if (c == '{')
    {
        token.type = LEFT_BRACE;
        strcpy(token.value, "{");
        token.line++;
        return token;
    }

    // Check for right brace
    if (c == '}')
    {
        token.type = RIGHT_BRACE;
        strcpy(token.value, "}");
        token.line++;
        return token;
    }

    // Check for colon
    if (c == ':')
    {
        token.type = COLON;
        strcpy(token.value, ":");
        token.line++;
        return token;
    }

    // Unknown token
    token.type = ERROR;
    strcpy(token.value, "");
    return token;
}

// Function to print token
void printToken(Token token)
{
    printf("%4d | %-12s | %s\n", token.line, token.value,
           token.type == ERROR ? "ERROR" : token.type == END_OF_FILE ? "END_OF_FILE"
                                       : token.type == IDENTIFIER    ? "IDENTIFIER"
                                       : token.type == TYPE          ? "TYPE"
                                       : token.type == SEMICOLON     ? "SEMICOLON"
                                       : token.type == LEFT_BRACE    ? "LEFT_BRACE"
                                       : token.type == RIGHT_BRACE   ? "RIGHT_BRACE"
                                       : token.type == COLON         ? "COLON"
                                       : token.type == MESSAGE       ? "MESSAGE"
                                       : token.type == STRUCT        ? "STRUCT"
                                       : token.type == HEADER        ? "HEADER"
                                       : token.type == FIELD         ? "FIELD"
                                                                     : "");
}

// Main function
int main()
{
    FILE *fp;
    Token token;

    // Open input file
    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    // Initialize line number
    int line = 1;

    // Tokenize input until end of file
    do
    {
        token = getNextToken(fp);
        token.line = line;

        // Update line number for multi-line tokens
        if (strcmp(token.value, "{") == 0 ||
            strcmp(token.value, "}") == 0 ||
            strcmp(token.value, ";") == 0 ||
            strcmp(token.value, ":") == 0)
        {
            line++;
        }

        // Print token
        printToken(token);
    } while (token.type != END_OF_FILE);

    // Close file
    fclose(fp);

    return 0;
}
