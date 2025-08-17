# 즉시 수정이 필요한 중요 이슈들

## 🚨 심각도: 높음 (High Severity)

### 1. 메모리 안전성 문제 (src/data.c)
```c
// 라인 27: 재귀 호출로 인한 잠재적 스택 오버플로우
data()->pwd = pwd;  // ❌ 잘못된 재귀 호출
```
**수정 방법:** `ms->pwd = pwd;` 로 직접 할당

**영향:** 프로그램 크래시 가능성, 메모리 누수

---

### 2. 초기화되지 않은 변수 (src/expander/remove_quote.c)
```c
// 라인 52: quote 변수가 초기화되지 않음
char quote;  // ❌ 초기화 누락
```
**수정 방법:** `char quote = 0;` 로 초기화

**영향:** 예측 불가능한 동작, 파싱 오류

---

### 3. 에러 처리 없이 시스템 호출 (src/parser/here_doc.c)
```c
// 라인 35: /dev/urandom 열기 실패 시 처리 없음
fd = open("/dev/urandom", O_RDONLY);  // ❌ 에러 체크 없음
```
**수정 방법:** 반환값 검사 및 대체 방법 제공

**영향:** 임시 파일 생성 실패, 보안 취약점

---

## ⚠️ 심각도: 중간 (Medium Severity)

### 4. 무한 루프 가능성 (src/parser/here_doc.c)
```c
// 라인 40-50: 파일명 생성 시 무한 루프 가능
while (!access(file_name, F_OK))  // ❌ 종료 조건 부족
```
**수정 방법:** 최대 재시도 횟수 제한

**영향:** 프로그램 행(hang), 리소스 고갈

---

### 5. NULL 포인터 검증 부족 (src/parser/syntax_error.c)
```c
// 라인 37-38: 포인터 역참조 전 NULL 체크 없음
token = node->content;
next_token = next->content;  // ❌ NULL 체크 없음
```
**수정 방법:** 포인터 사용 전 NULL 검사

**영향:** 세그멘테이션 폴트

---

### 6. 매직 넘버 사용 (여러 파일)
```c
// src/parser/syntax_error.c: 라인 20, 25
return (258);  // ❌ 의미 불명확한 상수
```
**수정 방법:** `#define SYNTAX_ERROR 258` 등으로 상수 정의

**영향:** 코드 가독성 저하, 유지보수 어려움

---

## 📝 심각도: 낮음 (Low Severity)

### 7. 파일명 오타 (src/signal/signal_hendler.c)
```
signal_hendler.c  // ❌ 오타
```
**수정 방법:** `signal_handler.c` 로 수정

**영향:** 전문성 저하

---

### 8. 일관성 없는 에러 처리
- 어떤 곳은 `errno` 사용
- 어떤 곳은 `FT_ERROR` 사용
- 어떤 곳은 숫자 리터럴 사용

**수정 방법:** 통일된 에러 코드 시스템 도입

---

## 수정 우선순위

### Phase 1 (즉시 수정)
1. `data()` 함수의 재귀 호출 문제
2. `quote` 변수 초기화
3. `/dev/urandom` 에러 처리

### Phase 2 (단기 수정)
4. 무한 루프 방지
5. NULL 포인터 검증 추가
6. 매직 넘버 상수화

### Phase 3 (중기 개선)
7. 파일명 오타 수정
8. 에러 처리 표준화

---

## 테스트 케이스

### 1. data() 함수 테스트
```bash
# 현재 디렉토리를 읽기 전용으로 설정 후 테스트
chmod 000 .
./minishell  # getcwd 실패 시나리오
```

### 2. quote 파싱 테스트
```bash
echo "'"'"'"  # 중첩 따옴표 테스트
echo '""'     # 따옴표 섞임 테스트
```

### 3. heredoc 테스트
```bash
# /tmp 디렉토리를 가득 채운 후 heredoc 테스트
cat << EOF
test
EOF
```

---

## 예상 수정 시간

- **Phase 1**: 2-3시간
- **Phase 2**: 4-6시간  
- **Phase 3**: 8-10시간

**총 예상 시간**: 14-19시간

이러한 수정을 통해 프로그램의 안정성과 신뢰성을 크게 향상시킬 수 있습니다.