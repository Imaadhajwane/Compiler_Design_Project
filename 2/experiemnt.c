#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

// Token types
typedef enum
{
    TOKEN_PROTOCOL,
    TOKEN_PROTOCOL_NAME,
    TOKEN_MESSAGE_TYPE,
    TOKEN_IDENTIFIER,
    TOKEN_FIELD_TYPE,
    TOKEN_SEMICOLON,
    TOKEN_OPEN_BRACE,
    TOKEN_CLOSE_BRACE,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

// Token structure
typedef struct
{
    TokenType type;
    char lexeme[100]; // Assuming maximum lexeme length is 100 characters
} Token;

// Define regular expression pattern for tokens
#define TOKEN_PATTERN "\\b(Protocol)\\s+([a-zA-Z][a-zA-Z0-9_]*)\\s*\\{|(REQUEST|RESPONSE)\\s+([a-zA-Z][a-zA-Z0-9_]*)\\s*\\{|([a-zA-Z][a-zA-Z0-9_]*)\\s*(INT|STRING|BOOL)\\s*;|\\{|\\}|;"

// Function to get the next token from input
Token getNextToken(FILE *fp)
{
    Token token;
    regex_t regex;
    regmatch_t match[6]; // We need to capture up to 5 groups plus the overall match
    char buffer[100];    // Buffer for reading input

    if (fgets(buffer, sizeof(buffer), fp) == NULL)
    {
        token.type = TOKEN_EOF;
        strcpy(token.lexeme, "");
        return token;
    }

    // Compile regular expression
    if (regcomp(&regex, TOKEN_PATTERN, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Regex compilation failed\n");
        exit(1);
    }

    // Execute regular expression
    if (regexec(&regex, buffer, 6, match, 0) == 0)
    {
        if (match[1].rm_so != -1)
        {
            token.type = TOKEN_PROTOCOL;
            strncpy(token.lexeme, buffer + match[1].rm_so, match[1].rm_eo - match[1].rm_so);
        }
        else if (match[2].rm_so != -1)
        {
            token.type = TOKEN_PROTOCOL_NAME;
            strncpy(token.lexeme, buffer + match[2].rm_so, match[2].rm_eo - match[2].rm_so);
        }
        else if (match[3].rm_so != -1)
        {
            token.type = TOKEN_MESSAGE_TYPE;
            strncpy(token.lexeme, buffer + match[3].rm_so, match[3].rm_eo - match[3].rm_so);
        }
        else if (match[4].rm_so != -1)
        {
            token.type = TOKEN_IDENTIFIER;
            strncpy(token.lexeme, buffer + match[4].rm_so, match[4].rm_eo - match[4].rm_so);
        }
        else if (match[5].rm_so != -1)
        {
            token.type = TOKEN_FIELD_TYPE;
            strncpy(token.lexeme, buffer + match[5].rm_so, match[5].rm_eo - match[5].rm_so);
        }
        else if (buffer[match[0].rm_so] == '{')
        {
            token.type = TOKEN_OPEN_BRACE;
            strcpy(token.lexeme, "{");
        }
        else if (buffer[match[0].rm_so] == '}')
        {
            token.type = TOKEN_CLOSE_BRACE;
            strcpy(token.lexeme, "}");
        }
        else if (buffer[match[0].rm_so] == ';')
        {
            token.type = TOKEN_SEMICOLON;
            strcpy(token.lexeme, ";");
        }
        token.lexeme[match[0].rm_eo - match[0].rm_so] = '\0'; // Null-terminate the lexeme
        regfree(&regex);
        return token;
    }

    regfree(&regex);

    // If no match found, it's an error
    token.type = TOKEN_ERROR;
    strcpy(token.lexeme, buffer);
    return token;
}

// Function to parse Protocol Specification Language
void parsePSL(FILE *fp)
{
    Token token;
    while ((token = getNextToken(fp)).type != TOKEN_EOF)
    {
        if (token.type == TOKEN_ERROR)
        {
            printf("Error: Unexpected token '%s'\n", token.lexeme);
            exit(1);
        }
    }
}

int main()
{
    FILE *fp = fopen("input2.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    parsePSL(fp);
    fclose(fp);

    // Semantic analysis completed without error
    FILE *resultFile = fopen("result.txt", "w");
    if (resultFile == NULL)
    {
        perror("Error creating result file");
        return 1;
    }
    fprintf(resultFile, "Semantic analysis completed without error.\n");

    // Copy contents of ad.txt to result file
    FILE *adFile = fopen("ad.txt", "r");
    if (adFile == NULL)
    {
        perror("Error opening ad.txt");
        fclose(resultFile);
        return 1;
    }

    char ch;
    while ((ch = fgetc(adFile)) != EOF)
    {
        fputc(ch, resultFile);
    }

    fclose(adFile);
    fclose(resultFile);

    return 0;
}
