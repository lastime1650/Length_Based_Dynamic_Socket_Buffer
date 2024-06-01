#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converter.h"
#include "parsing.h"

void print_sample(const unsigned char* sample, unsigned long sample_size);

int main() {
    unsigned long sample_size = 0;
    unsigned char* sample = NULL; // ��ü ���� 

    unsigned long sample2_size = 1;
    unsigned char sample2[1] = { 0xA }; // ���� �� ���� (�߰��� ��� �� ���� ) 

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
        Automatic_Parsing �� �ڵ����� �Ľ��� �ϸ�,
        
        ��޾� �ƴϱ� ������, "����-����Ʈ"������� �����͸� �����ϸ�,
        parsing.h�� ������ ���Ḯ��Ʈ ���� �Լ��� �̿��ؼ� ������ �� �ִ�.

        start_NODE �������� �ּҸ� ���ڿ� �����Ѵ�. 



        sample �ּҴ� Automatic_Parsing�ȿ��� ���� �ȴ�. 
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
        PRINT__Length_Based_Struct -> ��� ���� �ּҺ��� do/while�� ���� ��� ��带 ������� ���

        GET_one_NODE -> 2��° ������ index���� hint�� �̿��Ͽ� 1���� ��带 return�� (Ư�� ��� ���� ����)

        FREEPOOL__Length_Based_Struct -> ��� ���� ���� do/while�� ���� ��� ��� �Ҵ� ����

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