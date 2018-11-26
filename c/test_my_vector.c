#include "my_vector.h"
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef struct NODE {
        uint32_t mesh;
        int64_t id;
        double x;
        double y;
    } NODE;

    NODE aaa;
    my_vector vec;


    vec_init(&vec, sizeof(NODE));

    int i;
    for (i = 0; i < 10000; ++i) {
        aaa.id = i;
        vec_push_back(&vec, &aaa);
        printf("%d: size:%zu cap:%zu\n", i, vec.size, vec.capacity);
    }

    vec_shrink_to_fit(&vec);
    printf("%d: size:%zu cap:%zu\n", i, vec.size, vec.capacity);

    {
        NODE *ptr = (NODE *)vec_data(&vec);
        int cnt = vec_size(&vec);
        for (i = 0; i < cnt; ++i) {
            printf("id:%lld\n", ptr[i].id);
        }
    }

    vec_clear(&vec);
    
    return 0;
}
