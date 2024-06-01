char APPEND_4byte(
    unsigned char** Inout___ALL_DATA,
    unsigned long* Inout___ALL_DATA_SIZE,
    unsigned char* Input___RAW_DATA,
    unsigned long Input___RAW_DATA_SIZE
) {
    if (*Inout___ALL_DATA == NULL) {
        unsigned long all_malloc_size =  4 + Input___RAW_DATA_SIZE;
        unsigned char* TMP = (unsigned char*)malloc(all_malloc_size);
        if (TMP == NULL) {
            fprintf(stderr, "�Ҵ����\n");
            return 0;
        }

        printf("all_malloc_size -> %lu / TMP -> %p\n", all_malloc_size, TMP);

        // ���� �����͸� �� �޸� ������ ����
        printf("memcpy(%p, %p, %lu)\n", TMP, &Input___RAW_DATA_SIZE, 4);
        memcpy(TMP, &Input___RAW_DATA_SIZE, 4);

        memcpy(TMP+4, Input___RAW_DATA, Input___RAW_DATA_SIZE);

        *Inout___ALL_DATA = TMP;
        *Inout___ALL_DATA_SIZE = all_malloc_size;

        return 0x1;

    }
    else {
        unsigned long all_malloc_size = (*Inout___ALL_DATA_SIZE) + 4 + Input___RAW_DATA_SIZE;

        unsigned char* TMP = (unsigned char*)malloc(all_malloc_size);
        if (TMP == NULL) {
            fprintf(stderr, "�Ҵ����\n");
            return 0;
        }

        printf("all_malloc_size -> %lu / TMP -> %p\n", all_malloc_size, TMP);

        // ���� �����͸� �� �޸� ������ ����
        printf("memcpy(%p, %p, %lu)\n", TMP, *Inout___ALL_DATA, *Inout___ALL_DATA_SIZE);
        memcpy(TMP, *Inout___ALL_DATA, *Inout___ALL_DATA_SIZE);

        // ���� �ֱ�
        memcpy(TMP + *Inout___ALL_DATA_SIZE, &Input___RAW_DATA_SIZE, 4);

        // ���� ������ �ֱ�
        memcpy(TMP + *Inout___ALL_DATA_SIZE + 4, Input___RAW_DATA, Input___RAW_DATA_SIZE);

        // ���� �޸� ����
        free(*Inout___ALL_DATA);

        // ���ŵ� �����Ϳ� ũ�� ������Ʈ
        *Inout___ALL_DATA = TMP;
        *Inout___ALL_DATA_SIZE = all_malloc_size;
    }
    

    return 0x1;
}


char APPEND_8byte(
    unsigned char** Inout___ALL_DATA,
    unsigned long long* Inout___ALL_DATA_SIZE,
    unsigned char* Input___RAW_DATA,
    unsigned long long Input___RAW_DATA_SIZE
) {
    if (*Inout___ALL_DATA == NULL) {
        unsigned long all_malloc_size = 8 + Input___RAW_DATA_SIZE;
        unsigned char* TMP = (unsigned char*)malloc(all_malloc_size);
        if (TMP == NULL) {
            fprintf(stderr, "�Ҵ����\n");
            return 0;
        }

        printf("all_malloc_size -> %lu / TMP -> %p\n", all_malloc_size, TMP);

        // ���� �����͸� �� �޸� ������ ����
        printf("memcpy(%p, %p, %lu)\n", TMP, &Input___RAW_DATA_SIZE, 8);
        memcpy(TMP, &Input___RAW_DATA_SIZE, 8);

        memcpy(TMP + 8, Input___RAW_DATA, Input___RAW_DATA_SIZE);

        *Inout___ALL_DATA = TMP;
        *Inout___ALL_DATA_SIZE = all_malloc_size;

        return 0x1;

    }
    else {
        unsigned long all_malloc_size = (*Inout___ALL_DATA_SIZE) + 8 + Input___RAW_DATA_SIZE;

        unsigned char* TMP = (unsigned char*)malloc(all_malloc_size);
        if (TMP == NULL) {
            fprintf(stderr, "�Ҵ����\n");
            return 0;
        }

        printf("all_malloc_size -> %lu / TMP -> %p\n", all_malloc_size, TMP);

        // ���� �����͸� �� �޸� ������ ����
        printf("memcpy(%p, %p, %lu)\n", TMP, *Inout___ALL_DATA, *Inout___ALL_DATA_SIZE);
        memcpy(TMP, *Inout___ALL_DATA, *Inout___ALL_DATA_SIZE);

        // ���� �ֱ�
        memcpy(TMP + *Inout___ALL_DATA_SIZE, &Input___RAW_DATA_SIZE, 8);

        // ���� ������ �ֱ�
        memcpy(TMP + *Inout___ALL_DATA_SIZE + 8, Input___RAW_DATA, Input___RAW_DATA_SIZE);

        // ���� �޸� ����
        free(*Inout___ALL_DATA);

        // ���ŵ� �����Ϳ� ũ�� ������Ʈ
        *Inout___ALL_DATA = TMP;
        *Inout___ALL_DATA_SIZE = all_malloc_size;
    }


    return 0x1;
}