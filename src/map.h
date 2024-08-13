typedef struct {
    char* key;
    char* value;
} map_item;

typedef struct {
    int size;
    int count;
    map_item** items;
} map;

static map_item* map_new_item(const char*, const char*);
map* map_new();
static void map_del_item(map_item*);
void map_del(map*);