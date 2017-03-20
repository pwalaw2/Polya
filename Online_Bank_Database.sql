drop database `online_bank`;

CREATE DATABASE `online_bank`;

use `online_bank`;


CREATE TABLE  `users` (
  `USER_ID` varchar(10) NOT NULL,
  `PASSWD` varchar(100) NOT NULL,
  `STATUS` varchar(11) DEFAULT 'ACTIVE',
  `COUNT` int(10) unsigned NOT NULL DEFAULT '0',
  `TYPE` varchar(45) DEFAULT 'USER',
  PRIMARY KEY (`USER_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

insert into users (user_id,passwd,type) values('Admin','l8PIWjZHnbdqmwQJ1qip8g==','ADMIN');
/*   Admin username: Admin password: Admin@123    */

CREATE TABLE  `newaccount` (
  `ACC_NO` int(10) NOT NULL AUTO_INCREMENT,
  `FIRST_NAME` varchar(20) NOT NULL,
  `LAST_NAME` varchar(20) NOT NULL,
  `GENDER` varchar(2) NOT NULL,
  `ADDRESS1` varchar(100) NOT NULL,
  `ADDRESS2` varchar(100) DEFAULT NULL,
  `DATE_OF_BIRTH` date NOT NULL,
  `LAND_PHONE_NO` varchar(12) DEFAULT NULL,
  `MOBILE_NO` varchar(15) NOT NULL,
  `EMAIL` varchar(50) NOT NULL,
  `AMOUNT` float NOT NULL DEFAULT '0',
  `USER_ID` varchar(10) NOT NULL,
  PRIMARY KEY (`ACC_NO`) USING BTREE,
  KEY `account_ibfk_1` (`USER_ID`),
  CONSTRAINT `fk_ibfk_1` FOREIGN KEY (`USER_ID`) REFERENCES `users` (`USER_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=latin1;


CREATE TABLE  `transaction` (
  `TRANSACTION_ID` bigint(10) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `ACCOUNT_NO` int(10) NOT NULL,
  `DATE` date NOT NULL,
  `TIME` time NOT NULL,
  `NARRATION` varchar(50) DEFAULT NULL,
  `DEPOSIT` float DEFAULT NULL,
  `WITHDRAWAL` float DEFAULT NULL,
  `CLOSING_BALANCE` float NOT NULL,
  PRIMARY KEY (`TRANSACTION_ID`),
  KEY `transaction_ibfk_1` (`ACCOUNT_NO`),
  CONSTRAINT `transaction_ibfk_1` FOREIGN KEY (`ACCOUNT_NO`) REFERENCES `newaccount` (`ACC_NO`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=145 DEFAULT CHARSET=latin1;