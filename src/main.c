#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "map.h"

void test_map_new_and_del() {
    map* mp;

    mp = map_new();
    assert(mp != NULL);
    assert(mp->size > 0);
    assert(mp->count == 0);
    map_del(mp);
    printf("test_map_new_and_del passed\n");
}

void test_map_insert_and_search() {
    map* mp;
    char *value1, *value2, *value3, *value4;

    mp = map_new();
    map_insert(mp, "key1", "value1");
    map_insert(mp, "key2", "value2");
    map_insert(mp, "key3", "value3");

    value1 = map_search(mp, "key1");
    value2 = map_search(mp, "key2");
    value3 = map_search(mp, "key3");
    value4 = map_search(mp, "key4");

    assert(value1 != NULL && strcmp(value1, "value1") == 0);
    assert(value2 != NULL && strcmp(value2, "value2") == 0);
    assert(value3 != NULL && strcmp(value3, "value3") == 0);
    assert(value4 == NULL);

    map_del(mp);
    printf("test_map_insert_and_search passed\n");
}

void test_map_delete() {
    map* mp;
    char *value1, *value2;

    mp = map_new();
    map_insert(mp, "key1", "value1");
    map_insert(mp, "key2", "value2");

    map_delete(mp, "key1");
    value1 = map_search(mp, "key1");
    value2 = map_search(mp, "key2");
    assert(value1 == NULL);
    assert(value2 != NULL && strcmp(value2, "value2") == 0);

    map_del(mp);
    printf("test_map_delete passed\n");
}

void test_map_resize() {
    map* mp;
    int i;
    char key[10], value[10];
    
    mp = map_new();
    for (i = 0; i < 100; i++) {
        sprintf(key, "key%d", i);
        sprintf(value, "value%d", i);
        map_insert(mp, key, value);
    }

    for (i = 0; i < 100; i++) {
        sprintf(key, "key%d", i);
        sprintf(value, "value%d", i);
        char* result = map_search(mp, key);
        assert(result != NULL && strcmp(result, value) == 0);
    }

    map_del(mp);
    printf("test_map_resize passed\n");
}

int main() {
    test_map_new_and_del();
    test_map_insert_and_search();
    test_map_delete();
    test_map_resize();
    printf("All tests passed!\n");
    return 0;
}