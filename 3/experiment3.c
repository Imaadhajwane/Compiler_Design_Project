#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGES 10
#define MAX_FIELDS 10

// Define structures to represent protocol elements
typedef struct
{
    char name[50];
} Protocol;

typedef struct
{
    char name[50];
    char fields[MAX_FIELDS][50];
    int numFields;
} MessageType;

// Function to generate intermediate code from parsed tokens
void generateIntermediateCode(FILE *inputFile, FILE *outputFile)
{
    Protocol protocol;
    MessageType messages[MAX_MESSAGES];
    int numMessages = 0;
    int currentFieldIndex;

    char token[50];

    // Skip the first token "TOKEN_PROTOCOL"
    fscanf(inputFile, "%s", token);

    // Read protocol name
    fscanf(inputFile, "%s", token); // TOKEN_PROTOCOL_NAME
    fscanf(inputFile, "%s", protocol.name);

    while (fscanf(inputFile, "%s", token) != EOF)
    {
        if (strcmp(token, "TOKEN_MESSAGE_TYPE") == 0)
        {
            if (numMessages < MAX_MESSAGES)
            {
                fscanf(inputFile, "%s", messages[numMessages].name);
                messages[numMessages].numFields = 0; // Initialize number of fields
                currentFieldIndex = -1;
                numMessages++;
            }
            else
            {
                printf("Maximum number of messages exceeded.\n");
                break;
            }
        }
        else if (strcmp(token, "TOKEN_FIELD_TYPE") == 0)
        {
            if (numMessages > 0 && messages[numMessages - 1].numFields < MAX_FIELDS)
            {
                currentFieldIndex++;
                fscanf(inputFile, "%s", messages[numMessages - 1].fields[currentFieldIndex]);
                // Skip the field name token
                fscanf(inputFile, "%s", token);
                messages[numMessages - 1].numFields++; // Increment number of fields
            }
            else
            {
                printf("Maximum number of fields exceeded for message %d.\n", numMessages);
                break;
            }
        }
    }

    // Write intermediate code to output file
    fprintf(outputFile, "Protocol: %s\n", protocol.name);
    for (int i = 0; i < numMessages; i++)
    {
        fprintf(outputFile, "Message Type: %s\n", messages[i].name);
        fprintf(outputFile, "Fields:\n");
        for (int j = 0; j < messages[i].numFields; j++)
        {
            fprintf(outputFile, "- %s\n", messages[i].fields[j]);
        }
    }
}

int main()
{
    // Open input and output files
    FILE *inputFile = fopen("ad.txt", "r");
    if (inputFile == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    FILE *outputFile = fopen("intermediate_code.txt", "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    // Generate intermediate code from parsed tokens
    generateIntermediateCode(inputFile, outputFile);

    // Close files
    fclose(inputFile);
    fclose(outputFile);
    printf("Intermediate code generated sucessfully, result stored in text file");
    return 0;
}
