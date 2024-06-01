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
            fprintf(stderr, "할당실패\n");
            return 0;
        }

        printf("all_malloc_size -> %lu / TMP -> %p\n", all_malloc_size, TMP);

        // 기존 데이터를 새 메모리 영역에 복사
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
            fprintf(stderr, "할당실패\n");
            return 0;
        }

        printf("all_malloc_size -> %lu / TMP -> %p\n", all_malloc_size, TMP);

        // 기존 데이터를 새 메모리 영역에 복사
        printf("memcpy(%p, %p, %lu)\n", TMP, *Inout___ALL_DATA, *Inout___ALL_DATA_SIZE);
        memcpy(TMP, *Inout___ALL_DATA, *Inout___ALL_DATA_SIZE);

        // 길이 넣기
        memcpy(TMP + *Inout___ALL_DATA_SIZE, &Input___RAW_DATA_SIZE, 4);

        // 실제 데이터 넣기
        memcpy(TMP + *Inout___ALL_DATA_SIZE + 4, Input___RAW_DATA, Input___RAW_DATA_SIZE);

        // 기존 메모리 해제
        free(*Inout___ALL_DATA);

        // 갱신된 포인터와 크기 업데이트
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
            fprintf(stderr, "할당실패\n");
            return 0;
        }

        printf("all_malloc_size -> %lu / TMP -> %p\n", all_malloc_size, TMP);

        // 기존 데이터를 새 메모리 영역에 복사
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
            fprintf(stderr, "할당실패\n");
            return 0;
        }

        printf("all_malloc_size -> %lu / TMP -> %p\n", all_malloc_size, TMP);

        // 기존 데이터를 새 메모리 영역에 복사
        printf("memcpy(%p, %p, %lu)\n", TMP, *Inout___ALL_DATA, *Inout___ALL_DATA_SIZE);
        memcpy(TMP, *Inout___ALL_DATA, *Inout___ALL_DATA_SIZE);

        // 길이 넣기
        memcpy(TMP + *Inout___ALL_DATA_SIZE, &Input___RAW_DATA_SIZE, 8);

        // 실제 데이터 넣기
        memcpy(TMP + *Inout___ALL_DATA_SIZE + 8, Input___RAW_DATA, Input___RAW_DATA_SIZE);

        // 기존 메모리 해제
        free(*Inout___ALL_DATA);

        // 갱신된 포인터와 크기 업데이트
        *Inout___ALL_DATA = TMP;
        *Inout___ALL_DATA_SIZE = all_malloc_size;
    }


    return 0x1;
}