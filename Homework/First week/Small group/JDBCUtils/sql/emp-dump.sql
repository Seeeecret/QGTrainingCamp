-- MySQL dump 10.13  Distrib 8.0.32, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: test02
-- ------------------------------------------------------
-- Server version	8.0.32

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `emp`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `emp` (
  `id` int NOT NULL AUTO_INCREMENT,
  `workNo` varchar(10) DEFAULT NULL,
  `name` varchar(10) DEFAULT NULL,
  `gender` char(1) DEFAULT NULL,
  `age` tinyint unsigned DEFAULT NULL,
  `idcard` char(18) DEFAULT NULL,
  `workaddress` varchar(50) DEFAULT NULL,
  `entrydate` date DEFAULT NULL,
  `dept_id` int DEFAULT NULL COMMENT '部门ID',
  `salary` double DEFAULT NULL COMMENT '薪水',
  PRIMARY KEY (`id`),
  KEY `emp_fk` (`dept_id`),
  CONSTRAINT `emp_fk` FOREIGN KEY (`dept_id`) REFERENCES `dept` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='员工表';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `emp`
--

INSERT INTO `emp` (`id`, `workNo`, `name`, `gender`, `age`, `idcard`, `workaddress`, `entrydate`, `dept_id`, `salary`) VALUES (1,'00001','柳岩','女',28,'123456789012345678','北京','2000-01-01',3,6000),(2,'00002','张无忌','男',18,'123456789012345670','中山','2005-09-01',4,7000),(3,'00003','韦一笑','男',16,'123456789012345600',' 广州','2004-02-28',2,8000),(4,'00004','吴卓颖','女',26,'123456789012345000',' 广州','2004-02-28',1,9000),(5,'00005','吴卓颖','男',30,'123456789012345000','珠海','2003-02-28',1,60000),(6,'00006','袁文韬','女',25,'123456789012345000','成都','2003-07-18',4,13000),(7,'00007','罗政','男',45,'123456789012345000','成都','2006-07-20',4,17000),(8,'00008','刘毅杰','男',34,'123456789012345000','成都','2002-07-12',3,21000);
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-03-23 17:41:19
