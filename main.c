//
//  main.c
//  veriyapılarıödev2
//
//  Created by Hatice Kübra Erdem on 19.02.2025.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LOG_ENTRIES 1000
#define MAX_LOG_LENGTH 1024

// bağlantılı liste düğüm yapısını tanımlama
typedef struct SyslogNode {
    char log_entry[MAX_LOG_LENGTH];
    struct SyslogNode *next;
    
}SyslogNode;

//düğümleri statik olarak depolamak için dizi
SyslogNode node_array[MAX_LOG_ENTRIES];
int node_index = 0;

//yeni düğüm oluşturma
SyslogNode* createNode(char *log_entry) {
    if(node_index >= MAX_LOG_ENTRIES) {
        return NULL;
    }
    SyslogNode *newNode = &node_array[node_index++];
    strncpy(newNode->log_entry, log_entry, MAX_LOG_LENGTH);
    newNode->log_entry[MAX_LOG_LENGTH - 1] = '\0';
    newNode->next = NULL;
    return newNode;
}

//bağlantılı listeye düğüm ekleme
void appendNode(SyslogNode **head, char *log_entry) {
    SyslogNode *newNode = createNode(log_entry);
    if(newNode == NULL) {
        fprintf(strderr, "error: maximum log entries reached.\n");
        return;
    }
    if(*head == NULL){
        *head = newNode;
    } else {
        SyslogNode *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
    }

//bağlantılı listeyi görüntüleme
       void displayList(SyslogNode *head) {
        SyslogNode *temp = head;
        while(temp != NULL) {
            printf("%s", temp->log_entry);
            temp = temp->next;
        }
    }

int main(int argc, const char * argv[]){
        FILE *file;
        char line[MAX_LOG_LENGTH];
        SyslogNode *head = NULL;
        
 //syslog dosyasını açma
        file = fopen("/var/log/syslog", "r");
        if(file == NULL) {
            perror("error opening file");
            return 1;
        }
    
     //sistem günlüğü dosyasını okuma
        while(fgets(line, sizeof(line), file) != NULL) {
            appendNode(&head, line);
            
        }
    
    //close the file
    fclose(file);
    
    //display the linked list
    displayList(head);
    
    return 0;
}
