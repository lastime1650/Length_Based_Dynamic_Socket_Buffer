# Length_Based_Socket_Buffer
This repository maintains compatibility by creating a "length-based" standard for dynamic data between socket communications, regardless of programming language. 프로그래밍 언어 상관없이 "길이-기반"규격을 개발하여  오버플로우 없이 엔드포인트 간 동적 데이터를 주고받을 수 있는 저장소입니다.

# 기술 원리

![initial](https://github.com/lastime1650/Length_Based_Socket_Buffer/blob/main/image_for_readme/image.png)

이 저장소에서는 4바이트와 8바이트 2가지 모드를 가지고 동적 데이터를 구성하도록 구현하였습니다.

### 동적으로 어떻게 데이터를 쌓는가?

위 사진에 보듯이, 초기에서는 정해진 고정적길이 ( 4바이트 또는 8바이트 만 )을 결정하고, 이 길이에 따라 데이터를 동적으로 APPEND할 수 있습니다.

### 동적으로 생성된 데이터를 Receive하는 언어를 대상으로 구분없이 오버플로우 없이 정확하게 추출할 수 있는가?

그렇습니다. 이러한 방식은 언어 상관없이 동적으로 해석(Parsing)하여 Bytes기반으로 데이터를 추출합니다. 
