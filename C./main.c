#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converter.h"
#include "parsing.h"

void print_sample(const unsigned char* sample, unsigned long sample_size);

int main() {
    unsigned long sample_size = 0;
    unsigned char* sample = NULL; // 전체 버퍼 

    unsigned long sample2_size = 1;
    unsigned char sample2[1] = { 0xA }; // 삽입 될 버퍼 (추가에 사용 될 샘플 ) 

    printf("sample -> %p\n", sample);

    APPEND_4byte(
        &sample,
        &sample_size,
        sample2,
        sample2_size
    );

    print_sample(sample, sample_size);

    APPEND_4byte(
        &sample,
        &sample_size,
        sample2,
        sample2_size
    );

    print_sample(sample, sample_size);



    /*
        Automatic_Parsing 은 자동으로 파싱을 하며,
        
        고급언어가 아니기 떄문에, "연결-리스트"기반으로 데이터를 저장하며,
        parsing.h에 구현된 연결리스트 전용 함수를 이용해서 관리할 수 있다.

        start_NODE 포인터의 주소를 인자에 전달한다. 



        sample 주소는 Automatic_Parsing안에서 해제 된다. 
        //free(sample);
    
    */
    PLength_Based_Struct start_NODE = NULL;
    Automatic_Parsing(
        sample,
        sample_size,
        0x1,
        &start_NODE
    );

    /*
        PRINT__Length_Based_Struct -> 노드 시작 주소부터 do/while를 통해 모든 노드를 순서대로 출력

        GET_one_NODE -> 2번째 인자의 index값을 hint로 이용하여 1개의 노드를 return함 (특정 노드 접근 가능)

        FREEPOOL__Length_Based_Struct -> 노드 시작 부터 do/while를 통해 모든 노드 할당 해제

    */

    PRINT__Length_Based_Struct(start_NODE);

    GET_one_NODE(start_NODE, 1);

    FREEPOOL__Length_Based_Struct(start_NODE);

    

    return 0;
}


void print_sample(const unsigned char* sample, unsigned long sample_size) {
    for (unsigned long i = 0; i < sample_size; ++i) {
        printf("%02x ", sample[i]);
    }
    printf("\n");
}