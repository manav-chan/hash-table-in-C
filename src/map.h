#ifndef MAP_H
#define MAP_H

typedef struct {
    char* key;
    char* value;
} map_item;

typedef struct {
    int size;
    int base_size;
    int count;
    map_item** items;
} map;

static map_item *map_new_item(const char *, const char *);
map *map_new();
static map *map_new_size(const int);
static void map_del_item(map_item *);
void map_del(map *);
static int map_hash(const char *, const int, const int);
static int map_get_hash(const char *, const int, const int);
void map_insert(map*, const char *, const char *);
char *map_search(map*, const char*);
void map_delete(map*, const char*);
static void map_resize(map*, const int);
static void map_resize_up(map*);
static void map_resize_down(map*);

#endif