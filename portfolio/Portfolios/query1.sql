-- mysql db 사용
use mysql;
-- 계정 생성
create user 'bms'@'localhost' identified by '1234';
create user 'bms'@'%' identified by '1234';
-- 계정 생성 확인
select * from user where User = 'bms';
-- 처리 등록
flush privileges;

-- db 확인
show databases;

create database bms;

-- db에 사용자 권한부여
grant all privileges on bms.* to bms@localhost identified by '1234';
grant all privileges on bms.* to bms@'%'identified by '1234';

flush privileges;