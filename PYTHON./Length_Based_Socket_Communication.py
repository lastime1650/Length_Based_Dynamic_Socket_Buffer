import struct

class Length_Based_struct():
    def __init__(self,
                 is_maximum_size_4byte:bool = None #동적 데이터의 최대사이즈가 4바이트인가?
                 ):
        if is_maximum_size_4byte == None: return # 실패
        self.is_maximum_size_4byte = is_maximum_size_4byte


    # 소켓으로 전달하기 위한 데이터를 하나씩 축적할 때, "길이-기반"형태로 만들어주는 함수
    def Append_RAWDATA(self,
                       INPUT_BUFFER, # 소켓으로 보낼 총 데이터 ( 여기에 APPEND/WRITE된다 )
                       INPUT_current_parted_data # INPUT_BUFFER에 추가될 데이터
                       )->bytes:

        RAWDATA_SIZE = len(INPUT_current_parted_data)
        RAW_DATA_bytes = self.int_to_byte(RAWDATA_SIZE)

        INPUT_BUFFER += RAW_DATA_bytes
        INPUT_BUFFER += INPUT_current_parted_data

        return INPUT_BUFFER

    # SOcket을 통해 받은 전체 데이터를 자동 파싱하는 함수이며, 반환되는 정보는 동적 데이터이다.
    def Automatic_Parsing(self, INPUT_ALL_BUFFER) -> list :

        return_result_bytes_list = []

        # 초기 설정
        FINISH_SIZE = len(INPUT_ALL_BUFFER)
        print(f"FINISH_SIZE --> {FINISH_SIZE}")
        start_index = 0
        end_index  = 0

        if self.is_maximum_size_4byte:
            end_index += 4
        else:
            end_index += 8

        while True:
            # 1. 실제 데이터의 길이를 받는다.
            LENGTH:int = self.byte_to_int( INPUT_ALL_BUFFER[start_index:end_index] )
            if LENGTH == None: return None

            # 2. 실제 데이터를 읽기 위한 index 이동
            start_index = end_index
            end_index = end_index + LENGTH

            # 3. (1)에서 받은 길이만큼 데이터를 얻는다.
            Part_of_RAWDATA:bytes = INPUT_ALL_BUFFER[start_index:end_index]
            return_result_bytes_list.append(Part_of_RAWDATA)

            # 4. 다음 index 이동 ( byte고려 )
            start_index = end_index
            if self.is_maximum_size_4byte:
                end_index += 4
            else:
                end_index += 8

            # 5. 데이터 끝인가?
            if start_index == FINISH_SIZE: return return_result_bytes_list


    # 동적 데이터를 읽기 전에, 길이를 알아내기 위해 사용하는 함수
    def byte_to_int(self, INPUT_byte:bytes) -> int:

        if self.is_maximum_size_4byte: # 4바이트
            if len(INPUT_byte) != 4: return None # 길이검증
            converted_int = int( struct.unpack('<I', INPUT_byte)[0] )
            return converted_int

        else: # 8바이트
            if len(INPUT_byte) != 8: return None  # 길이검증
            converted_int = int(struct.unpack('<Q', INPUT_byte)[0])
            return converted_int

        return None

    # 동적으로 추가할 "데이터의 길이"를 받아 'is_maximum_size_4byte' 값에 따라 고정된 바이트안에서 바이트가 return 된다.
    def int_to_byte(self, INPUT_data_size:int = None) -> bytes:

        if self.is_maximum_size_4byte: # 4바이트
            converted_byte = struct.pack('<I', INPUT_data_size)
            if len(converted_byte) == 4: return converted_byte
        else: # 8바이트
            converted_byte = struct.pack('<Q', INPUT_data_size)
            if len(converted_byte) == 8: return converted_byte


        return None


a = Length_Based_struct(True)
print( a.byte_to_int( a.int_to_byte(10) ) )

# 데이터 만들어보기
import random
SOCKET_BUFFER = b''

for i in range( 3 ):
    print(f"반복 횟수 -> {i+1}")
    # call
    SOCKET_BUFFER = a.Append_RAWDATA(
        INPUT_BUFFER=SOCKET_BUFFER,
        INPUT_current_parted_data=b'A'+(random.randint(2,5)).to_bytes(length=1,byteorder="little")
    )

print(f" 생성된 소켓 버퍼 --> {SOCKET_BUFFER}")

# 데이터 파싱하기
print("데이터를 이제 파싱해봅시다.")
Parsed_SOCKET_BUFFER = a.Automatic_Parsing(
    INPUT_ALL_BUFFER=SOCKET_BUFFER
)

print(f" 파싱된 소켓 버퍼 --> {Parsed_SOCKET_BUFFER}")