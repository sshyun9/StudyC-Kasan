-- SQL (Structured Query Language)

-- 1. SELECT 쿼리 (조회)
-- 가장 기본쿼리
SELECT *  -- * = All
From contact;

-- 기본 쿼리(위와 같음)
SELECT Id, name, phonenum, email, addr
from contact;

-- 데이터 몇개있는지 조회 쿼리
-- FROM contact *
-- Where Id = 2;

-- 데이터를 원하는 컬럼만 조회
SELECT name, phonenum, email
from contact;

-- 이름으로 조회하는 쿼리
SELECT *
From contact
WHERE name = '홍길동'; --  DB에서 같은지 비교 =

-- 2. INSERT 쿼리
insert into contact
(name, phonenum, addr) 
VALUES
('홍길순', '0101111-8888', 'hds@daum.net', '횡성');

-- NULL값 제외
INSERT INTO contact
(name) VALUES 손흥민;  -- 데이터 입력불가
-- 컬럼값이  NOT NULL 인 것은 모두 입력되어야..
INSERT INTO contact
(name, phonenum) VALUES ('손흥민', '010-7878-9090');

-- 컬럼이 4개인데 4개 다 데이터를 넣겠다고 하면
INSERT INTO contact
(name, phonenum, email, addr)
VALUES
('이동욱', '010-6868-5656', 'ldw@gmail.com', '서울')

-- UPDATE 쿼리(데이터 수정)
-- 홍길동 id = 1, phoneneumger = 010-0000-9999 --> 010-7777-6648
UPDATE contact SET
		phonenum = '010-7777-6648'
	where id = 1;  -- where 절 필수
    
-- z컬럼이 1개 이상 변경
UPDATE contact  SET
		phonenum = '010-2222-3333',  -- 쉼표 필수!
        email = 'gdhong@yahoo.com'
where id = 1;
    
-- 4. /DELETE 삭제쿼리
DELETE FROM contact
WHERE id = 4;  -- where 절 없으면 안됨
