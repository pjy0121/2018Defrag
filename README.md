# 2018Defrag
동국대학교 컴퓨터공학과 종합설계 조각모음 팀

## Leap motion을 이용한 3D 그림 그리기 프로그램

Leap motion을 활용한 모션인식 => OpenGL을 활용한 3D Object Rendering

필요 라이브러리 : OpenGL(+ glew, glm), Leap SDK V2

### 키 동작
- ENTER : 그리기 시작
- TAB : 그리기 멈춤
- Q : 프로그램 종료
- B : 화면 지우기
- F/L : 그림 파일 저장/불러오기
- K/L : 점의 크기(전체 그림의 두께) 작게/크게
- G/H : 물체 크기 확대/축소
- D/A : X축 기준 회전시키기 빠르게/느리게
- W/S : Y축 기준 회전시키기 빠르게/느리게
- 숫자 : 펜 색 바꾸기(1 : 빨강, 2 : 초록, 3 : 파랑)