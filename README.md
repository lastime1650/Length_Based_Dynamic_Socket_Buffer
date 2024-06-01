# Length_Based_Socket_Buffer
This repository maintains compatibility by creating a "length-based" standard for dynamic data between socket communications, regardless of programming language. 프로그래밍 언어 상관없이 "길이-기반"규격을 개발하여  오버플로우 없이 엔드포인트 간 동적 데이터를 주고받을 수 있는 저장소입니다. ( 서로 다른 언어를 사용하는 환경에서 Socket통신을 할 때 사용하여도 "길이-기반" format 규격으로 파싱하면 문제없습니다.  )

# 기술 원리 ( little endian 지원 )

![initial](https://github.com/lastime1650/Length_Based_Socket_Buffer/blob/main/image_for_readme/image.png)

이 저장소에서는 4바이트와 8바이트 2가지 모드를 가지고 동적 데이터를 구성하도록 구현하였습니다.

### 동적으로 어떻게 데이터를 쌓는가?

위 사진에 보듯이, 초기에서는 정해진 고정적길이 ( 4바이트 또는 8바이트 만 )을 결정하고, 이 길이에 따라 데이터를 동적으로 APPEND할 수 있습니다.

### 동적으로 생성된 데이터를 Receive하는 언어를 대상으로 한다면, 언어 상관없이 오버플로우 없이 모두 정확하게 추출할 수 있는가?

그렇습니다. 이러한 방식은 언어 상관없이 동적으로 해석(Parsing)하여 Bytes기반으로 데이터를 추출합니다. 

</br></br>

# 현재 사용할 수 있는 언어

제가 현재 C[C언어_코드보기](https://github.com/lastime1650/Length_Based_Dynamic_Socket_Buffer/blob/main/C./main.c), RUST[RUST언어_코드보기](https://github.com/lastime1650/Length_Based_Dynamic_Socket_Buffer/blob/main/RUST./main.rs), PYTHON[PYTHON언어 코드보기](https://github.com/lastime1650/Length_Based_Dynamic_Socket_Buffer/blob/main/PYTHON./Length_Based_Socket_Communication.py) 3가지 언어를 이용하여 다 똑같은 "길이-기반" 데이터를 만들고, 관리하는 기능/동작 을 구현했습니다.

실제로 소켓을 통하여 서로 다른 언어영억에서 "길이-기반"데이터를 자동파싱하면서 놀면 재밌습니다. 

