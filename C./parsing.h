typedef struct Length_Based_Struct {
	unsigned char* Previous_Address;
	unsigned long long node_index;
	
	char is_4byte;
	
	unsigned char* RAW_DATA_Address;
	unsigned long long RAW_DATA_SIZE;

	unsigned char* Next_Address;
}Length_Based_Struct, *PLength_Based_Struct;



PLength_Based_Struct CREATE_NODE__Length_Based_Struct(
	unsigned char* Previous_Address,
	unsigned long long node_index,

	char is_4byte,

	unsigned char* RAW_DATA_Address,
	unsigned long long RAW_DATA_SIZE
) {
	PLength_Based_Struct new = (PLength_Based_Struct)malloc(sizeof(Length_Based_Struct));
	if (Previous_Address) {
		new->Previous_Address = Previous_Address;
	}
	else {
		new->Previous_Address = NULL;
	}
	new->node_index = node_index;
	new->is_4byte = is_4byte;
	new->RAW_DATA_Address = (unsigned char*)malloc(RAW_DATA_SIZE);
	memcpy(new->RAW_DATA_Address, RAW_DATA_Address, RAW_DATA_SIZE);
	new->RAW_DATA_SIZE = RAW_DATA_SIZE;

	new->Next_Address = NULL;

	return new;

}

PLength_Based_Struct APPEND_NODE__Length_Based_Struct(

	PLength_Based_Struct current_node,
	unsigned long long node_index,
	unsigned char* RAW_DATA_Address,
	unsigned long long RAW_DATA_SIZE
) {

	PLength_Based_Struct append_node = CREATE_NODE__Length_Based_Struct((unsigned char* )current_node, node_index,current_node->is_4byte, RAW_DATA_Address, RAW_DATA_SIZE);

	current_node->Next_Address = (unsigned char* )append_node;

	return append_node;
}

PLength_Based_Struct GET_one_NODE(PLength_Based_Struct Start_Node, unsigned long long node_index) {
	PLength_Based_Struct current_node = Start_Node;
	do {

		if (current_node->node_index == node_index) {
			printf("당신이 입력한 index의 노드를 추출했습니다! GET_one_NODE -> [%llu] , RAW_DATA주소: %p , RAW_DATA_길이: %llu\n", current_node->node_index, current_node->RAW_DATA_Address, current_node->RAW_DATA_SIZE);
			return current_node;
		}
		
		current_node = current_node->Next_Address;


	} while (current_node != NULL);

}

char PRINT__Length_Based_Struct(PLength_Based_Struct Start_Node) {

	PLength_Based_Struct current_node = Start_Node;

	do {
		
		printf("지금 print하고 있는 노드의 인덱스 -> [%llu] , RAW_DATA주소: %p , RAW_DATA_길이: %llu\n", current_node->node_index,current_node->RAW_DATA_Address, current_node->RAW_DATA_SIZE);
		current_node = current_node->Next_Address;


	} while (current_node != NULL);

	return 0x1;
}

char FREEPOOL__Length_Based_Struct(PLength_Based_Struct Start_Node) {

	PLength_Based_Struct current_node = Start_Node;

	do {

		//printf("RAW_DATA주소: %p , RAW_DATA_길이: %llu\n", current_node->RAW_DATA_Address, current_node->RAW_DATA_SIZE);

		PLength_Based_Struct next_current_node = current_node->Next_Address;
		free(current_node);
		current_node = next_current_node;

		if (current_node == NULL) {
			free(current_node);
			break;
		}

	} while (current_node != NULL);

	return 0x1;
}


char Automatic_Parsing(
	unsigned char* ALL_BUFFER_addr,
	unsigned long long ALL_BUFFER_SIZE,
	char is_4byte,

	PLength_Based_Struct* Output_Parsed_Start_Node
) {
	unsigned char* remember_ALL_BUFFER_start_address = ALL_BUFFER_addr;
	unsigned char* FINISH_ALL_BUFFER_address = ALL_BUFFER_addr+ ALL_BUFFER_SIZE;
	unsigned long long node_index = 0;

	char move_byte = 0;
	if (is_4byte) {
		move_byte = 4;
	}
	else {
		move_byte = 8;
	}

	PLength_Based_Struct start_NODE = NULL;
	PLength_Based_Struct current_NODE = NULL;
	while (1) {

		ALL_BUFFER_addr = ALL_BUFFER_addr;
		unsigned long long LENGTH = 0;
		memcpy(&LENGTH, ALL_BUFFER_addr, move_byte);
		printf("\nLENGTH->%lu\n", LENGTH);

		ALL_BUFFER_addr = ALL_BUFFER_addr + move_byte; // 데이터 추출
		if (current_NODE == NULL) {
			// 최초 노드 생성시
			if (is_4byte) {
				current_NODE = CREATE_NODE__Length_Based_Struct(current_NODE, node_index, 0x1, ALL_BUFFER_addr, LENGTH);
				
			}
			else {
				current_NODE = CREATE_NODE__Length_Based_Struct(current_NODE, node_index, 0x0, ALL_BUFFER_addr, LENGTH);
				
			}
			node_index += 1;
			start_NODE = current_NODE;
		}
		else {
			// 기존 노드 추가시
			current_NODE = APPEND_NODE__Length_Based_Struct(current_NODE, node_index,ALL_BUFFER_addr, LENGTH);
			node_index += 1;
		}

		ALL_BUFFER_addr = ALL_BUFFER_addr + LENGTH;

		if (ALL_BUFFER_addr == FINISH_ALL_BUFFER_address) break;
	}
	// 이제 -> ALL_BUFFER_addr 주소는 필요없음 ( 파싱했응게 ) 
	free(remember_ALL_BUFFER_start_address);

	*Output_Parsed_Start_Node = start_NODE;

	
	return 0x1;
	

}