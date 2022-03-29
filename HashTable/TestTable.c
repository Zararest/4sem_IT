#include "TestTable.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <assert.h>

int throw_null = 0;

int findKey(char** array, const char* elem, int maxSize){

    for (int i = 0; i < maxSize; i++){

        if (array[i] != NULL && strcmp(elem, array[i]) == 0){

            return i;
        }
    }

    return -1;
}

void removeKey(char** array, const char* elem, int maxSize){

    int numOfKey = findKey(array, elem, maxSize);

    if (numOfKey != -1){

        free(array[numOfKey]);
        array[numOfKey] = NULL;
    }
}

int addToArray(char** array, const char* elem, int maxSize){

    if (findKey(array, elem, maxSize) != -1){

        return 0;
    }

    int i = 0;
    while (array[i] != NULL){
        
        i++;
        assert(i < maxSize);
    }

    array[i] = (char*) calloc(MAX_KEY_SIZE, sizeof(char));
    memcpy(array[i], elem, MAX_KEY_SIZE);

    return 1;
}

void freeArray(char** array, int size){

    for (int i = 0; i < size; i++){

        if (array[i] != NULL){

            free(array[i]);
        }
    }

    free(array);
}

int test_table(const char* fileName){

    FILE* data = fopen(fileName, "r");

    assert(data != NULL);

    int numOfComands = 0;
    fscanf(data, "%i", &numOfComands);

    HashTable* table = createHashTable(1);
    char** keys = (char**) calloc(numOfComands, sizeof(char*));
    char* tableElem = NULL;
    int numOfErrors = 0;

    for (int i = 0; i < numOfComands; i++){

        char tmpKey [MAX_KEY_SIZE] = {};
        char curCommand[MAX_KEY_SIZE] = {};
        int keySize = 0, arrayRet, tableRet;

        fscanf(data, "%s %i", curCommand, &keySize);
        assert(keySize <= MAX_KEY_SIZE);
        fscanf(data, "%s", tmpKey);

        if (curCommand[0] == 'a'){

            arrayRet = addToArray(keys, tmpKey, i + 1);
            tableRet = addElem(table, tmpKey, tmpKey, keySize);

            numOfErrors += arrayRet != tableRet;
        }

        if (curCommand[0] == 'g'){

            arrayRet = findKey(keys, tmpKey, i + 1);
            tableElem = (char*) getElem(table, tmpKey);
            
            if (tableElem != NULL){

                numOfErrors += strcmp(tableElem, tmpKey) != 0;
                free(tableElem);
            } else{

                numOfErrors += arrayRet != -1;
            }
        }

        if (curCommand[0] == 'r'){

            removeKey(keys, tmpKey, i + 1);
            removeElem(table, tmpKey);
        }
    }

    freeArray(keys, numOfComands);
    freeHashTable(table);
    fclose(data);

    return numOfErrors;
}

int tets_negatives(){

    throw_null = 0;

    int num_of_errors = 0;

    num_of_errors += Hash(NULL) != 0;
    
    HashTable* table = createHashTable(10);
    HashTable* table_1 = NULL;

    table->capacity = -1;
    num_of_errors += addElem(table, "a", "a", 2) != -1;
    table->capacity = 10;

    table->loadFactor = 2;
    num_of_errors += addElem(table, "a", "a", 2) != -1;
    table->loadFactor = 0;

    table->size = -1;
    num_of_errors += addElem(table, "a", "a", 2) != -1;
    table->size = 0;

    table->deletedNum = -1;
    num_of_errors += addElem(table, "a", "a", 2) != -1;
    table->deletedNum = 1;

    table->dirtyFactor = 2;
    num_of_errors += addElem(table, "a", "a", 2) != -1;
    num_of_errors += getElem(table, "a") != NULL;
    removeElem(table, "a");
    table->dirtyFactor = 0;
    free(table->content);
    free(table);
    
    throw_null = 1;

    table_1 = createHashTable(10);
    num_of_errors += table_1 != NULL;
    
    throw_null = 2;

    table_1 = createHashTable(10);
    num_of_errors += table_1 != NULL;
    
    throw_null = 0;

    freeHashTable(NULL);
    rehash_(NULL, -1);
    rehash(NULL);
    insertCell_(NULL, NULL);

    HashTable* table_2 = createHashTable(10);
    removeElem(table_2, NULL);

    num_of_errors += addElem(table_2, NULL, NULL, 1) != -1;

    table_2->dirtyFactor = 0.8;
    rehash(table_2);
    void* old_ptr = table_2->content;

    throw_null = 1;

    rehash(table_2);
    num_of_errors += old_ptr != table_2->content;

    throw_null = 2;

    rehash(table_2);

    throw_null = 1;

    rehash_(table_2, 1);
    num_of_errors += addElem(table_2, "a", "a", 2) != -1;

    throw_null = 2;
    
    num_of_errors += addElem(table_2, "b", "a", 2) != -1;

    throw_null = 0;

    freeHashTable(table_2);

    HashTable* table_3 = createHashTable(10);
    char tmp[4] = {"abc"};

    for (int i = 0; i < 10; i++){

        table_3->content[i].key = tmp;
        table_3->content[i].valid = 1;
    }

    num_of_errors += addElem(table_3, "aaa", "aaa", 3) != -1;
    num_of_errors += getElem(table_3, "aaa") != NULL;
    removeElem(table_3, "aaa");

    free(table_3->content);
    free(table_3);

    return num_of_errors;
}