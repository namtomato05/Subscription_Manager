# SubManager
구독 서비스 및 고정 지출 관리 프로그램

---

## 프로젝트 소개
현대인은 많은 구독 서비스를 이용하고 있다.
넷플릭스, 제미나이, 스포티파이, 쿠팡 로켓와우 등 매달 자동결제되는 서비스들이 늘어나면서
**내가 매달 얼마를 지출하는지, 언제 결제되는지** 를 하나하나 파악하기 어려운 상황이다.

SubManager는 이러한 문제를 해결하기 위해 개발된 구독 서비스 관리 프로그램이다.
등록부터 통계까지 직관적인 UI로 내 구독 현황을 한눈에 파악할 수 있다.

---

## 개발 환경
- 언어: C++
- 프레임워크: MFC (Microsoft Foundation Class)
- IDE: Visual Studio 2022
- OS: Windows

---

## 클래스 구조
- Expense                   
:구독 서비스 데이터 (서비스명, 결제일, 월 금액, 인원수)

- SubManager                 
: 전체 구독 목록 관리 (등록, 삭제, 통계 계산)

- CSubscriptionManagerDlg   
: MFC 다이얼로그 UI 및 이벤트 처리

---

### 주요기능

### 등록
- 서비스명, 결제일, 월 금액, 인원수 입력
- 인원수 기반 내 부담금 자동 계산
- 초기화 버튼으로 입력 내용 초기화

### 목록
- 등록된 구독 서비스를 표 형태로 한눈에 확인
- 서비스명 / 결제일 / 월 금액 / 인원수 / 내 부담금 표시
- 항목 선택 후 삭제 가능

### 통계
- 이번 달 총 지출 자동 계산
- 내 실제 부담금 합계 (인원수 나눈 값들의 합)
- 결제 임박 서비스 표시 (오늘 기준 3일 이내)

---
## 객체지향 설계 원칙
- 단일 책임 원칙(SRP): 각 클래스는 하나의 역할만 담당
- 캡슐화: 데이터와 기능을 클래스 내부에 묶어 관리
- 확장성: 새로운 기능 추가가 용이한 구조로 설계
- 변경 최소화: 요구사항 변경 시 영향 범위를 최소화하는 구조

---
### 화면
<img width="330" alt="image" src="https://github.com/user-attachments/assets/919f1250-b235-4da8-946c-f711f36fd12c" />
<img width="330" alt="image" src="https://github.com/user-attachments/assets/a9557cc9-8432-458e-ad26-7333955c77c0" />
<img width="330" alt="image" src="https://github.com/user-attachments/assets/a4f1d085-67fd-45c5-9de4-5402abe946c9" />
